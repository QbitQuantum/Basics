int ReportTripletEvent(
  float Power, float MeanPower, float period,
  float mid_time_bin, int start_time_bin, int freq_bin,
  int pot_len,const float *PoT, int write_triplet
) {
  TRIPLET_INFO ti;
  triplet triplet;
  int retval=0, i, j;
  double step,norm,index;
  double max_power=0;
  static int * inv;

// debug possible heap corruption -- jeffc
#ifdef _WIN32
BOINCASSERT(_CrtCheckMemory());
#endif

  if (!inv) inv = (int*)calloc_a(swi.analysis_cfg.triplet_pot_length, sizeof(int), MEM_ALIGN);

  // triplet info
  ti.score=Power;
  ti.t.peak_power=Power;
  ti.t.mean_power=MeanPower;
  ti.freq_bin=freq_bin;
  ti.time_bin=mid_time_bin+start_time_bin+0.5f;
  ti.t.chirp_rate=ChirpFftPairs[analysis_state.icfft].ChirpRate;
  ti.t.fft_len=ChirpFftPairs[analysis_state.icfft].FftLen;
  ti.bperiod=period;
  ti.t.period=static_cast<float>(period*static_cast<double>(ti.t.fft_len)/swi.subband_sample_rate);
  ti.t.freq=cnvt_bin_hz(freq_bin, ti.t.fft_len);
  double t_offset=(static_cast<double>(mid_time_bin)+start_time_bin+0.5)
      *static_cast<double>(ti.t.fft_len)/
         swi.subband_sample_rate;
  ti.t.detection_freq=calc_detection_freq(ti.t.freq,ti.t.chirp_rate,t_offset);
  ti.t.time=swi.time_recorded+t_offset/86400.0;
  time_to_ra_dec(ti.t.time, &ti.t.ra, &ti.t.decl);

  // Populate the min and max PoT arrays.  These are only used
  // for graphics.
  memset(ti.pot_min,0xff,swi.analysis_cfg.triplet_pot_length*sizeof(int));
  memset(ti.pot_max,0,swi.analysis_cfg.triplet_pot_length*sizeof(int));
  step=static_cast<double>(pot_len)/swi.analysis_cfg.triplet_pot_length;
  ti.scale=static_cast<float>(1.0/step);
  index=0;
  for (i=0;i<pot_len;i++) {
    if (PoT[i]>max_power) max_power=PoT[i];
  }
  norm=255.0/max_power;
  float mtb = mid_time_bin;
  if (pot_len > swi.analysis_cfg.triplet_pot_length) {
    ti.tpotind0_0 = ti.tpotind0_1 = static_cast<int>(((mtb-period)*swi.analysis_cfg.triplet_pot_length)/pot_len);
    ti.tpotind1_0 = ti.tpotind1_1 = static_cast<int>(((mtb)*swi.analysis_cfg.triplet_pot_length)/pot_len);
    ti.tpotind2_0 = ti.tpotind2_1 = static_cast<int>(((mtb+period)*swi.analysis_cfg.triplet_pot_length)/pot_len);
    for (j=0; j<pot_len; j++) {
      i = (j*swi.analysis_cfg.triplet_pot_length)/pot_len;
      if ((PoT[j]*norm)<ti.pot_min[i]) {
        ti.pot_min[i]=static_cast<unsigned int>(floor(PoT[j]*norm));
      }
      if ((PoT[j]*norm)>ti.pot_max[i]) {
        ti.pot_max[i]=static_cast<unsigned int>(floor(PoT[j]*norm));
      }
    }
  } else {
    memset(inv, -1, sizeof(inv));
    for (i=0;i<swi.analysis_cfg.triplet_pot_length;i++) {
      j = (i*pot_len)/swi.analysis_cfg.triplet_pot_length;
      if (inv[j] < 0) inv[j] = i;
      if ((PoT[j]*norm)<ti.pot_min[i]) {
        ti.pot_min[i]=static_cast<unsigned int>(floor(PoT[j]*norm));
      }
      if ((PoT[j]*norm)>ti.pot_max[i]) {
        ti.pot_max[i]=static_cast<unsigned int>(floor(PoT[j]*norm));
      }
    }
    ti.tpotind0_0 = inv[static_cast<int>(mtb-period)];
    ti.tpotind0_1 = inv[static_cast<int>(mtb-period+1)];
    ti.tpotind1_0 = (inv[static_cast<int>(mtb)]+inv[static_cast<int>(mtb+1)])/2;
    ti.tpotind1_1 = (inv[static_cast<int>(mtb+1)]+inv[static_cast<int>(mtb+2)])/2;
    ti.tpotind2_0 = inv[static_cast<int>(mtb+period)];
    if (mtb+period+1 >= pot_len) ti.tpotind2_1 = swi.analysis_cfg.triplet_pot_length-1;
    else ti.tpotind2_1 = inv[static_cast<int>(mtb+period+1)];
  }

  // Update sah_graphics triplet info regardless of whether it is the
  // best thus far.  If a triplet has made it this far, display it.
#ifdef BOINC_APP_GRAPHICS
    if (!nographics()) sah_graphics->ti.copy(&ti);
#endif

  // best thus far ?
  if (ti.score>best_triplet->score) {
    *best_triplet=ti;
  }


  if (write_triplet) {

    if (signal_count > swi.analysis_cfg.max_signals) {
      SETIERROR(RESULT_OVERFLOW,"in ReportTripletEvent");
    }

    retval = outfile.printf("%s", ti.t.print_xml(0,0,1).c_str());

    if (retval < 0) {
      SETIERROR(WRITE_FAILED,"in ReportTripletEvent");
    } else {
      signal_count++;
      triplet_count++;
    }

  }

// debug possible heap corruption -- jeffc
#ifdef _WIN32
BOINCASSERT(_CrtCheckMemory());
#endif

  return(retval);
}