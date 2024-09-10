TH2F* Smooth(TH2F* thish, Int_t ntimes, Option_t *option, Int_t offset) {

   // Smooth bin contents of this 2-d histogram using kernel algorithms
   // similar to the ones used in the raster graphics community.
   // Bin contents in the active range are replaced by their smooth values.
   // If Errors are defined via Sumw2, they are scaled.
   // 3 kernels are proposed k5a, k5b and k3a.
   // k5a and k5b act on 5x5 cells (i-2,i-1,i,i+1,i+2, and same for j)
   // k5b is a bit more stronger in smoothing
   // k3a acts only on 3x3 cells (i-1,i,i+1, and same for j).
   // By default the kernel "k5a" is used. You can select the kernels "k5b" or "k3a"
   // via the option argument.
   // If TAxis::SetRange has been called on the x or/and y axis, only the bins
   // in the specified range are smoothed.
   // In the current implementation if the first argument is not used (default value=1).
   //
   // implementation by David McKee ([email protected]). Extended by Rene Brun

   Double_t k5a[5][5] =  { { 0, 0, 1, 0, 0 },
                           { 0, 2, 2, 2, 0 },
                           { 1, 2, 5, 2, 1 },
                           { 0, 2, 2, 2, 0 },
                           { 0, 0, 1, 0, 0 } };
   Double_t k5b[5][5] =  { { 0, 1, 2, 1, 0 },
                           { 1, 2, 4, 2, 1 },
                           { 2, 4, 8, 4, 2 },
                           { 1, 2, 4, 2, 1 },
                           { 0, 1, 2, 1, 0 } };
   Double_t k3a[3][3] =  { { 0, 1, 0 },
                           { 1, 2, 1 },
                           { 0, 1, 0 } };

   if (ntimes > 1) {
      Warning("Smooth","Currently only ntimes=1 is supported");
   }
   TString opt = option;
   opt.ToLower();
   Int_t ksize_x=5;
   Int_t ksize_y=5;
   Double_t *kernel = &k5a[0][0];
   if (opt.Contains("k5b")) kernel = &k5b[0][0];
   if (opt.Contains("k3a")) {
      kernel = &k3a[0][0];
      ksize_x=3;
      ksize_y=3;
   }

   TH2F* hworking = (TH2F*)thish->Clone();

   // find i,j ranges
   Int_t ifirst = thish->GetXaxis()->GetFirst();
   Int_t ilast  = thish->GetXaxis()->GetLast();
   Int_t jfirst = thish->GetYaxis()->GetFirst();
   Int_t jlast  = thish->GetYaxis()->GetLast();

   // Determine the size of the bin buffer(s) needed
   Int_t nx = thish->GetNbinsX();
   Int_t ny = thish->GetNbinsY();
  cout << nx << " " << ny << endl; 
   Int_t bufSize  = (nx+2)*(ny+2);
   Double_t *buf  = new Double_t[bufSize];
   Double_t *ebuf = new Double_t[bufSize];

   // Copy all the data to the temporary buffers
   Int_t i,j,bin;
   for (i=ifirst; i<=ilast; i++){
      for (j=jfirst; j<=jlast; j++){
         Int_t bin = thish->GetBin(i,j);
         buf[bin] =thish->GetBinContent(bin);
         ebuf[bin]=thish->GetBinError(bin);
      }
   }

   // Kernel tail sizes (kernel sizes must be odd for this to work!)
   Int_t x_push = (ksize_x-1)/2;
   Int_t y_push = (ksize_y-1)/2;

   // main work loop
   for (int i=ifirst; i<=ilast; i++){
      for (int j=jfirst; j<=jlast; j++) {
         if (i-j<offset) continue;

         Double_t content = 0.0;
         Double_t error = 0.0;
         Double_t norm = 0.0;

         for (Int_t n=0; n<ksize_x; n++) {
            for (Int_t m=0; m<ksize_y; m++) {
               Int_t xb = i+(n-x_push);
               Int_t yb = j+(m-y_push);
               if ( (xb >= 1) && (xb <= nx) && (yb >= 1) && (yb <= ny) ) {
                  Int_t bin = thish->GetBin(xb,yb);
                  Double_t k = kernel[n*ksize_y +m];
                  //if ( (k != 0.0 ) && (buf[bin] != 0.0) ) { // General version probably does not want the second condition
                  if ( k != 0.0 ) {
                     norm    += k;
                     content += k*buf[bin];
                     error   += k*k*buf[bin]*buf[bin];
                  }
               }
            }
         }

         if ( norm != 0.0 ) {
            hworking->SetBinContent(i,j,content/norm);
            error /= (norm*norm);
            hworking->SetBinError(i,j,sqrt(error));
         }
      }
   }

   delete [] buf;
   delete [] ebuf;
   return hworking;
}