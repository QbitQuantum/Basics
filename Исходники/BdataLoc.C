// ======= FIXME: Hall A lib ================================================
//_____________________________________________________________________________
Int_t TrigBitLoc::Configure( const TObjArray* params, Int_t start )
{
  // Initialize CrateLoc from given parmeters

  // Load name, crate, slot, channel
  Int_t ret = CrateLocMulti::Configure( params, start );
  if( ret )
    return ret;

  // Additional parameters: lower and upper TDC cuts
  cutlo = GetString( params, start+4 ).Atoi();
  cuthi = GetString( params, start+5 ).Atoi();
  
  // The bit number is determined from any trailing digits of the name,
  // which must be in the range 0-31
  assert( fName.Length() > 0 ); // else bug in base class Configure()
  Int_t pos = fName.Length()-1, end = pos;
  TString e;
  do {
    e = fName(pos); 
  } while( e.IsDigit() && pos-- > 0 );
  if( pos == end ) { // No digits at the end of the name
    Error( "TrigBitLoc", "Name of trigger bit variable %s must end with bit "
	   "number (0-31). Example: \"bit12\". Fix database.", GetName() );
    return 50;
  }
  e = fName(pos+1,end-pos);
  Int_t val = e.Atoi();
  if( val < 0 || val > 31 ) {
    Error( "TrigBitLoc", "Illegal bit number %d in trigger bit name %s. "
	   "Must be 0-31. Fix database.", val, GetName() );
    return 50;
  }
  bitnum = val;
  
  return 0;
}