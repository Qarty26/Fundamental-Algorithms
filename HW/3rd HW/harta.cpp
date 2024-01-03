#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class MaxFlow
{
    int n;
    vector<vector<int>> capacity;
    vector<vector<int>> adj;
    vector<vector<int>> flow;

public:


    vector<vector<int>> getFlow()
    {
        return this->flow;
    }

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

    void printFlow()
    {
        for(int i=0; i<flow.size(); i++)
        {

            cout<<i<<": ";
            for(int j=0;j<flow[i].size();j++)
                cout<<flow[i][j]<<" ";
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

    void Harta()
    {
        ifstream in("harta.in");
        ofstream out("harta.out");

        int n,x,y;
        in>>n;

        vector<vector<int>> capacity(n+n+2,vector<int>(n+n+2,0));
        vector<vector<int>> adj(n+n+2);

        for(int i=1;i<=n;i++)
        {
            in>>x>>y;

            adj[0].push_back(i);
            adj[i].push_back(0);
            capacity[0][i] = x;

            adj[i+n].push_back(n+n+1);
            adj[n+n+1].push_back(i+n);
            capacity[i+n][n+n+1] = y;

            for(int j=1 ;j<=n;j++)
            {
                if(j!=i)
                {
                    adj[i].push_back(j+n);
                    adj[j+n].push_back(i);
                    capacity[i][j+n] = 1;
                }
            }
        }


        MaxFlow flow(n+n+2, capacity, adj);
        out<< flow.maxflow(0, n+n+1)<<endl;
        //flow.printFlow();

        for(int i = 1 ; i <= n ; i++)
            for(int j = n + 1 ; j <= n+n ; j++)
                if(flow.getFlow()[i][j])
                    out<<i<<" "<<j-n<<endl;
        in.close();
        out.close();
    }
};


int main() {

    Solution s;
    s.Harta();


    return 0;
}