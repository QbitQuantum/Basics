ParticleFactory::~ParticleFactory()
{
	delete[] GetInstance().contingHolder;
	delete[] GetInstance().contingHolderCold;
	
}