#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <unordered_map>
using namespace std;

class MaxFlow
{
    int n;
    vector<vector<int>> capacity;
    vector<vector<int>> adj;
    vector<vector<int>> flow;

public:

    MaxFlow(int n,vector<vector<int>>&capacity,vector<vector<int>>&adj)
    {
        this -> n = n;
        this -> capacity = capacity;
        this -> adj = adj;
        this -> flow = vector<vector<int>> (this->capacity.size(), vector<int>(this->capacity.size(),0));

    }

    void printAdj()
    {
        for(int i=0; i<adj.size(); i++)
        {

            cout<<i<<": ";
            for(int j=0;j<adj[i].size();j++)
                cout<<adj[i][j]<<" ";
            cout<<endl;
        }
    }

    int bfs(int s, int t, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, 1e9});

        while (!q.empty()) {
            int cur = q.front().first;
            int flw = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > flow[cur][next]) {
                    parent[next] = cur;
                    int new_flow = min(flw, this->capacity[cur][next] - this->flow[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }

        return 0;
    }

    int maxflow(int s, int t)
    {
        int flw = 0;
        vector<int> parent(this->capacity.size());
        int newFlow;

        while(newFlow = bfs(s,t,parent)){

            flw += newFlow;
            int current = t;
            while(current != s){
                int prev = parent[current];
                flow[current][prev] -= newFlow;
                flow[prev][current] += newFlow;
                current = prev;
            }
        }
        return flw;
    }

};

class Solution
{
public:

    void Negot()
    {
        ifstream in("negot.in");
        ofstream out("negot.out");

        int n,m,k,ti,aux;
        in>>n>>m>>k;

        vector<vector<int>> capacity(n+m+2,vector<int>(n+m+2,0));
        vector<vector<int>> adj(n+m+2);



        for(int i=0; i<n; i++)
        {
            in>>ti;
            for(int j=0; j<ti; j++)
            {
                in>>aux;
                adj[i+1].push_back(aux+n);
                adj[aux+n].push_back(i+1);
                capacity[i+1][aux+n] = 1;
            }
        }

        for(int i=0; i<n; i++)
        {
            adj[0].push_back(i+1);
            adj[i+1].push_back(0);
            capacity[0][i+1] = k;
        }

        for(int i=1; i<=m; i++)
        {
            adj[i+n].push_back(m+n+1);
            adj[m+n+1].push_back(i+n);
            capacity[i+n][m+n+1] = 1;
        }

        MaxFlow flow(n+m+2, capacity, adj);
        //flow.printAdj();
        out<< flow.maxflow(0, n+m+1);

        in.close();
        out.close();



    }
};


int main() {

    Solution s;
    s.Negot();


    return 0;
}
