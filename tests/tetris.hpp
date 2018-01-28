#include "../include/gui.hpp"


//rotation: https://gamedev.stackexchange.com/questions/17974/how-to-rotate-blocks-in-tetris
struct block{
  int y, x;
  std::vector<std::vector<char>> block_;
  int color_;
  void left_rotate(){
    //precondition: rows and columns must be the same size
    //1 - am I even or odd?
    int radius = 1;
    int c = block_.size() / 2;
    int temp; //O(1) extra space!
    if (block_.size() % 2 == 0){
      for (int r=0; r<=c-1; ++r){
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
  void right_rotate(){
    //precondition: rows and columns must be the same size
    //1 - am I even or odd?
    int radius = 1;
    int c = block_.size() / 2;
    int temp; //O(1) extra space!
    if (block_.size() % 2 == 0){
      for (int r=0; r<=c-1; ++r){
        //for every rotatable block along that radius
        for (int b=-r; b <= r; ++b){
          //swap
          temp = block_[c-r-1][c+b];
          block_[c-r-1][c+b]   = block_[c-b-1][c-r-1];
          block_[c-b-1][c-r-1] = block_[c+r][c-b-1];  
          block_[c+r][c-b-1]   = block_[c+b][c+r];
          block_[c+b][c+r]     = temp; //wow I hope this works
        }
        ++radius ;
      }
    } else {
      for (int r=1; r+c<(int)block_.size(); ++r){
        //for every rotatable block along that radius
        for (int b=(-r + 1); b <= r; ++b){
          //swap
          temp = block_[c-r][c+b]; 
          block_[c-r][c+b] = block_[c-b][c-r]; 
          block_[c-b][c-r] = block_[c+r][c-b];
          block_[c + r][c - b] = block_[c+b][c+r];
          block_[c+b][ c+r] = temp;    //TODO: Verify this works
        }
        ++radius ;
      }
    }
  }

};

//colors
//Cyan I
//Yellow O
//Purple T
//Green S
//Red Z
//Blue J
//Orange L 
enum {CYAN=1, YELLOW, PURPLE, GREEN, RED, BLUE};
const int COLOR_ORANGE=8;
void custom_colors(){
  init_color(COLOR_ORANGE, 1000, 840, 0);
  init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(PURPLE, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(RED, COLOR_RED, COLOR_BLACK);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(YELLOW, COLOR_ORANGE, COLOR_BLACK);
}

//the list of tetris blocks: i, j, l, o, s, t, z
struct i_block : block {
  i_block(){
    color_ = CYAN;
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
    color_ = BLUE;
    block_ = {
      {'#',' ',' '},
      {'#','#','#'},
      {' ',' ',' '}
    };
  }
};

struct l_block : block {
  l_block(){
    color_ = YELLOW;
    block_ = {
      {' ',' ','#'},
      {'#','#','#'},
      {' ',' ',' '}
    };
  }
};

struct t_block : block {
  t_block(){
    color_ = PURPLE;
    block_ = {
      {' ','#',' '},
      {'#','#','#'},
      {' ',' ',' '}
    };
  }
};

struct s_block : block {
  s_block(){
    color_ = GREEN;
    block_ = {
      {' ','#','#'},
      {'#','#',' '},
      {' ',' ',' '}
    };
  }
};

struct z_block : block {
  z_block(){
    color_ = RED;
    block_ = {
      {'#','#',' '},
      {' ','#','#'},
      {' ',' ',' '}
    };
  }
};


struct o_block : block {
  o_block(){
    color_ = YELLOW;
    block_ = {
      {'#','#'},
      {'#','#'}
    };
  }
  void left_rotate()  { /* do nothing */ }
  void right_rotate() { /* do nothing */ }
};


//random generator based on: http://tetris.wikia.com/wiki/Random_Generator


void permute(std::vector<block*> &blocks, std::vector<block*> &ret){
  if (blocks.size() == 0)
    return ;
  int e = rand() % blocks.size();
  ret.push_back(blocks[e]);
  blocks.erase(blocks.begin() + e);
  permute(blocks, ret);
}

void fill_bag(std::vector<block*> &bag){
  std::vector<block*> unpermuted = {new i_block(), new l_block, new j_block(),
      new t_block, new s_block, new z_block(), new o_block()};

  permute(unpermuted, bag);
}

block* generate_teromino(){
  static std::vector<block*> blockpool;

  if (blockpool.size() == 0)
    fill_bag(blockpool);

  block *ret = blockpool.back();
  blockpool.pop_back();
  return ret;
}
