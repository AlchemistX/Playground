#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;

using coord = pair<int, int>;
using coords = set<coord>;

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

bool check (coords &co, coord &dc)
{
  int cnt = 0;
  for (auto d: delta) {
    coord ddc = dc + d;
    if (find(begin(co), end(co), ddc) != end(co)) {
      cnt++;
    }
  }

  return cnt > 1;
}

int advance(coords &co, coords &ad)
{
  coords n;
  for (auto c: ad) {
    for (auto d: delta) {
      coord dc = c + d;
      if (dc.first < 1   || dc.second < 1) continue;
      if (dc.first > MAX || dc.second > MAX) continue;
      if ((find(begin(co), end(co), dc) == end(co)) && (check (co, dc))) {
        n.insert(dc);
      }
    }
  }

  co.insert(begin(n), end(n));
  ad.swap(n);
  return ad.size();
}

int count_tick(coords &co)
{
  int tick = 0;
  coords ad(co);
  while (advance(co, ad)) tick++;
  return tick;
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
      co.emplace(stoi(r), stoi(c));
    }
    out << count_tick(co) << endl;
    cout << "." << endl;
  }

  return 0;
}
