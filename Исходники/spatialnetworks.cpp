// [[Rcpp::export]]
arma::mat join_spatiallines_coords(SEXP sldf, double startx, double starty) {

  Rcpp::S4 obj(sldf);
  List lines = obj.slot("lines");
  arma::mat fullcoords;

  double prevx = startx;
  double prevy = starty;

  for (unsigned int i = 0; i < lines.length(); i++) {
    List Lines = Rcpp::S4(lines(i)).slot("Lines");
    arma::mat thiscoords = as<arma::mat>(Rcpp::S4(Lines(0)).slot("coords"));
    if (thiscoords(0,0) == prevx && thiscoords(0,1) == prevy) {
      thiscoords = thiscoords.rows(1,thiscoords.n_rows-1);
    }
    else {
      thiscoords = thiscoords.rows(arma::linspace<arma::uvec>(thiscoords.n_rows-2, 0, thiscoords.n_rows-1));
    }
    fullcoords.insert_rows(fullcoords.n_rows, thiscoords);
    prevx = fullcoords(fullcoords.n_rows-1,0);
    prevy = fullcoords(fullcoords.n_rows-1,1);
  }

  return fullcoords;

}