_inline double _cubeBrightnessReduction( double base )
{
	return lossCalculator( cbrt( base ), cbrt( base * _effectiveFPS( ) / _currentFPS( ) ) );
}