#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
ifstream in("trilant.in");
ofstream out("trilant.out");

vector<vector<pair<int,long long>>> connections;


void findPath(int node,int endNode, vector<pair<long long,int>>& parent)
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

struct CompareSecond {
    bool operator()(const pair<int, long long>& left, const pair<int, long long>& right) const {
        return left.second > right.second;
    }
};

vector<pair<long long, int>> dijk(int start)
{
    priority_queue <pair <int,long long>,
            vector<pair <int,long long>>,
            CompareSecond
    > que;
    vector<pair<long long, int>> distancesAndParent(connections.size(),{LLONG_MAX, -1});
    vector<bool> visited(connections.size(),false);

    for(int i=1;i<connections.size();i++)
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

            for (int i = 0; i < connections[head].size(); i++) {
                if (distancesAndParent[connections[head][i].first].first > cost + connections[head][i].second) {
                    distancesAndParent[connections[head][i].first].first = cost + connections[head][i].second;
                    que.push({connections[head][i].first, distancesAndParent[connections[head][i].first].first});
                    distancesAndParent[connections[head][i].first].second = head;
                }
            }
        }
    }

    return distancesAndParent;

}

int main() {

    int n,m,a,b,c,x,y,cost;
    in>>n>>m>>a>>b>>c;
    connections.resize(n+1);

    for(int i=0;i<m;i++)
    {
        in>>x>>y>>cost;
        connections[x].push_back({y,cost});
        connections[y].push_back({x,cost});
    }

   /* for(int i=0;i<connections.size();i++)
        for(int j=0;j<connections[i].size();j++)
            cout<<i<<" "<<connections[i][j].first<<" "<<connections[i][j].second<<endl;
*/
    vector<pair<long long,int>> costsAndPathFromA;
    vector<pair<long long,int>> costsAndPathFromB;
    vector<pair<long long, int>> costsAndPathFromC;

    costsAndPathFromA = dijk(a);
    costsAndPathFromB = dijk(b);
    costsAndPathFromC = dijk(c);


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
    findPath(nodeX,a,costsAndPathFromA);
    findPath(nodeX,b,costsAndPathFromB);
    findPath(nodeX,c,costsAndPathFromC);


    return 0;
}

