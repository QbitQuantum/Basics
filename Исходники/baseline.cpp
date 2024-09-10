bool Baseline::is_male(RandomBin& rb)
{
	return (rb.rand(RandomBin::Baseline) <= prop_male);
}