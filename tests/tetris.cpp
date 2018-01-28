#include "tetris.hpp"


const int b_hgt=22;
const int b_wdt=10;

//top 2 rows should be hidden, int for each color_pair, colors:
int board[b_hgt][b_wdt];

void draw_board(ngl::canvas &c){
  const int offset = 3;
  for (int col=0; col<7; ++col){
    for (int x=0; x<b_wdt; ++x)
      for (int y=0; y<b_hgt; ++y){
        if (board[y][x] == col)
          c.add_char(offset + y,offset + x,'#' | COLOR_PAIR(col));
        else
          c.add_char(offset + y,offset + x,'.');
      }
  }
}


void move_down(block* m){
}

void move_left(block* m){
}

void move_right(block* m){
}

int main(){
  ngl::cursapp &m = ngl::cursapp::instance();
  auto wins = m.partition(2);
  wins[0].add_entity(draw_board);
}
