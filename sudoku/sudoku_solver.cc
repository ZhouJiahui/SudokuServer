#include "sudoku_solver.h"

#include <set>

namespace sudoku {

SudokuSolver::SudokuSolver(std::vector<std::vector<char>>& board)
  : board_(board) {
}

bool SudokuSolver::Solve() {
  return Dfs(0, 0);
}

bool SudokuSolver::CheckValid(size_t x, size_t y) {
  std::set<char> s;
  for (size_t i = 0; i < board_[x].size(); ++i) {
    if (s.count(board_[x][i])) {
      return false;
    }
    if (board_[x][i] != '.') {
      s.insert(board_[x][i]);
    }
  }
  s.clear();
  for (size_t i = 0; i < board_.size(); ++i) {
    if (s.count(board_[i][y])) {
      return false;
    }
    if (board_[i][y] != '.') {
      s.insert(board_[i][y]);
    }
  }
  s.clear();
  auto a = x - x % 3;
  auto b = y - y % 3;
  for (size_t i = a; i < a + 3; ++i) {
    for (size_t j = b; j < b + 3; ++j) {
      if (s.count(board_[i][j])) {
        return false;
      }
      if (board_[i][j] != '.') {
        s.insert(board_[i][j]);
      }
    }
  }
  return true;
}

bool SudokuSolver::Dfs(size_t x, size_t y) {
  if (x == board_.size()) {
    return true;
  }
  if (board_[x][y] == '.') {
    for (size_t i = 1; i <= 9; ++i) {
      board_[x][y] = '0' + i;
      if (CheckValid(x, y)) {
        auto nx = x;
        auto ny = y + 1;
        if (ny == board_[x].size()) {
          ++nx;
          ny = 0;
        }
        if (Dfs(nx, ny)) {
          return true;
        }
      }
    }
    board_[x][y] = '.';
    return false;
  }
  auto nx = x;
  auto ny = y + 1;
  if (ny == board_[x].size()) {
    ++nx;
    ny = 0;
  }
  return Dfs(nx, ny);
}

}
