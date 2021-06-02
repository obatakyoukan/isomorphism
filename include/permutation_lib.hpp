
#include "permutation.hpp"
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


