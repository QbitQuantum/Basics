	// always produces the same pseudo-random sequence
NoiseSource::NoiseSource(const unsigned int InputSize)
{
  int i;

  NoiseArray = new int[InputSize];
  ArraySize = InputSize;
  SRand(2542);
  for(i=0; i < ArraySize; i++)
    NoiseArray[i] = i;
  for(i=0; i < 20; i++)
    RandomizeArray();
}