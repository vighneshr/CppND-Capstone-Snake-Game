#ifndef LAYOUT_H
#define LAYOUT_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "pregame.h"
#include "SDL.h"
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

class Layout : public PreGame {
public:
  Layout(){};
  ~Layout(){};
  bool Construct(vector<SDL_Point> &gamelayout);
  bool setup();
private:
  string filename;
  void PopulatePoints(const vector<vector<int>> board, vector<SDL_Point> &gamelayout);
  vector<vector<int>> ReadBoardFile(string path);
  vector<int> ParseLine(string line);
  std::vector<SDL_Point> layout;
};
#endif