#include "tetris.hpp"


const int b_hgt=22;
const int b_wdt=10;

block* cur_block;

//top 2 rows should be hidden, int for each color_pair, colors:
int board[b_hgt][b_wdt] = {{0}};

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


void spawn(){
  cur_block = generate_teromino();
  const int y=0, x=3;
  cur_block->y = y;
  cur_block->x = x;
}

bool collide(block* m){
  if (m->x < 0)
    return true;
  //x and y are top left
  for (unsigned int i=0; i<m->block_.size(); ++i)
    for (unsigned int j=0; j< m->block_[i].size(); ++j)
      if (m->block_[i][j] == '#' &&
            (board[m->y+j][m->x+i] != 0 || m->x+i > b_wdt) )
        return true;

  return false;
}

//modify canvas settings before drawing
void undraw_block(block* m){
  if (m != NULL){
    return;
  }
  for (unsigned int i=0; i<m->block_.size(); ++i)
    for (unsigned int j=0; j< m->block_[i].size(); ++j)
      if (m->block_[i][j] == '#')
        board[m->y+j][m->x+i] = 0;
}

void draw_block(block* m){
  if (m != NULL){
    return;
  }
  for (unsigned int i=0; i<m->block_.size(); ++i)
    for (unsigned int j=0; j< m->block_[i].size(); ++j)
      if (m->block_[i][j] == '#')
        board[m->y+j][m->x+i] = m->color_;
}

void move_down(block* m){
  if (m != NULL){
    return;
  }
  undraw_block(m);
  m->y++;
  if (collide(m)){
    m->y--;
    draw_block(m);
    delete cur_block;
    cur_block = NULL;
  }
  else{
    draw_block(m);
  }
}

void move_left(block* m){
  if (m != NULL){
    return;
  }
  undraw_block(m);
  m->x--;
  if (collide(m))
    m->x++;

  draw_block(m);
}

void move_right(block* m){
  if (m != NULL){
    return;
  }
  undraw_block(m);
  m->x++;
  if (collide(m))
    m->x--;

  draw_block(m);
}

void rotate(block* m){
  //if this doesn't work, use hard-coded tetrominoes
  m->left_rotate();
}

void tetris_check(){
  //check starting w/ the bottom rows for a tetris, then move up
}

//main game behavior
void update_game(const ngl::event& s){
  static int turn_timer=2; //do global move-down every 20 frames
  if (s.type == ngl::KEYBD){
    switch(s.x){
      case ' ': //move to "up" if keys work
        rotate(cur_block);
        break;
      case KEY_LEFT:
        move_left(cur_block);
        break;
      case KEY_RIGHT:
        move_right(cur_block);
        break;
      case KEY_DOWN:
        move_down(cur_block);
        break;
    }
  }
  if (turn_timer<1){
    //global_update
    if (cur_block == NULL){
      spawn();
    }
    else{
      move_down(cur_block);
    }
    turn_timer = 20;
  }
  else{
    --turn_timer;
  }
}

int main(){
  ngl::cursapp &m = ngl::cursapp::instance();
  auto wins = m.partition(3);
  wins[1].add_entity(draw_board, update_game);
  m.run();
}
