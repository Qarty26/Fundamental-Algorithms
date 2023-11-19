#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream in("rusuoaica.in");
ofstream out("rusuoaica.out");

vector<int> parent;

struct edge
{
    int startNode,endNode,cost;

}edges[400001];

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

bool compare(edge a, edge b)
{
    return a.cost < b.cost;
}

int main()
{
    int n,M,m=0,a,x,y,costEdge;
    int totalCost = 0;
    in>>n>>M>>a;

    for(int i=0;i<M;i++)
    {
        in>>x>>y>>costEdge;
        if(costEdge>a)
            totalCost-=costEdge;
        else
            {
                edges[m].startNode = x;
                edges[m].endNode = y;
                edges[m].cost = costEdge;
                m++;
            }

    }

    sort(edges, edges+m,compare);


    for(int i=0;i<=n;i++)
        parent.push_back(i);


    int used=0;
    for(int i=0;i<m;i++)
        if(findParent(edges[i].startNode) != findParent(edges[i].endNode))
        {
            totalCost+=edges[i].cost;
            used+=1;
            unionParents(edges[i].startNode,edges[i].endNode);
        }
        else
            totalCost-=edges[i].cost;

    totalCost += a*(n-used-1);

    out<<totalCost;


    return 0;
}
