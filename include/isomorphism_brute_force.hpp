#ifndef ISOMORPHISM_BRUTE_FORCE_HPP
#define ISOMORPHISM_BRUTE_FORCE_HPP

#include <algorithm>
#include "graph.hpp"
#include "graph_lib.hpp"
#include "graph_print.hpp"

bool graph::compare( graph& G ){
 if( size() != G.size() ) return false;
 for( int i = 0 ; i < n ; i++ )
  for( int j = 0 ; j < n ; j++ )
   if( is_edge( V[i] , V[j] ) != G.is_edge( G.V[i] , G.V[j] ) )
    return false;
 return true;
}

bool graph::Isomorphism_Brute_Force( graph& G ) {
 bool res = false;
 do {
  if( compare( G ) ){
   G.print_V_alphabet();
   res = true;
   //return true;
  }

 } while( std::next_permutation( G.V.begin(), G.V.end() ) );
 return res;
}

#endif
