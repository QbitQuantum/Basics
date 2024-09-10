  void P (int64 t)
    {
      int cc; /* { dg-excess-errors "note: 'cc' was declared here" } */
      if (GetC (&cc) <= 0 ) /* return flag checked wrongly */
        return;
      
      if (t && cc <= 0 )  /* { dg-warning "uninitialized" "uninitialized variable warning" } */
        {
          this->do_sth();
          return;
        }

    do_sth2();
  }