#ifndef SUDOKU_SUDOKU_SOLVER_H_
#define SUDOKU_SUDOKU_SOLVER_H_

#include <stddef.h>
#include <vector>

namespace sudoku {

class SudokuSolver {
public:
  SudokuSolver(std::vector<std::vector<char>>& board);

  bool Solve();

private:
  bool CheckValid(size_t x, size_t y);

  bool Dfs(size_t x, size_t y);

private:
  std::vector<std::vector<char>>& board_;
};

}

#endif // SUDOKU_SUDOKU_SOLVER_H_
