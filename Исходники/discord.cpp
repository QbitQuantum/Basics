//' Finds a discord using brute force algorithm.
//'
//' @param ts the input timeseries.
//' @param w_size the sliding window size.
//' @param discords_num the number of discords to report.
//' @useDynLib jmotif
//' @export
//' @references Keogh, E., Lin, J., Fu, A.,
//' HOT SAX: Efficiently finding the most unusual time series subsequence.
//' Proceeding ICDM '05 Proceedings of the Fifth IEEE International Conference on Data Mining
//' @examples
//' discords = find_discords_brute_force(ecg0606[1:600], 100, 1)
//' plot(ecg0606[1:600], type = "l", col = "cornflowerblue", main = "ECG 0606")
//' lines(x=c(discords[1,2]:(discords[1,2]+100)),
//'    y=ecg0606[discords[1,2]:(discords[1,2]+100)], col="red")
// [[Rcpp::export]]
Rcpp::DataFrame find_discords_brute_force(
    NumericVector ts, int w_size, int discords_num) {

  std::map<int, double> res;

  VisitRegistry registry(ts.length());
  registry.markVisited(ts.length() - w_size, ts.length());

  // Rcout << "starting search of " << discords_num << " discords..." << "\n";

  int discord_counter = 0;
  while(discord_counter < discords_num){

    discord_record rec = find_best_discord_brute_force(ts, w_size, &registry);

    //     Rcout << "found a discord " << discord_counter << " at " << rec.index;
    //     Rcout << ", NN distance: " << rec.nn_distance << "\n";

    if(rec.nn_distance == 0 || rec.index == -1){ break; }

    res.insert(std::make_pair(rec.index, rec.nn_distance));

    int start = rec.index - w_size;
    if(start<0){
      start = 0;
    }
    int end = rec.index + w_size;
    if(end>=ts.length()){
      end = ts.length();
    }

    // Rcout << "marking as visited from " << start << " to " << end << "\n";
    registry.markVisited(start, end);
    discord_counter = discord_counter + 1;
  }

  std::vector<int> positions;
  std::vector<double > distances;

  for(std::map<int, double>::iterator it = res.begin(); it != res.end(); it++) {
    positions.push_back(it->first);
    distances.push_back(it->second);
  }
  // make results
  return Rcpp::DataFrame::create(
    Named("nn_distance") = distances,
    Named("position") = positions
  );
}