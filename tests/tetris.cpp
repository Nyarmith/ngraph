#include "../include/gui.hpp"

//random generator based on: http://tetris.wikia.com/wiki/Random_Generator

//rotation: https://gamedev.stackexchange.com/questions/17974/how-to-rotate-blocks-in-tetris
struct block{
  std::vector<std::vector<char>> block_;
  void left_rotate(){
    //precondition: rows and columns must be the same size
    //1 - am I even or odd?
    int radius = 1;
    int c = block_.size() / 2;
    int temp; //O(1) extra space!
    if (block_.size() % 2 == 0){
      for (int r=0; r<c-1; ++r){
        //for every rotatable block along that radius
        for (int b=-r; b <= r; ++b){
          //swap
          temp = block_[c+b][ c+r];
          block_[c+b][c+r] = block_[c+r][c-b-1];
          block_[c+r][c-b-1] = block_[c-b-1][c-r-1];
          block_[c-b-1][c-r-1] = block_[c-r-1][c+b];
          block_[c-r-1][c+b] = temp; //wow I hope this works
        }
        ++radius ;
      }
    } else {
      for (int r=1; r+c<(int)block_.size(); ++r){
        //for every rotatable block along that radius
        for (int b=(-r + 1); b <= r; ++b){
          //swap
          temp = block_[c+b][ c+r];
          block_[c+b][c+r] = block_[c + r][c - b];
          block_[c+r][c-b] = block_[c-b][c-r];
          block_[c-b][c-r] = block_[c-r][c+b];
          block_[c-r][c+b] = temp;    //TODO: Verify this works
        }
        ++radius ;
      }
    }
  }
  void right_rotate();
};


//the list of tetris blocks: i, j, l, o, s, t, z
struct l_block : block {
  l_block(){
    block_ = {
      {' ',' ',' ',' '},
      {'#','#','#','#'},
      {' ',' ',' ',' '},
      {' ',' ',' ',' '}
    };
  }
};

struct j_block : block {
  j_block(){
    block_ = {
      {'#',' ',' '},
      {'#','#','#'},
      {' ',' ',' '}
    };
  }
};

struct t_block : block {
  t_block(){
    block_ = {
      {' ','#',' '},
      {'#','#','#'},
      {' ',' ',' '}
    };
  }
};

struct s_block : block {
  s_block(){
    block_ = {
      {' ','#','#'},
      {'#','#',' '},
      {' ',' ',' '}
    };
  }
};

struct z_block : block {
  z_block(){
    block_ = {
      {'#','#',' '},
      {' ','#','#'},
      {' ',' ',' '}
    };
  }
};


struct o_block : block {
  o_block(){
    block_ = {
      {'#','#'},
      {'#','#'}
    };
  }
  void left_rotate()  { /* do nothing */ }
  void right_rotate() { /* do nothing */ }
};
