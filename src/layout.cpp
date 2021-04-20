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
        cout << line << std::endl;
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
          cout << "i : " << i << "j : " << j << " ...\n";
          SDL_Point temp{i, j};
          gamelayout.emplace_back(temp);
      }
    }
  }
}

bool Layout::Construct(int level, vector<SDL_Point> &gamelayout) {
  vector<vector<int>> board;
  if (level == 0) {
    board = ReadBoardFile("../board/board_level0.txt");
  } else if (level == 1) {
    board = ReadBoardFile("../board/board_level1.txt");
  }
  PopulatePoints(board, gamelayout);
  return true;
}