#include "entity.hpp"

namespace ngl {
  class context_menu : public entity {
    typedef std::vector<std::string> wordlist;
    public:
      void draw(canvas &g){
        for (wordlist::iterator p = entries_.begin(); p != entries_.end(); ++p){
          g.text(*p); //TODO, add highlighting and string justification/padding
        }
      }
      void add(std::string s){ entries_.push_back(s); }
      bool rm(std::string s){ 
        wordlist::iterator p = std::find(entries_.begin(), entries_.end(), s);
        if (p == entries_.end())
          return false;
        else
          entries_.erase(p);
        return true;
      }
      void select(wordlist::size_type i){
        selected = i;
      }
      void unselect(){
        selected = -1;
      }
    private:
      void maxlength(){
        maxw = 0;
        for (wordlist::size_type i=0; i<entries_.size(); ++i){
          if (entries_[i].length() > maxw)
            maxw = entries_[i].length();
        }
      }
      wordlist entries_;
      wordlist::size_type selected;
      wordlist::size_type maxw;
  };
}
