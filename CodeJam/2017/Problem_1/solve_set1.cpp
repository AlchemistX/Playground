#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
using namespace std;

using coord = pair<int, int>;
using coords = vector<coord>;

const int MAX = 500;
coord delta[] = {coord(-1, 0), coord(0, -1), coord(1, 0), coord(0, 1)};

coord operator+(const coord a, const coord b)
{
  return coord(a.first + b.first, a.second + b.second);
}

std::ostream& operator<<(std::ostream& os, const coord& c)
{
  os << "(" << c.first << ", " << c.second << ")";
  return os;
}

int advance(coords &co, coords &ad)
{
  for(auto c: ad)
    cout << c << endl;
  return 0;
}

int count_tick(coords &co)
{
  int tick = 0;
  coords ad(co);
  while (advance(co, ad)) tick++;
  return 0;
}

int main (int argc, char ** argv)
{
  if (argc < 2) {
    cout << "Usage : " << argv[0] << " input.in" << endl;
  }

  string name_in(argv[1]);
  string name_out(argv[1]);
  name_out.replace(name_out.find("in"), string("in").length(), "out");

  ifstream in(name_in);
  ofstream out(name_out);

  string line;
  getline(in, line);
  for (int T = stoi(line); T > 0; --T) {
    getline(in, line);
    coords co;
    for (int N = stoi(line); N > 0; --N) {
      getline(in, line);
      istringstream iss(line);
      string r, c;
      iss >> r >> c;
      int R = stoi(r);
      int C = stoi(c);
      co.push_back(coord(R,C));
    }
    out << count_tick(co) << endl;
  }

  return 0;
}
