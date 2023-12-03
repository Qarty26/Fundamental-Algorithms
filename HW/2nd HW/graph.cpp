#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <algorithm>
#include <fstream>
#include <climits>
#include <cmath>
#include <iomanip>

using namespace std;

class Graph
{
    vector<vector<pair<int,long long>>> connectionsWithCost;
    int size;
    int noEdges;

    struct CompareSecond {
        bool operator()(const pair<int, long long>& left, const pair<int, long long>& right) const {
            return left.second > right.second;
        }
    };



public:

    Graph(int size, int noEdges, vector<vector<pair<int,long long>>>& connections)
    {
        this->size = size;
        this-> noEdges = noEdges;
        this->connectionsWithCost = connections;

    }

    Graph(int size, vector<vector<int>>& connections,bool oriented)
    {
        this->size = size;
        connectionsWithCost.resize(size);
        for(int i=0;i<connections.size();i++)
        {
            this->connectionsWithCost[connections[i][0]].push_back({connections[i][1],connections[i][2]});
            if(oriented == false)
                this->connectionsWithCost[connections[i][1]].push_back({connections[i][0],connections[i][2]});
        }


    }

    vector<pair<long long, int>> dijk(int start)
    {
        priority_queue <pair <int,long long>,
                vector<pair <int,long long>>,
                CompareSecond
        > que;
        vector<pair<long long, int>> distancesAndParent(connectionsWithCost.size(),{LLONG_MAX, -1});
        vector<bool> visited(connectionsWithCost.size(),false);

        for(int i=1;i<connectionsWithCost.size();i++)
            distancesAndParent[i].second=i;

        que.push({start,0});
        distancesAndParent[start].first = 0;
        while(!que.empty())
        {
            int head = que.top().first;
            long long cost = que.top().second;
            que.pop();

            if (visited[head] == false)
            {
                visited[head] = true;

                for (int i = 0; i < connectionsWithCost[head].size(); i++) {
                    if (distancesAndParent[connectionsWithCost[head][i].first].first > cost + connectionsWithCost[head][i].second) {
                        distancesAndParent[connectionsWithCost[head][i].first].first = cost + connectionsWithCost[head][i].second;
                        que.push({connectionsWithCost[head][i].first, distancesAndParent[connectionsWithCost[head][i].first].first});
                        distancesAndParent[connectionsWithCost[head][i].first].second = head;
                    }
                }
            }
        }

        return distancesAndParent;

    }

    int shortestPathWithinKStops (int src, int dst, int k)
    {
        queue<pair<int,pair<int,int>>> que;
        vector<int> costs(size,100001);
        que.push({0,{src,0}});

        while(!que.empty())
        {
            pair<int,pair<int,int>>head = que.front();
            int stops = head.first;
            int destination = head.second.first;
            int cost = head.second.second;
            que.pop();

            if(stops <= k)
            {
                for(int i=0;i<connectionsWithCost[destination].size();i++)
                    if(cost + connectionsWithCost[destination][i].second < costs[connectionsWithCost[destination][i].first])
                    {
                        costs[connectionsWithCost[destination][i].first] = cost + connectionsWithCost[destination][i].second;
                        que.push({stops+1,{connectionsWithCost[destination][i].first,costs[connectionsWithCost[destination][i].first]}});
                    }
            }
            else
                break;
        }


        if (costs[dst] == 100001)
            return -1;
        return costs[dst];

    }

    vector<int> BfsZeroOne(int maxCost)
    {
        deque<int> deq;
        vector<int> toRaiseCumulative(size+1,50001);
        deq.push_front(1);
        toRaiseCumulative[1]=0;

        while(!deq.empty())
        {
            int head = deq.front();
            deq.pop_front();

            for(int i=0;i<connectionsWithCost[head].size();i++)
                if(toRaiseCumulative[connectionsWithCost[head][i].first] - connectionsWithCost[head][i].second  > toRaiseCumulative[head])
                {
                    if(connectionsWithCost[head][i].second >= maxCost)
                    {
                        toRaiseCumulative[connectionsWithCost[head][i].first] = toRaiseCumulative[head];
                        deq.push_front(connectionsWithCost[head][i].first);
                    }
                    else
                    {
                        toRaiseCumulative[connectionsWithCost[head][i].first] = toRaiseCumulative[head]+1;
                        deq.push_back(connectionsWithCost[head][i].first);
                    }
                }
        }

        return toRaiseCumulative;
    }
};

class Solution
{
    void findPath(int node,int endNode, vector<pair<long long,int>>& parent,ofstream &out)
    {
        vector<int> result;
        while(node!=endNode)
        {
            result.push_back(node);
            node = parent[node].second;
        }
        result.push_back(endNode);

        out<<result.size()<<" ";
        for(int i=0;i<result.size();i++)
            out<<result[i]<<" ";
        out<<endl;
    }
public:

    void trilant()
    {
        ifstream in("trilant.in");
        ofstream out("trilant.out");

        int n,m,a,b,c,x,y,cost;
        in>>n>>m>>a>>b>>c;
        vector<vector<pair<int,long long>>> connections;
        connections.resize(n+1);

        for(int i=0;i<m;i++)
        {
            in>>x>>y>>cost;
            connections[x].push_back({y,cost});
            connections[y].push_back({x,cost});
        }


        Graph g(n,m,connections);
        vector<pair<long long,int>> costsAndPathFromA;
        vector<pair<long long,int>> costsAndPathFromB;
        vector<pair<long long, int>> costsAndPathFromC;

        costsAndPathFromA = g.dijk(a);
        costsAndPathFromB = g.dijk(b);
        costsAndPathFromC = g.dijk(c);


        long long minDist = LLONG_MAX;
        int nodeX = -1;
        for(int i=1;i<=n;i++)
        {
            if(costsAndPathFromA[i].first + costsAndPathFromB[i].first + costsAndPathFromC[i].first < minDist)
            {
                minDist = costsAndPathFromA[i].first + costsAndPathFromB[i].first + costsAndPathFromC[i].first;
                nodeX = i;
            }
        }
        out<<minDist<<endl;
        findPath(nodeX,a,costsAndPathFromA,out);
        findPath(nodeX,b,costsAndPathFromB,out);
        findPath(nodeX,c,costsAndPathFromC,out);

        in.close();
        out.close();
    }

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {

        Graph g(n,flights,true);
        return g.shortestPathWithinKStops(src,dst,k);
    }

    void camionas()
    {
        ifstream in("camionas.in");
        ofstream out("camionas.out");
        int n,m,g,x,y,w;

        in>>n>>m>>g;
        vector<vector<pair<int,long long>>> edges(n+1);

        for(int i=0;i<m;i++)
        {
            in>>x>>y>>w;
            edges[x].push_back({y,w});
            edges[y].push_back({x,w});
        }

        Graph graph(n,m,edges);
         out<<graph.BfsZeroOne(g)[n];


        in.close();
        out.close();
    }
};

int main() {

    Solution s;

    /*vector<vector<int>> flights = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    cout<<s.findCheapestPrice(4,flights,0,3,1); done*/
    //s.trilant();  done
    //s.camionas(); done

    return 0;
}
