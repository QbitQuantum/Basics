void PulseParameters::marshall()
{
    NTOHD(pulseThreshold);
    NTOHD(tripletThreshold);
    NTOHD(singletThreshold);
}