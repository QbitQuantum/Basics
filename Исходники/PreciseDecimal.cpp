void PreciseDecimal::SetRealNumber(const double NewRealNumber) {
	if (DecimalState == StringExact) {
		long IntPart = IntegerPartUnRound(NewRealNumber);
		long IntLen = NumberDigits(IntPart);
		
		//now get the mantissa
		long MantPart = DecimalPart(NewRealNumber) * pow(10.0, 10.0); //lose some precision
		long MantLen = NumberDigits(MantPart);

		//convert both to strings and store
		delete [] NumberData.StringPrecision.Integer;
		NumberData.StringPrecision.Integer = new char[IntLen + 1];
		NumberData.StringPrecision.Integer[IntLen] = 0;
		_ltoa(IntPart, NumberData.StringPrecision.Integer, 10);

		delete [] NumberData.StringPrecision.Mantissa;
		NumberData.StringPrecision.Mantissa = new char[MantLen + 1];
		NumberData.StringPrecision.Mantissa[MantLen] = 0;
		_ltoa(IntPart, NumberData.StringPrecision.Mantissa, 10);
	}
	else {
		NumberData.RealPrecision = NewRealNumber;
	}
}