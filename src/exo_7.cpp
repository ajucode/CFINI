/*__________________________________________________________________________________________________

  autor: Pedro Guarderas
  email: ajusworkopensource@gmail.com
  date: 25-02-2015
  file: exo_7.cpp
  This program is free software; you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software Foundation;
  either version 2 of the License, or (at your option) any later version.
  __________________________________________________________________________________________________
*/

#include <fstream>
#include <vector>
#include <cmath>

#include "solver.hpp"


double f( double x ) {
  return( max( x - 20.0, 0.0 ) );
//   return( sin( sx ) );
}

int main() {
  double n = 600;
  double m = 600;
  double T = 2.0, X = 100.0;
  double h, k;
  double sigma, mu, r;
  
  vector< double > t( n ), a( n ), b( n ), c( n ); 
  vector< double > x( m ), s( m );
  vector< vector< double > > S;
  
  h = T / ( n - 1.0 );
  k = X / ( m - 1.0 );
  
  sigma = 1.0;
  mu = 2.0;
  r = 1.05;
  
  for ( size_t j = 0; j < m; j++ ) {
    x[j] = j * k;
    s[j] = f( x[j] );
    a[j] = 0.5 * h * ( mu / k - pow( sigma / k, 2.0 ) ); 
    b[j] = 1 + h * ( r + pow( sigma / k, 2.0 ) );
    c[j] = -0.5 * h * ( mu / k + pow( sigma / k, 2.0 ) );
  }
  
 
  for ( size_t i = 0; i < n; i++ ) {
    t[i] = i * h;
    S.push_back( s );
    solveTDSnd( a, b, c, s );
  } 

  ofstream file;
  file.open ("solution.txt");
  for ( size_t i = 0; i < n; i++ ) {
    for ( size_t j = 0; j < m; j++ ) {
      file << S[i][j] << "\t";
    }
    file << endl;
  }
  file.close();

  return 0;
}
