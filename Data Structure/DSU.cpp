#include <bits/stdc++.h>
using namespace std;
int parent[100002],size[100002];
void Make_set(int  v)
{
    parent[v] = v;
    size[v]=1;

}
int find(int v)
{
    if(v == parent[v])
        return  v;
    return parent[v]=find(parent[v]);
}
void Union(int a,int b)
{
    a= find(a);
    b= find(b);
    //  printf("  %c   %c ",a,b );
    if(a!=b)
    {
        if(size[a] < size[b])
            swap(a,b);

        parent[b] = a;
        size[a]+=size[b];

    }


}
int main(){
    int T,n,x,y,cont1,cont2;
    char c;
    string s;

    scanf("%d",&T);

    for(int tc=1;tc<=T;tc++){
        scanf("\n%d\n",&n);

        for(int i=1;i<=n;i++) Make_set(i);

        cont1=cont2=0;

        while(1){
            if(!getline(cin,s) || s.empty()) break;
            sscanf(s.c_str(),"%c %d %d",&c,&x,&y);

            if(c=='c') Union(x,y);
            else find(x)==find(y)? cont1++:cont2++;
        }

        if(tc!=1) printf("\n");
        printf("%d,%d\n",cont1,cont2);
    }

    return 0;
}
/*2
10
c 1 5
c 2 7
q 7 1
c 3 9
q 9 6
c 2 5
q 7 5
1
q 1 1
c 1 1
q 1 1*/