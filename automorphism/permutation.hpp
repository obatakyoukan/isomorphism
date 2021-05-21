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
void run(int n,  std::vector< std::set< permutation > > &G ,
  std::function<void(permutation&,bool&)> use , bool &DoneEarly );
void runbacktrack(int n, int l, std::vector< std::set< permutation > > &G, 
  permutation &g , std::function<void(permutation&,bool&)> use , bool& DoneEarly);
void List( int n , std::vector< std::set< permutation > > &G );
void ListUse(permutation &g , bool &DoneEarly);
std::vector< std::set< permutation > > MakePermutationGroup( int n, std::set< permutation > &G );
std::vector< std::set< permutation > > gen( int n , std::set< permutation > &Gamma );
void enter( int n , permutation &g, std::vector< std::set< permutation > > &G);

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
  bool exits = false;
  for( auto h : G[i] ){
   if( h.p[i] = x ){
    permutation pi3 = ( h.inv() ).mult( *this );
    //for( int j = 0 ; j < n ; j++ ) this->p[j] = pi3[j];
    *this = pi3;
    exits = true;
   }
  }
  if( !exits ) return i;
 }
 return n;
}



void run( int n ,std::vector< std::set< permutation > > &G ,
  std::function< void(permutation&,bool&) > use, bool &DoneEarly ){
 std::vector< int > Ip(n);
 iota( Ip.begin() , Ip.end() , 0 );
 permutation I( Ip );
 runbacktrack( n , 0 , G , I , use , DoneEarly );
}
void runbacktrack( int n , int l , std::vector< std::set< permutation > > &G, 
  permutation &g , std::function<void(permutation&,bool&)> use , bool& DoneEarly ){
 if( DoneEarly ) return;
 if( l == n ) use(g,DoneEarly);
 else {
  for( auto h : G[l] ){
   permutation fl = g.mult( h );
   runbacktrack( n, l + 1 , G , fl , use , DoneEarly );
  }
 }
}
void List( int n , std::vector< std::set< permutation > > &G ){
 bool DoneEarly = false;
 run( n , G , ListUse , DoneEarly );
}
void ListUse( permutation &g, bool &DoneEarly ){
 std::cout<<g.str<<std::endl;
}
std::vector< std::set< permutation > > MakePermutationGroup( int n , std::set< permutation > &G ){
 std::vector< std::set< permutation > > Gi( n );// G , G_0 , G1 ,..., G_n-2
 std::vector< std::set< permutation > > U( n );
 Gi[0] = G;
 for( int i = 1 ; i < n ; i++ ){
  for( auto g : Gi[i-1] ){
   if( g.p[i-1] == i-1 ) Gi[i].insert( g );
  }
 }
 for( int i = 0 ; i < n ; i++ ){
  std::vector< bool > no_use( n , true );
  for( auto g: Gi[i] ){
   if( no_use[ g.p[i] ] ){
    U[i].insert( g );
    no_use[ g.p[i] ] = false;
   }
  }
 }
 return U;
}

std::vector< std::set< permutation > > gen( int n , std::set< permutation > &Gamma ){
 std::vector< int > Ip( n );
 iota( Ip.begin() , Ip.end() , 0 );
 permutation I( Ip );
 std::vector< std::set< permutation > > G(n);
 for(int i = 0 ; i < n ; i++ ) G[i].insert( I );
 for( auto a : Gamma ) enter( n , a , G );
 return G;
}

void enter( int n , permutation &g, std::vector< std::set< permutation > > &G ){
 int i = g.test( G );
 if( i == n ) return;
 else {
  std::cout<<i<<std::endl;
  std::cout<<g.str<<std::endl;
  G[i].insert( g );
 }
 for( int j = 0 ; j <= i ; j++ )
  for( auto h : G[j] ){
   permutation f = g.mult( h );
   enter( n , f , G );
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

