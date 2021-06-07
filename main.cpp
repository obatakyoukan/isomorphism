#include "graph.hpp"
#include "isomorphism.hpp"
#include "isomorphism_brute_force.hpp"
#include "cert1.hpp"
#include "cert2.hpp"
#include <time.h>

int main(){
 int n,m;
 std::cin>>n>>m;
 std::vector< std::vector< bool > > E1( n , std::vector< bool > ( n , false ) );
 for( int i = 0 ; i < m ; i++ ){
  int u,v;
  std::cin>>u>>v;
  E1[u][v] = E1[v][u] = true;
 }
 graph g1( E1 );
 
 std::cin>>n>>m;
 std::vector< std::vector< bool > > E2( n , std::vector< bool > ( n , false ) );
 for( int i = 0 ; i < m ; i++ ){
  int u,v;
  std::cin>>u>>v;
  E2[u][v] = E2[v][u] = true;
 }
 graph g2( E2 );
 clock_t start,end;
 double time;
 
 std::cout<<"Brute Force"<<std::endl;
 start = clock();
 g1.Isomorphism_Brute_Force(g2);
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;
 
 std::cout<<"Isomorphism devide"<<std::endl;
 g1 = graph( E1 );
 g2 = graph( E2 );
 start = clock();
 g1.Isomorphism(g2);
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;
 
 std::cout<<"Cert1"<<std::endl;
 g1 = graph( E1 );
 g2 = graph( E2 );
 start = clock();
 std::cout<<g1.Cert1()<<std::endl;
 std::cout<<g2.Cert1()<<std::endl;
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;

 std::cout<<"Cert2"<<std::endl;
 g1 = graph( E1 );
 g2 = graph( E2 );
 start = clock();
 std::cout<<g1.Cert2()<<std::endl;
 std::cout<<g2.Cert2()<<std::endl;
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;
 
 std::cout<<"Cert3"<<std::endl;
 g1 = graph( E1 );
 g2 = graph( E2 );
 start = clock();
 std::cout<<g1.Cert3()<<std::endl;
 std::cout<<g2.Cert3()<<std::endl;
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;

 std::cout<<"Cert4"<<std::endl;
 g1 = graph( E1 );
 g2 = graph( E2 );
 start = clock();
 std::cout<<g1.Cert4()<<std::endl;
 std::cout<<g2.Cert4()<<std::endl;
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;


 return 0;
}

