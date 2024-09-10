void checkZeroFinite(const double tmp) throw(std::range_error) {
    if ((tmp == 0.0) || (! _finite(tmp))) {
      if (tmp == 0.0) {
	    printf("ERROR: we have encountered a zero!\n");
      } else if(_isnan(tmp)) {
	    printf("ERROR: we have encountered a nan!\n");
      } else if (_fpclass(tmp) == _FPCLASS_PINF) {
        printf("ERROR: we have encountered a pos inf!\n");
      } else {
        printf("ERROR: we have encountered a neg inf!\n");
      }
      char sbuf[64];
      sprintf(sbuf, "checkZeroFinite: zero or indef exceeded: %g\n",
              tmp);
      throw std::range_error(sbuf);
    }
  }