#ifndef REFINE_HPP
#define REFINE_HPP
#include "graph.hpp"
#include "graph_lib.hpp"
#include "basic_function.hpp"

std::map< int, std::set<int> > graph::REFINE( std::map< int , std::set<int> > &A ){
 std::map< int , std::set<int> > B = A;
 std::map< int , std::set<int> > S;
 for( auto it : B )
  S[ B.size() - 1 - it.first ] = it.second;

 std::set< int > U , T;
 for( auto v : V ) U.insert( v );
 int N = B.size();
 while( N != 0 ) {
  N--;
  T = S[ N ];
  if( basic_function::SetInclude( T , U ) ){
   basic_function::SetDelete( U , T );
   int j = 0;
   while( j < B.size() and B.size() < n ){
    if( B.size() != 1 ) {
     SpritAndUpdate( B , j , N , U , S , T );
    }
    j++;
   }
   if( B.size() == n ) return B;
  }
 }
 return B;
}

void graph::SpritAndUpdate( std::map< int,std::set<int> > &B , int j , 
  int &N , std::set< int >  &U, std::map< int,std::set< int > > &S, std::set< int > &T ) {

 std::map<int, std::set<int> > L;
 for( auto u : B[j] ){
  int h = AbsAndSet( u , T );
  L[h].insert( u );
 }
 int m = 0;
 for(int h = 0 ; h < n ; h++ )
  if( L[h].size() != 0 ) m++;
 if( m > 1 ){
  for( int h = B.size() - 1 ; h > j ; h-- )
   B[ m - 1 + h ] = B[ h ];
  int k = 0;
  for( int h = 0 ; h < n ; h++ )
   if( L[h].size() != 0 ){
    B[ j + k ] = L[h];
    S[ N + m -1 -k ] = L[h];
    //S[ N + k ] = L[h];
    for( auto x : L[h] ) U.insert( x );
    k++;
   }
  j += m - 1;
  N += m;
 }

}

int graph::AbsAndSet( int u, std::set< int > &T ){
 int res = 0;
 for( int i = 0 ; i < n ; i++ ) 
  if( is_edge( u , i ) ) {
   auto it = T.find( i );
   if( it != T.end() ) res++; 
  }
 return res;
}

#endif
