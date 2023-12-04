#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
class DSU //used for union find methods
{
    int size; //number of nodes
    vector<int> parent; //parents of the nodes
    vector<int> sizeComponent; //the size (number of conected nodes) of a component

public:

//----------------- CONSTRUCTOR --------------
    DSU(int size)
    {
        this-> size = size;
        for(int i=0;i<=size;i++)
        {
            parent.push_back(i);
            sizeComponent.push_back(1);
        }
    }
//-------------- END CONSTRUCTOR --------------

    int findParent(int node)
    {
        if (parent[node] == node) return node;

        // find the root node and do compression
        int result = findParent(parent[node]);
        parent[node] = result;
        return result;
    }

    void unionParents(int a, int b) //basic union function
    {
        int ua = findParent(a);
        int ub = findParent(b);

        if(ub == ua)
            return;

        parent[ua] = ub;
    }

     void unionWithSize(int node1, int node2) //union function with component size
     {
         node1 = findParent(node1);
         node2 = findParent(node2);

         if (node1 == node2)
             return;

         sizeComponent[node1] += sizeComponent[node2];
         parent[node2] = node1;
     }
 //-------------------GETTERS---------------------
     int getSizeComponent(int index) const
     {
         return this->sizeComponent[index];
     }
};
class Solution {

public:
    static bool compareDistance(const vector<int>& vect1, const vector<int>& vect2) {
        return vect1[2] < vect2[2];
    }

    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries)
    {
        vector<bool> result(queries.size(), false);
        DSU dsu(n);

        sort(edgeList.begin(), edgeList.end(), compareDistance);

        for(int i=0;i<queries.size();i++)
            queries[i].push_back(i);

        sort(queries.begin(), queries.end(), compareDistance);
        int CurrentEdge = 0;

        for(int i=0;i<queries.size();i++)
        {
            int limit = queries[i][2];

            while(CurrentEdge < edgeList.size() && edgeList[CurrentEdge][2] < limit)
            {
                dsu.unionParents(edgeList[CurrentEdge][0],edgeList[CurrentEdge][1]);
                CurrentEdge++;
            }

            if(dsu.findParent(queries[i][0]) == dsu.findParent(queries[i][1]))
                result[queries[i][3]] = true;
        }


        return result;

    }
};

int main() {

    Solution s;
    vector<vector<int>> EdgeList = {{0,1,10},{1,2,5},{2,3,9},{3,4,13}};
    vector<vector<int>> queries = {{0,4,14},{1,4,13}};

    s.distanceLimitedPathsExist(5,EdgeList,queries);
    return 0;
}
