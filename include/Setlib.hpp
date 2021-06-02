#include <set>

bool SetInclude( std::set< int > &A , std::set< int > &B ); // A <= B
void SetDelete( std::set< int > &A, std::set< int > &B ); // A / B

bool SetInclude( std::set< int > &A, std::set< int > &B ){
 for( auto v : A )
  if( B.find( v ) == B.end() ) return false; //Bにない
 return true;
}

void SetDelete( std::set< int > &A, std::set< int > &B ){ // A / B
 for( auto i : B ) A.erase( i );
}


