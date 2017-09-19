#include <sofa/pbrpc/pbrpc.h>
#include "sudoku_service.pb.h"
#include <string>
#include <stdio.h>

// Using global RpcClient object can help share resources such as threads and buffers.
sofa::pbrpc::RpcClient g_rpc_client;
std::string msg = ".................................................................................";
int main()
{

  sofa::pbrpc::RpcChannelOptions channel_options;
  sofa::pbrpc::RpcChannel rpc_channel(&g_rpc_client, "127.0.0.1:12321", channel_options);

  sofa::pbrpc::RpcController* cntl = new sofa::pbrpc::RpcController();
  cntl->SetTimeout(3000);
  sofa_sudoku::SudokuRequest* request = new sofa_sudoku::SudokuRequest();
  request->set_request(msg);
  sofa_sudoku::SudokuResponse* response = new sofa_sudoku::SudokuResponse();

  sofa_sudoku::SudokuServer_Stub* stub = new sofa_sudoku::SudokuServer_Stub(&rpc_channel);
  stub->Solve(cntl, request, response, NULL);

  printf("RemoteAddress=%s\n", cntl->RemoteAddress().c_str());
  printf("IsRequestSent=%s\n", (cntl->IsRequestSent() ? "true" : "false"));
  if (cntl->IsRequestSent()) {
    printf("LocalAddress=%s\n", cntl->LocalAddress().c_str());
    printf("SentBytes=%ld\n", cntl->SentBytes());
  }

  if (cntl->Failed()) {
    printf("request failed: %s\n", cntl->ErrorText().c_str());
  } else {
    printf("request succeed: %s\n", response->response().c_str());
  }

  delete cntl;
  delete request;
  delete response;
  delete stub;

  return 0;
}
