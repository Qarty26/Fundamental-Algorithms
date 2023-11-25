#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream in("bile.in");
ofstream out("bile.out");

vector<int> root;
vector<int> sizeComponent;
bool checked[1000][1000];
vector<int> result;

int findRoot(int node)
{
    if(root[node] == node)
        return node;

    return root[node] = findRoot(root[node]);
}

void unionn(int node1, int node2)
{
    node1 = findRoot(node1);
    node2 = findRoot(node2);

    if (node1 == node2)
        return;

    sizeComponent[node1] += sizeComponent[node2];
    root[node2] = node1;
}
/*
int getMax(int size)
{
    int maxx = 0;
    for(int node=0;node<size;node++)
        if(root[node] == node && sizeComponent[node] > maxx)
            maxx = sizeComponent[node];

    return maxx;
}
*/

bool inMatrix(int n, pair<int,int> coord, pair<int,int> directions)
{
    if(0 <= coord.first + directions.first && coord.first + directions.first < n &&
        0 <= coord.second + directions.second && coord.second + directions.second < n)
        return true;
    return false;
}

int main() {

    int n;
    int maxim = 1;
    in>>n;

    vector<pair<int,int>> coordBila(n*n+1);
    vector<pair<int,int>> directions {{0,1},{0,-1},{1,0},{-1,0}};
    for(int i=0;i<n*n;i++)
    {
        in>>coordBila[i].first>>coordBila[i].second;
        coordBila[i].first--;
        coordBila[i].second--;
        root.push_back(i);
        sizeComponent.push_back(1);
    }

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

                unionn(x * n + y,line * n + column );
            }
        }
        checked[coordBila[i].first][coordBila[i].second] = true;
        maxim = max(maxim,sizeComponent[x*n+y]);
        result.push_back(maxim);
    }

    for(int i=result.size()-2;i>=0;i--)
        out<<result[i]<<endl;

    return 0;
}
