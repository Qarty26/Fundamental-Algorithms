#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream in("oracol.in");
ofstream out("oracol.out");



struct edge
{
    int startNode,endNode,cost;

};
vector<edge> edges;
vector<int> parent;

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
    int n,price;
    in>>n;
    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++)
        {
            in>>price;
            edges.push_back({i,j+1,price});
        }

    sort(edges.begin(), edges.end(),compare);

/*    for(int i=0;i<edges.size();i++)
        cout<<edges[i].startNode<<" "<<edges[i].endNode<<" "<<edges[i].cost<<endl;*/

    for(int i=0;i<=n;i++)
        parent.push_back(i);

    int totalCost = 0;
    for(int i=0;i<edges.size();i++)
        if(findParent(edges[i].startNode) != findParent(edges[i].endNode))
        {
            totalCost+=edges[i].cost;
            unionParents(edges[i].startNode,edges[i].endNode);
        }

    out<<totalCost;



    return 0;
}
