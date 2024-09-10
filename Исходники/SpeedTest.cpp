double
SpeedTest (pfHash hash, uint32_t seed, const int trials, const int blocksize,
	   const int align)
{
  Rand r (seed);

  uint8_t *buf = new uint8_t[blocksize + 512];

  uint64_t t1 = reinterpret_cast < uint64_t > (buf);

  t1 = (t1 + 255) & BIG_CONSTANT (0xFFFFFFFFFFFFFF00);
  t1 += align;

  uint8_t *block = reinterpret_cast < uint8_t * >(t1);

  r.rand_p (block, blocksize);

  //----------

  std::vector < double >times;
  times.reserve (trials);

  for (int itrial = 0; itrial < trials; itrial++)
    {
      r.rand_p (block, blocksize);

      double t = (double) timehash (hash, block, blocksize, itrial);

      if (t > 0)
	times.push_back (t);
    }

  //----------

  std::sort (times.begin (), times.end ());

  FilterOutliers (times);

  delete[]buf;

  return CalcMean (times);
}