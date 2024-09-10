QuatF& QuatF::operator /=( const QuatF & c )
{
   QuatF temp = c;
   return ( (*this) *= temp.inverse() );
}