#include "graph.hpp"
#include "cert1.hpp"
#include "cert2.hpp"
#include <string>
#include <time.h>

int main(){
 int n,m;
 char o;
 std::string s;
 std::cin>>o>>s>>n>>m;
 std::vector< std::vector< bool > > E( n , std::vector< bool > ( n , false ) );
 for( int i = 0 ; i < m ; i++ ){
  int u,v;
  std::cin>>o>>u>>v;
  u--,v--;
  E[u][v] = E[v][u] = true;
 }
 graph g( E );
 
 clock_t start,end;
 double time;

 /*
 start = clock();
 std::cout<<"Cert1"<<std::endl;
 std::cout<<g.Cert1()<<std::endl;
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;
 */

 start = clock();
 std::cout<<"Cert2"<<std::endl;
 std::cout<<g.Cert2()<<std::endl;
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;

 /*
 start = clock();
 std::cout<<"Cert3"<<std::endl;
 std::cout<<g.Cert3()<<std::endl;
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;
 */

 start = clock();
 std::cout<<"Cert4"<<std::endl;
 std::cout<<g.Cert4()<<std::endl;
 end= clock();
 time = static_cast<double> (end-start) / CLOCKS_PER_SEC * 1.0;
 std::cout << "time = " << time << " [sec]" << std::endl;


 return 0;
}

