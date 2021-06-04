#ifndef ISOMORPHISM_HPP
#define ISOMORPHISM_HPP
#include "graph.hpp"
#include "graph_lib.hpp"

bool graph::FindIsomorphism( int l , std::vector< int > &W, std::vector< int > &f , graph& G, std::vector< std::vector<int> > &X, std::vector< std::vector<int> >  &Y ){
 if( l == n ) {
  for(int i  = 0 ; i < n ; i++ ) {
   if( i != 0 ) std::cout<<' ';
   std::cout<<char('a'+f[i]);
  }
  std::cout<<std::endl;
  return true;
 }
 int j = W[l];
 for( auto y : Y[j] ){
  bool ok = true;
  for( int u = 0 ; u < l ; u++ ){
   if( is_edge( u , l ) != G.is_edge( f[u] , y ) or f[u] == y ) ok = false; //or  f[u] == yを加えないと、同じ役割をする頂点が消える可能性がある。
  }
  if( ok ) {
   f[l] = y;
   if( FindIsomorphism( l + 1 , W , f , G , X, Y ) ) return true;
  }
 }
 return false;
}

bool graph::Isomorphism( graph& G ) {
 std::map< std::tuple<int , Vector> , std::vector<int> > X = getPartitions();
 std::map< std::tuple<int , Vector> , std::vector<int> > Y = G.getPartitions();
 if( n != G.size() ) return false;
 //if( n != G.n ) return false;
 if( X.size() != Y.size() ) return false;// G1 and G2 are not isomorphic
 for( auto i : X ) {
  if( i.second.size() != Y[ i.first ].size() ) return false;
 }
 // Order the partitions so that :
 // | X[i] | = | Y[i] | <= | X[i+1] | = Y[ i + 1 ] for all i
 
 std::vector< std::pair< int , std::tuple<int, Vector > > > Ordertmp;
 std::vector< std::vector< int > > XX;
 std::vector< std::vector< int > > YY;
 for( auto i: X ) Ordertmp.push_back( std::pair< int , std::tuple<int, Vector > >  ( i.second.size() , i.first ) );
 sort( Ordertmp.begin() , Ordertmp.end() );
 for( auto i : Ordertmp ){
  XX.push_back( X[ i.second ] );
  YY.push_back( Y[ i.second ] );
 }
 std::vector< int > W( n );
 int N = X.size();
 for( int i = 0 ; i < N ; i++ )
  for( auto x : XX[i] ) W[x] = i ;
 std::vector< int > f(n);
 iota( f.begin() , f.end() , 0 );
 return FindIsomorphism( 0 , W , f, G , XX , YY );
}

#endif
