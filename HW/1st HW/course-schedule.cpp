#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {

    int degr[numCourses+1];
    int i,ok=0;
    queue<int> coada;
    vector<int> sol;

    for(i=0;i<numCourses;i++)
        degr[i]=0;


    for(i=0;i<prerequisites.size();i++)
        degr[prerequisites[i][0]]++;

   // for(i=0;i<numCourses;i++)
    //    cout<<i<<degr[i]<<endl;

    //cout<<endl;

    if(prerequisites.size()==0)
        for(i=0;i<numCourses;i++)
            sol.push_back(i);
    else


    while(ok!=numCourses)
    {
        for(i=0;i<numCourses;i++)
            if(degr[i]==0)
            {
               coada.push(i);
               degr[i]=-1;
               //cout<<"Added "<<i<<endl;
            }

        //for(i=0;i<numCourses;i++)
          //  cout<<degr[i]<<" ";

        //cout<<endl;


       // cout<<coada.front()<<" conectat cu ";
        for(i=0;i<prerequisites.size();i++)
            if(prerequisites[i][1]==coada.front())
            {
                //cout<<prerequisites[i][0]<<" ";
                degr[prerequisites[i][0]]--;

            }
        //cout<<endl;

        if(!coada.empty())
        {
            sol.push_back(coada.front());
            coada.pop();
        }

        //cout<<"Delete "<<coada.front()<<endl;

        ok++;
    }

    for(i=0;i<sol.size();i++)
        cout<<sol[i]<<" ";

    if(sol.size()!=numCourses)
        return {};
    return sol;
    }
};

int main()
{

    Solution s;
    vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
    s.findOrder(4,prerequisites);

    return 0;
}
