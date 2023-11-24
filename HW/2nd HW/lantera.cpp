#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
ifstream in("lanterna.in");
ofstream out("lanterna.out");

struct Edge
{
    int endNode;
    int time;
    int watt;
};

pair<int,int> dikj(int startn,int endn, vector<int>& base, vector<vector<Edge>>& connections, vector<pair<int,int>> nrBaterii)
{
    queue<Edge> que;
    que.push({startn,0,0});
    nrBaterii[startn] = {0,0};

    while(!que.empty())
    {
        int nod = que.front().endNode;
        int dist = que.front().time;
        int baterii = que.front().watt;
        que.pop();

        //cout<<"Nodul "<<nod<<endl;

        for(int i=0;i<connections[nod].size();i++)
        {
            //cout<<connections[nod][i].endNode<<": ";
            if(nrBaterii[ connections[nod][i].endNode ].first > connections[nod][i].time + dist)
            {
                //cout<<"update dist+bat";
                nrBaterii[ connections[nod][i].endNode ].first = connections[nod][i].time + dist;
                nrBaterii[ connections[nod][i].endNode ].second = connections[nod][i].watt + baterii;

                if(base[connections[nod][i].endNode] == 0)
                    que.push({connections[nod][i].endNode,connections[nod][i].time + dist,connections[nod][i].watt + baterii});
                else
                    que.push({connections[nod][i].endNode,connections[nod][i].time + dist,0});

            }
            else if(nrBaterii[ connections[nod][i].endNode ].first == connections[nod][i].time + dist &&
                    nrBaterii[ connections[nod][i].endNode ].second > connections[nod][i].watt + baterii)
            {
                //cout<<"update bat";
                nrBaterii[ connections[nod][i].endNode ].second = connections[nod][i].watt + baterii;
            }
            //else
            //cout<<"nimic";

            //cout<<endl;
        }
    }

    //cout<<nrBaterii[endn].first<<" "<<nrBaterii[endn].second;

    return nrBaterii[endn];
}

int main() {

    int n,k,m,x,y,t,w;


    in>>n>>k;

    vector<int> base(n+1);
    vector<pair<int,int>> nrBaterii(n+1,{5000,0});
    vector<vector<Edge>> connections(n+1);



    for(int i=1;i<=n;i++)
        in>>base[i];

    in>>m;
    for(int i=0;i<m;i++)
    {
        in>>x>>y>>t>>w;
        connections[x].push_back({y,t,w});
        connections[y].push_back({x,t,w});
    }

    int maxBetween = 0;
    int totalTime = dikj(1,n,base,connections,nrBaterii).first;
    int rawBattery = dikj(1,n,base,connections,nrBaterii).second;
    for(int i=1;i<=n;i++)
        if(base[i] == 1 & totalTime == dikj(1,i,base,connections,nrBaterii).first +
        dikj(i,n,base,connections,nrBaterii).first &&

        max(dikj(1,i,base,connections,nrBaterii).second,dikj(i,n,base,connections,nrBaterii).second)
        ==dikj(1,n,base,connections,nrBaterii).second)
        {
            if(dikj(1,i,base,connections,nrBaterii).second > maxBetween)
                maxBetween = dikj(1,i,base,connections,nrBaterii).second;
            if(dikj(i,n,base,connections,nrBaterii).second > maxBetween)
                maxBetween = dikj(i,n,base,connections,nrBaterii).second;

        }

    out<<totalTime<<" "<<max(rawBattery,maxBetween)<<endl;

    //cout<<dikj(1,4,base,connections,nrBaterii).first<<" "<<dikj(1,4,base,connections,nrBaterii).second<<endl;
    //cout<<dikj(4,n,base,connections,nrBaterii).first<<" "<<dikj(4,n,base,connections,nrBaterii).second<<endl;
    //cout<<dikj(1,n,base,connections,nrBaterii).first<<" "<<dikj(1,n,base,connections,nrBaterii).second<<endl;
    return 0;
}
