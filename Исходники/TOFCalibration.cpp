  void TOFCalibration::calculateCalibCoeffs_(MSExperiment<> & calib_spectra)
  {
    // flight times are needed later
    calib_peaks_ft_ = calib_spectra;


    // convert flight times of peaks into m/z values
    applyTOFConversion_(calib_spectra);
    std::vector<std::vector<unsigned int> > monoiso_peaks;
    getMonoisotopicPeaks_(calib_spectra, monoiso_peaks);

    startProgress(0, calib_spectra.size(), "quadratic fitting of calibrant spectra");
    // do the quadratic fitting for each calibration spectra separately
    for (unsigned int spec = 0; spec < calib_spectra.size(); ++spec)
    {
      std::vector<unsigned int> monoiso_peaks_scan;
      std::vector<double> exp_masses;
      // match the m/z-values to the expected masses
      matchMasses_(calib_spectra, monoiso_peaks, monoiso_peaks_scan, exp_masses, spec);

      // the actual quadratic fitting part
      Size n = exp_masses.size();
      if (n < 3)
      {
        continue;
      }

      // matrix containing the observations
      std::vector<double> x;
      // vector containing the expected masses
      std::vector<double> y;

      for (Size i = 0; i < n; i++)
      {
        // get the flight time
        double xi = ((calib_peaks_ft_.begin() + spec)->begin() + monoiso_peaks_scan[i])->getMZ();
        x.push_back(xi);
        y.push_back(exp_masses[i]);
      }

      Math::QuadraticRegression qr;
      qr.computeRegression(x.begin(), x.end(), y.begin());

#ifdef DEBUG_CALIBRATION
      std::cout << "chi^2: " << qr.getChiSquared() << std::endl;//DEBUG
      std::cout << "a: " << qr.getA() << "b: " << qr.getB()
            << "c: " << qr.getC() << std::endl;//DEBUG
#endif
      // store the coefficients
      coeff_quad_fit_.push_back(qr.getA());
      coeff_quad_fit_.push_back(qr.getB());
      coeff_quad_fit_.push_back(qr.getC());

      // determine the errors in ppm
      for (Size p = 0; p < n; ++p)
      {
#ifdef DEBUG_CALIBRATION
        std::cout << exp_masses[p]
                  << "\t" << mQ_(calib_peaks_ft_[spec][monoiso_peaks_scan[p]].getMZ(), spec) - exp_masses[p] << std::endl;
#endif
        errors_[exp_masses[p]].push_back((mQ_(calib_peaks_ft_[spec][monoiso_peaks_scan[p]].getMZ(), spec) - exp_masses[p]));
      }
      setProgress(spec);
    }
    endProgress();

    if (coeff_quad_fit_.empty())
    {
      String mess = String("Data can't be calibrated, not enough reference masses found: ") + coeff_quad_fit_.size() / 3;
      throw Exception::UnableToCalibrate(__FILE__, __LINE__, __PRETTY_FUNCTION__, "UnableToCalibrate", mess.c_str());
    }
    averageErrors_();
    averageCoefficients_();
  }