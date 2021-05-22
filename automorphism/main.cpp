#include <iostream>
#include <vector>
#include <set>
#include "permutation.hpp"


int main(){
 //std::vector<int> p = { 1 , 3 , 0 , 2 , 5 , 7 , 4 , 6 };
 /*
 std::vector<int> ap = { 4 , 2 , 3 , 1 , 0 }; 
 permutation a( ap );
 std::vector<int> bp = { 0 , 2 , 4 , 3 , 1 };
 permutation b( bp );
 std::cout<<a.str<<std::endl;
 std::cout<<a.arraytostring()<<std::endl;
 std::cout<<b.arraytostring()<<std::endl;
 std::cout<< a.mult( b ).arraytostring()<<std::endl;
 */
 int n;
 std::cin>>n;
 std::string s1,s2;
 std::cin>>s1>>s2;
 permutation a( s1 );
 permutation b( s2 );
 std::set< permutation > Gamma;
 Gamma.insert( s1 );
 Gamma.insert( s2 );
 //std::vector< permutation > Gamma;
 //Gamma.push_back( s1 );
 //Gamma.push_back( s2 );
 
 /*
 for( auto g: Gamma ){
  std::cout<<g.n<<" : "<<g.str<<std::endl;
 }
 std::cout<<"Gamma size is "<<Gamma.size()<<std::endl;
 */ 
 //std::set< permutation > G = simplegen( n , Gamma );
 //std::cout<<"G size is "<<G.size()<<std::endl;
 //for( auto g: G ) std::cout<<g.str<<std::endl;
 
 //std::vector< std::set< permutation > > U = MakePermutationGroup( n , G );
 
 /*
 std::vector< int > Ip(n);
 iota( Ip.begin() , Ip.end() , 0 );
 permutation I( Ip );
 std::cout<<I.str<<std::endl;
 std::cout<<(I.inv()).str<<std::endl;
 std::cout<<b.str<<std::endl;
 std::cout<<(I.inv() ).mult( b ).str<<std::endl;
 */

 std::vector< std::set< permutation > > U = gen( n , Gamma );
 print_G( n , U );
 /*
 for( int i = 0 ; i < n ; i++ ){
  std::cout<<"U[ "<< i <<" ]"<< std::endl;
  for( auto g : U[i] ) std::cout<<g.str<<std::endl;
 }
 */
 //std::cout<<"LIST"<<std::endl;
 //List( n , U );
 return 0;
}

