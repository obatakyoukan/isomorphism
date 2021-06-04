

#include <iostream>
#include <vector>

struct Vector {
 std::vector< int > a;
 Vector() {}
 Vector( std::vector< int > &_a ) : a(_a) {}
 bool operator < ( const Vector& b ) const {
  for( int i = 0 ; i < a.size() ; i++ )
   if( a[i] != b.a[i] ) return a[i] < b.a[i];
  return a[0] < b.a[0];
 }
 bool operator == ( const Vector& b ) const {
  if( a.size() != b.a.size() ) return false;
  for( int i = 0 ; i < a.size() ; i++ )
   if( a[i] != b.a[i] ) return false;
  return true;
 }
 void print() {
  for( int i = 0 ; i < a.size() ; i++ ){
   if( i != 0 ) std::cout<<' ';
   std::cout<<a[i];
  }
  std::cout<<std::endl;
 }
};


