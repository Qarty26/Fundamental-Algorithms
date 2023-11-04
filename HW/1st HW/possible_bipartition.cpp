#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:


    bool isBipartite(int n, vector<vector<int>>& connect)
    {
        queue<int> coada;
        vector<int> culori (n+1,0);
        int m=n;

        coada.push(connect[1][0]);
        culori[coada.front()]=1;

        while(m>0)
        {
            int head = coada.front();
            for(int i=0;i<connect[head].size();i++)
            {
                if(culori[connect[head][i]] == 0)
                {
                    coada.push(connect[head][i]);
                    culori[connect[head][i]] = 3 - culori[head];
                }
                else if(culori[head] == culori[connect[head][i]])
                    return false;

            }
            coada.pop();
            m--;

            if(coada.empty() && m!=0)
                for(int j=1;j<=n;j++)
                    if(culori[j]==0)
                    {
                       coada.push(j);
                       break;
                    }

        }
        return true;
    }



    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {

        int i;
        vector<vector<int>> connect;

        for(i=0;i<=n;i++)
            connect.push_back({});
        for(i=0;i<dislikes.size();i++)
        {
            connect[dislikes[i][0]].push_back(dislikes[i][1]);
            connect[dislikes[i][1]].push_back(dislikes[i][0]);
        }




        if(n>1)
            return isBipartite(n,connect);

        return true;
    }

};

int main()
{
    Solution s;
    std::vector<std::vector<int>> dislikes = {{1,2},{1,3},{2,4}};
    cout<<s.possibleBipartition(4,dislikes);
    return 0;
}


