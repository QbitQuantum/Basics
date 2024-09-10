void Action_Pairwise::Print() {
  if (nframes_ < 1) return;
  // Divide matrices by # of frames
  double norm = 1.0 / (double)nframes_;
  for (unsigned int i = 0; i != vdwMat_->Size(); i++)
  {
    (*vdwMat_)[i] *= norm;
    (*eleMat_)[i] *= norm;
  }
  // Write out final results
  CpptrajFile AvgOut;
  if (AvgOut.OpenWrite( avgout_ )) return;
  if (nb_calcType_ == NORMAL)
    mprintf("  PAIRWISE: Writing all pairs with |<evdw>| > %.4f, |<eelec>| > %.4f\n",
            cut_evdw_, cut_eelec_);
  else if (nb_calcType_ == COMPARE_REF)
    mprintf("  PAIRWISE: Writing all pairs with |<dEvdw>| > %.4f, |<dEelec>| > %.4f\n",
            cut_evdw_, cut_eelec_);
  AvgOut.Printf("%-16s %5s -- %16s %5s : ENE\n","#Name1", "At1", "Name2", "At2");
  for (AtomMask::const_iterator m1 = Mask0_.begin(); m1 != Mask0_.end(); ++m1) {
    for (AtomMask::const_iterator m2 = m1 + 1; m2 != Mask0_.end(); ++m2)
    {
      double EV = vdwMat_->GetElement(*m1, *m2);
      double EE = eleMat_->GetElement(*m1, *m2);
      bool outputv = ( fabs(EV) > cut_evdw_ );
      bool outpute = ( fabs(EE) > cut_eelec_ );
      if (outputv || outpute) {
        AvgOut.Printf("%16s %5i -- %16s %5i :",
                CurrentParm_->TruncResAtomName(*m1).c_str(), *m1 + 1,
                CurrentParm_->TruncResAtomName(*m2).c_str(), *m2 + 1);
        if (outputv) AvgOut.Printf("  EVDW= %12.5e", EV);
        if (outpute) AvgOut.Printf(" EELEC= %12.5e", EE);
        AvgOut.Printf("\n");
      }
    }
  }
}