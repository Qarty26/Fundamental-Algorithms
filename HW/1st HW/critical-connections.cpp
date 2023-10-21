#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
        int i,j;
        vector<vector<int>> connect;
        vector<int> nivel;
        vector<int> nivel_min;
        vector<int> viz;
        vector<vector<int>> rez;

    void Dfs(int node)
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

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections)
    {

        for(i=0;i<n;i++)
        {
            nivel.push_back(0);
            nivel_min.push_back(0);
            viz.push_back(0);
            connect.push_back({});
        }

        for(i=0;i<connections.size();i++)
        {
            connect[connections[i][0]].push_back(connections[i][1]);
            connect[connections[i][1]].push_back(connections[i][0]);
        }
/*
        for(i=0;i<connect.size();i++)
        {
            cout<<i<<": ";
            for(j=0;j<connect[i].size();j++)
                cout<<connect[i][j]<<" ";
            cout<<endl;
        }
*/

    Dfs(0);
/*
            for(i=0;i<rez.size();i++)
                cout<<rez[i][0]<<" "<<rez[i][1]<<endl;
*/
    return rez;

    }
};

int main()
{
    Solution s;
    vector<vector<int>> connections = {{0,1},{1,2},{2,0},{1,3}};
    s.criticalConnections(4,connections);


    return 0;
}
