void CalcRMSD::Run()
{

  OBAlign align;
  unsigned int cutoff_passed = 0;
  unsigned int N = 0;
  OBMol rmol, tmol;
  vector<double> rmsd;

  const double binvals_arr[8] = {0.2, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 100.0};
  vector<double> binvals(binvals_arr, binvals_arr+8);

  // For every test_conf there is a reference, but not v.v.
  bool more_to_come = tconv.Read(&tmol);
  while (more_to_come) {
    N++;
    string title = tmol.GetTitle();

    // Get the corresponding reference
    rconv.Read(&rmol);
    while (rmol.GetTitle() != title) {
      cout << "..Molecule " << N 
           << "\n..title = " << rmol.GetTitle()
           << "\n..number of confs = 0\n";
      N++;
      rconv.Read(&rmol);
    }
    cout << "..Molecule " << N << "\n..title = " << rmol.GetTitle() << "\n";
    
    align.SetRefMol(rmol);
    rmsd.clear();
    while (tmol.GetTitle() == title) {
      align.SetTargetMol(tmol);
      align.Align();
      rmsd.push_back(align.GetRMSD());
      more_to_come = tconv.Read(&tmol);
      if (!more_to_come) break;
    }

    sort(rmsd.begin(), rmsd.end());

    cout << "..number of confs = " << rmsd.size() << "\n";
    cout << "..minimum rmsd = " << rmsd.at(0) << "\n";
    
    int bin_idx = 0;
    vector<int> bins(binvals.size());
    for(vector<double>::iterator it=rmsd.begin(); it!=rmsd.end(); ++it) {
      while (*it > binvals[bin_idx])
        bin_idx++;
      bins[bin_idx]++;
    }

    vector<int> cumbins(bins);
    for(int i=1; i<8; ++i)
      cumbins[i] += cumbins[i-1];

    cout << "..confs less than cutoffs: ";
    cout << binvals[0];
    for (int i=1; i < binvals.size(); i++)
      cout << " " << binvals[i];
    cout << "\n";

    cout << ".." << cumbins[0];
    for (int i=1; i < cumbins.size(); i++)
      cout << " " << cumbins[i];
    cout << "\n";

    cout << "..cutoff (" << rmsd_cutoff << ") passed = ";
    if (rmsd.at(0) <= rmsd_cutoff) {
      cout << " Yes\n";
      cutoff_passed++;
    }
    else
      cout << " No\n";
  cout << "\n";

  }

  cout << "\n**Summary\n..number of molecules = " << N 
       << "\n..less than cutoff(" << rmsd_cutoff << ") = " << cutoff_passed << "\n";

}