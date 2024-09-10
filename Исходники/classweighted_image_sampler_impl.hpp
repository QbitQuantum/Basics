unsigned int ClassWeightedImageSampler<type, nChannels>::sample(const type *data, const unsigned char *labels,
							  unsigned int width, unsigned int height,
							  unsigned int *samples) const
{
  unsigned int **perClassBucket = new unsigned int*[m_nClasses];
  for (int i=0; i<m_nClasses; i++) perClassBucket[i] = new unsigned int[m_perClassBucketSize[i]];
  
  unsigned int *perClassNSamples = new unsigned int[m_nClasses];
  unsigned int *perClassCounter = new unsigned int[m_nClasses];
  std::fill(perClassNSamples, perClassNSamples+m_nClasses, 0);
  std::fill(perClassCounter, perClassCounter+m_nClasses, 0);
  
  boost::random::mt19937 gen;
  boost::random::uniform_01<> dist;
  
  boost::crc_32_type checksum_agent;  
  checksum_agent.process_bytes((unsigned char*)data, sizeof(type)*width*height*nChannels);
  gen.seed(checksum_agent.checksum() ^ this->m_seed);


  // Scan the whole image and perform per-class reservoir sampling
  for (int i=0; i<width*height; i++)
  {
    unsigned char label = labels[i];
    if (label)
    {
      label -= 1;
      unsigned int *currBucket = perClassBucket[label];
      unsigned int perClassBucketSize = m_perClassBucketSize[label];

      if (perClassNSamples[label]<perClassBucketSize)
      {
        currBucket[perClassNSamples[label]] = i;
        perClassNSamples[label]++;
      }
      else
      {
        unsigned int j = roundf(dist(gen)*perClassCounter[label]);
        if (j<perClassBucketSize)
	{
          currBucket[j] = i;
        }
      }
      perClassCounter[label]++;
    }
  }

  // Copy the sampled pixels to the output buffer
  unsigned int totSamples=perClassNSamples[0];
  std::copy(perClassBucket[0], perClassBucket[0]+perClassNSamples[0], samples);
  for (int i=1; i<m_nClasses; i++)
  {
    std::copy(perClassBucket[i], perClassBucket[i]+perClassNSamples[i],
	      samples+totSamples);
    totSamples += perClassNSamples[i];
  }
  
  // Finally, sort samples
  std::sort(samples, samples+totSamples);

  for (int i=0; i<m_nClasses; i++) delete perClassBucket[i];
  delete []perClassBucket;
  delete []perClassNSamples;
  delete []perClassCounter;

  return totSamples;
}