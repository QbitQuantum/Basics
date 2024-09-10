void StatisticsSampler::samplePotentialEnergy(System &system)
{
    m_potentialEnergy = system.potential()->potentialEnergy();
}