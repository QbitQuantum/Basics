  bool MZTrafoModel::train( std::vector<double> obs_mz, std::vector<double> theo_mz, std::vector<double> weights, MODELTYPE md, bool use_RANSAC )
  {
    coeff_.clear();

    if (obs_mz.empty())
    {
      //LOG_ERROR << "Input to calibration model is empty!" << std::endl;
      return false;
    }

    if (use_RANSAC)
    {
      if (ransac_params_ == nullptr)
      {
        throw Exception::Precondition(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION, "TrafoModel::train(): no RANSAC parameters were set before calling train(). Internal error!");
      }
      if (!(md == LINEAR || md == QUADRATIC))
      {
        LOG_ERROR << "RANSAC is implemented for LINEAR and QUADRATIC models only! Please disable RANSAC or choose the LINEAR or QUADRATIC model." << std::endl;
        throw Exception::NotImplemented(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION);
      }
    }

    try
    {
      if (md == LINEAR)
      {
        if (obs_mz.size() < 2) return false;

        if (use_RANSAC && 
          (obs_mz.size() > ransac_params_->n)) // with fewer points, RANSAC will fail
        {
          std::vector<std::pair<double, double> > r, pairs;
          for (Size i = 0; i < obs_mz.size(); ++i)
          {
            pairs.push_back(std::make_pair(theo_mz[i], obs_mz[i]));
          }
          r = Math::RANSAC<Math::RansacModelLinear>().ransac(pairs, *ransac_params_);
          if (r.size() < 2)
          {
            return false; // RANSAC failed
          }
          obs_mz.clear();
          theo_mz.clear();
          for (Size i = 0; i < r.size(); ++i)
          {
            theo_mz.push_back(r[i].first);
            obs_mz.push_back(r[i].second);
          }
        }

        double confidence_interval_P(0.0);
        Math::LinearRegression lr;
        lr.computeRegression(confidence_interval_P, theo_mz.begin(), theo_mz.end(), obs_mz.begin(), false);
        coeff_.push_back(lr.getIntercept());
        coeff_.push_back(lr.getSlope());
        coeff_.push_back(0.0);
      }
      else if (md == LINEAR_WEIGHTED)
      {
        if (obs_mz.size() < 2) return false;

        double confidence_interval_P(0.0);
        Math::LinearRegression lr;
        lr.computeRegressionWeighted(confidence_interval_P, theo_mz.begin(), theo_mz.end(), obs_mz.begin(), weights.begin(), false);
        coeff_.push_back(lr.getIntercept());
        coeff_.push_back(lr.getSlope());
        coeff_.push_back(0.0);
      }
      else if (md == QUADRATIC)
      {
        if (obs_mz.size() < 3) return false;

        if (use_RANSAC && 
          (obs_mz.size() > ransac_params_->n)) // with fewer points, RANSAC will fail
        {

          std::vector<std::pair<double, double> > r, pairs;
          for (Size i = 0; i < obs_mz.size(); ++i)
          {
            pairs.push_back(std::make_pair(theo_mz[i], obs_mz[i]));
          }
          r = Math::RANSAC<Math::RansacModelQuadratic>().ransac(pairs, *ransac_params_);
          obs_mz.clear();
          theo_mz.clear();
          for (Size i = 0; i < r.size(); ++i)
          {
            theo_mz.push_back(r[i].first);
            obs_mz.push_back(r[i].second);
          }
        }
        // Quadratic fit
        Math::QuadraticRegression qr;
        qr.computeRegression(theo_mz.begin(), theo_mz.end(), obs_mz.begin());
        coeff_.push_back(qr.getA());
        coeff_.push_back(qr.getB());
        coeff_.push_back(qr.getC());
      }
      else if (md == QUADRATIC_WEIGHTED)
      {
        if (obs_mz.size() < 3) return false;

        // Quadratic fit (weighted)
        Math::QuadraticRegression qr;
        qr.computeRegressionWeighted(theo_mz.begin(), theo_mz.end(), obs_mz.begin(), weights.begin());
        coeff_.push_back(qr.getA());
        coeff_.push_back(qr.getB());
        coeff_.push_back(qr.getC());
      }

#ifdef DEBUG_TRAFOMODEL
      printf("# mz regression parameters: Y = %3.10f + %3.10f X + %3.10f X^2\n",
        coeff_[0],
        coeff_[1],
        coeff_[2]);

      // print results
      std::cout << "Calibration details:\n\n";
      std::cout << "m/z(theo) m/z(obs) ppm(before) | ppm(after)\n";
      std::vector<double> st_ppm_before, st_ppm_after;
      for (Size i = 0; i < obs_mz.size(); i++)
      {
        if (use_ppm_) st_ppm_before.push_back(obs_mz[i]);
        else st_ppm_before.push_back(Math::getPPM(theo_mz[i], obs_mz[i]));

        double obs_mz_v = obs_mz[i];
        if (use_ppm_) obs_mz_v = Math::ppmToMass(obs_mz_v, theo_mz[i]) + theo_mz[i]; //

        st_ppm_after.push_back(Math::getPPM(theo_mz[i], predict(obs_mz_v))); // predict() is ppm-aware itself

        printf("%4.5f  %4.5f  %2.1f | %2.1f\n", theo_mz[i], obs_mz_v, st_ppm_before.back(), st_ppm_after.back());
      }
      // use median and MAD to ignore outliers
      double m = Math::median(st_ppm_before.begin(), st_ppm_before.end());
      std::cout << "ppm before: median = " << m << "  MAD = " << Math::MAD(st_ppm_before.begin(), st_ppm_before.end(), m) << "\n";
      m = Math::median(st_ppm_after.begin(), st_ppm_after.end()); 
      std::cout << "ppm after : median = " << m << "  MAD = " << Math::MAD(st_ppm_after.begin(), st_ppm_after.end(), m) << "\n";
#endif

      return true;
    }
    catch (Exception::BaseException& /*e*/)
    {
      //LOG_ERROR << "Exception during model fitting: " << e.getMessage() << std::endl;
      return false;
    }
  }