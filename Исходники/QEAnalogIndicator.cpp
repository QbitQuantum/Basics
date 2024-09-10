//------------------------------------------------------------------------------
//
bool QEAnalogIndicator::firstValue (int & itc, double & value, bool & isMajor)
{
   double real;
   bool result;

   if (this->getLogScale ()) {
      real = 9.0 * LOG10 (this->mMinimum);
   } else {
      real = this->mMinimum / this->getMinorInterval ();
   }

   // Use floor to round down and - 0.5 to mitigate any rounding effects.
   // Subtract an addition -1 to ensure first call to nextValue returns a
   // value no greater than the first required value.
   //
   itc = int (floor (real) - 0.5) - 1;

   result = this->nextValue (itc, value, isMajor);
   while (result && (value < this->mMinimum)) {
      result = this->nextValue (itc, value, isMajor);
   }
   return result;
}