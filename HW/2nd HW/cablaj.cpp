#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
ifstream in("cablaj.in");
ofstream out("cablaj.out");


int main()
{
    int n;
    double totalCost=0.0;
    int nextNode;
    in>>n;
    vector<pair<int, int>> coordinates(n+1);
    vector<int> visited(n+1,0);
    vector<double> minDist(n+1,30000* sqrt(2));

    for(int i=0;i<n;i++)
        in>>coordinates[i].first>>coordinates[i].second;

    minDist[0]=0.0;
    for(int i=1;i<n;i++)
        minDist[i] = sqrt(pow(coordinates[i].first - coordinates[0].first,2) + pow(coordinates[i].second - coordinates[0].second,2));
    visited[0]=1;


    for(int contor=1;contor<n;contor++) //in each loop we add a node do MST, we already have the node 0
    {
        nextNode=contor;
        double shortestEdge= 30000 * sqrt(2); //diagonal of the grid with max_length = 30000

        //minimum distance from any node in Mst to any unvisited node
        for(int node=1; node<=n; node++)
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
        for(int node=1;node<n;node++)
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

    out<<fixed<<setprecision(4)<<totalCost;

    return 0;
}
