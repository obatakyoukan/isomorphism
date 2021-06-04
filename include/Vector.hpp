#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>

class Vector {
 private:
  std::vector<int> a;
 public:
  Vector() {}
  Vector( std::vector<int> &_a): a(_a) {}
  int size() { return a.size() ; }
  void push(int v) { a.push_back(v); }
  
  int& operator[](int);
  bool operator < ( const Vector& b ) const ;
  bool operator == ( const Vector& b ) const ;
  
  void print();
};

int& Vector::operator[](int i) {
 return a[i];
}

bool Vector::operator < ( const Vector& b ) const {
 for( int i = 0 ; i < a.size(); i++ )
  if( a[i] != b.a[i] ) return a[i] < b.a[i];
 return a[0] < b.a[0];
}
bool Vector::operator == ( const Vector& b ) const {
 if( a.size() != b.a.size() ) return false;
 for( int i = 0 ; i < a.size() ; i++ ) 
  if( a[i] != b.a[i] ) return false;
 return true;
}

void Vector::print() {
 for( int i = 0 ; i < a.size() ; i++ ) {
  if( i != 0 ) std::cout<<' ';
  std::cout<<a[i];
 }
 std::cout<<std::endl;
}


#endif
