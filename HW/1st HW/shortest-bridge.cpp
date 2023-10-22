#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> grid_copy;
    queue<vector<int>> coada;

    void st_land(int &x, int &y)
    {
        for(int i=0;i<grid_copy.size();i++)
            for(int j=0;j<grid_copy[i].size();j++)
                if(grid_copy[i][j]==1)
                {
                    x=i;
                    y=j;
                    return;
                }
    }
    void filling(int x, int y)
    {
        grid_copy[x][y]=2;

        if(0<=x-1 && x-1<grid_copy.size())
        {
            if(grid_copy[x-1][y]==1)
                filling(x-1,y);
        }
        if(0<=x+1 && x+1<grid_copy.size())
        {
            if(grid_copy[x+1][y]==1)
                filling(x+1,y);
        }
        if(0<=y-1 && y-1<grid_copy.size())
        {
            if(grid_copy[x][y-1]==1)
                filling(x,y-1);
        }
        if(0<=y+1 && y+1<grid_copy.size())
        {
            if(grid_copy[x][y+1]==1)
                filling(x,y+1);
        }
    }
    void afisare(vector<vector<int>> grid)
    {
        for(int i=0;i<grid.size();i++)
        {
            for(int j=0;j<grid[i].size();j++)
                cout<<grid[i][j]<<" ";
            cout<<endl;
        }
    }

    int searching()
    {
        while(!coada.empty())
        {
            if(0<=coada.front()[0]-1 && coada.front()[0]-1<grid_copy.size() && grid_copy[coada.front()[0]-1][coada.front()[1]]==0)
            {
                coada.push({coada.front()[0]-1,coada.front()[1],coada.front()[2]+1});
                grid_copy[coada.front()[0]-1][coada.front()[1]]=3;
            }
            else if(0<=coada.front()[0]-1 && coada.front()[0]-1<grid_copy.size() && grid_copy[coada.front()[0]-1][coada.front()[1]]==1)
                return coada.front()[2];

            if(0<=coada.front()[0]+1 && coada.front()[0]+1<grid_copy.size() && grid_copy[coada.front()[0]+1][coada.front()[1]]==0)
            {
                coada.push({coada.front()[0]+1,coada.front()[1],coada.front()[2]+1});
                grid_copy[coada.front()[0]+1][coada.front()[1]]=3;
            }
            else if(0<=coada.front()[0]+1 && coada.front()[0]+1<grid_copy.size() && grid_copy[coada.front()[0]+1][coada.front()[1]]==1)
                return coada.front()[2];

            if(0<=coada.front()[1]-1 && coada.front()[1]-1<grid_copy.size() && grid_copy[coada.front()[0]][coada.front()[1]-1]==0)
            {
                coada.push({coada.front()[0],coada.front()[1]-1,coada.front()[2]+1});
                grid_copy[coada.front()[0]][coada.front()[1]-1]=3;
            }

            else if(0<=coada.front()[1]-1 && coada.front()[1]-1<grid_copy.size() && grid_copy[coada.front()[0]][coada.front()[1]-1]==1)
                return coada.front()[2];

            if(0<=coada.front()[1]+1 && coada.front()[1]+1<grid_copy.size() && grid_copy[coada.front()[0]][coada.front()[1]+1]==0)
            {
                coada.push({coada.front()[0],coada.front()[1]+1,coada.front()[2]+1});
                grid_copy[coada.front()[0]][coada.front()[1]+1]=3;
            }

            else if(0<=coada.front()[1]+1 && coada.front()[1]+1<grid_copy.size() && grid_copy[coada.front()[0]][coada.front()[1]+1]==1)
                return coada.front()[2];

            coada.pop();

        }

        return 0;
    }

    void bordering()
    {
        for(int x=0;x<grid_copy.size();x++)
        {
            for(int y=0;y<grid_copy[x].size();y++)
                if(grid_copy[x][y]==2)
                {
                    if(0<=x-1 && x-1<grid_copy.size())
                    {
                        if(grid_copy[x-1][y]==0)
                        {
                            grid_copy[x-1][y]=3;
                            coada.push({x-1,y,1});
                        }

                    }

                    if(0<=x+1 && x+1<grid_copy.size())
                    {
                        if(grid_copy[x+1][y]==0)
                        {
                            grid_copy[x+1][y]=3;
                            coada.push({x+1,y,1});
                        }
                    }

                    if(0<=y-1 && y-1<grid_copy.size())
                    {
                        if(grid_copy[x][y-1]==0)
                        {
                            grid_copy[x][y-1]=3;
                            coada.push({x,y-1,1});
                        }
                                           }
                    if(0<=y+1 && y+1<grid_copy.size())
                    {
                        if(grid_copy[x][y+1]==0)
                        {
                            grid_copy[x][y+1]=3;
                            coada.push({x,y+1,1});
                        }
                    }
                }

        }
    }

    int shortestBridge(vector<vector<int>>& grid)
    {

        int x,y,n;
        grid_copy=grid;
        n=grid_copy.size();
        st_land(x,y);
        filling(x,y);
        bordering();
        //afisare(grid_copy);
        return searching();


        return 0;

    }
};

int main()
{
    Solution s;
    vector<vector<int>> grid = {{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}};
    cout<<s.shortestBridge(grid);

    return 0;
}
