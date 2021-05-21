#include "graph.hpp"

int main(){
 int n,m;
 std::cin>>n>>m;
 std::vector< std::vector< bool > > E( n , std::vector< bool > ( n , false ) );
 for( int i = 0 ; i < m ; i++ ){
  int u,v;
  std::cin>>u>>v;
  E[u][v] = E[v][u] = true;
 }
 graph g( E );
 std::cout<<g.Cert1()<<std::endl;

 /*
 std::map< int , std::set< int > > A;
 A[0].insert( 0 );
 for(int i = 1 ; i <= 7 ; i++ ) A[1].insert( i );

 
 std::map< int , std::set<int> > B = g.REFINE(A);
 print_partition( B );
 */
 return 0;
}

