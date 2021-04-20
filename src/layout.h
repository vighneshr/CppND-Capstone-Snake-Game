#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "SDL.h"
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

class Layout {
public:
  Layout(){};
  ~Layout(){};
  bool Construct(int level, vector<SDL_Point> &gamelayout);
private:
  void PopulatePoints(const vector<vector<int>> board, vector<SDL_Point> &gamelayout);
  vector<vector<int>> ReadBoardFile(string path);
  vector<int> ParseLine(string line);
  std::vector<SDL_Point> layout;
};