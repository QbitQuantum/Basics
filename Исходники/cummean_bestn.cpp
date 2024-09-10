// [[Rcpp::export]]
NumericVector ptsThresh(NumericVector values,NumericVector endDates,int window){
  int valuesLen = values.length();
  NumericVector out = clone(values);
  NumericVector startDates = endDates - window;

  for (int i = 0; i < valuesLen; ++i){
    LogicalVector idx = (endDates <= endDates[i]) & (endDates >= startDates[i]);
    NumericVector valuesWindow = values[idx];
    int lenCur = valuesWindow.length();

    if (lenCur == 1){
      out[i] = (1.4 / 1.3) * valuesWindow[i];
    }
    if (lenCur == 2){
      out[i] = (1.5 / 2.4) * sum(valuesWindow);
    }
    if (lenCur == 3){
      out[i] = (1.5 / 3.3) * sum(valuesWindow);
    }
    if (lenCur == 4){
      out[i] = (1.5 / 4.0) * sum(valuesWindow);
    }
    if (lenCur >= 5){
      std::nth_element(valuesWindow.begin(),valuesWindow.begin() + 5,valuesWindow.end());
      out[i] = valuesWindow[4];
    }
  }

  return out;
}