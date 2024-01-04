#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;

class MaxFlow
{
    int n;
    vector<vector<int>> capacity;
    vector<vector<int>> adj;


public:

    vector<vector<int>> flow;

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

    void Ghizi()
    {
        ifstream in("ghizi.in");
        ofstream out("ghizi.out");

        int n,k,t1,t2;
        vector<vector<int>> capacity(102,vector<int>(102,0));
        vector<vector<int>> adj(102);
        vector<pair<int,int>> volunteers;
        in>>n>>k;

        for(int i=0; i<n; i++)
        {
            in>>t1>>t2;
            volunteers.push_back({t1,t2});
            adj[t1].push_back(t2);
            adj[t2].push_back(t1);
            capacity[t1][t2]++;
        }

        adj[100].push_back(101);
        adj[101].push_back(100);
        capacity[100][101] = k;

        MaxFlow flow(102,capacity,adj);
        flow.maxflow(0,101);

        vector<int> sol;

        for(int i=0;i<n;i++){
            int x=volunteers[i].first;
            int y=volunteers[i].second;
            if(flow.flow[x][y]){

                flow.flow[x][y]--;
                sol.push_back(i+1);
            }
        }
        out<<sol.size()<<endl;

        sort(sol.begin(), sol.end());
        for(int i=0;i<sol.size();i++)
        {
            out<<sol[i]<<" ";
        }

        in.close();
        out.close();
    }
};


int main()
{
    Solution s;
    s.Ghizi();
    return 0;
}