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

struct edge
{
    int startNode,endNode,cost;
    bool operator<(const edge& a) const
    {
        return this->cost < a.cost;
    }
};

class DSU
{
    int size;
    vector<int> parent;
    vector<int> sizeComponent;

public:

    DSU(int size)
    {
        this-> size = size;
        for(int i=0;i<=size;i++)
        {
            parent.push_back(i);
            sizeComponent.push_back(1);
        }
    }

    int findParent(int x)
    {
        if(parent[x]!=x)
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParents(int a, int b)
    {
        int ua = findParent(a);
        int ub = findParent(b);

        parent[ua] = ub;
    }

    void unionWithSize(int node1, int node2)
    {
        node1 = findParent(node1);
        node2 = findParent(node2);

        if (node1 == node2)
            return;

        sizeComponent[node1] += sizeComponent[node2];
        parent[node2] = node1;
    }

    int getSizeComponent(int index) const
    {
        return this->sizeComponent[index];
    }
};

class Graph
{
    vector<vector<pair<int,long long>>> connectionsWithCost;
    int size;
    int noEdges;
    vector<pair<int,int>> coordinates;

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

    Graph(int size, vector<pair<int,int>> coordinates)
    {
        this->size = size;
        this->coordinates = coordinates;
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

    int mstWithCoord()
    {
        double totalCost=0.0;
        int nextNode;

        vector<int> visited(size+1,0);
        vector<double> minDist(size+1,30000* sqrt(2));

        minDist[0]=0.0;
        for(int i=1;i<size;i++)
            minDist[i] = sqrt(pow(coordinates[i].first - coordinates[0].first,2) + pow(coordinates[i].second - coordinates[0].second,2));
        visited[0]=1;


        for(int contor=1;contor<size;contor++) //in each loop we add a node do MST, we already have the node 0
        {
            nextNode=contor;
            double shortestEdge= 30000 * sqrt(2); //diagonal of the grid with max_length = 30000

            //minimum distance from any node in Mst to any unvisited node
            for(int node=1; node<=size; node++)
            {
                if(visited[node] == 0 && minDist[node] < shortestEdge)
                {
                    shortestEdge = minDist[node];
                    nextNode = node;
                }
            }

            //adding to the total and marking the added node
            totalCost+=shortestEdge;
            visited[nextNode]=1;

            //updating the minimum distance from the new node to any unvisited node
            for(int node=1;node<size;node++)
            {
                if(visited[node] == 0)
                {
                    double tempDist = sqrt(pow(coordinates[node].first - coordinates[nextNode].first,2)
                                           + pow(coordinates[node].second - coordinates[nextNode].second,2));

                    if(tempDist < minDist[node])
                        minDist[node] = tempDist;
                }
            }

        }

        return totalCost;
    }
};

class Solution
{

    static bool compareDistance(const vector<int>& vect1, const vector<int>& vect2)
    {
        return vect1[2] < vect2[2];
    }

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

    int dragoni1(int start,vector<vector<pair<int,int>>>& connections,int dmax[])
    {
        queue<int> que;
        bool visited[connections.size()+1];
        for(int i=1;i<=connections.size();i++)
            visited[i] = false;

        int maxx = dmax[1];
        que.push(start);

        while(!que.empty())
        {
            int head = que.front();
            //cout<<"Head is "<<head<<endl;
            que.pop();
            visited[head] = true;
            for(int i=0;i<connections[head].size();i++)
                if(!visited[connections[head][i].first] && connections[head][i].second <= dmax[1])
                {
                    //cout<<"connected with"<<connections[head][i].first<<endl;
                    que.push(connections[head][i].first);
                }


            if(dmax[head] > maxx)
            {
                //cout<<"new max at"<<head;
                maxx = dmax[head];
            }

        }

        return maxx;
    }

    int dragoni2(int start,int n,vector<vector<pair<int,int>>>& connections,int dmax[])
    {
        vector<int> distMax(n+1,0);
        priority_queue <
                std::pair <int, std::pair <int, int>>,
                std::vector <std::pair <int, std::pair <int, int>>>,
                std::greater <std::pair <int, std::pair <int, int>>>
        > que;

        que.push({0,{start,dmax[start]}});

        while(!que.empty())
        {
            int actual_distance = que.top().first;
            int current_node = que.top().second.first;
            int which_dragon = que.top().second.second;
            //cout<<"current node = "<<current_node<<endl;
            que.pop();

            if(which_dragon < distMax[current_node])
                continue;

            distMax[current_node] = which_dragon;
            if(current_node == n)
                return actual_distance;

            for(int i=0;i<connections[current_node].size();i++)
            {
                int nextDragon = max(which_dragon,dmax[connections[current_node][i].first]);
                if(connections[current_node][i].second <= which_dragon && distMax[connections[current_node][i].first] < nextDragon)
                {
                    que.push({actual_distance + connections[current_node][i].second,{connections[current_node][i].first,nextDragon}});
                }
            }

        }
        return 0;
    }

    bool inMatrix(int n, pair<int,int> coord, pair<int,int> directions)
    {
        if(0 <= coord.first + directions.first && coord.first + directions.first < n &&
           0 <= coord.second + directions.second && coord.second + directions.second < n)
            return true;
        return false;
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

    void cablaj()
    {
        ifstream in("cablaj.in");
        ofstream out("cablaj.out");

        int n;

        in>>n;

        vector<pair<int, int>> coordinates(n+1);

        for(int i=0;i<n;i++)
            in>>coordinates[i].first>>coordinates[i].second;




        Graph g(n,coordinates);
        out<<fixed<<setprecision(4)<<g.mstWithCoord();

        in.close();
        out.close();
    }

    void dragoni()
    {
        ifstream in("dragoni.in");
        ofstream out("dragoni.out");

        int p,n,m,a,b,d;
        in>>p>>n>>m;

        int dmax[1000];
        vector<vector<pair<int,int>>> connections;
        connections.resize(n+1);
        for(int i=1;i<=n;i++)
            in>>dmax[i];

        for(int i=1;i<=m;i++)
        {
            in>>a>>b>>d;
            connections[a].push_back({b,d});
            connections[b].push_back({a,d});
        }

        if(p==1)
            out<<dragoni1(1,connections,dmax);
        else
            out<<dragoni2(1,n,connections,dmax);
    }

    void rusuoaica()
    {
        ifstream in("rusuoaica.in");
        ofstream out("rusuoaica.out");

        int n,M,a,x,y,costEdge;
        int totalCost = 0;
        vector<edge> edges;
        in>>n>>M>>a;

        for(int i=0;i<M;i++)
        {
            in>>x>>y>>costEdge;
            if(costEdge>a)
                totalCost-=costEdge;
            else
                edges.push_back({x,y,costEdge});
        }

        sort(edges.begin(), edges.end());

        DSU dsu(n);

        int used=0;
        for(int i=0;i<edges.size();i++)
            if(dsu.findParent(edges[i].startNode) != dsu.findParent(edges[i].endNode))
            {
                totalCost+=edges[i].cost;
                used+=1;
                dsu.unionParents(edges[i].startNode,edges[i].endNode);
            }
            else
                totalCost-=edges[i].cost;

        totalCost += a*(n-used-1);

        out<<totalCost;

        in.close();
        out.close();
    }

    void oracol()
    {
        ifstream in("oracol.in");
        ofstream out("oracol.out");

        vector<edge> edges;

        int n,price;
        in>>n;
        for(int i=0;i<n;i++)
            for(int j=i;j<n;j++)
            {
                in>>price;
                edges.push_back({i,j+1,price});
            }

        sort(edges.begin(), edges.end());

        DSU dsu(n);

        int totalCost = 0;
        for(int i=0;i<edges.size();i++)
            if(dsu.findParent(edges[i].startNode) != dsu.findParent(edges[i].endNode))
            {
                totalCost+=edges[i].cost;
                dsu.unionParents(edges[i].startNode,edges[i].endNode);
            }

        out<<totalCost;

        in.close();
        out.close();
    }

    void bile()
    {
        ifstream in("bile.in");
        ofstream out("bile.out");

        int n;
        int maxim = 1;
        in>>n;

        bool checked[1000][1000];
        vector<int> result;
        vector<pair<int,int>> coordBila(n*n+1);
        vector<pair<int,int>> directions {{0,1},{0,-1},{1,0},{-1,0}};
        for(int i=0;i<n*n;i++)
        {
            in>>coordBila[i].first>>coordBila[i].second;
            coordBila[i].first--;
            coordBila[i].second--;
        }

        DSU dsu(n*n);

        result.push_back(0);
        for(int i=n*n-1;i>=0;i--)
        {
            int x = coordBila[i].first;
            int y = coordBila[i].second;
            for(int j=0;j<4;j++) {

                if (inMatrix(n, coordBila[i], directions[j]) &&
                    checked[x + directions[j].first][y + directions[j].second]) {
                    int line = x + directions[j].first;
                    int column = y + directions[j].second;

                    dsu.unionWithSize(x * n + y,line * n + column );
                }
            }
            checked[coordBila[i].first][coordBila[i].second] = true;
            maxim = max(maxim,dsu.getSizeComponent(x*n+y));
            result.push_back(maxim);
        }

        for(int i=result.size()-2;i>=0;i--)
            out<<result[i]<<endl;

        in.close();
        out.close();
    }

    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries)
    {
        vector<bool> result(queries.size(), false);
        DSU dsu(n);

        sort(edgeList.begin(), edgeList.end(), compareDistance);

        for(int i=0;i<queries.size();i++)
            queries[i].push_back(i);

        sort(queries.begin(), queries.end(), compareDistance);
        int CurrentEdge = 0;

        for(int i=0;i<queries.size();i++)
        {
            int limit = queries[i][2];

            while(CurrentEdge < edgeList.size() && edgeList[CurrentEdge][2] < limit)
            {
                dsu.unionParents(edgeList[CurrentEdge][0],edgeList[CurrentEdge][1]);
                CurrentEdge++;
            }



            if(dsu.findParent(queries[i][0]) == dsu.findParent(queries[i][1]))
                result[queries[i][3]] = true;
        }


        return result;

    }
};

int main() {

    Solution s;

    /*vector<vector<int>> flights = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    cout<<s.findCheapestPrice(4,flights,0,3,1); done*/
    //s.trilant();  done
    //s.camionas(); done
    //s.cablaj(); done
    //s.dragoni(); done
    //s.rusuoaica(); done
    //s.oracol(); done
    //s.bile(); done

//    vector<vector<int>> EdgeList = {{0,1,10},{1,2,5},{2,3,9},{3,4,13}};
//    vector<vector<int>> queries = {{0,4,14},{1,4,13}};
//
//    s.distanceLimitedPathsExist(5,EdgeList,queries);
    
    return 0;
}
