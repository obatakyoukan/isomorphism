#ifndef PERMUTATION_LIBRARY_HPP
#define PERMUTATION_LIBRARY_HPP

#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <stack>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

#include "permutation.hpp"


namespace permutation_function {
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
 int test(int n , permutation &g,  std::vector< std::set< permutation > > &G);
 void print_G( int n , std::vector< std::set< permutation > > &G );

 void enter2( int n , permutation &g, permutation &beta, std::vector< std::set< permutation > > &G);
 int test2( int n , permutation &g, permutation &beta,  std::vector< std::set< permutation > > &G );
 void changebase( int n , permutation &beta, permutation &beta_dash , std::vector< std::set< permutation > > &G );

 //関数
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
  for( auto a : Gamma )  enter( n , a , G );
  return G;
 }

 int test( int n , permutation &g, std::vector< std::set< permutation > > &G ){
  for(int i = 0 ; i < n ; i++ ){
   int x = g.p[i];
   bool exits = false;
   for( auto h : G[i] ){
    if( h.p[i] == x ){
     permutation pi3 = ( h.inv() ).mult( g );
     g = pi3;
     exits = true;
     break;
    }
   }
   if( !exits ) return i;
  }
  return n;
 }

 void enter( int n , permutation &g, std::vector< std::set< permutation > > &G ){
  int i = test( n , g , G );
  if( i == n ) return;
  else {
   G[i].insert( g );
  }
  for( int j = 0 ; j <= i ; j++ )
   for( auto h : G[j] ){
    permutation f = g.mult( h );
    enter( n , f , G );
   }
 }

 int test2( int n , permutation &g, permutation &beta, std::vector< std::set< permutation > > &G ){
  for(int i = 0 ; i < n ; i++ ){
   int x = g.p[ beta.p[i] ];
   bool exits = false;
   for( auto h : G[i] ){
    if( h.p[ beta.p[i] ] == x ){
     permutation pi3 = ( h.inv() ).mult( g );
     g = pi3;
     exits = true;
     break;
    }
   }
   if( !exits ) return i;
  }
  return n;
 }

 void enter2( int n , permutation &g, permutation &beta, std::vector< std::set< permutation > > &G ){
  int i = test2( n , g , beta , G );
  if( i == n ) return;
  else {
   G[i].insert( g );
  }
  for( int j = 0 ; j <= i ; j++ )
   for( auto h : G[j] ){
    permutation f = g.mult( h );
    enter2( n , f , beta , G );
   }
 }

 void changebase( int n , permutation &beta, permutation &beta_dash, std::vector< std::set< permutation > > &G ){
  std::vector< std::set< permutation > > H(n);
  std::vector< int > Ip( n );
  iota( Ip.begin() , Ip.end() , 0 );
  permutation I(Ip);
  for( int i = 0 ; i < n ; i++ ) H[i].insert( I );

  for( int i = 0 ; i < n ; i++ ){
   for( auto g : G[i] ){
    enter2( n , g , beta_dash , H );
   }
  }
  G = H;
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

 void print_G( int n , std::vector< std::set< permutation > > &G ){
  for( int i = 0 ; i < n ; i++ ){
   std::cout<<"U[ "<< i <<" ]"<< std::endl;
   for( auto g : G[i] ) std::cout<<g.str<<std::endl;
  }
 }


};


#endif
