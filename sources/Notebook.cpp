#include <string>
#include "Direction.hpp"
#include "Notebook.hpp"
#include <iostream>
#include <stdexcept>
#include<iterator>
using namespace std;
// using ariel::Direction;

namespace ariel
{
    Notebook::Notebook()
    {
    }
    Notebook::~Notebook()
    {
    }
    void Notebook::write(int p, int r, int c, Direction d, const string &data)
    {
        const unsigned int maxcol = 100;
         const unsigned int maxc = 126;
          const unsigned int minc = 32;
        if ((c + int(data.length()) > maxcol && d == Direction::Horizontal) || r < 0 || c < 0 || p < 0 || data == "~"||c>=maxcol||data=="\n")
        {
            throw std::invalid_argument("error try another argument");
            return;
        }
        for(unsigned int i=0;i<data.length();i++)
        {
            if(data[i]=='~'|| data[i]=='\n' || data[i]<minc || data[i]>maxc)
            {
                throw std::invalid_argument("error try another argument");
                return;
            }
        }
        unsigned row = (unsigned int)(r);
        unsigned page = (unsigned int)(p);
        unsigned colum = (unsigned int)(c);
        if (d == Direction::Horizontal)
        {
            if (notebook.find(page) == notebook.end() || notebook[page].find(row) == notebook[page].end())
            {
                vector<char> line(maxcol, '_');
                notebook[page][row] = line;
                unsigned int k = 0;
                for (unsigned int j = colum; j < data.length() + colum; j++)
                {
                    notebook[page][row][j] = data[k];
                    k++;
                }
            }
            else
            {
                for (unsigned int j = colum; j < data.length() + colum; j++)
                {
                    if (notebook[page][row][j] != '_')
                    {
                        throw std::invalid_argument("error already written here");
                        return;
                    }
                }
                unsigned int k = 0;
                for (unsigned int j = colum; j < data.length() + colum; j++)
                {
                    notebook[page][row][j] = data[k++];
                }
            }
            // for (unsigned int j = colum; j < data.length() + colum; j++)
            // {
            //     cout << notebook[page][row][j];
            // }
        }
        else
        {
            vector<char> line(maxcol, '_');
            for (unsigned int i = row; i < row + data.length(); i++)
            {
                if (notebook.find(page) == notebook.end() || notebook[page].find(i) == notebook[page].end())
                {
                    notebook[page][i] = line;
                }
            }
            for (unsigned int j = row; j < data.length() + row; j++)
            {
                if (notebook[page][j][colum] != '_')
                {
                    throw std::invalid_argument("error already written here");
                    return;
                }
            }
            unsigned int k = 0;
            for (unsigned int j = row; j < data.length() + row; j++)
            {
                notebook[page][j][colum] = data[k];
                k++;
            }
            // for (unsigned int j = row; j < data.length() + row; j++)
            // {
            //     cout << notebook[page][j][colum];
            // }
        }
    }

    string Notebook::read(int p, int r, int c, Direction d, int data)
    {
        const unsigned int maxcol = 100;
        if ((data + c > maxcol && d == Direction::Horizontal) || c > maxcol || r < 0 || c < 0 || p < 0 || data < 0||c>=maxcol)
        {
            throw std::invalid_argument("error try another argument");
        }
        string ans;
        unsigned row = (unsigned int)(r);
        unsigned page = (unsigned int)(p);
        unsigned colum = (unsigned int)(c);
        vector<char> line(maxcol, '_');
        if (d == Direction::Horizontal)
        {
            if (notebook.find(page) == notebook.end() || notebook[page].find(row) == notebook[page].end())
            {
                vector<char> line(maxcol, '_');
                notebook[page][row] = line;
            }

            for (unsigned int i = colum; i < (unsigned int)data + colum; i++)
            {
                ans += notebook[page][row][i];
            }
        }
        else
        {
            for (unsigned int i = row; i < row + (unsigned int)data; i++)
            {
                if (notebook.find(page) == notebook.end() || notebook[page].find(i) == notebook[page].end())
                {
                    notebook[page][i] = line;
                }
            }

            for (unsigned int i = row; i < (unsigned int)data + row; i++)
            {
                ans += notebook[page][i][colum];
                // cout<< i;
                // cout<<notebook[page][i][colum];
            }
        }

        return ans;
    }
    void Notebook::erase(int p, int r, int c, Direction d, int data)
    {
        const unsigned int maxcol = 100;
        if ((data + c > maxcol && d == Direction::Horizontal) || c > maxcol || r < 0 || c < 0 || p < 0 || data < 0 ||c>=maxcol)
        {
            throw std::invalid_argument("error try another argument");
        }
        unsigned row = (unsigned int)(r);
        unsigned page = (unsigned int)(p);
        unsigned colum = (unsigned int)(c);
        vector<char> line(maxcol, '_');
        if (d == Direction::Horizontal)
        {
            if (notebook.find(page) == notebook.end() || notebook[page].find(row) == notebook[page].end())
            {
                notebook[page][row] = line;
            }
            for (unsigned int i = colum; i < (unsigned int)data + colum; i++)
            {
                notebook[page][row][i] = '~';
            }
        }
        else
        {
            for (unsigned int i = row; i < row + (unsigned int)data; i++)
            {
                if (notebook.find(page) == notebook.end() || notebook[page].find(i) == notebook[page].end())
                {
                    notebook[page][i] = line;
                }
            }

            for (unsigned int i = row; i < (unsigned int)data + row; i++)
            {
                notebook[page][i][colum] = '~';
                // cout<< i;
                // cout<<notebook[page][i][colum];
            }
        }
    }
    void Notebook::show(int p)
    {
        if(p<0)
        {
            throw std::invalid_argument("error try another argument");
        }
        const unsigned int temp=50;
        unsigned int page = (unsigned int)p;
        unsigned int i = 0;
        unsigned int k = 0;
        const unsigned int maxcol = 100;
        const unsigned int maxrow = 100;
        vector<char> line(maxcol, '_');
            for (; i <= maxrow; i++)
            {
                if (notebook.find(page) == notebook.end() || notebook[page].find(i) == notebook[page].end())
                {
                    notebook[page][i] = line;
                }
                cout << i << ":";
                for (unsigned int j = 0; j < maxcol; j++)
                {
                    cout << notebook[page][i][j];
                }
                cout << endl;
            }
    }
};
