#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
using namespace std;
ifstream in("padure.in");
ofstream out("padure.out");

class Solution
{
public:

    bool in_graph(int x, int y, int n, int m)
    {
        if(0<=x && x<n && 0<=y && y<m)
            return true;

        return false;
    }
    int padure(int n,int m, int pl,int pc, int cl, int cc,vector<vector<int>>& graph)
    {

        vector<vector<int>> cost(n, vector<int>(m,32000));
        deque<pair<int,int>> deq;
        vector<pair<int,int>> coordinates = {{-1,0},{1,0},{0,-1}, {0,1}};
        deq.push_front({pl-1,pc-1});
        cost[pl-1][pc-1] = 0;
        while(!deq.empty())
        {
            int x=deq.front().first;
            int y=deq.front().second;
            deq.pop_front();

            for(int i=0;i<coordinates.size();i++)
            {
                int x_new = x + coordinates[i].first;
                int y_new = y + coordinates[i].second;

                if(in_graph(x_new,y_new,n,m) && cost[x_new][y_new] > cost[x][y])
                {
                    if(graph[x_new][y_new] != graph[x][y])
                    {
                        cost[x_new][y_new] = cost[x][y] + 1;
                        deq.push_back({x_new,y_new});
                    }
                    else
                    {
                        cost[x_new][y_new] = cost[x][y];
                        deq.push_front({x_new,y_new});
                    }
                }
            }



        }

        return cost[cl-1][cc-1];
    }
};

int main()
{
    Solution s;
    int n,m,pl,pc,cl,cc,x;
    vector<vector<int>> graph;
    in>>n>>m>>pl>>pc>>cl>>cc;

    for(int i=0;i<n;i++)
        graph.push_back({});

    for(int i=0;i<n;i++)
       for(int j=0;j<m;j++)
       {
           in>>x;
           graph[i].push_back(x);
       }


    out<<s.padure(n,m,pl,pc,cl,cc,graph);


    return 0;
}
