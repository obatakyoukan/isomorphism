#include "graph.hpp"

int main(){
 int n,m;
 std::cin>>n>>m;
 std::vector< std::vector< bool > > E1( n , std::vector< bool > ( n , false ) );
 for( int i = 0 ; i < m ; i++ ){
  int u,v;
  std::cin>>u>>v;
  E1[u][v] = E1[v][u] = true;
 }
 graph g1( E1 );
 
 std::cin>>n>>m;
 std::vector< std::vector< bool > > E2( n , std::vector< bool > ( n , false ) );
 for( int i = 0 ; i < m ; i++ ){
  int u,v;
  std::cin>>u>>v;
  E2[u][v] = E2[v][u] = true;
 }
 graph g2( E2 );
 g1.Isomorphism(g2);
 //g1.Isomorphism_Brute_Force(g2);
 std::cout<<g1.Cert1()<<std::endl;
 std::cout<<g2.Cert1()<<std::endl;

 return 0;
}

