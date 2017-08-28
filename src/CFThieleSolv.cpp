
#include <RcppArmadillo.h>

using namespace Rcpp;


//' @title Thiele equations solver
//' @description Solver for Thiele equation and computation of Mathematical reserves. The solver 
//' is implemented with a Crank-Nicolson algorithm.
//' @param t time grid, could be adapted
//' @param V0 initial mathematical reserve
//' @param b fixed benefits
//' @param B transition benefits
//' @return Return a list with the mathematical reserve, the time grid.
//' @note The solver is implemented to compute the solution forwards in time.
//' @author Pedro Guarderas
//' @export
// [[Rcpp::export]]
List CFThieleSolv( const arma::colvec& t,
                   const arma::colvec& V0,
                   const arma::mat& b,
                   const arma::cube& B,
                   const double& theta = 0.5 ) {
  
  int M, N, n, i;
  double dt;
  
  N = t.size();
  M = V0.size();
  
  arma::rowvec U( M );
  arma::mat V( N, M );
  arma::mat A( M, M );

  // Setting final conditions  
  V.row( 0 ) = V0.t();
  
  // Thiele equation solver
  for ( n = 0; n < N - 1; n++ ) {
    dt = t( n + 1 ) - t( n );
    A = arma::eye( M, M ) - ( 1.0 - theta ) * dt * B.slice( n + 1 );
    U = V.row( n ) + theta * dt * ( b.row( n ) + V.row( n ) * B.slice( n ) ) + ( 1.0 - theta ) * dt * b.row( n + 1 );
    U = arma::trans( arma::solve( A.t(), U.t() ) );
    V.row( n + 1 ) = U; 
  }
  
  return  List::create( Named( "V" ) = V,
                        Named( "t" ) = t );
}
    