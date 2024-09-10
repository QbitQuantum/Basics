bool checkFileOK( std::ifstream &istr, const std::string &fname, const std::string &fmess )
{
   if ( !istr )
   {
      std::string ebuff = ( boost::format( "Failed to open %s (%s)" ) % fmess % fname ).str();
      char *emess = _strerror( ebuff.c_str() );
      MinosParameters::getMinosParameters() ->mshowMessage( emess );
      return false;
   }
   return true;
}