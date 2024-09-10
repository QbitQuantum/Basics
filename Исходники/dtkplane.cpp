//*******************************************************************************************
void makeGnuplotFile(optFlags &opts, string &gnpn,string &outn,char p2p,
                     solreal dimparam,bondNetWork &bn,int a1,int a2,int a3,waveFunctionGrid2D &grd)
{
   ofstream gfil;
   gfil.open(gnpn.c_str());
   
   /* Choosing the label (legend) for the plot  and the zrange for the plot */
   solreal minzrange,maxzrange;
   string plbl=getFieldTypeKeyShort(p2p);;
   switch (p2p) {
      case 'd':
         minzrange=0.0e0;
         maxzrange=0.6e0;
         break;
      case 'g':
         minzrange=0.0e0;
         maxzrange=2.0e0;
         break;
      case 'l':
         minzrange=-2.0e0;
         maxzrange=2.0e0;
         break;
      case 'E':
         minzrange=0.0e0;
         maxzrange=1.0e0;
         break;
      case 'S':
         minzrange=-10.0e0;
         maxzrange=10.0e0;
         break;
      case 'L':
         minzrange=0.0e0;
         maxzrange=1.0e0;
         break;
      case 'M':
         minzrange=0.0e0;
         maxzrange=2.0e0;
         break;
      case 'N':
         minzrange=0.0e0;
         maxzrange=2.0e0;
         break;
      case 'G':
         minzrange=0.0e0;
         maxzrange=10.0e0;
         break;
      case 'K':
         minzrange=0.0e0;
         maxzrange=10.0e0;
         break;
      case 'p' :
         minzrange=0.0e0;
         maxzrange=2.0e0;
         break;
      case 'P' :
         minzrange=0.0e0;
         maxzrange=2.0e0;
         break;
      case 'r' :
         minzrange=-1.0e0;
         maxzrange=1.0e0;
         break;
      case 's' :
         minzrange=0.0e0;
         maxzrange=1.0e0;
         break;
      case 'u' :
         minzrange=-1.0e0;
         maxzrange=1.0e0;
         break;
      case 'U' :
         minzrange=-1.0e0;
         maxzrange=1.0e0;
         break;
      case 'V':
         minzrange=-0.6e0;
         maxzrange=0.6e0;
         break;
      default:
         setScrRedBoldFont();
         cout << "Error: The property \"" << p2p << "\" does not exist!" << endl;
         setScrNormalFont();
         exit(1);
         break;
   }
   
   gfil << "reset" << endl;
   
   /* In this part the name is scanned for possible occurrings of the character '_'.
    For a proper display in the eps file, it has to be changed to "\_" */
   string line="";
   for (size_t i=0; i<outn.length(); i++) {
      if (outn[i]=='_') {line+='\\';}
      line+=outn[i];
   }
   gfil << "set title '" << line << "'" << endl;
   
   /* Adding an underscore and braces to the atome labels in order to make the numbers
    subindices */
   
   gfil << "set isosample 300, 300" << endl;
   
   gfil << "set zrange [" << minzrange << ":" << maxzrange << "]" << endl;
   
   gfil << "set contour base" << endl;

   gfil << "set cntrparam bspline" << endl;
   
   //gfil << "set cntrparam levels discrete 0.001, 0.005, 0.02, 0.05, 0.1, 0.2, 0.3" <<endl;

   gfil << "set cntrparam levels incremental " << minzrange << ", " 
        << (0.10*(maxzrange-minzrange)) << ", " << maxzrange << endl;
   
   gfil << "unset surface" << endl;
   
   gfil << "set table 'contourtemp.dat'" << endl;
   
   gfil << "splot '" << outn << "'";
   if (p2p=='N' || p2p=='p' || p2p=='U') {gfil << " using 1:2:(sqrt($3*$3+$4*$4))";}
   gfil << endl;
   
   gfil << "unset table" << endl;
   
   gfil << "reset" << endl;
   
   gfil << "unset key" << endl;
   
   gfil << "set size ratio 1" << endl;
   
   gfil << "set tmargin at screen 0.99\nset bmargin at screen 0.01\nset lmargin at screen 0.01" << endl;
   
   gfil << "dimparam=" << dimparam
        << " #Decrease this number to zoom in the plot" << endl;
   
   if (p2p=='N'||p2p=='p'||p2p=='U') {
      gfil << "VMXS=dimparam/40.0 #Maximum lenght of the vectors" << endl;
   }
   
   gfil << "set notics" << endl;
   
   gfil << "set xrange[-dimparam:dimparam]\nset yrange[-dimparam:dimparam]" << endl;
   
   gfil << "minvalfield=" << minzrange << endl << "maxvalfield=" << maxzrange << endl;
   
   gfil << "set cbrange [minvalfield:maxvalfield]" << endl;
   
   gfil << "set style data lines" << endl;
   
   gfil << "set palette rgbformulae 33,13,10" << endl;
   
   if (p2p=='N'||p2p=='p'||p2p=='U') {
      //gfil << "plot '" << outn << "' using 1:2:3:4:(sqrt($3*$3+$4*$4)) "
      //<< "with vectors head size 0.1,20,60 filled lc palette";
      gfil << "plot '" << outn << "' every 1:1 using 1:2:(sqrt($3*$3+$4*$4)>VMXS? VMXS*$3/sqrt($3*$3+$4*$4) : $3):(sqrt($3*$3+$4*$4)>VMXS ? VMXS*$4/sqrt($3*$3+$4*$4) : $4):(sqrt($3*$3+$4*$4)) "
           << "with vectors head size 0.1,20,60 filled lc palette" << endl;
   } else {
      gfil << "plot '" << outn << "' with image" << endl;
   }
   
   if (opts.showcont) {gfil << "replot 'contourtemp.dat' w l lt -1 lw 1 ";}
   else {gfil << " #replot 'contourtemp.dat' w l lt -1 lw 1 #Activate this line to show contours";}
   gfil << endl;
   
   /* Here the atoms' labels are set and written to the gnuplot input file. */
   
   writeScrCharLine(gfil,'#');
   gfil << "# Here are the labes of the atoms" << endl;
   writeScrCharLine(gfil,'#');
   
   string lbl;
   int at[3];
   at[0]=a1; at[1]=a2; at[2]=a3;
   solreal xproj,yproj;
   size_t pos;
   std::ostringstream numst;
   bool IDefPlane;
   for (int i=0; i<bn.nNuc; i++) {
      xproj=0.0e0;
      yproj=0.0e0;
      IDefPlane=false;
      for (int j=0; j<3; j++) {
         xproj+=(bn.R[i][j]-grd.orig[j])*grd.dircos1[j];
         yproj+=(bn.R[i][j]-grd.orig[j])*grd.dircos2[j];
         if ((i==at[j])&&opts.showatlbl) {IDefPlane=true;}
      }
      if (opts.showallatlbl||IDefPlane) {lbl="";} else {lbl="#";}
      lbl+="set label ";
      numst.str("");
      numst << (i+1);
      lbl+=numst.str();
      lbl+=" at ";
      numst.str("");
      numst << xproj << "," << yproj;
      lbl+=numst.str();
      lbl+=" '";
      lbl+=bn.atLbl[i];
      /* Adding an underscore and braces to the atome labels in order to make the numbers
         subindices */
      pos=lbl.find_last_not_of("0123456789");
      if (pos!=string::npos) {
         lbl.insert(pos+1,"_{");
         lbl.append("}");
      }
      lbl+="' front offset character -0.5,-0.15";
      for (int k=0; k<3; k++) {
         if (at[k]==i) {lbl+=" #* This atom was used for setting the plane!";}
      }
      gfil << lbl << endl;
   }
   writeScrCharLine(gfil,'#');
   
   /* Here is enabled the logarithmic scale in the case of G, d or g */
   gfil << "set terminal postscript eps enhanced color fontscale 1.75 lw 2 dashlength 4" << endl;
   
   string imgnam,epsname,extepsname,pdfname;
   imgnam=outn.substr(0,(outn.length()-4));
   imgnam.append("ext.eps"); //here is set the name for the image
   gfil << "set output '";
   gfil << imgnam << "'" << endl; //so far, the image's name is *.eps
   gfil << "set cbtics #deactivate if you do not want tics on the colorbox scale" << endl;
   gfil << "replot" << endl;
   extepsname=imgnam;
   epsname=outn.substr(0,(outn.length()-3));
   epsname.append("eps");
   pdfname=outn.substr(0,(outn.length()-3));
   pdfname.append("eps");
   gfil << "#" << endl;
   writeScrCharLine(gfil,'#');
   gfil << "#                 END OF GNUPLOT COMMANDS" << endl;
   writeScrCharLine(gfil,'#');
   gfil << "#If you want to reconstruct the plot using this file, type:" << endl
        << "#gnuplot " << gnpn << endl
        << "#epstool --copy -b " << extepsname << " " << epsname << endl
        << "#epstopdf --outfile=" << pdfname << " " << extepsname << endl;
   
   gfil.close();
#if (defined(__APPLE__)||defined(__linux__))
   line=string("gnuplot ");
#endif
#if (defined(__CYGWIN__))
   line=string("wgnuplot ");
#endif
   line+=gnpn;
   cout << "Calling gnuplot... ";
   system(line.c_str());
#if _HAVE_EPSTOOL_
   line=string("epstool --copy -b ");
   line+=(imgnam+string(" "));
   imgnam=outn.substr(0,(outn.length()-3)); //Here the image name changes from eps to pdf
   imgnam.append("eps");
   line+=imgnam;
   if (opts.quiet) {line+=string(" > /dev/null 2>&1");}
   system(line.c_str());
#endif
#if _HAVE_EPSTOPDF_
   string pdfnam=outn.substr(0,(outn.length()-3));
   pdfnam.append("pdf");
   line=string("epstopdf --outfile=")+pdfnam+string(" ")+imgnam;
   if (opts.quiet) {line+=string(" > /dev/null 2>&1");}
   system(line.c_str());
#endif
#if (defined(__APPLE__)||defined(__linux__)||defined(__CYGWIN__))
   line="rm ";
#if _HAVE_EPSTOOL_
   line+=imgnam;
#endif
   imgnam=outn.substr(0,(outn.length()-4));
   imgnam.append("ext.eps");
   line+=(string(" ")+imgnam);
   system(line.c_str());
#endif//defined(__APPLE__)||defined(__linux__)
   cout << "Done." << endl;
   return;
}