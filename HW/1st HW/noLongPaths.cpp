#include <iostream>
#include<vector>
#include <queue>
//#include <fstream>
using namespace std;
//ifstream in("data.in");

class Solution
{
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

    vector<int> whichBipartite(int n, vector<vector<int>>& connect)
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
        return culori;
    }

    string noLongPaths(int n, vector<vector<int>>& connections)
    {
        vector<vector<int>> connect;
        vector<int> colors(n+1);
        string result = "";

        for(int i=0;i<=n;i++)
            connect.push_back({});
        for(int i=0;i<connections.size();i++)
        {
            connect[connections[i][0]].push_back(connections[i][1]);
            connect[connections[i][1]].push_back(connections[i][0]);
        }

        if(isBipartite(n,connect) == false)
            return "NO";
        else
        {
            colors = whichBipartite(n,connect);
            for(int i=0;i<connections.size();i++)
                if(colors[connections[i][0]]==1 && colors[connections[i][1]]==2)
                    result += "1";
                else
                    result += "0";

            return("YES\n" + result);

        }

    }
};

int main()
{
    Solution s;
    int noNodes, noEdges,aux1, aux2;
    vector<vector<int>> connections;

    cin>>noNodes>>noEdges;
    for(int i=0;i<noEdges;i++)
    {
        cin>>aux1>>aux2;
        connections.push_back({aux1,aux2});
    }
    cout<<s.noLongPaths(noNodes,connections);

    return 0;
}
/* testcase for file input
6 5
1 5
2 1
1 4
3 1
6 1
*/
