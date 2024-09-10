template <typename T> void ork::TVector2<T>::Serp( const TVector2<T> & PA, const TVector2<T> & PB, const TVector2<T> & PC, const TVector2<T> & PD, T Par )
{
	TVector2<T> PAB, PCD;
	PAB.Lerp( PA, PB, Par );
	PCD.Lerp( PC, PD, Par );
	Lerp( PAB, PCD, Par );
}