RankFourTensor
RankTwoTensor::d2thirdInvariant() const
{
  RankTwoTensor s = 0.5 * deviatoric();
  s += s.transpose();

  RankFourTensor d2;
  for (unsigned int i = 0; i < N; ++i)
    for (unsigned int j = 0; j < N; ++j)
      for (unsigned int k = 0; k < N; ++k)
        for (unsigned int l = 0; l < N; ++l)
        {
          d2(i, j, k, l) = (i==j)*s(k, l)/3.0 + (k==l)*s(i, j)/3.0;
          //for (unsigned int a = 0; a < N; ++a)
          //  for (unsigned int b = 0; b < N; ++b)
          //    d2(i, j, k, l) += 0.5*(PermutationTensor::eps(i, k, a)*PermutationTensor::eps(j, l, b) + PermutationTensor::eps(i, l, a)*PermutationTensor::eps(j, k, b))*s(a, b);
        }

  // I'm not sure which is more readable: the above
  // PermutationTensor stuff, or the stuff below.
  // Anyway, they yield the same result, and so i leave
  // both of them here to enlighten you!

  d2(0, 0, 1, 1) += s(2, 2);
  d2(0, 0, 1, 2) -= s(2, 1);
  d2(0, 0, 2, 1) -= s(1, 2);
  d2(0, 0, 2, 2) += s(1, 1);

  d2(0, 1, 0, 1) -= s(2, 2)/2.0;
  d2(0, 1, 1, 0) -= s(2, 2)/2.0;
  d2(0, 1, 0, 2) += s(1, 2)/2.0;
  d2(0, 1, 2, 0) += s(1, 2)/2.0;
  d2(0, 1, 1, 2) += s(2, 0)/2.0;
  d2(0, 1, 2, 1) += s(2, 0)/2.0;
  d2(0, 1, 2, 2) -= s(1, 0);

  d2(0, 2, 0, 1) += s(2, 1)/2.0;
  d2(0, 2, 1, 0) += s(2, 1)/2.0;
  d2(0, 2, 0, 2) -= s(1, 1)/2.0;
  d2(0, 2, 2, 0) -= s(1, 1)/2.0;
  d2(0, 2, 1, 1) -= s(2, 0);
  d2(0, 2, 1, 2) += s(1, 0)/2.0;
  d2(0, 2, 2, 1) += s(1, 0)/2.0;

  d2(1, 0, 0, 1) -= s(2, 2)/2.0;
  d2(1, 0, 1, 0) -= s(2, 2)/2.0;
  d2(1, 0, 0, 2) += s(1, 2)/2.0;
  d2(1, 0, 2, 0) += s(1, 2)/2.0;
  d2(1, 0, 1, 2) += s(2, 0)/2.0;
  d2(1, 0, 2, 1) += s(2, 0)/2.0;
  d2(1, 0, 2, 2) -= s(1, 0);

  d2(1, 1, 0, 0) += s(2, 2);
  d2(1, 1, 0, 2) -= s(2, 0);
  d2(1, 1, 2, 0) -= s(2, 0);
  d2(1, 1, 2, 2) += s(0, 0);

  d2(1, 2, 0, 0) -= s(2, 1);
  d2(1, 2, 0, 1) += s(2, 0)/2.0;
  d2(1, 2, 1, 0) += s(2, 0)/2.0;
  d2(1, 2, 0, 2) += s(0, 1)/2.0;
  d2(1, 2, 2, 0) += s(0, 1)/2.0;
  d2(1, 2, 1, 2) -= s(0, 0)/2.0;
  d2(1, 2, 2, 1) -= s(0, 0)/2.0;

  d2(2, 0, 0, 1) += s(2, 1)/2.0;
  d2(2, 0, 1, 0) += s(2, 1)/2.0;
  d2(2, 0, 0, 2) -= s(1, 1)/2.0;
  d2(2, 0, 2, 0) -= s(1, 1)/2.0;
  d2(2, 0, 1, 1) -= s(2, 0);
  d2(2, 0, 1, 2) += s(1, 0)/2.0;
  d2(2, 0, 2, 1) += s(1, 0)/2.0;

  d2(2, 1, 0, 0) -= s(2, 1);
  d2(2, 1, 0, 1) += s(2, 0)/2.0;
  d2(2, 1, 1, 0) += s(2, 0)/2.0;
  d2(2, 1, 0, 2) += s(0, 1)/2.0;
  d2(2, 1, 2, 0) += s(0, 1)/2.0;
  d2(2, 1, 1, 2) -= s(0, 0)/2.0;
  d2(2, 1, 2, 1) -= s(0, 0)/2.0;

  d2(2, 2, 0, 0) += s(1, 1);
  d2(2, 2, 0, 1) -= s(1, 0);
  d2(2, 2, 1, 0) -= s(1, 0);
  d2(2, 2, 1, 1) += s(0, 0);

  return d2;
}