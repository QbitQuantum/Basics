float log2f( float n )
{
	// logb (x) = (loga(x)) / (loga(B))
	return logf(n) / logf(2);
}