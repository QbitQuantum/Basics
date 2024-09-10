//' Computes the convex minorant of a polygon.
//' @param x,y the coordinates of the polygon
//' @return vector of the y-coordinates of the convex minorant
//[[Rcpp::export]]
NumericVector convexMinorant(NumericVector x, NumericVector y) {
  
  int ny = y.length();

  NumericVector XX = x; 
  NumericVector XY = y; 
  
  vector<Point> P(ny);
  for (int i = 0; i < ny; i++) {
    P[i].x = XX[i];
    P[i].y = XY[i];
  }
  
  vector<Point> convHull = convex_hull(P);
  
  int            nP = convHull.size();
  vector<int>    convHullX(nP); 
  vector<double> convHullY(nP); 
  for (int i = 0; i < nP; i++) {
    convHullX[i] = convHull.at(i).x;
    convHullY[i] = convHull.at(i).y;
  }
  
  NumericVector XXX     = Rcpp::wrap(convHullX);
  NumericVector XYY     = Rcpp::wrap(convHullY);
  NumericVector slopes  = compute_slopes(XXX, XYY);
  return slopes;
  //return List::create(Named("slopes") = slopes, Named("x") = XXX, Named("y") = XYY);
}