#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
    vector<vector<int>> connect;
    vector<int> nivel;
    vector<int> nivel_min;
    vector<int> viz;
    vector<int> safe;
    queue<vector<int>> coada;


    void st_land(int &x, int &y) //finding the first patch of island, helping function for shortest bridge
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

    void filling(int x, int y) //marking the first island, helping function for shortest bridge
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

    void bordering() // making a border around the map, helping function for shortest bridge
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


public:

    void Dfs(int node) //helping method for critical connections
    {
        viz[node] = 1;
        nivel_min[node] = nivel[node];
        for(int i=0;i<connect[node].size();i++)
        {
            int vecin=connect[node][i];
            if(viz[vecin]==0)
            {
                nivel[vecin] = nivel[node]+1;
                Dfs(vecin);
                nivel_min[node] = nivel_min[node] < nivel_min[vecin] ? nivel_min[node] : nivel_min[vecin];
                if(nivel_min[vecin]>nivel[node]) rez.push_back({vecin,node});
            }
            else
                if(nivel[vecin] < nivel[node]-1)
                    nivel_min[node] = nivel_min[node] < nivel[vecin] ? nivel_min[node] : nivel[vecin];

        }
    }

    int dfs(int node) //returns 0 if the node is not safe, 1 if it is safe
    {
        if(safe[node]!=-1)
            return safe[node];

        safe[node] = 0;
        for(int j=0;j<connect[node].size();j++)
            if(dfs(connect[node][j])==0)
                return safe[node];

        safe[node] = 1;
        return safe[node];
    }

    int BfsSearch(vector<vector<int>> grid) //searching by layers to find the 2nd island, helping function for shortest bridge
    {

        int x,y,n;
        vector<vector<int>> grid_copy;
        grid_copy=grid;
        n=grid_copy.size();
        st_land(x,y);
        filling(x,y);
        bordering();

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

    Graph()
    {

    }



};

class Solution
{
    int i,j;
    vector<vector<int>> connect;
    vector<int> nivel;
    vector<int> nivel_min;
    vector<int> viz;
    vector<vector<int>> rez;
    vector<int> safe;
    vector<int> sol;
    queue<vector<int>> coada;

public:

    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {

        int colors[n+1],i,m;
        m=n;
        queue<int> coada;
        for(i=1;i<=n;i++)
            colors[i]=0; // in colors, 0 = unvisited, 1 = 1st color, 2= 2nd color

        if(n>1)
        {
            coada.push(dislikes[0][0]);
            colors[coada.front()]=1; //starting the queue

            while(m>0) //m = number of unvisited nodes
            {
                for(i=0;i<dislikes.size();i++)
                {
                    if(coada.front() == dislikes[i][0])
                   {
                        if(colors[dislikes[i][1]]==0) //if the pair has one unvisited member
                        {
                            coada.push(dislikes[i][1]);
                            if(colors[coada.front()]==1) colors[dislikes[i][1]]=2;
                                else colors[dislikes[i][1]]=1;
                            //colored in the opposite color
                        }
                        else if(colors[dislikes[i][1]]==colors[coada.front()]) //checked if we colored the pair in 2 different colors
                            return false;
                   }

                    //like above
                    if(coada.front() == dislikes[i][1])
                   {
                        if(colors[dislikes[i][0]]==0)
                        {
                            coada.push(dislikes[i][0]);
                            if(colors[coada.front()]==1) colors[dislikes[i][0]]=2;
                                else colors[dislikes[i][0]]=1;
                        }

                        else if(colors[dislikes[i][0]]==colors[coada.front()])
                            return false;
                   }
                }
                coada.pop();
                m--;

                if(coada.empty() && m!=0)
                    for(i=1;i<=n;i++)
                        if(colors[i]==0)
                        {
                           coada.push(i);
                           break;
                        }
                //if the queue is empty and we have unvisited nodes (m!=0), we push in queue the first unvisited node
            }
        }
        return true;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {

        int degr[numCourses+1];
        int i,ok=0;
        queue<int> coada;
        vector<int> sol;

        for(i=0;i<numCourses;i++)
            degr[i]=0;


        for(i=0;i<prerequisites.size();i++)
            degr[prerequisites[i][0]]++;


        if(prerequisites.size()==0) //if there are no dependencies, we ca push all the courses in any way
            for(i=0;i<numCourses;i++)
                sol.push_back(i);
        else


        while(ok!=numCourses)
        {
            for(i=0;i<numCourses;i++)
                if(degr[i]==0) //pushing elements with inner degree = 0 and marking them as visited
                {
                   coada.push(i);
                   degr[i]=-1;
                }

            for(i=0;i<prerequisites.size();i++)
                if(prerequisites[i][1]==coada.front())
                    degr[prerequisites[i][0]]--; //"removing" edges


            if(!coada.empty())
            {
                sol.push_back(coada.front());
                coada.pop();
            }

            ok++;
        }

        if(sol.size()!=numCourses) //if the solution size != number of courses => can't take all the courses
            return {};
        return sol;
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections)
    {
        Graph g;
        connect.clear();
        for(i=0;i<n;i++) //initialing
        {
            nivel.push_back(0);
            nivel_min.push_back(0);
            viz.push_back(0);
            connect.push_back({});
        }

        for(i=0;i<connections.size();i++) //rearranging the data
        {
            connect[connections[i][0]].push_back(connections[i][1]);
            connect[connections[i][1]].push_back(connections[i][0]);
        }

        g.Dfs(0);

        return rez;

    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph)
    {
            Graph g;
            connect = graph;

            for(int i=0;i<graph.size();i++)
                safe.push_back(-1);

            for(int i=0;i<graph.size();i++)
                if(g.dfs(i)==1)
                    sol.push_back(i);

            return sol;
    }

    int shortestBridge(vector<vector<int>>& grid)
    {
        Graph g;
        return g.BfsSearch(grid);

        return 0;
    }

};

int main()
{

    Solution s;
    vector<vector<int>> grid = {{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,0,1,0,0}};
    cout<<s.shortestBridge(grid);

    return 0;
}
