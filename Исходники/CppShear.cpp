 void CppShear::getEta1Eta2(double& eta1, double& eta2) const 
 {
     double scale;
     // get ratio of eta amplitude to e amplitude:
     scale = std::sqrt(e1*e1 + e2*e2);
     if (scale>0.001) scale = atanh(scale)/scale;
     else scale=1.;
     eta1 = e1*scale;
     eta2 = e2*scale;
 }