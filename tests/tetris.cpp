#include "tetris.hpp"


const int b_hgt=22;
const int b_wdt=10;
int points=0;

block* preview_block = NULL;
block* cur_block = NULL;

//top 2 rows should be hidden, int for each color_pair, colors:
int board[b_hgt][b_wdt] = {{0}};

void draw_board(ngl::canvas &c){
  const int offset = 3;
  for (int col=0; col<8; ++col){
    for (int x=0; x<b_wdt; ++x){
      for (int y=0; y<b_hgt; ++y){
        if (col == 0){
          c.add_char(offset + y,offset + x,'.' | COLOR_PAIR(col));
        }
        else if (board[y][x] == col){
          c.add_char(offset + y,offset + x,'#' | COLOR_PAIR(col));
        }
      }
    }
  }
}

//right-window
void piece_preview(ngl::canvas &c){
  const int offset=4;
  c.box(offset,offset,6,6);
  for (unsigned i=0; i<preview_block->block_.size(); ++i){
    for (unsigned j=0; j<preview_block->block_[i].size(); ++j){
      if (preview_block->block_[i][j] != ' ')
        c.add_char(offset+i+2, offset+j+1, preview_block->block_[i][j] |
          COLOR_PAIR(preview_block->color_));
    }
  }
}

//left-window
void point_score(ngl::canvas &c){
  const int offset=4;
  c.box (offset,offset, 3, 8);
  c.set_color(2);
  c.text(offset+1, offset+1,std::to_string(points));
  c.set_color(2,false);
}

void tetris_check(){
  int clears=0;
  bool clear;
  //check each row for bottom-up
  for (int r=b_hgt-1; r>-0; --r){
    clear=true;
    for (int w=0; w < b_wdt; ++w){
      //check each row, shift the tetorisu blocks down
      clear = clear && (board[r][w] != 0);
    }
    if (clear){
      clears++;
      //move everything down
      for (int rw = r; rw > 0; --rw){
        for (int bw = 0; bw < b_wdt; ++bw){
            board[rw][bw] = board[rw-1][bw];
        }
      }
      for (int bw = 0; bw < b_wdt; ++bw){
        board[0][bw] = 0;
      }
    }
  }

  switch(clears){
    case 0:
      points += 2;
      break;
    case 1:
      points += 40;
      break;
    case 2:
      points += 100;
      break;
    case 3:
      points += 300;
      break;
    case 4:
      points += 1200;
      break;
  }
}

bool collide(block* m){
  //x and y are top left
  for (unsigned int i=0; i<m->block_.size(); ++i)
    for (unsigned int j=0; j< m->block_[i].size(); ++j)
      if (m->block_[i][j] == '#' &&
          (m->x+(int)i < 0 ||
           m->x+i >= b_wdt ||
           m->y+j >= b_hgt ||
           board[m->y+j][m->x+i] != 0) )
        return true;

  return false;
}

//modify canvas settings before drawing
void undraw_block(block* m){
  if (m == NULL){
    return;
  }
  for (unsigned int i=0; i<m->block_.size(); ++i)
    for (unsigned int j=0; j< m->block_[i].size(); ++j)
      if (m->block_[i][j] == '#')
        board[m->y+j][m->x+i] = 0;
}

void draw_block(block* m){
  if (m == NULL){
    return;
  }
  for (unsigned int i=0; i<m->block_.size(); ++i)
    for (unsigned int j=0; j< m->block_[i].size(); ++j)
      if (m->block_[i][j] == '#')
        board[m->y+j][m->x+i] = m->color_;
}

void spawn(){
  cur_block = preview_block;
  preview_block = generate_teromino();
  const int y=0, x=3;
  cur_block->y = y;
  cur_block->x = x;

  draw_block(cur_block);
}

void move_down(block* m){
  if (m == NULL){
    return;
  }
  undraw_block(m);
  m->y++;
  if (collide(m)){
    m->y--;
    draw_block(m);
    delete cur_block;
    cur_block = NULL;
    tetris_check();
  }
  else{
    draw_block(m);
  }
}

void move_left(block* m){
  if (m == NULL){
    return;
  }
  undraw_block(m);
  m->x--;
  if (collide(m))
    m->x++;

  draw_block(m);
}

void move_right(block* m){
  if (m == NULL){
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
  undraw_block(m);
  m->left_rotate();
  draw_block(m);
}

//main game behavior
void update_game(const ngl::event& s){
  static int turn_timer=0; //do global move-down every 20 frames
  //global_update
  if (cur_block == NULL){
    spawn();
  }
  if (s.type == ngl::KEYBD){
    switch(s.x){
      case KEY_UP: //move to "up" if keys work
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
    move_down(cur_block);
    turn_timer = 15;
  }
  else{
    --turn_timer;
  }
}

int main(){
  ngl::cursapp &m = ngl::cursapp::instance();
  custom_colors();
  preview_block = generate_teromino();
  auto wins = m.partition(3);
  wins[0].add_entity(point_score);
  wins[1].add_entity(draw_board, update_game);
  wins[2].add_entity(piece_preview);
  m.run();
}
