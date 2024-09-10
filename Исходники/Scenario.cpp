double IndustryScenario::calcIndustryDraw(NormalRandomNumberGenerator& randGen, IndustryEntry& industryEntry)
{
	double random1 = randGen.rand();
	double random2 = randGen.rand();
	return (industryEntry.correl * random1) + (sqrt(1 - (industryEntry.correl*industryEntry.correl)) * random2);
}