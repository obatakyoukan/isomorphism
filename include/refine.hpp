

#include "graph_lib.hpp"

// Algorithm 7.5
std::map<int, std::set< int > > graph::REFINE( std::map<int, std::set< int > > &A ){
 std::map<int, std::set<int> > B = A;
 std::map<int, std::set<int> > S;
 for( auto i : B ){
  S[ B.size() - 1 - i.first ] = i.second;
 }

 std::set< int > U , T;
 for( auto v : V ) U.insert( v );
 int N = B.size();
 while( N != 0 ){
  N--;
  T = S[ N ];
  if( SetInclude( T , U ) ){
   SetDelete( U , T );
   int j = 0;
   while( j < B.size() and B.size() < n ){
    if( B.size() != 1 ) SpritAndUpdate( B , j , N , U ,S ,T );
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

//Algorithm 7.6
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




