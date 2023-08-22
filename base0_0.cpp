//FOR 0,0 as start


#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int dirx[]={1,1,2,2,-1,-1,-2,-2};
int diry[]={2,-2,1,-1,2,-2,1,-1};
vector<pair<int,int>> res;
int ctr=0;
int max(int a,int b)
{
    if(a>=b)
    return a;
    return b;
}
void dfs(int mark[][8],int i,int j)
{
    mark[i][j]=1;
    res.push_back({i,j});
    if(res.size()==64)
    {
        return;
    }
    for(int k=0;k<8;k++)
    {
        if(i+dirx[k]<8&&i+dirx[k]>=0&&j+diry[k]<8&&j+diry[k]>=0&&mark[i+dirx[k]][j+diry[k]]==0)
        {
            dfs(mark,i+dirx[k],j+diry[k]);
            if(res.size()==64)
            {
                return;}
        }
    }
    res.pop_back();
    mark[i][j]=0;
}
int main()
{
    ofstream outputFile("output.txt");
    // Check if the file is open
    if (!outputFile) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
    int mark[8][8]={{0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}};
    dfs(mark,1,1);
    int ctr=1;
    for(int i=27;ctr<=64;i=(i+1)%64)
    {
        outputFile<<res[i].first<<" "<<res[i].second<<" "<<ctr<<endl;
        ctr++;
    }
}