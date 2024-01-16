#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <climits>
using namespace std;

class Graph
{
    int size; //size of the graph
    vector<vector<int>> capacity; //capacity matrix
    vector<vector<int>> adj; //adjacency matrix
    vector<vector<int>> flow; //flow matrix

public:


    //getter function for flow

    //parameters: none

    //return: the requested flow (vector<vector<int>>)
    vector<vector<int>> getFlow()
    {
        return this->flow;
    }


    //constructor for maximum flow

    //parameters:
    //--size of the graph(int)
    //--capacity matrix(vector<vector<int>>)
    //--adjacency matrix(vector<vector<int>>)

    Graph(int size,vector<vector<int>>&capacity,vector<vector<int>>&adj)
    {
        this -> size = size;
        this -> capacity = capacity;
        this -> adj = adj;
        this -> flow = vector<vector<int>> (this->capacity.size(), vector<int>(this->capacity.size(),0));

    }

    //function that prints the adjacency matrix

    //paramenters: none

    //return value: none

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


    //function based on breath first search to determine a path from source to sink and
    //the flow obtained on that path

    //parameters:
    //-start node (int)
    //-end node (int)
    //- parents of nodes (vector<int>)

    //return value: the flow for the found path(int)

    int bfs(int s, int t, vector<int>& parent)
    {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, INT_MAX});

        while (!q.empty()) {
            int cur = q.front().first;
            int flw = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > flow[cur][next]) {
                    parent[next] = cur;
                    int new_flow = min(flw, this->capacity[cur][next] - this->flow[cur][next]);
                    q.push({next, new_flow});
                    if (next == t)
                        return new_flow;

                }
            }
        }

        return 0;
    }


    //function based on edmonds karp algorithm to find the maximum flow in a graph

    //parameters:
    //--start node (int)
    //--end node (int)

    //return value: the maximum flow in the graph (int)
    int maxflow(int s, int t)
    {
        int flw = 0;
        vector<int> parent(this->capacity.size());
        int newFlow;

        //while there's a path on which we can send flow (>0)
        while(true)
        {
            newFlow = bfs(s,t,parent);

            //if the maximum flow in our current graph is 0, we end the loop
            if(!newFlow)
                break;

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
        int start = 0;
        int finish = 100;

        //first 100 nodes: the moments of time
        //last node: sink
        vector<vector<int>> capacity(finish+2,vector<int>(finish+2,0));
        vector<vector<int>> adj(finish+2);
        vector<pair<int,int>> volunteers;

        in>>n>>k;

        for(int i=0; i<n; i++)
        {
            in>>t1>>t2;
            //linking the start time with the end time
            volunteers.push_back({t1,t2});
            adj[t1].push_back(t2);
            adj[t2].push_back(t1);
            //capacity increases (instead of =1 because there might be 2 volunteers overlaying)
            capacity[t1][t2]++;
        }

        //linking the end node with the sink
        adj[finish].push_back(finish+1);
        adj[finish+1].push_back(finish);
        capacity[finish][finish+1] = k;

        Graph flow(finish+2,capacity,adj);
        flow.maxflow(start,finish+1);

        vector<int> sol;

        //if we used that volunteer (flow > 0)
        for(int i=0; i<n; i++){
            int x=volunteers[i].first;
            int y=volunteers[i].second;
            if(flow.getFlow()[x][y]){

                flow.getFlow()[x][y]--;
                sol.push_back(i+1);
            }
        }

        out<<sol.size()<<endl;
        for(int i=0; i<sol.size(); i++)
        {
            out<<sol[i]<<" ";
        }

        in.close();
        out.close();
    }

    void Harta()
    {
        ifstream in("harta.in");
        ofstream out("harta.out");

        int n,x,y;
        in>>n;

        //first element: source
        //next n elements: the cities
        //next n elements: the cities again
        //last element: sink
        vector<vector<int>> capacity(n+n+2,vector<int>(n+n+2,0));
        vector<vector<int>> adj(n+n+2);

        for(int i=1; i<=n; i++)
        {
            in>>x>>y;

            //linking the source with the first set of cities
            adj[0].push_back(i);
            adj[i].push_back(0);
            capacity[0][i] = x;

            //linking the second set of cities with the sink
            adj[i+n].push_back(n+n+1);
            adj[n+n+1].push_back(i+n);
            capacity[i+n][n+n+1] = y;


            //link the first set of cities with the second set of cities
            for(int j=1; j<=n; j++)
            {
                if(j!=i)
                {
                    adj[i].push_back(j+n);
                    adj[j+n].push_back(i);
                    capacity[i][j+n] = 1;
                }
            }
        }

        Graph flow(n+n+2, capacity, adj);
        //the result is the maximum flow in the graph and
        out<< flow.maxflow(0, n+n+1)<<endl;


        //the nodes between which we sent flow
        for(int i = 1 ; i <= n ; i++)
            for(int j = n + 1 ; j <= n+n ; j++)
                if(flow.getFlow()[i][j])
                    out<<i<<" "<<j-n<<endl;
        in.close();
        out.close();
    }

    void Negot()
    {
        ifstream in("negot.in");
        ofstream out("negot.out");

        int n,m,k,ti,aux;
        in>>n>>m>>k;


        //first element: source
        //next n elements: producers
        //next m elements: shops
        //last element: sink
        vector<vector<int>> capacity(n+m+2,vector<int>(n+m+2,0));
        vector<vector<int>> adj(n+m+2);


        //linking the producers with the shops
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

        //linking the source with the producers
        for(int i=0; i<n; i++)
        {
            adj[0].push_back(i+1);
            adj[i+1].push_back(0);
            capacity[0][i+1] = k;
        }

        //linking the shops with the sink
        for(int i=1; i<=m; i++)
        {
            adj[i+n].push_back(m+n+1);
            adj[m+n+1].push_back(i+n);
            capacity[i+n][m+n+1] = 1;
        }

        Graph flow(n+m+2, capacity, adj);
        //the result for the problem is the maximum flow in the graph
        out<< flow.maxflow(0, n+m+1);

        in.close();
        out.close();
    }
};


int main()
{
    Solution s;

    s.Ghizi();
    s.Negot();
    s.Harta();

    return 0;
}