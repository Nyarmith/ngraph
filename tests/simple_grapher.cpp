#include "../include/cursapp.hpp"
#include "../include/gui.hpp"


//like nplot but with multiple functions and with colors
class ngplot : public gui_entity{
  public:
    typedef std::function<double(double)> graph_t;

    ngplot(int y, int x, int h, int w,
        double range[] = [-10,10],
        double domain[] = [-10,10]){
    }

    std::string add_function(graph_t f){
      //add function and return string of its id
    }

    void add_function(graph_t f, std::string id){
      //pls
    }

    bool rm_function(std::string in){
      //pls
    }

    void set_range(double in[]){
      range_[0] =  in[0];
      range_[1] =  in[1];
    }

    void set_domain(double in[]){
      domain_[0] =  in[0];
      domain_[1] =  in[1];
    }

    void normal_draw(canvas &c) {
      for (int i=0; i<=h_; ++i)
        for (int j=0; j<=w_; ++j)
          c.add_char(i, j, '.');


      for (auto i : graph_)
        c.add_char(i.first, i.second, 'x');
    };

  private:
    int t_x(double x){
      x -= domain_[0];
      x /= (domain_[1] - domain_[0]);
      x *= (double)w_;
      return x + .5;
    }

    int t_y(double y){
      y -= domain_[0];
      y /= (range_[1] - range_[0]);
      y *= (double)h_;
      return h_ - y + .5;
    }

    void compute_coords(){
      double x_step =  (domain_[1] - domain_[0]) / w_;

      double x_cur = domain_[0];
      float y,x;
      for (int i=0; i<=w_; ++i){
        y = f_(x_cur);
        y = t_y(y);
        x = t_x(x_cur);
        graph_.push_back( std::make_pair(y,x));
        x_cur += x_step;
      }
    }

    int entry_;
    double domain_[2];
    double range_[2];
    std::map<std::string,graph_t> fs_;
    const graph_t dflt_=[](double){return 1.0;};
    std::map<std::string, std::vector< std::pair<int,int> > > graph_;
};

//have form for inputting function entry
//make parser for fn entry
//

int main(){
  ngl::cursapp &m = ngl::cursapp::instance();
  auto wins = m.partition(2);

  //left window
  ngplot my_plot();

  //right window
  fninput input;
  plotlister lister;

  wins[0].add_entity(&my_plot);
  wins[1].add_entity(input);
  wins[1].add_entity(lister);

  m.run();
}

