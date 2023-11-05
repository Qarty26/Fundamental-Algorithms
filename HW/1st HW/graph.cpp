#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

class Graph
{

    void st_land(int &x, int &y,vector<vector<int>>& grid_copy) //finding the first patch of island, helping function for shortest bridge
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

    void filling(int x, int y,vector<vector<int>>& grid_copy) //marking the first island, helping function for shortest bridge
    {
        grid_copy[x][y]=2;

        if(0<=x-1 && x-1<grid_copy.size())
        {
            if(grid_copy[x-1][y]==1)
                filling(x-1,y,grid_copy);
        }
        if(0<=x+1 && x+1<grid_copy.size())
        {
            if(grid_copy[x+1][y]==1)
                filling(x+1,y,grid_copy);
        }
        if(0<=y-1 && y-1<grid_copy.size())
        {
            if(grid_copy[x][y-1]==1)
                filling(x,y-1,grid_copy);
        }
        if(0<=y+1 && y+1<grid_copy.size())
        {
            if(grid_copy[x][y+1]==1)
                filling(x,y+1,grid_copy);
        }
    }

    queue<vector<int>> bordering(vector<vector<int>>& grid_copy) // making a border around the island
    {
        queue<vector<int>> coada;
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
        return coada;
    }

    int searching(queue<vector<int>> coada,vector<vector<int>> grid_copy)
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
    }

    void Dfs(int node,vector<vector<int>>& connect,vector<int> &nivel,vector<int> &nivel_min,vector<int> &viz,vector<vector<int>> &rez) //helping method for critical connections
    {
        viz[node] = 1;
        nivel_min[node] = nivel[node];
        for(int i=0;i<connect[node].size();i++)
        {
            int vecin=connect[node][i];
            if(viz[vecin]==0)
            {
                nivel[vecin] = nivel[node]+1;
                Dfs(vecin,connect,nivel,nivel_min,viz,rez);
                nivel_min[node] = nivel_min[node] < nivel_min[vecin] ? nivel_min[node] : nivel_min[vecin];
                if(nivel_min[vecin]>nivel[node]) rez.push_back({vecin,node});
            }
            else
                if(nivel[vecin] < nivel[node]-1)
                    nivel_min[node] = nivel_min[node] < nivel[vecin] ? nivel_min[node] : nivel[vecin];

        }
    }
public:

    vector<vector<int>> findCriticalConections(int n, vector<vector<int>>& connections)
    {
        vector<int> nivel(n,0);
        vector<int> nivel_min(n,0);
        vector<int> viz(n,0);
        vector<vector<int>> rez;
        vector<vector<int>> connect;

        for(int i=0;i<n;i++)
            connect.push_back({});

        for(int i=0;i<connections.size();i++) //rearranging the data
        {
            connect[connections[i][0]].push_back(connections[i][1]);
            connect[connections[i][1]].push_back(connections[i][0]);
        }

        Dfs(0,connect,nivel,nivel_min,viz,rez);

        return rez;
    }

    int dfs(int node, vector<vector<int>>& connect, vector<int>& safe) //returns 0 if the node is not safe, 1 if it is safe
    {
        if(safe[node]!=-1)
            return safe[node];

        safe[node] = 0;
        for(int j=0;j<connect[node].size();j++)
            if(dfs(connect[node][j],connect,safe)==0)
                return safe[node];

        safe[node] = 1;
        return safe[node];
    }

    int BfsSearch(vector<vector<int>> grid) //searching by layers to find the 2nd island, helping function for shortest bridge
    {

        int x,y,n;
        queue<vector<int>> coada;
        n=grid.size();
        st_land(x,y,grid);
        filling(x,y,grid);
        coada = bordering(grid);
        return searching(coada,grid);

        return 0;
    }

    bool isBipartite(int n, vector<vector<int>>& connect)
    {
        queue<int> coada;
        vector<int> culori (n+1,0);
        int m=n;

        coada.push(connect[1][0]);
        culori[coada.front()]=1;

        while(m>0)
        {
            int head = coada.front();
            for(int i=0;i<connect[head].size();i++)
            {
                if(culori[connect[head][i]] == 0)
                {
                    coada.push(connect[head][i]);
                    culori[connect[head][i]] = 3 - culori[head];
                }
                else if(culori[head] == culori[connect[head][i]])
                    return false;

            }
            coada.pop();
            m--;

            if(coada.empty() && m!=0)
                for(int j=1;j<=n;j++)
                    if(culori[j]==0)
                    {
                       coada.push(j);
                       break;
                    }

        }
        return true;
    }

    vector<int> whichBipartite(int n, vector<vector<int>>& connect)
    {
        queue<int> coada;
        vector<int> culori (n+1,0);
        int m=n;

        coada.push(connect[1][0]);
        culori[coada.front()]=1;

        while(m>0)
        {
            int head = coada.front();
            for(int i=0;i<connect[head].size();i++)
            {
                if(culori[connect[head][i]] == 0)
                {
                    coada.push(connect[head][i]);
                    culori[connect[head][i]] = 3 - culori[head];
                }

            }
            coada.pop();
            m--;

            if(coada.empty() && m!=0)
                for(int j=1;j<=n;j++)
                    if(culori[j]==0)
                    {
                       coada.push(j);
                       break;
                    }

        }
        return culori;
    }

    int doFind(int x, vector<int> &parent)
    {
        while(parent[x]!=x)
            x = doFind(parent[x],parent);

        return x;
    }

    vector<int> doUnion(int a, int b,vector<int>& parent)
    {
        int ua = doFind(a,parent);
        int ub = doFind(b,parent);

        parent[ua] = ub;

        return parent;
    }

    Graph()
    {

    }



};

class Solution
{

    queue<vector<int>> coada;

public:

    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {
        int i;
        Graph g;
        vector<vector<int>> connect;

        for(i=0;i<=n;i++)
            connect.push_back({});
        for(i=0;i<dislikes.size();i++)
        {
            connect[dislikes[i][0]].push_back(dislikes[i][1]);
            connect[dislikes[i][1]].push_back(dislikes[i][0]);
        }

        if(n>1)
            return g.isBipartite(n,connect);

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
        return g.findCriticalConections(n,connections);

    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph)
    {
            Graph g;
            vector<vector<int>> connect;
            vector<int> safe,sol;

            connect = graph;
            for(int i=0;i<graph.size();i++)
                safe.push_back(-1);

            for(int i=0;i<graph.size();i++)
                if(g.dfs(i,connect,safe)==1)
                    sol.push_back(i);

            return sol;
    }

    int shortestBridge(vector<vector<int>>& grid)
    {
        Graph g;
        return g.BfsSearch(grid);

        return 0;
    }

    bool equationsPossible(vector<string>& equations)
    {
        Graph g;
        vector<int> parent(26);
        int a,b;

        for(int i=0;i<26;i++)
            parent[i]=i;

        for(int i=0;i<equations.size();i++)
            if (equations[i][1]== '=')
            {
                a = equations[i][0] - 'a';
                b = equations[i][3] - 'a';
                parent = g.doUnion(a,b,parent);
            }

        for(int i=0;i<equations.size();i++)
            if (equations[i][1]== '!')
            {
                a = equations[i][0] - 'a';
                b = equations[i][3] - 'a';

                if(g.doFind(a,parent) == g.doFind(b,parent))
                    return false;
            }
        return true;

    }

    string noLongPaths(int n, vector<vector<int>>& connections)
    {
        Graph g;
        vector<vector<int>> connect;
        vector<int> colors(n+1);
        string result = "";

        for(int i=0;i<=n;i++)
            connect.push_back({});
        for(int i=0;i<connections.size();i++)
        {
            connect[connections[i][0]].push_back(connections[i][1]);
            connect[connections[i][1]].push_back(connections[i][0]);
        }

        if(g.isBipartite(n,connect) == false)
            return "NO";
        else
        {
            colors = g.whichBipartite(n,connect);
            for(int i=0;i<connections.size();i++)
                if(colors[connections[i][0]]==1 && colors[connections[i][1]]==2)
                    result += "1";
                else
                    result += "0";

            return("YES\n" + result);
        }
    }

    int minMaxDist(int n, vector<int>& marked, vector<vector<int>>& graph)
    {

        if(marked.size()==1)
            return 0;

        int distances[n + 1];
        memset(distances, 0, sizeof(distances));
        vector<vector<int>> connect(n + 1);
        queue<int> coada;




        for(int i=0;i<graph.size();i++)
        {
            connect[graph[i][0]].push_back(graph[i][1]);
            connect[graph[i][1]].push_back(graph[i][0]);
        }

        coada.push(marked[0]);
        while(!coada.empty())
        {
            for(int i=0;i<connect[coada.front()].size();i++)
            {
                int neighbour = connect[coada.front()][i];
                if(distances[neighbour]==0 && neighbour!=marked[0])
                {
                    coada.push(neighbour);
                    distances[neighbour] = distances[coada.front()] + 1;
                }

            }
            coada.pop();
        }



        int max_distance = 0;
        int st_extreme = -1;
        for(int i=0;i<marked.size();i++)
            if(distances[marked[i]]>max_distance)
            {
                max_distance = distances[marked[i]];
                st_extreme = marked[i];
            }


        memset(distances, 0, sizeof(distances));


        coada.push(st_extreme);
        while(!coada.empty())
        {
            for(int i=0;i<connect[coada.front()].size();i++)
            {
                int neighbour = connect[coada.front()][i];
                if(distances[neighbour]==0 && neighbour!=st_extreme)
                {
                    coada.push(neighbour);
                    distances[neighbour] = distances[coada.front()] + 1;
                }

            }
            coada.pop();
        }

        max_distance = 0;
        for(int i=0;i<marked.size();i++)
            if(distances[marked[i]]>max_distance)
                max_distance = distances[marked[i]];


        return ((max_distance+1)/2);

    }

};

int main()
{


    return 0;
}
