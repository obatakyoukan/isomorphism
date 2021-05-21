#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <stack>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

//String to permutation
std::vector< int > stringtoarray( std::string C );
//構造体の宣言
struct permutation {
 int n;
 std::vector<int> p;
 std::string str; // 辞書順のために作成
 permutation() {}

 permutation(int  n ) : n( n ) , p( n ) { str = arraytostring();} 
 permutation( std::vector<int> p ) : n( p.size() ) , p( p ) { str = arraytostring(); }
 permutation( std::string _str ) {
  p = stringtoarray( _str );
  n = p.size();
  str = arraytostring();
 }

 permutation mult(permutation b);// a[ b [i] ]
 permutation inv();
 std::string arraytostring();
 int test( std::vector< std::set< permutation > > &G);

 bool operator < (const permutation b ) const {
  if( n != b.n ) {
   std::cerr<<"Size different"<<std::endl;
   return n < b.n;
  }
  return str < b.str;
 }
 bool operator == (const permutation b ) const {
  return str == b.str;
 }
 bool operator != (const permutation b ) const {
  return str != b.str;
 }

};
//関数の宣言
std::set< permutation > simplegen( int n , std::set< permutation > &Gamma );
void run(int n,  std::vector< std::set< permutation > > &G , std::function<void(bool&)> use );
void runbacktrack(int n, int l, std::vector< std::set< permutation > > &G, permutation g , std::function<void(bool&)> use , bool& DoneEarly);
void List( int n , std::vector< std::set< permutation > > &G );


permutation permutation::mult(permutation b) {
 assert( n == b.n );
 std::vector<int> c( n );
 for( int i = 0 ; i < n ; i++ ){
  c[i] = p[ b.p[i] ];
 }
 return permutation( c );
}

permutation permutation::inv() {
 std::vector<int> c( n );
 for( int i = 0 ; i < n ; i++ ){
  c[ p[i] ] = i;
 }
 return permutation( c );
}

std::string permutation::arraytostring() {
 std::vector<bool> P(n,true);
 std::string C = "";
 for( int i = 0 ; i < n ; i++ ){
  if( P[i] ){
   //if( i != 0 ) C += " ";
   C += "(";
   C += std::to_string( i );
   P[i] =  false;
   int j = i;
   while( P[ p[j] ] ){
    C += ",";
    j = p[j];
    C += std::to_string( j );
    P[j] = false;
   }
   C += ")";
  }
 }
 return C;
}

int permutation::test( std::vector< std::set< permutation > > &G ){
 for(int i = 0 ; i < n ; i++ ){
  int x = p[i];
 }
 return n;
}


void run( int n ,std::vector< std::set< permutation > > &G , std::function< void(bool&) > use ){
 bool DoneEarly = false;
 std::vector< int > Ip(n);
 iota( Ip.begin() , Ip.end() , 0 );
 permutation I( Ip );
 runbacktrack( n , 0 , G , I , use , DoneEarly );
}
void runbacktrack( int n , int l , std::vector< std::set< permutation > > &G, permutation g , std::function<void(bool&)> use , bool& DoneEarly ){
 if( DoneEarly ) return;
 if( l == n ) use(DoneEarly);
 else {
  for( auto h : G[l] ){
   permutation fl = g.mult( h );
   runbacktrack( n, l + 1 , G , fl , use , DoneEarly );
  }
 }
}


//関数の内容
std::vector< int > stringtoarray( std::string C ){
 int n = 0;
 for(int i = 0 ; i < C.size() ;  ){
  if( C[i] == '(' ){
   i++;
   int tmp = 0;
   while( i < C.size() and '0' <= C[i] and C[i] <= '9' ){
    tmp *= 10;
    tmp += C[i] - '0';
    i++;
   }
   n = std::max( n , tmp + 1 );
  }else if( C[i] == ',' ){
   i++;
   int tmp = 0;
   while( i < C.size() and '0' <= C[i] and C[i] <= '9' ){
    tmp *= 10;
    tmp += C[i] - '0';
    i++;
   }
   n = std::max( n , tmp + 1 );
  }else if( C[i] == ')' ){
   i++;
  }else {
   std::cerr<<"Formal err"<<std::endl;
   exit(1);
  }
 }
 std::vector< int > res( n );
 iota( res.begin() , res.end()  , 0 );
 int x,y,z;
 for(int i = 0 ; i < C.size() ;  ){
  if( C[i] == '(' ){
   i++;
   int tmp = 0;
   while( i < C.size() and '0' <= C[i] and C[i] <= '9' ){
    tmp *= 10;
    tmp += C[i] - '0';
    i++;
   }
   x = tmp;
   z = tmp;
  }else if( C[i] == ',' ){
   i++;
   int tmp = 0;
   while( i < C.size() and '0' <= C[i] and C[i] <= '9' ){
    tmp *= 10;
    tmp += C[i] - '0';
    i++;
   }
   y = tmp;
   res[ x ] = y;
   x = y;
  }else if( C[i] == ')' ){
   res[x] = z;
   i++;
  }else {
   std::cerr<<"Formal err"<<std::endl;
   exit(1);
  }
 }
 return res;
}

std::set< permutation > simplegen( int n , std::set< permutation > &Gamma ) {
 for( auto g : Gamma ) {
  if( n != g.n ) {
   std::cerr<<"Gamma Size is different from n"<<std::endl;
   exit(1);
  }
 }
 std::set< permutation > res;
 std::set< permutation > New;
 std::vector< int > I( n );
 iota( I.begin() , I.end() , 0 );
 New.insert( permutation( I ) );
 while( !New.empty() ){
  for(auto i : New ) res.insert( i );
  std::set< permutation > Last;
  Last.swap( New ); // Last <- New  and New <- 0
  for(auto g : Gamma ) {
   for( auto h : Last ) {
    permutation f = g.mult( h );
    auto it = res.find( f );
    if( it == res.end() ) {
     New.insert( f );
    }
   }
  }

 }
 return res;
}

