
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <numeric>
#include "CompResult.hpp"
#include "Vector.hpp"

class graph {
 private:
  int n;
  std::vector< std::vector< bool > > g;
  std::vector< int > deg;
 public:
  std::vector< int > V;
  graph() {}
  graph( int n );
  graph( std::vector< std::vector< bool > > &_g );
  
  int size();
  bool is_edge( int x, int y );
  void make_deg();
  int getdeg(int i );

  bool compare( graph& G);
  bool Isomorphism_Brute_Force( graph& G);
  
  //Algorithm 7.1
  std::map< std::tuple<int, Vector> , std::vector<int> > getPartitions();
  bool Isomorphism( graph& G );
  bool FindIsomorphism( int l , std::vector<int> &W , std::vector<int> &f, graph& G, std::vector< std::vector<int> > &X, std::vector< std::vector<int> > &Y);

  void print();
  void print_V();
  void print_V_alphabet();
  void print_G();

};

graph::graph( int n ): n(n) {
 V = std::vector<int> ( n );
 iota( V.begin() , V.end() , 0 );
 make_deg();
}

graph::graph( std::vector< std::vector< bool > > &_g) : g(_g) {
 n = g.size();
 V = std::vector<int> ( n );
 iota( V.begin() , V.end() , 0 );
 make_deg();
}

int graph::size() { return n; }
bool graph::is_edge( int x , int y ) { return g[x][y] ; }

void graph::make_deg() {
 deg = std::vector< int > ( n , 0 );
 for(int i = 0 ; i < n ; i++ )
  for(int j = 0 ; j < n ; j++ )
   if( is_edge( i , j ) ) deg[i]++;
}
int graph::getdeg(int i ) { return deg[i]; }



