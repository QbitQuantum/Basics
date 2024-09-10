int
main()
{
  try
    {
      _controlfp( _RC_UP, _MCW_RC );
      throw 1;
    }
  catch ( ... )
    {
      // Sets the rounding mode to 0 and show that it's realy the case.
      _controlfp( 0, _MCW_RC );
    }

  // After the catch, this value will not be 0 in x64
  unsigned int cw = _controlfp( 0, 0 ) & _MCW_RC;
  return (cw != 0);
}