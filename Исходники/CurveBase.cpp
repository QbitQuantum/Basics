void UCurveBase::MakeTransactional() 
{
	SetFlags(GetFlags() | RF_Transactional);
}