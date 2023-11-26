#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream in("dragoni.in");
ofstream out("dragoni.out");

int dmax[1000];
vector<vector<pair<int,int>>> connections;

int p1(int start)
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

int p2(int start,int n)
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
}

int main()
{
    int p,n,m,a,b,d;
    in>>p>>n>>m;

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
        out<<p1(1);
    else
        out<<p2(1,n);


    return 0;
}
