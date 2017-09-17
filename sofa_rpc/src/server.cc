#include "sofa/pbrpc/pbrpc.h"
#include "sudoku_service.pb.h"
#include <sudoku_solver.h>
#include <stdio.h>

bool WebServlet(const sofa::pbrpc::HTTPRequest& request, sofa::pbrpc::HTTPResponse& response) {
  return response.content->Append("<h1>Hello from sofa-pbrpc web server</h1>");
}

class SudokuServerImpl : public sofa_sudoku::SudokuServer {
public:
  SudokuServerImpl() = default;
  ~SudokuServerImpl() = default;

private:
  void Solve(google::protobuf::RpcController* controller,
             const sofa_sudoku::SudokuRequest* request,
             sofa_sudoku::SudokuResponse* response,
             google::protobuf::Closure* done) {
    sofa::pbrpc::RpcController* cntl = static_cast<sofa::pbrpc::RpcController*>(controller);
    printf("Solve(): request message from %s:%s\n", cntl->RemoteAddress().c_str(), request->request().c_str());

    std::string board = request->request();
    bool solved = solver_.Solve(board);
    response->set_anwser(solved);
    printf("Solve(): has anwser %s\n", (solved? "true": "false"));
    if (solved) {
      response->set_response(board);
      printf("Solve(): response message: %s\n", response->response().c_str());
    }
    done->Run();
  }

private:
  sudoku::SudokuSolver solver_;
};

int main() {
  sofa::pbrpc::RpcServerOptions options;
  sofa::pbrpc::RpcServer rpc_server(options);

  sofa::pbrpc::Servlet servlet = sofa::pbrpc::NewPermanentExtClosure(&WebServlet);
  rpc_server.RegisterWebServlet("/hello", servlet);

  if (!rpc_server.Start("0.0.0.0:12321")) {
    printf("start server failed\n");
    return 1;
  }
    
  sofa_sudoku::SudokuServer* sudoku_service = new SudokuServerImpl();
  if (!rpc_server.RegisterService(sudoku_service)) {
    printf("export service failed\n");
    return 1;
  }

  rpc_server.Run();

  rpc_server.Stop();

  return 0;
}
