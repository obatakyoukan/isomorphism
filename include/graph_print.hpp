#ifndef GRAPH_PRINT_HPP
#define GRAPH_PRINT_HPP
#include "graph.hpp"

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
   std::cout<<is_edge(V[i],V[j]) ? 1 : 0;
  }
  std::cout<<std::endl;
 }
}

void graph::print() {
 print_V();
 print_G();
}


#endif
