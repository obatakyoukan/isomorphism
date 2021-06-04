#ifndef GRAPH_LIB_HPP
#define GRAPH_LIB_HPP

#include "graph_lib.hpp"

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

CompResult graph::Compare( std::vector< int > &mu , std::vector< int > &pi, int l ){
 for(int j = 1 ; j < l ; j++ ){
  for(int i = 0; i < j ; i++ ){
   int x = is_edge( mu[i], mu[j] ) ? 1 : 0;
   int y = is_edge( pi[i], pi[j] ) ? 1 : 0;
   if( x < y ) return CompResult::Worse;
   if( x > y ) return CompResult::Better;
  }
 }
 return CompResult::Equal;
}

#endif
