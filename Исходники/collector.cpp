void CollectorTime::setValue(int i, const Token& t) {
  switch(t.type()) {
  case TOKEN_STRING: {
    boost::container::string buffer;
    SourceIterators string = t.getString(&buffer);
    std::string std_string(string.first, string.second);

    parser_.setDate(std_string.c_str());
    bool res = (format_ == "") ? parser_.parseTime() : parser_.parse(format_);

    if (!res) {
      warn(t.row(), t.col(), "time like " +  format_, std_string);
      INTEGER(column_)[i] = NA_INTEGER;
      return;
    }

    DateTime dt = parser_.makeTime();
    if (!dt.validTime()) {
      warn(t.row(), t.col(), "valid date", std_string);
      INTEGER(column_)[i] = NA_INTEGER;
      return;
    }
    INTEGER(column_)[i] = dt.time();
    return;
  }
  case TOKEN_MISSING:
  case TOKEN_EMPTY:
    INTEGER(column_)[i] = NA_INTEGER;
  case TOKEN_EOF:
    Rcpp::stop("Invalid token");
  }

}