#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <string>
#include <type_traits>
#include "permutation.hpp"

enum class CompResult { Worse , Better , Equal };

struct Vector {//D2 配列用
 std::vector< int > a;
 Vector() {}
 Vector( std::vector< int > &_a): a(_a) {}
 bool operator < (const Vector& b ) const{
  for(int i = 0 ; i < a.size() ; i++ ){
   if( a[i] != b.a[i] ) return a[i] < b.a[i];
  }
  return a[0] < b.a[0];
 }

 bool operator == (const Vector& b ) const {
  if( a.size() != b.a.size() ) return false;
  for( int i = 0 ; i < a.size() ; i++ ) {
   if( a[i] != b.a[i] ) return false;
  }
  return true;
 }
 void print() {
  for( int i = 0; i < a.size() ; i++ ) {
   if( i != 0 ) std::cout<<' ';
   std::cout<<a[i];
  }
  std::cout<<std::endl;
 }
};

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
  bool FindIsomorphism( int l, std::vector<int> &W, std::vector<int> &f, graph& G , std::vector< std::vector< int > > &X , std::vector< std::vector<int> > &Y);

  //Algorithm 7.5
  std::map<int, std::set< int > > REFINE( std::map<int, std::set< int > > &A );
  void SpritAndUpdate( std::map<int, std::set< int > > &B , int j , 
    int &N , std::set< int > &U, std::map<int, std::set< int > > &S, std::set< int > &T);
  int AbsAndSet( int u , std::set< int > &T );// | T and N_g(u) |
  //Algorithm 7.6
  CompResult Compare( std::vector< int > &mu , std::vector< int > &pi, int l ); 
  //Algorithm 7.7
  void Canon1( std::map< int , std::set<int> > &P, std::vector<int> &mu, bool &BestExist );
  //Algorithm 7.8
  std::string Cert1();
  //Algorithm 7.9
  void Canon2( permutation &beta, std::vector< std::set< permutation > > &G, std::map< int , std::set<int> > &P, std::vector<int> &mu , bool &BestExist );
  //Algorithm 7.10
  std::string Cert2();
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
bool SetInclude( std::set< int > &A , std::set< int > &B ); // A <= B
void SetDelete( std::set< int > &A, std::set< int > &B ); // A / B

// Algorithm 7.5
std::map<int, std::set< int > > graph::REFINE( std::map<int, std::set< int > > &A ){
 std::map<int, std::set<int> > B = A;
 std::map<int, std::set<int> > S;
 for( auto i : B ){
  S[ B.size() - 1 - i.first ] = i.second;
 }

 std::set< int > U , T;
 for( auto v : V ) U.insert( v );
 int N = B.size();
 while( N != 0 ){
  N--;
  T = S[ N ];
  if( SetInclude( T , U ) ){
   SetDelete( U , T );
   int j = 0;
   while( j < B.size() and B.size() < n ){
    if( B.size() != 1 ) {
     SpritAndUpdate( B , j , N , U ,S ,T );
    }
    j++;
   }
   if( B.size() == n ) return B;
  }
 }
 return B;
}


void graph::SpritAndUpdate( std::map< int,std::set<int> > &B , int j , 
  int &N , std::set< int >  &U, std::map< int,std::set< int > > &S, std::set< int > &T ) {
 std::map<int, std::set<int> > L;
 for( auto u : B[j] ){
  int h = AbsAndSet( u , T );
  L[h].insert( u );
 }
 
 int m = 0;
 for(int h = 0 ; h < n ; h++ )
  if( L[h].size() != 0 ) m++;
 if( m > 1 ){
  for( int h = B.size() - 1 ; h > j ; h-- )
   B[ m - 1 + h ] = B[ h ];
  int k = 0;
  for( int h = 0 ; h < n ; h++ )
   if( L[h].size() != 0 ){
    B[ j + k ] = L[h];
    S[ N + m -1 -k ] = L[h];
    //S[ N + k ] = L[h];
    for( auto x : L[h] ) U.insert( x );
    k++;
   }
  j += m - 1;
  N += m;
 }
}

bool SetInclude( std::set< int > &A, std::set< int > &B ){
 for( auto v : A )
  if( B.find( v ) == B.end() ) return false; //Bにない
 return true;
}

void SetDelete( std::set< int > &A, std::set< int > &B ){ // A / B
 for( auto i : B ) A.erase( i );
}

int graph::AbsAndSet( int u, std::set< int > &T ){
 int res = 0;
 for( int i = 0 ; i < n ; i++ ) 
  if( is_edge( u , i ) ) {
   auto it = T.find( i );
   if( it != T.end() ) res++; 
  }
 return res;
}

//Algorithm 7.6
CompResult graph::Compare( std::vector< int > &mu , std::vector< int > &pi, int l ){
 for(int j = 1 ; j < l ; j++ ){
  for(int i = 0; i < j ; i++ ){
   int x = is_edge( mu[i], mu[j] ) ? 1 : 0;
   int y = is_edge( pi[i], pi[j] ) ? 1 : 0;
   if( x < y ) return CompResult::Worse;
   if( x > y ) return CompResult::Better;
  }
 }
 return CompResult::Equal;
}
//Algorithm 7.7
void graph::Canon1( std::map<int , std::set< int > > &P , std::vector<int> &mu , bool &BestExist ){
 std::map< int , std::set<int> > Q = REFINE( P );
 //print_partition( Q );
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

//Algorithm 7.8
std::string graph::Cert1() {
 std::map<int , std::set<int> > P;
 std::vector<int> mu( n );
 iota( mu.begin() , mu.end() , 0 );
 for(int i = 0 ; i < n ; i++ ) {
  P[0].insert( i );
 }
 bool BestExist = false;
 Canon1( P , mu , BestExist );
 unsigned long long int num = 0;
 std::string s = "";
 for(int i = 1 ; i < n ; i++ )
  for(int j = 0 ; j < i ; j++ )
  {
   num <<= 1;
   if( is_edge( mu[i] , mu[j] ) ){
    s += "1";
    num++;
   }else{
    s += "0";
   }
  }
 /*
 for(int i= 0; i< n ; i++ ){
  if(i != 0 ) std::cout<<" ";
  std::cout<<mu[i];
 }
 std::cout<<std::endl;
 std::cout<<num<<std::endl;
 */
 return s;
}

//Algorithm 7.9
void graph::Canon2( permutation &beta, std::vector< std::set<permutation> > &G , std::map<int , std::set< int > > &P , std::vector<int> &mu , bool &BestExist ){
 std::map< int , std::set<int> > Q = REFINE( P );
 //print_partition( Q );
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
  }else if( Res == CompResult::Equal ){
   std::vector< int > pi2tmp( n );
   for(int i = 0 ; i < n ; i++ ) pi2tmp[ pi[i] ] = mu[i];
   permutation pi2( pi2tmp );
   enter2( n , pi2  , beta , G );
  }
 }else if( Res != CompResult::Worse ){
  std::set<int> C = Q[l];
  std::set<int> D = Q[l];
  std::map<int,std::set<int> > R;
  for( int j = 0 ; j < l ; j++ ) R[j] = Q[j];
  for( int j = l + 1 ; j < Q.size(); j++ ) R[j+1] = Q[j];
  std::vector< bool > no_check( n , false );
  for( auto u : C )
  //for( auto it = C.begin() ; it != C.end() ; it++ )
  {
  // int u = *it;
   if( no_check[ u ] ) continue;
   std::set<int> Rl , Rl1 = D;
   Rl.insert( u );
   Rl1.erase( u );
   R[l] = Rl;
   R[l+1] = Rl1;
   Canon2( beta , G , R , mu , BestExist );
   std::vector< int > beta_dashtmp( n );
   std::vector< bool > no_use( n , true );
   for( int j = 0 ; j <= l ; j++ ) {
    beta_dashtmp[j] = *R[j].begin();
    no_use[ *R[j].begin() ] = false;
   }
   int j = l;
   for( int i = 0 ; i < n ; i++ ) 
    if( no_use[i] ) {
     j++;
     beta_dashtmp[j] = i;
    }
   permutation beta_dash( beta_dashtmp );
   changebase( n , beta , beta_dash , G );
   for( auto g : G[l] ) {
    no_check[ g.p[u]  ] = true;
   }
  }
 }
}

//Algorithm 7.10
std::string graph::Cert2() {
 std::map<int , std::set<int> > P;
 std::vector<int> mu( n );
 iota( mu.begin() , mu.end() , 0 );
 for(int i = 0 ; i < n ; i++ ) {
  P[0].insert( i );
 }
 bool BestExist = false;
 std::vector< int > Ip(n);
 iota( Ip.begin() , Ip.end() , 0 );
 permutation I( Ip );
 std::vector< std::set< permutation > > G(n);
 for( int i = 0 ; i < n ; i++ ) G[i].insert( I );
 Canon2( I , G , P , mu , BestExist );

 unsigned long long int num = 0;
 std::string s = "";
 for(int i = 1 ; i < n ; i++ )
  for(int j = 0 ; j < i ; j++ )
  {
   num <<= 1;
   if( is_edge( mu[i] , mu[j] ) ){
    s += "1";
    num++;
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
 //for(int i = 0 ; i < n ; i++ ) P[0].insert( i );
 std::map< std::tuple<int,Vector> , std::vector<int> > X = getPartitions();
 int index = 0;
 for( auto it : X ) {
  for( auto v : it.second ) P[ index ].insert( v );
  index++;
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

std::string graph::Cert4() {
 std::map<int , std::set<int> > P;
 std::vector<int> mu( n );
 iota( mu.begin() , mu.end() , 0 );
 //for(int i = 0 ; i < n ; i++ ) P[0].insert( i ); 
 std::map< std::tuple<int,Vector> , std::vector<int> > X = getPartitions();
 int index = 0;
 for( auto it : X ) {
  for( auto v : it.second ) P[ index ].insert( v );
  index++;
 }
 
 bool BestExist = false;
 std::vector< int > Ip(n);
 iota( Ip.begin() , Ip.end() , 0 );
 permutation I( Ip );
 std::vector< std::set< permutation > > G(n);
 for( int i = 0 ; i < n ; i++ ) G[i].insert( I );
 Canon2( I , G , P , mu , BestExist );

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

//Algorithm 7.1
std::map< std::tuple<int,Vector> , std::vector<int> > graph::getPartitions() {
 std::map< std::tuple<int, Vector > , std::vector<int> > res;
 for(int i = 0 ; i < n ; i++ ) {
  int d1 = getdeg(i);
  std::vector< int > d2( n , 0 );
  for( int j = 0 ; j < n ;  j ++ ) {
   if( is_edge( i, j ) ) d2[ getdeg(j) ]++;
  }
  Vector d2v( d2 );
  res[ std::tie( d1 , d2v ) ].push_back( i );
 }
 return res;
}

bool graph::FindIsomorphism( int l , std::vector< int > &W, std::vector< int > &f , graph& G, std::vector< std::vector<int> > &X, std::vector< std::vector<int> >  &Y ){
 if( l == n ) {
  for(int i  = 0 ; i < n ; i++ ) {
   if( i != 0 ) std::cout<<' ';
   std::cout<<char('a'+f[i]);
  }
  std::cout<<std::endl;
  return true;
 }
 int j = W[l];
 for( auto y : Y[j] ){
  bool ok = true;
  for( int u = 0 ; u < l ; u++ ){
   if( is_edge( u , l ) != G.is_edge( f[u] , y ) or f[u] == y ) ok = false; //or  f[u] == yを加えないと、同じ役割をする頂点が消える可能性がある。
  }
  if( ok ) {
   f[l] = y;
   if( FindIsomorphism( l + 1 , W , f , G , X, Y ) ) return true;
  }
 }
 return false;
}

bool graph::Isomorphism( graph& G ) {
 std::map< std::tuple<int , Vector> , std::vector<int> > X = getPartitions();
 std::map< std::tuple<int , Vector> , std::vector<int> > Y = G.getPartitions();
 if( n != G.n ) return false;
 if( X.size() != Y.size() ) return false;// G1 and G2 are not isomorphic
 for( auto i : X ) {
  if( i.second.size() != Y[ i.first ].size() ) return false;
 }
 // Order the partitions so that :
 // | X[i] | = | Y[i] | <= | X[i+1] | = Y[ i + 1 ] for all i
 
 std::vector< std::pair< int , std::tuple<int, Vector > > > Ordertmp;
 std::vector< std::vector< int > > XX;
 std::vector< std::vector< int > > YY;
 for( auto i: X ) Ordertmp.push_back( std::pair< int , std::tuple<int, Vector > >  ( i.second.size() , i.first ) );
 sort( Ordertmp.begin() , Ordertmp.end() );
 for( auto i : Ordertmp ){
  XX.push_back( X[ i.second ] );
  YY.push_back( Y[ i.second ] );
 }
 std::vector< int > W( n );
 int N = X.size();
 for( int i = 0 ; i < N ; i++ )
  for( auto x : XX[i] ) W[x] = i ;
 std::vector< int > f(n);
 iota( f.begin() , f.end() , 0 );
 return FindIsomorphism( 0 , W , f, G , XX , YY );
}

bool graph::Isomorphism_Brute_Force( graph& G ) { //Brute Force algorithm 
 bool res = false;
 do {
  if( compare( G ) ){
   G.print_V_alphabet();
   res = true;
   //return true; 
  }
 } while( std::next_permutation( G.V.begin() , G.V.end() ) );
 return res;
}


bool graph::is_edge(int x,int y ) { return g[x][y]; }
bool graph::is_edge_x(int i,int j ) { return g[V[i]][V[j]]; }
bool graph::compare( graph& G ) {
 if( n != G.n ) return false;
 for( int i = 0 ; i < n ; i++ ){
  for( int j = 0 ; j < n ; j++ ){
   if( is_edge_x( i , j ) != G.is_edge_x( i , j ) ) return false;
  }
 }
 return true;
}



void graph::make_deg() {
 deg = std::vector< int > ( n , 0 );
 for(int i = 0 ; i < n ; i++ )
  for( int j = 0 ; j < n ; j++)
   if( is_edge_x( i , j ) ) deg[i]++;
}
void graph::print_V() {
 for(int i = 0 ; i < n ; i++ ) {
  if( i != 0 ) std::cout<<' ';
  std::cout<<V[i];
 }
 std::cout<<std::endl;
}
void graph::print_V_alphabet() {
 for(int i = 0 ; i < n ; i++ ) {
  if( i != 0 ) std::cout<<' ';
  std::cout<<(char)('a'+V[i]);
 }
 std::cout<<std::endl;
}
void graph::print_G() {
 for(int i = 0 ; i < n ; i++ ){
  for(int j = 0 ; j < n ; j++ ){
   if( j != 0 ) std::cout<<' ';
   std::cout<<is_edge_x(i,j) ? 1 : 0;
  }
  std::cout<<std::endl;
 }
}
void graph::print() {
 print_V();
 print_G();
}

void print_partition( std::map<int , std::set<int> > &A ){
 std::cout<<"[";
 for( auto i : A ){
  std::cout<<"{ ";
  for( auto j : i.second ) std::cout<<j<<" ";
  std::cout<<"} ";
 }
 std::cout<<"]"<<std::endl;
}

