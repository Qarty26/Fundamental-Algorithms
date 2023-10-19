#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {

        int culori[n+1],i,m;
        m=n;
        queue<int> coada;
        for(i=1;i<=n;i++)
            culori[i]=0;
if(n>1){
        coada.push(dislikes[0][0]);
        culori[coada.front()]=1;

while(m>0)
{
    //cout<<"New while, front is"<<coada.front()<<endl;

        for(i=0;i<dislikes.size();i++)
        {
            if(coada.front() == dislikes[i][0])
           {
                if(culori[dislikes[i][1]]==0)
                {
                    coada.push(dislikes[i][1]);
                    //cout<<"Added "<<dislikes[i][1]<<endl;
                    if(culori[coada.front()]==1) culori[dislikes[i][1]]=2;
                        else culori[dislikes[i][1]]=1;
                }

                else if(culori[dislikes[i][1]]==culori[coada.front()])
                {
                    //cout<<"Am crapat, cumva..";
                    return false;
                }

           }


            if(coada.front() == dislikes[i][1])
           {
                if(culori[dislikes[i][0]]==0)
                {
                    coada.push(dislikes[i][0]);
                    //cout<<"Added "<<dislikes[i][0]<<endl;
                    if(culori[coada.front()]==1) culori[dislikes[i][0]]=2;
                        else culori[dislikes[i][0]]=1;
                }

                else if(culori[dislikes[i][0]]==culori[coada.front()])
                {
                    //cout<<"Am crapat, cumva..";
                    return false;
                }
           }
        }
        //cout<<"Removed "<<coada.front()<<endl;
        coada.pop();
        m--;
        //cout<<"m="<<m<<endl;

        if(coada.empty() && m!=0)
            for(i=1;i<=n;i++)
                if(culori[i]==0)
                {
                   coada.push(i);
                   break;
                }

}

       /* while(!coada.empty())
        {
            cout<<"("<<coada.front()<<","<<culori[coada.front()]<<") ";
            //cout<<coada.front()<<" ";
            coada.pop();
        }*/



    }
    return true;
    }

};

int main()
{
    Solution s;
    std::vector<std::vector<int>> dislikes = {};
    cout<<s.possibleBipartition(1,dislikes);
    return 0;
}


