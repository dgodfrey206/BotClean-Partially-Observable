#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>
using namespace std;

struct node {
  int x, y;
  node(int x,int y):x(x),y(y){}
  int distTo(node n) const {
    return abs(x - n.x) + abs(y - n.y);
  }
};

node null = {-1,-1};

bool operator==(node lhs,node rhs){return (lhs.x==rhs.x)&&(lhs.y==rhs.y);}
bool operator!=(node lhs,node rhs){return!(lhs==rhs);}

string print_move(int x, int y) {
  if (x < 0)
    return "DOWN";
  else if (x > 0)
    return "UP";
  else if (y < 0)
    return "RIGHT";
  else if (y > 0)
    return "LEFT";
  return "CLEAN";
}

void next_move(int posr, int posc, vector<string> board) {
  node bot = node{posr, posc};
  vector<node> dirty_cells;
  int i, j, n = 5, m = 5;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j) {
      if (board[i][j] == 'd')
        dirty_cells.push_back(node{i, j});
    }
  }
  
  node nearestCell = null;
  for (i = 0; i < dirty_cells.size(); ++i) {
    node n = dirty_cells[i];
    if (nearestCell == null || bot.distTo(n) < bot.distTo(nearestCell))
      nearestCell = n;
  }
  if (nearestCell != null)
    cout << print_move(bot.x - nearestCell.x, bot.y - nearestCell.y) << '\n';
  else {
    // otherwise move in a clockwise motion...
    string leftMove = print_move(0,1), rightMove = print_move(0,-1),
           upMove   = print_move(1,0), downMove = print_move(-1,0);
    node topLeft    = node(bot.x-1,bot.y-1), topRight = node(bot.x-1,bot.y+1),
         bottomLeft = node(bot.x+1,bot.y-1), bottomRight = node(bot.x+1,bot.y+1);
    
    if (topRight.y >= m-1 && bottomRight.x < n-1)
      cout << downMove; // move down if at the right corner
    else if (bottomRight.x >= n-1 && bottomLeft.y > 0)
      cout << leftMove; // move left if at bottom corner
    else if (bottomLeft.y <= 0 && topLeft.x > 0)
      cout << upMove; // move up if at the left corner
    else if (topLeft.x <= 0 && topRight.y < m-1)
      cout << rightMove; // move right if at the top corner
    else // it's somewhere between the corners, just move right
    {
      cout << rightMove;
    }
  }
}

int main() {
    int pos[2];
    vector<string> board;
    cin >> pos[0] >> pos[1];
    for (int i = 0; i < 5; i++) {
        string s; cin >> s;
        board.push_back(s);
    }
    next_move(pos[0], pos[1], board);
}
