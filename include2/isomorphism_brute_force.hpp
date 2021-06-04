

#include "graph_lib.hpp"

bool graph::Isomorphism_Brute_Force( graph& G ) { //Brute Force algorithm 
 bool res = false;
 do {
  if( compare( G ) ){
   G.print_V_alphabet();
   res = true;
   //return true; 
  }
 } while( std::next_permutation( G.V.begin() , G.V.end() ) );
 return res;
}



