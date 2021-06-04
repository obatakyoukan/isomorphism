#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include <vector>
#include <cassert>
#include <string>
#include "permutation_function.hpp"

class permutation {
 public:
 //private:
  int n;
  std::vector<int> p;
  std::string str;
 public:
  permutation() {}
  permutation(int n ) : n( n ),p(n) { str = arraytostring(); }
  permutation( std::vector<int> p ) : n( p.size() ), p ( p ) { str = arraytostring(); }
  permutation( std::string str ){
   p = permutation_function::stringtoarray( str );
   n = p.size();
   str = arraytostring();
  }

  permutation mult( permutation& b );
  permutation inv();
  std::string arraytostring();

  bool operator < ( const permutation& b ) const {
   if( n != b.n ) {
    return n < b.n;
   }
   return str < b.str;
  }
  bool operator == ( const permutation& b ) const {
   return str == b.str;
  }
  bool operator != ( const permutation& b ) const {
   return str != b.str;
  }
};

permutation permutation::mult(permutation& b) {
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


#endif
