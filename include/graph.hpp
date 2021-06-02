#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <string>
#include "permutation.hpp"


class graph {
 private:
  int n;//これは、publicかも? なぜかコンパイルエラー出ない?????
  std::vector< int > V;
  std::vector< std::vector<bool> > g;
  std::vector< int > deg;
 public:
  graph() {}
  graph( int n ) : n( n ) {
   g = std::vector< std::vector<bool> > ( n , std::vector<bool> ( n , false ) );
   V = std::vector< int > ( n );
   iota( V.begin() , V.end() , 0 );
   make_deg();
  }
  graph( std::vector< std::vector< bool > > &_g ) : g(_g) {
   n = g.size();
   V = std::vector< int > ( n );
   iota( V.begin() , V.end() , 0 );
   make_deg();
  }
  graph( std::vector< int > &_V, std::vector< std::vector< bool > > &_g ) : V(_V) , g(_g) {
   n = g.size();
   make_deg();
  }


  bool is_edge(int x , int y );//g[x][y]を返す．
  bool is_edge_x(int i, int j);//g[ V[i] ] [ V[j] ]
  bool compare( graph& G );
  bool Isomorphism_Brute_Force( graph& G );


  //Algorithm 7.1
  std::map< std::tuple<int, Vector>, std::vector<int> > getPartitions();
  bool Isomorphism( graph& G ); 
  bool FindIsomorphism( int l, std::vector<int> &W, std::vector<int> &f, graph& G ,
    std::vector< std::vector< int > > &X , std::vector< std::vector<int> > &Y);

  //Algorithm 7.5
  std::map<int, std::set< int > > REFINE( std::map<int, std::set< int > > &A );
  void SpritAndUpdate( std::map<int, std::set< int > > &B , int j , 
    int &N , std::set< int > &U, std::map<int, std::set< int > > &S, std::set< int > &T);
  int AbsAndSet( int u , std::set< int > &T );// | T and N_g(u) |
  CompResult Compare( std::vector< int > &mu , std::vector< int > &pi, int l ); //Algorithm 7.6
  
  void Canon1( std::map< int , std::set<int> > &P, std::vector<int> &mu, bool &BestExist );//Algorithm 7.7
  std::string Cert1(); //Algorithm 7.8
  void Canon2( permutation &beta, std::vector< std::set< permutation > > &G, 
    std::map< int , std::set<int> > &P, std::vector<int> &mu , bool &BestExist );//Algorithm 7.9
  std::string Cert2();//Algorithm 7.10
  std::string Cert3();
  std::string Cert4();

  void make_deg();
  int getdeg(int i) { return deg[i]; } 

  void print();
  void print_V();
  void print_V_alphabet();
  void print_G();
};

void print_partition( std::map< int , std::set< int > > &A );


