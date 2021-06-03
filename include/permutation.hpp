#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <stack>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

//String to permutation
std::vector< int > stringtoarray( std::string C );
//構造体の宣言
struct permutation {
 int n;
 std::vector<int> p;
 std::string str; // 辞書順のために作成
 permutation() {}

 permutation(int  n ) : n( n ) , p( n ) { str = arraytostring();} 
 permutation( std::vector<int> p ) : n( p.size() ) , p( p ) { str = arraytostring(); }
 permutation( std::string _str ) {
  p = stringtoarray( _str );
  n = p.size();
  str = arraytostring();
 }

 permutation mult(permutation b);// a[ b [i] ]
 permutation inv();
 std::string arraytostring();
 

 bool operator < (const permutation b ) const {
  if( n != b.n ) {
   std::cerr<<"Size different"<<std::endl;
   return n < b.n;
  }
  return str < b.str;
 }
 bool operator == (const permutation b ) const {
  return str == b.str;
 }
 bool operator != (const permutation b ) const {
  return str != b.str;
 }

};
//関数の宣言
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




