#include "sudoku_solver.h"

#include <set>

namespace sudoku {

bool SudokuSolver::Solve(std::string& board) {
  return Dfs(0, board);
}

bool SudokuSolver::CheckValid(size_t cur, std::string& board) {
  std::set<char> s;
  size_t beg;
  size_t end;
  beg = cur  - cur % 9;
  end = beg + 9; 
  for (size_t i = beg; i < end; ++i) {
    if (s.count(board[i])) {
      return false;
    }
    if (board[i] != '.') {
      s.insert(board[i]);
    }
  }

  s.clear();
  beg = cur % 9;
  end = 9 * 9 + beg;
  for (size_t i = beg; i < end; i += 9) {
    if (s.count(board[i])) {
      return false;
    }
    if (board[i] != '.') {
      s.insert(board[i]);
    }
  }

  s.clear();
  auto a = cur / 9 - cur / 9 % 3;
  auto b = cur % 9 - cur % 9 % 3;
  for (size_t i = a; i < a + 3; ++i) {
    for (size_t j = b; j < b + 3; ++j) {
      size_t pos = i * 9 + j;
      if (s.count(board[pos])) {
        return false;
      }
      if (board[pos] != '.') {
        s.insert(board[pos]);
      }
    }
  }
  return true;
}

bool SudokuSolver::Dfs(size_t cur, std::string& board) {
  if (cur == board.size()) {
    return true;
  }
  if (board[cur] == '.') {
    for (size_t i = 1; i <= 9; ++i) {
      board[cur] = '0' + i;
      if (CheckValid(cur, board)) {
        if (Dfs(cur + 1, board)) {
          return true;
        }
      }
    }
    board[cur] = '.';
    return false;
  }
  return Dfs(cur + 1, board);
}

}
