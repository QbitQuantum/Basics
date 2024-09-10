void
PeakConvert2::myProcess(realvec& in, realvec& out)
{
  mrs_natural o,i;
  out.setval(0);
  peakView pkViewOut(out);

  const mrs_bool useMasking	= getctrl("mrs_bool/useMasking")->to<mrs_bool>();
  const mrs_real probThresh	= getctrl("mrs_real/probabilityTresh")->to<mrs_real>();

  max_->updControl("mrs_natural/nMaximums", frameMaxNumPeaks_);

  max_->setctrl("mrs_natural/inSamples", size_);
  max_->setctrl("mrs_natural/inObservations", 1);
  max_->update();
  tmp_.stretch(frameMaxNumPeaks_*2);

  for(mrs_natural f=0 ; f < inSamples_; ++f)
  {
    //we should avoid the first empty frames,
    //that will contain silence and consequently create
    //discontinuities in the signal, ruining the peak calculation!
    //only process if we have a full data vector (i.e. no zeros)
    if(frame_ >= skip_)
    {
      // get pair of ffts
      in.getCol (f, tmpBuff_);

      // compute magnitude, phase, and instantaneous frequency
      this->ComputeMagnitudeAndPhase (tmpBuff_);

      // compute masking threshold
      if (useMasking && pick_)
        ComputeMasking (tmpBuff_);
      else
        masked_.setval(10.);

      // select bins with local maxima in magnitude (--> peaks)
      peaks_ = mag_;
      if(pick_)
        this->ComputePeaker (mag_, peaks_);
      else
      {
        for (o = 0 ; o < downFrequency_ ; o++)
          peaks_(o)=0.0;
        for (o = upFrequency_ ; o < (mrs_natural)peaks_.getSize() ; o++)
          peaks_(o)=0.0;
      }

      if (lpCoeff_ > 0)
        FreqSmear (lpPeakerRes_);

      //compute the probability of a peak being a peak
      for(o=0 ; o < size_ ; o++)
      {
        if (peaks_(o) <= 0)
        {
          frequency_(o)		= .0;
          //lastmag_(o)		= .0;
          lastfrequency_(o)	= .0;
          // time smearing if no new peak
          lpPeakerRes_(o)	*=lpCoeff_;
          continue;
        }
#ifdef ORIGINAL_VERSION
        // probability of peak being a masker
        peakProb_(0)	= 0;
        // probability of peak being stationary
        peakProb_(1)	= 0;
        // probability of peak being tonal
        peakProb_(2)	= (abs(frequency_(o)/fundamental_-o) > .5)? 0 : 1;
#else
        // probability of peak being a masker
        peakProb_(0)	= max((mrs_real).1, (mrs_real).5 * (mrs_real)(log10(masked_(o)) +1.));
        // probability of peak being stationary
        peakProb_(1)	= max((mrs_real).1, (mrs_real)lpPeakerRes_(o));
        // probability or peak being tonal
        peakProb_(2)	= GaussianPdf (frequency_(o)/fundamental_-o, gaussianStd);
#endif

        // reset lpPeakerRes with peaker results
        lpPeakerRes_(o)	= 1;

        peakProb_ *= peakProbWeight_;
        if ((peakProb_.sum() < probThresh) && pick_)
        {
          peaks_(o)		= .0;
          frequency_(o)	= .0;
          //lastmag_(o)		= .0;
          lastfrequency_(o)	= .0;
        }
      }

      // keep only the frameMaxNumPeaks_ highest amplitude local maxima
      tmp_.setval(0.);
      max_->process(peaks_, tmp_);

      nbPeaks_=tmp_.getSize()/2;
      realvec index_(nbPeaks_); //[!] make member to avoid reallocation at each tick!
      for (i=0 ; i<nbPeaks_ ; i++)
        index_(i) = tmp_(2*i+1);

      // search for bins interval
      realvec interval_(nbPeaks_*2); //[!] make member to avoid reallocation at each tick!
      interval_.setval(0);
      if(pick_)
        getShortBinInterval(interval_, index_, mag_);
      else
      {
        for (i=0 ; i<nbPeaks_ ; i++)
          interval_(2*i+1) = index_(i);
      }

#ifdef LOG2FILE
      for (i=0 ; i<nbPeaks_ ; i++)
      {
        mrs_real value = frequency_((mrs_natural) (index_(i)+.1));
        pFDbgFile << std::scientific << std::setprecision(4) << value << "\t";
      }
      pFDbgFile << std::endl;
#endif
#ifdef MARSYAS_MATLAB
#ifdef MTLB_DBG_LOG
      MATLAB_PUT(mag_, "peaks");
      MATLAB_PUT(peaks_, "k");
      MATLAB_PUT(tmp_, "tmp");
      MATLAB_PUT(interval_, "int");
      MATLAB_PUT(frequency_, "freq");
//			MATLAB_EVAL("figure(1);clf;hold on ;plot(peaks);stem(k);stem(tmp(2:2:end)+1, peaks(tmp(2:2:end)+1), 'r')");
//			MATLAB_EVAL("stem(int+1, peaks(int+1), 'k')");
      MATLAB_EVAL("figure(1);hold on ;stem(freq(tmp(2:2:end)+1), peaks(tmp(2:2:end)+1), 'r');hold off");
#endif
#endif


      // fill output with peaks data
      interval_ /= N_;

      for (i = 0; i < nbPeaks_; i++)
      {
        mrs_natural index = (mrs_natural) (index_(i)+.1);
        pkViewOut(i, peakView::pkFrequency, f) = frequency_(index);
        pkViewOut(i, peakView::pkAmplitude, f) = magCorr_(index);
        pkViewOut(i, peakView::pkPhase, f) = -phase_(index);
        pkViewOut(i, peakView::pkDeltaFrequency, f) = deltafrequency_(index);
        pkViewOut(i, peakView::pkDeltaAmplitude, f) = /*abs*/(deltamag_(index));
        pkViewOut(i, peakView::pkFrame, f) = frame_;
        pkViewOut(i, peakView::pkGroup, f) = 0.;//(pick_)?-1.:0.; //This should be -1!!!! [TODO]
        pkViewOut(i, peakView::pkVolume, f) = 1.0;
        pkViewOut(i, peakView::pkBinLow, f) = interval_(2*i);
        pkViewOut(i, peakView::pkBin, f) = index_(i);
        pkViewOut(i, peakView::pkBinHigh, f) = interval_(2*i+1);
        pkViewOut(i, peakView::pkTrack, f) = -1.0; //null-track ID

        MRSASSERT((index_(i) <= interval_(2*i)) || (interval_(2*i+1) <= index_(i)));

        if(useStereoSpectrum_)
          pkViewOut(i, peakView::pkPan, f) = in((mrs_natural)index_(i)+2*N_, f);
        else
          pkViewOut(i, peakView::pkPan, f) = 0.0;
      }
    }
    else //if not yet reached "skip" number of frames...
    {
      for(mrs_natural i=0; i< frameMaxNumPeaks_; ++i)
      {
        //pkViewOut(i, peakView::pkFrequency, f) = 0;
        //pkViewOut(i, peakView::pkAmplitude, f) = 0;
        //pkViewOut(i, peakView::pkPhase, f) = 0;
        //pkViewOut(i, peakView::pkDeltaFrequency, f) = 0;
        //pkViewOut(i, peakView::pkDeltaAmplitude, f) = 0;
        pkViewOut(i, peakView::pkFrame, f) = frame_;
        //pkViewOut(i, peakView::pkGroup, f) = -1;
        //pkViewOut(i, peakView::pkVolume, f) = 0;
        //pkViewOut(i, peakView::pkPan, f) = 0;
        //pkViewOut(i, peakView::pkBinLow, f) = 0;
        //pkViewOut(i, peakView::pkBin, f) = 0;
        //pkViewOut(i, peakView::pkBinHigh, f) = 0;
      }
    }
    frame_++;
  }

  //count the total number of existing peaks (i.e. peak freq != 0)
  ctrl_totalNumPeaks_->setValue(pkViewOut.getTotalNumPeaks());
}