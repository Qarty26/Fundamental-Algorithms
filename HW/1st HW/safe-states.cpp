#include <iostream>
#include <vector>
using namespace std;

class Solution {

    vector<int> safe;
    vector<int> sol;
    vector<vector<int>> connections;

public:

    int dfs(int node)
    {
        if(safe[node]!=-1)
            return safe[node];

        safe[node] = 0;
        cout<<"Sunt la nodul "<<node<<endl;
        for(int j=0;j<connections[node].size();j++)
            if(dfs(connections[node][j])==0)
            {
                cout<<"Nodul "<<node<<" NU e safe"<<endl;
                return safe[node];
            }

        safe[node] = 1;
        cout<<"Nodul "<<node<<" e safe"<<endl;
        return safe[node];
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph)
    {

            connections = graph;

            for(int i=0;i<graph.size();i++)
                safe.push_back(-1);

            for(int i=0;i<graph.size();i++)
                if(dfs(i)==1)
                    sol.push_back(i);

            return sol;
    }

};

int main()
{
    Solution s;
    vector<vector<int>> graph = {{1,2},{2,3},{5},{0},{5},{},{}};
    s.eventualSafeNodes(graph);

    return 0;
}
