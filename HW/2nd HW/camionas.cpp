#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
ifstream in("camionas.in");
ofstream out("camionas.out");

int main()
{
    int n,m,g,x,y,w;

    in>>n>>m>>g;
    deque<int> deq;
    vector<int> toRaiseCumulative(n+1,50001);
    vector<vector<pair<int,int>>> edges(n+1);

    for(int i=0;i<m;i++)
    {
        in>>x>>y>>w;
        edges[x].push_back({y,w});
        edges[y].push_back({x,w});
    }



    int head;
    deq.push_front(1);
    toRaiseCumulative[1]=0;

    while(!deq.empty())
    {
        head = deq.front();
        deq.pop_front();

        for(int i=0;i<edges[head].size();i++)
            if(toRaiseCumulative[edges[head][i].first] - edges[head][i].second  > toRaiseCumulative[head])
            {
                if(edges[head][i].second >= g)
                {
                    toRaiseCumulative[edges[head][i].first] = toRaiseCumulative[head];
                    deq.push_front(edges[head][i].first);
                }
                else
                {
                    toRaiseCumulative[edges[head][i].first] = toRaiseCumulative[head]+1;
                    deq.push_back(edges[head][i].first);
                }
            }
    }

    cout<<toRaiseCumulative[n];

    return 0;
}
