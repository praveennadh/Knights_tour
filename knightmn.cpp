//FOR 0,0 as start


#include<bits/stdc++.h>
#include<fstream>
using namespace std;

    int n,m;
    ofstream outputFile("bug.txt");
class coor{
    public:
    int x;
    int y;
    vector<coor*> adj;
};
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
void erase(coor* c1,coor* c2)
{
    coor* cadj1;
    coor* cadj2;
    for(auto x:c1->adj)
    if(x!=c2)
    cadj1=x;
    for(auto x:c2->adj)
    if(x!=c1)
    cadj2=x;
    c1->adj={cadj1};
    c2->adj={cadj2};
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
int cnt=0;
void dfs2(vector<vector<int>> &v1,coor* c1)
{
    if(cnt==m*n*64)
    return;
    cnt++;
    v1[c1->x][c1->y]=1;
    outputFile<<c1->x<<" "<<c1->y<<" "<<cnt<<endl;
    if(v1[c1->adj[0]->x][c1->adj[0]->y]==0)
    {
        dfs2(v1,c1->adj[0]);
    }
    else
    {
        dfs2(v1,c1->adj[1]);
    }
}
int main()
{
    int mark[8][8]={{0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}};
    dfs(mark,1,1);
    cin>>m>>n;
    coor* mat[8*m][8*n];
    for(int i=0;i<8*m;i++)
    for(int j=0;j<8*n;j++)
    {
        mat[i][j]=new coor();
        mat[i][j]->x=i;
        mat[i][j]->y=j;
    }
    int ctr=0;
    for(int k1=0;k1<m;k1++)
    for(int k=0;k<n;k++)
    for(int i=0;i<64;i++)
    {
        //cout<<res[i].first<<','<<res[i].second<<" "<<res[(i+63)%64].first<<','<<res[(i+63)%64].second<<endl;
        mat[res[i].first+k1*8][res[i].second+k*8]->adj.push_back(mat[res[(i+63)%64].first+k1*8][res[(i+63)%64].second+k*8]);
        ctr++;
        mat[res[(i+63)%64].first+k1*8][res[(i+63)%64].second+k*8]->adj.push_back(mat[res[i].first+k1*8][res[i].second+k*8]);
    }
    cout<<ctr;
    for(int k1=0;k1<m;k1++)
    for(int k=1;k<n;k++)
    {
        erase(mat[k1*8+6][8*k+1],mat[k1*8+4][8*k]);
        erase(mat[k1*8+7][8*(k-1)+7],mat[k1*8+5][8*(k-1)+6]);
        mat[k1*8+6][8*k+1]->adj.push_back(mat[k1*8+7][8*(k-1)+7]);
        mat[k1*8+7][8*(k-1)+7]->adj.push_back(mat[k1*8+6][8*k+1]);
        mat[k1*8+4][8*k]->adj.push_back(mat[k1*8+5][8*(k-1)+6]);
        mat[k1*8+5][8*(k-1)+6]->adj.push_back(mat[k1*8+4][8*k]);
    }
    for(int k=1;k<m;k++)
    {
        erase(mat[8*k+0][7],mat[8*k+1][5]);
        erase(mat[8*(k-1)+6][6],mat[8*(k-1)+7][4]);
        mat[8*k+0][7]->adj.push_back(mat[8*(k-1)+6][6]);
        mat[8*(k-1)+6][6]->adj.push_back(mat[8*k+0][7]);
        mat[8*k+1][5]->adj.push_back(mat[8*(k-1)+7][4]);
        mat[8*(k-1)+7][4]->adj.push_back(mat[8*k+1][5]);
    }
    vector<int> v1(8*n,0);
    vector<vector<int>> mark1(8*m,v1);
    for(int i=0;i<8*m;i++)
    {for(int j=0;j<8*n;j++)
    {
        if(mat[i][j]->adj[0]==mat[i][j]->adj[1])
        cout<<"x"<<endl;
    }}
    dfs2(mark1,mat[0][0]);
    /*for(auto x:mat[7][7]->adj)
    cout<<x->x<<" "<<x->y<<endl;
    for(auto x:mat[5][6]->adj)
    cout<<x->x<<" "<<x->y<<endl;*/
}