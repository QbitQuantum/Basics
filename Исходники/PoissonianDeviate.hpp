        unsigned long long operator() ( const double & lam, RNG & rng ) const {
          double enlam = exp(-lam);
          unsigned long long X = 0u;
          double prod = 1.0;

          while (true) {
            prod *= rng.rand();

            if (prod > enlam)
              X += 1u;
            else
              return X;
          }
        }