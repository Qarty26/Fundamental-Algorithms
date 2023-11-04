#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
//#include <fstream>
using namespace std;
//#ifstream in("data.in");

class Solution {
public:


    int minMaxDist(int n, vector<int>& marked, vector<vector<int>>& graph)
    {

        if(marked.size()==1)
            return 0;

        int distances[n + 1];
        memset(distances, 0, sizeof(distances));
        vector<vector<int>> connect(n + 1);
        queue<int> coada;




        for(int i=0;i<graph.size();i++)
        {
            connect[graph[i][0]].push_back(graph[i][1]);
            connect[graph[i][1]].push_back(graph[i][0]);
        }

        coada.push(marked[0]);
        while(!coada.empty())
        {
            for(int i=0;i<connect[coada.front()].size();i++)
            {
                int neighbour = connect[coada.front()][i];
                if(distances[neighbour]==0 && neighbour!=marked[0])
                {
                    coada.push(neighbour);
                    distances[neighbour] = distances[coada.front()] + 1;
                }

            }
            coada.pop();
        }



        int max_distance = 0;
        int st_extreme = -1;
        for(int i=0;i<marked.size();i++)
            if(distances[marked[i]]>max_distance)
            {
                max_distance = distances[marked[i]];
                st_extreme = marked[i];
            }


        memset(distances, 0, sizeof(distances));


        coada.push(st_extreme);
        while(!coada.empty())
        {
            for(int i=0;i<connect[coada.front()].size();i++)
            {
                int neighbour = connect[coada.front()][i];
                if(distances[neighbour]==0 && neighbour!=st_extreme)
                {
                    coada.push(neighbour);
                    distances[neighbour] = distances[coada.front()] + 1;
                }

            }
            coada.pop();
        }

        max_distance = 0;
        for(int i=0;i<marked.size();i++)
            if(distances[marked[i]]>max_distance)
                max_distance = distances[marked[i]];


        return ((max_distance+1)/2);

    }
};

int main()
{


    int noTests,n,spec,i,j,aux,aux2;
    vector<int> speciale;
    vector<vector<int>> graph;
    cin>>noTests;
    for(i=0;i<noTests;i++)
    {
        cin>>n>>spec;
        speciale.clear();
        graph.clear();

        for(j=0;j<spec;j++)
        {
            cin>>aux;
            speciale.push_back(aux);

        }

        for(j=0;j<n-1;j++)
        {
            cin>>aux>>aux2;
            graph.push_back({aux,aux2});
        }

        Solution s;

        cout<<s.minMaxDist(n,speciale,graph)<<endl;
    }

    return 0;
}

/*
testcase for file input
6
7 3
2 6 7
1 2
1 3
2 4
2 5
3 6
3 7
4 4
1 2 3 4
1 2
2 3
3 4
5 1
1
1 2
1 3
1 4
1 5
5 2
4 5
1 2
2 3
1 4
4 5
10 8
1 2 3 4 5 8 9 10
2 10
10 5
5 3
3 1
1 7
7 4
4 9
8 9
6 1
10 9
1 2 4 5 6 7 8 9 10
1 3
3 9
9 4
4 10
10 6
6 7
7 2
2 5
5 8
*/
