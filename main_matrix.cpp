#include "graph.hpp"

int main(){
 int n;
 std::cin>>n;
 std::vector< std::vector< bool > > E( n , std::vector< bool > ( n , false ) );
 for( int i = 0 ; i < n ; i++ ){
  for(int j = 0 ; j < n ; j++ ){
   int t;
   std::cin>>t;
   if( t == 1 ) E[i][j] = true;
  }
 }
 
 graph g( E );
 
 std::map< std::tuple< int , Vector > , std::vector<int> > X = g.getPartitions();
 std::cout<<"The Size of X is "<<X.size()<<std::endl;
 /*
 for( auto i : X ){
  int d;
  Vector D;
  std::tie( d , D ) = i.first;
  Vector V = Vector(i.second);

  std::cout<<"Degree: "<<d<<std::endl;
  //D.print();
  V.print();
 }
 */
 
 std::cout<<g.Cert4()<<std::endl;

 /*
 std::map< int , std::set< int > > A;
 A[0].insert( 0 );
 for(int i = 1 ; i <= 7 ; i++ ) A[1].insert( i );

 
 std::map< int , std::set<int> > B = g.REFINE(A);
 print_partition( B );
 */
 return 0;
}

