#ifndef PERMUTATION_FUNCTION_HPP
#define PERMUTATION_FUNCTION_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>


namespace permutation_function {
 std::vector< int > stringtoarray( std::string C );
};

std::vector< int > permutation_function::stringtoarray( std::string C ){
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
#endif
