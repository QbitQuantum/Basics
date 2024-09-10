void rdphi::ParseOptions(TString p_option)
{

  do_50_50 = false;
  left_50 = false;
  do_mc = false;
  do_muon = false;
  ident = "ident_test";
  input_path = "./";
  output_path = "../output";
  lepton_mass = Ok_el_mass;


  try
  {
    TObjArray *s = p_option.Tokenize(",; \n\015\012");
    cout << endl << "Okla_ParseOptions: input=" << endl 
      << p_option << endl;

    for( int i = 0 ; i < s->GetEntriesFast() ; i++)
    {
      TString c = ((TObjString *)(*s)[i])->GetString();
      c.ToLower();
      cout << endl << "Okla_ParseOptions: directive \"" << c << "\": " << endl;

      TObjArray *t = c.Tokenize("=:");

      if ( 
        (s->GetEntriesFast() == 1 ) &&
        ( t->GetEntriesFast() == 1 ) ) throw "Error processing parameters";

      if ( t->GetEntriesFast() != 2 ) throw("invalid var=val or var:val (no space or \",\" allowed around\"=\" or \":\")");
      TString var = ((TObjString *)(*t)[0])->GetString();
      TString val = ((TObjString *)(*t)[1])->GetString();


      if( var == "identifier" ){
        ident = val;
      }
      else if( var == "input_path" ){
        input_path = val;
      }
      else if( var == "output_path" ){
        output_path = val;
      }
      else if( var == "do_50_50" ){
        do_50_50 = string_true_false(val);
      }
      else if( var == "left_50" ){
        left_50 = string_true_false(val);
      }
      else if( var == "do_mc" ){
        do_mc = string_true_false(val);
      }
      
      else if( var == "do_muon" ){
        do_muon = string_true_false(val);
        if ( do_muon ) lepton_mass = Ok_mu_mass;
      }
      
      else{
        cout << endl << "throwing exception c:" << c << "   var: "<< var << "  val: " << val << endl; 
        throw( (const char *)(TString(" unknown var ") + var) );
      }
    }
  }
  catch(char * e)
  {
    cout << endl << "OklaParseOptions: Error: " << e << endl;
    exit(0);
  }
  catch(...)
  {
    cout << endl << "OklaParseOptions: Error: invalid parameter: " << endl;
    cout << p_option << endl;
    exit(0);
  }
}