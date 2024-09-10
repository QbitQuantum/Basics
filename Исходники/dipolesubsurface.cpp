 Spectrum operator()(float d2) const {
     Spectrum dpos = Sqrt(Spectrum(d2) + zpos * zpos);
     Spectrum dneg = Sqrt(Spectrum(d2) + zneg * zneg);
     Spectrum Rd = (1.f / (4.f * M_PI)) *
         ((zpos * (dpos * sigma_tr + Spectrum(1.f)) *
           Exp(-sigma_tr * dpos)) / (dpos * dpos * dpos) -
          (zneg * (dneg * sigma_tr + Spectrum(1.f)) *
           Exp(-sigma_tr * dneg)) / (dneg * dneg * dneg));
     return Rd.Clamp();
 }