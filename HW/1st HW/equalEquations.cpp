#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    int doFind(int x, vector<int> &parent)
    {
        while(parent[x]!=x)
            x = doFind(parent[x],parent);

        return x;
    }

    vector<int> doUnion(int a, int b,vector<int>& parent)
    {
        int ua = doFind(a,parent);
        int ub = doFind(b,parent);

        parent[ua] = ub;

        return parent;
    }

    bool equationsPossible(vector<string>& equations)
    {
        vector<int> parent(26);
        int a,b;

        for(int i=0;i<26;i++)
            parent[i]=i;

        for(int i=0;i<equations.size();i++)
            if (equations[i][1]== '=')
            {
                a = equations[i][0] - 'a';
                b = equations[i][3] - 'a';
                parent = doUnion(a,b,parent);
            }

        for(int i=0;i<equations.size();i++)
            if (equations[i][1]== '!')
            {
                a = equations[i][0] - 'a';
                b = equations[i][3] - 'a';

                if(doFind(a,parent) == doFind(b,parent))
                    return false;
            }
        return true;

    }
};

int main()
{

    Solution s;
    vector<string> eq {"a==b","b!=a"};
    cout<<s.equationsPossible(eq);
    return 0;
}
