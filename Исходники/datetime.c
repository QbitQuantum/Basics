SEXP make_dt(SEXP year, SEXP month, SEXP day, SEXP hour, SEXP minute, SEXP second) {

  if(!isInteger(year)) error("year must be integer");
  if(!isInteger(month)) error("month must be integer");
  if(!isInteger(day)) error("day must be integer");
  if(!isInteger(hour)) error("hour must be integer");
  if(!isInteger(minute)) error("minute must be integer");
  if(!isNumeric(second)) error("second must be numeric");

  R_len_t n = LENGTH(year);
  
  if(n != LENGTH(month)) error("length of 'month' vector is not the same as that of 'year'");
  if(n != LENGTH(day)) error("length of 'day' vector is not the same as that of 'year'");
  if(n != LENGTH(hour)) error("length of 'hour' vector is not the same as that of 'year'");
  if(n != LENGTH(minute)) error("length of 'minute' vector is not the same as that of 'year'");
  if(n != LENGTH(second)) error("length of 'second' vector is not the same as that of 'year'");

  int* pyear = INTEGER(year);
  int* pmonth = INTEGER(month);
  int* pday = INTEGER(day);
  int* phour = INTEGER(hour);
  int* pminute = INTEGER(minute);

  int int_second = TYPEOF(second) == INTSXP;

  SEXP res = allocVector(REALSXP, n);
  double *data = REAL(res);

  for(int i = 0; i < n; i++) {

	// main accumulator
    double SECS = 0.0;

	int y = pyear[i];
	int m = pmonth[i];
	int d = pday[i];
	int H = phour[i];
	int M = pminute[i];
	int naS;
	double S;

	if(int_second){
	  S = (double) INTEGER(second)[i];
	  naS = INTEGER(second)[i] == NA_INTEGER;
	} else {
	  S = REAL(second)[i];
	  naS = ISNA(S);
	}

	if(naS || y == NA_INTEGER || m == NA_INTEGER || d == NA_INTEGER || H == NA_INTEGER || M == NA_INTEGER) {

	  data[i] = NA_REAL;

	} else {
	  
	  if ( 0 < m && m < 13 )
		SECS += sm[m];
	  else {
		data[i] = NA_REAL;
		continue;
	  }
	
	  if ( 0 < d && d < 32 )
		SECS += (d - 1) * 86400;
	  else {
		data[i] = NA_REAL;
		continue; 
	  }

	  if( H < 25 )
		SECS += H * 3600;
	  else {
		data[i] = NA_REAL;
		continue;
	  }
	
	  if ( M < 61 )
		SECS += M * 60;
	  else{
		data[i] = NA_REAL;
		continue;
	  }

	  // allow leap seconds
	  if ( S < 62 ) {
		SECS += S;
	  } else {
		data[i] = NA_REAL;
		continue;
	  }

	  int is_leap = LEAP(y);

	  if(check_ymd(y, m, d, is_leap)){
	
		SECS += d30;
		y -= 2000;
		SECS += y * yearlen;
		SECS += adjust_leap_years(y, m, is_leap);

		data[i] = SECS;
	  
	  } else {
		data[i] = NA_REAL;
	  }
	}
  }
  
  return res;
}