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
    vector<int> distance(n,1e9);
    queue<pair<int,pair<int,int>>> que; //pair<current_node,pair<actual_distance, which_dragon>>
    que.push({start,{0,dmax[start]}});
    distance[start] = 0;

    while(!que.empty())
    {
        int current_node = que.front().first;
        int actual_distance = que.front().second.first;
        int which_dragon = max(que.front().second.second,dmax[current_node]);
        cout<<"head is"<<current_node<<endl;
        que.pop();

        for(int i=0;i<connections[current_node].size();i++)
        {
            if(connections[current_node][i].second <= which_dragon &&
            distance[connections[current_node][i].first] > actual_distance + connections[current_node][i].second)
            {
                cout<<"making node "<<connections[current_node][i].first<<" better"<<endl;
                cout<<distance[connections[current_node][i].first]<<" "<<actual_distance<<" "<<connections[current_node][i].second<<endl;
                
                distance[connections[current_node][i].first] = actual_distance + connections[current_node][i].second;
                cout<<"updated result: "<<distance[connections[current_node][i].first]<<endl;
                que.push({connections[current_node][i].first,{actual_distance + connections[current_node][i].second,which_dragon}});
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
    //else
        out<<p2(1,n);


    return 0;
}
