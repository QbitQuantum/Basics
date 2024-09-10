bool commonPort::initialise( const PortConfig & /*port*/, commonController &mon )
{
   if ( initialisePort() && openPort() )
   {
      mon.portChain.push_back( this );
      monitor = &mon;
      return true;
   }
   return false;
}