#ifndef SUDOKU_SUDOKU_SOLVER_H_
#define SUDOKU_SUDOKU_SOLVER_H_

#include <stddef.h>
#include <string>

namespace sudoku {

class SudokuSolver {
public:
  bool Solve(std::string& board);

private:
  bool CheckValid(size_t cur, std::string& board);

  bool Dfs(size_t cur, std::string& board);

};

}

#endif // SUDOKU_SUDOKU_SOLVER_H_
