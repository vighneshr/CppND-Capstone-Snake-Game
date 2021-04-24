#include "layout.h"

vector<int> Layout::ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<int> row;
    while (sline >> n >> c && c == ',') {
      row.push_back(n);
    }
    return row;
}

vector<vector<int>> Layout::ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<int>> board;
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      board.push_back(ParseLine(line));
    }
  }
  return board;
}

void Layout::PopulatePoints(
    const vector<vector<int>> board,
    vector<SDL_Point> &gamelayout)
{
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      if (board[j][i] == 1) {
          SDL_Point temp{i, j};
          gamelayout.emplace_back(std::move(temp));
      }
    }
  }
}

bool Layout::setup() {
  //precheck and get filename
  if (getLevel() > getAvailableLevels()) {
    return false;
  }
  filename = "../board/board_level" + std::to_string(getLevel()) + ".txt";

  return true;
}

bool Layout::Construct(vector<SDL_Point> &gamelayout) {
  vector<vector<int>> board;
  board = ReadBoardFile(filename);
  PopulatePoints(board, gamelayout);
  return true;
}