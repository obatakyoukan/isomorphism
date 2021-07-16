#ifndef CERT1_HPP
#define CERT1_HPP
#include "graph.hpp"
#include "graph_lib.hpp"
#include "graph_print.hpp"
#include "refine.hpp"
#include "basic_function.hpp"
#include "CompResult.hpp"

void graph::Canon1( std::map<int , std::set< int > > &P , std::vector<int> &mu , bool &BestExist ){
 std::map< int , std::set<int> > Q = REFINE( P );
 //basic_function::print_partition( Q );
 int l = -1;
 for(auto i : Q )
  if( i.second.size() > 1 ){
   l = i.first;
   break;
  }
 CompResult Res = CompResult::Better;
 std::vector<int> pi;
 if( l == - 1 ){
  l = n;
  pi = std::vector<int> ( n );
 }else pi = std::vector<int> ( l + 1 );
 if( BestExist ){
 	for(int i=0;i<l;i++) pi[i] = *Q[i].begin();
	Res = Compare( mu , pi , l ); 
 }

 if( l == n ){
  if( !BestExist ){
   for(int i = 0 ; i < n ; i++ ) mu[i] = *Q[i].begin();
   BestExist = true;
  }else if( Res == CompResult::Better ){
   mu = pi;
   //std::cout<<"Better"<<std::endl;
  }
 }else if( Res != CompResult::Worse ){
  std::set<int> C = Q[l];
  std::set<int> D = Q[l];
  std::map<int,std::set<int> > R;
  for( int j = 0 ; j < l ; j++ ) R[j] = Q[j];
  for( int j = l + 1 ; j < Q.size(); j++ ) R[j+1] = Q[j];
  for( auto u : C ){
   std::set<int> Rl , Rl1 = D;
   Rl.insert( u );
   Rl1.erase( u );
   R[l] = Rl;
   R[l+1] = Rl1;
   Canon1( R , mu , BestExist );
  }
 }
}

std::string graph::Cert1() {
 std::map<int , std::set<int> > P;
 std::vector<int> mu( n );
 iota( mu.begin() , mu.end() , 0 );
 for(int i = 0 ; i < n ; i++ ) {
  P[0].insert( i );
 }
 bool BestExist = false;
 Canon1( P , mu , BestExist );
 //unsigned long long int num = 0;
 std::string s = "";
 for(int i = 1 ; i < n ; i++ )
  for(int j = 0 ; j < i ; j++ )
  {
   //num <<= 1;
   if( is_edge( mu[i] , mu[j] ) ){
    s += "1";
    //num++;
   }else{
    s += "0";
   }
  }
 return s;
}

std::string graph::Cert3() {
 std::map<int , std::set<int> > P;
 std::vector<int> mu( n );
 iota( mu.begin() , mu.end() , 0 );
 std::map< std::tuple<int,Vector> , std::vector<int> > X = getPartitions();
 int index = 0;

 std::cerr << "GetPartitions() :";
 for( auto it : X ) {
  for( auto v : it.second ) P[ index ].insert( v );
  index++;
  //Output
  std::cerr <<" {";
  for( auto v : it.second ) std::cerr << " " << v ;
  std::cerr <<" }";
 }
 std::cerr << std::endl;

 bool BestExist = false;
 Canon1( P , mu , BestExist );
 //unsigned long long int num = 0;
 std::string s = "";
 for(int i = 1 ; i < n ; i++ )
  for(int j = 0 ; j < i ; j++ )
  {
   //num <<= 1;
   if( is_edge( mu[i] , mu[j] ) ){
    s += "1";
    //num++;
   }else{
    s += "0";
   }
  }
 return s;
}

std::vector<int> graph::Cert1v() {
 std::map<int , std::set<int> > P;
 std::vector<int> mu( n );
 iota( mu.begin() , mu.end() , 0 );
 for(int i = 0 ; i < n ; i++ ) {
  P[0].insert( i );
 }
 bool BestExist = false;
 Canon1( P , mu , BestExist );
 return mu;
}

std::vector<int> graph::Cert3v() {
 std::map<int , std::set<int> > P;
 std::vector<int> mu( n );
 iota( mu.begin() , mu.end() , 0 );
 std::map< std::tuple<int,Vector> , std::vector<int> > X = getPartitions();
 int index = 0;
 for( auto it : X ) {
  for( auto v : it.second ) P[ index ].insert( v );
  index++;
 }

 bool BestExist = false;
 Canon1( P , mu , BestExist );
 return mu;
}

#endif
