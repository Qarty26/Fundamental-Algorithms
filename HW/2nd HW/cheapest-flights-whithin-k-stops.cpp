#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        vector<vector<pair<int,int>>> connections(n);
        queue<pair<int,pair<int,int>>> que;
        vector<int> costs(n,100001);

        for(int i=0;i<flights.size();i++)
            connections[flights[i][0]].push_back({flights[i][1],flights[i][2]});

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
                for(int i=0;i<connections[destination].size();i++)
                    if(cost + connections[destination][i].second < costs[connections[destination][i].first])
                    {
                        costs[connections[destination][i].first] = cost + connections[destination][i].second;
                        que.push({stops+1,{connections[destination][i].first,costs[connections[destination][i].first]}});
                    }
            }
            else
                break;
        }


        if (costs[dst] == 100001)
            return -1;
        return costs[dst];
    }
};

int main()
{
    Solution s;
    vector<vector<int>> flights = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    cout<<s.findCheapestPrice(4,flights,0,3,1);
    return 0;
}
