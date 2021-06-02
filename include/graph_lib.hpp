
#include "graph.hpp"
//Algorithm 7.1
std::map< std::tuple<int,Vector> , std::vector<int> > graph::getPartitions() {
 std::map< std::tuple<int, Vector > , std::vector<int> > res;
 for(int i = 0 ; i < n ; i++ ) {
  int d1 = getdeg(i);
  std::vector< int > d2( n , 0 );
  for( int j = 0 ; j < n ;  j ++ ) {
   if( is_edge( i, j ) ) d2[ getdeg(j) ]++;
  }
  Vector d2v( d2 );
  res[ std::tie( d1 , d2v ) ].push_back( i );
 }
 return res;
}

bool graph::is_edge(int x,int y ) { return g[x][y]; }
bool graph::is_edge_x(int i,int j ) { return g[V[i]][V[j]]; }
bool graph::compare( graph& G ) {
 if( n != G.n ) return false;
 for( int i = 0 ; i < n ; i++ ){
  for( int j = 0 ; j < n ; j++ ){
   if( is_edge_x( i , j ) != G.is_edge_x( i , j ) ) return false;
  }
 }
 return true;
}

void graph::make_deg() {
 deg = std::vector< int > ( n , 0 );
 for(int i = 0 ; i < n ; i++ )
  for( int j = 0 ; j < n ; j++)
   if( is_edge_x( i , j ) ) deg[i]++;
}
void graph::print_V() {
 for(int i = 0 ; i < n ; i++ ) {
  if( i != 0 ) std::cout<<' ';
  std::cout<<V[i];
 }
 std::cout<<std::endl;
}
void graph::print_V_alphabet() {
 for(int i = 0 ; i < n ; i++ ) {
  if( i != 0 ) std::cout<<' ';
  std::cout<<(char)('a'+V[i]);
 }
 std::cout<<std::endl;
}
void graph::print_G() {
 for(int i = 0 ; i < n ; i++ ){
  for(int j = 0 ; j < n ; j++ ){
   if( j != 0 ) std::cout<<' ';
   std::cout<<is_edge_x(i,j) ? 1 : 0;
  }
  std::cout<<std::endl;
 }
}
void graph::print() {
 print_V();
 print_G();
}

void print_partition( std::map<int , std::set<int> > &A ){
 std::cout<<"[";
 for( auto i : A ){
  std::cout<<"{ ";
  for( auto j : i.second ) std::cout<<j<<" ";
  std::cout<<"} ";
 }
 std::cout<<"]"<<std::endl;
}

