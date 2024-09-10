   // used to create output file for canvas
   void imgconv( TCanvas* c, const TString & fname )
   {
      // return;
      if (NULL == c) {
         cout << "*** Error in TMVAGlob::imgconv: canvas is NULL" << endl;
      }
      else {
         // create directory if not existing
         TString f = fname;
         TString dir = f.Remove( f.Last( '/' ), f.Length() - f.Last( '/' ) );
         gSystem->mkdir( dir );

         TString pngName = fname + ".png";
         TString gifName = fname + ".gif";
         TString epsName = fname + ".eps";
         c->cd();

         // create eps (other option: c->Print( epsName ))
         if (UsePaperStyle) {
            c->Print(epsName);
         } 
         else {
            cout << "--- --------------------------------------------------------------------" << endl;
            cout << "--- If you want to save the image as eps, gif or png, please comment out " << endl;
            cout << "--- the corresponding lines (line no. 239-241) in tmvaglob.C" << endl;
            cout << "--- --------------------------------------------------------------------" << endl;
            c->Print(epsName);
            c->Print(pngName);
            // c->Print(gifName);
         }
      }
   }