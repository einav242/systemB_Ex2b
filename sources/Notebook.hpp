#include <string>
#include "Direction.hpp"
#include<vector>
#include<unordered_map>
#include<stdexcept>
#include<map>
using  namespace std;
using  ariel::Direction;

namespace ariel{
    class Notebook { 
        private:
            unordered_map<unsigned int,unordered_map<unsigned int,vector<char>>> notebook;
        public:
            Notebook(); 
            ~Notebook(); 
            void write(int page,int row,int colum,Direction d, const string & data);
            string read(int page,int row,int colum,Direction d,int data);
            void erase(int page,int row,int colum,Direction d,int data); 
            void show(int page);     
    };
}