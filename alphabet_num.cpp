#include<bits/stdc++.h>
using namespace std;

int main(){
 int n,m;
 cin>>n>>m;
 cout<<n<<' '<<m<<endl;
 for(int i = 0 ; i< m ; i++ ){
  char u,v;
  cin>>u>>v;
  cout<<u-'a'<<' '<<v-'a'<<endl;
 }
 return 0;
}

