    bool operator() (const Item& item) {

      dirs_vox.index(0) = item.pos[0];
      dirs_vox.index(1) = item.pos[1];
      dirs_vox.index(2) = item.pos[2];

      if (check_input (item)) {
        for (auto l = Loop(3) (dirs_vox); l; ++l)
          dirs_vox.value() = NAN;
        return true;
      }

      std::vector<Direction> all_peaks;

      for (size_t i = 0; i < size_t(dirs.rows()); i++) {
        Direction p (dirs (i,0), dirs (i,1));
        p.a = Math::SH::get_peak (item.data, lmax, p.v);
        if (std::isfinite (p.a)) {
          for (size_t j = 0; j < all_peaks.size(); j++) {
            if (std::abs (p.v.dot (all_peaks[j].v)) > DOT_THRESHOLD) {
              p.a = NAN;
              break;
            }
          }
        }
        if (std::isfinite (p.a) && p.a >= threshold) 
          all_peaks.push_back (p);
      }

      if (ipeaks_vox) {
        ipeaks_vox->index(0) = item.pos[0];
        ipeaks_vox->index(1) = item.pos[1];
        ipeaks_vox->index(2) = item.pos[2];

        for (int i = 0; i < npeaks; i++) {
          Eigen::Vector3f p;
          ipeaks_vox->index(3) = 3*i;
          for (int n = 0; n < 3; n++) {
            p[n] = ipeaks_vox->value();
            ipeaks_vox->index(3)++;
          }
          p.normalize();

          value_type mdot = 0.0;
          for (size_t n = 0; n < all_peaks.size(); n++) {
            value_type f = std::abs (p.dot (all_peaks[n].v));
            if (f > mdot) {
              mdot = f;
              peaks_out[i] = all_peaks[n];
            }
          }
        }
      }
      else if (true_peaks.size()) {
        for (int i = 0; i < npeaks; i++) {
          value_type mdot = 0.0;
          for (size_t n = 0; n < all_peaks.size(); n++) {
            value_type f = std::abs (all_peaks[n].v.dot (true_peaks[i].v));
            if (f > mdot) {
              mdot = f;
              peaks_out[i] = all_peaks[n];
            }
          }
        }
      }
      else std::partial_sort_copy (all_peaks.begin(), all_peaks.end(), peaks_out.begin(), peaks_out.end());

      int actual_npeaks = std::min (npeaks, (int) all_peaks.size());
      dirs_vox.index(3) = 0;
      for (int n = 0; n < actual_npeaks; n++) {
        dirs_vox.value() = peaks_out[n].a*peaks_out[n].v[0];
        dirs_vox.index(3)++;
        dirs_vox.value() = peaks_out[n].a*peaks_out[n].v[1];
        dirs_vox.index(3)++;
        dirs_vox.value() = peaks_out[n].a*peaks_out[n].v[2];
        dirs_vox.index(3)++;
      }
      for (; dirs_vox.index(3) < 3*npeaks; dirs_vox.index(3)++) dirs_vox.value() = NAN;

      return true;
    }