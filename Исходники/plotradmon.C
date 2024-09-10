Int_t getscaler( Int_t scalervector, Int_t scalerchannel, Char_t *start_datetime, Char_t *end_datetime )
{

  TSQLServer *serv = TSQLServer::Connect("mysql://phnxdb1.phenix.bnl.gov/scalers", "phoncs", "phenix7815");
  
  // Create the sql query
  
  Int_t which_table, which_rate;

  which_table = (scalerchannel/16) + 1;
  which_rate = ( scalerchannel%16 ) + 1;
  
  TString scaler_field_name = "rate";
  scaler_field_name += which_rate;

  TString columns = "UNIX_TIMESTAMP(rs.read_datetime) AS read_timestamp,rs.";
  columns += scaler_field_name;
  columns += ", (@csum:=@csum+60.0*rs.";
  columns += scaler_field_name;
  columns += ") as cum";
  
  TString sql = "SELECT ";
  sql += columns;
  sql += " FROM rhicscaler";
  sql += which_table;
  sql += " AS rs WHERE";
  sql += " rs.read_datetime>=\"";
  sql += start_datetime;
  sql += "\" AND rs.read_datetime<=\"";
  sql += end_datetime;
  sql += "\";";

  cout << "sql query: " << sql << endl;

  TSQLResult *res;
  res = serv->Query("SET @csum=0.0;");
  res = serv->Query(sql);

  // Extract the result of the query into vectors

  Int_t nrows = res->GetRowCount();
  Int_t nfields = res->GetFieldCount();
  cout << "rows: " << nrows << " columns: " << nfields << endl;

  TString fieldname;
  TString field;
  TSQLRow *row;

  Double_t read_timestamp;
  Double_t cum;
  Double_t running_sum = 0.0;
  Double_t summand = 0.0;

  sread_time[scalervector].clear();
  cum_scaler_db[scalervector].clear();
  cum_scaler_sum[scalervector].clear();

  for (Int_t i = 0; i < nrows; i++) {
    row = res->Next();
    for (Int_t j = 0; j < nfields; j++) {
      fieldname = TString( res->GetFieldName(j) );
      field = TString( row->GetField(j) );
      // Extract all columns of each row
      // std::cout << "fieldname: " << fieldname << " field: " << field << std::endl;
      if ( fieldname == "read_timestamp" ) read_timestamp = field.Atof();
      if ( fieldname == "cum" ) cum = field.Atof();
      if ( fieldname == scaler_field_name ) summand = field.Atof();
    }
    // Save all the columns in this row in vectors for plotting
    sread_time[scalervector].push_back(read_timestamp);
    cum_scaler_db[scalervector].push_back(cum);
    running_sum += 60.0*summand;
    cum_scaler_sum[scalervector].push_back(running_sum);
  }
  
  return nrows;
  
}