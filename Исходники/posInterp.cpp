//------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
try {
   totaltime = clock();
   int iret,reading,nread;
   size_t nfile;

      // Title and description
   Title = PrgmName + ", part of the GPS ToolKit, Ver " + PrgmVers + ", Run ";
   PrgmEpoch.setLocalTime();
   Title += printTime(PrgmEpoch,"%04Y/%02m/%02d %02H:%02M:%02S");
   Title += "\n";
   cout << Title;

      // get command line
   iret=GetCommandLine(argc, argv);
   if(iret) return iret;

   PrevEpoch = CommonTime::BEGINNING_OF_TIME;

   // loop over input files - reading them twice
   Ninterps = 0;
   for(reading=1; reading <= 2; reading++) {
      nread = 0;
      for(nfile=0; nfile<PIC.InputObsName.size(); nfile++) {
         iret = ReadFile(nfile,reading);
         if(iret < 0) break;
         nread++;
      }
      // quit if error
      if(iret < 0) break;

      if(nread>0) {
         iret = AfterReadingFiles(reading);
         if(iret < 0) break;
      }

      CurrEpoch = CommonTime::BEGINNING_OF_TIME;
   }

   PIC.oflog << PrgmName << " did " << Ninterps << " interpolations" << endl;
   totaltime = clock()-totaltime;
   PIC.oflog << PrgmName << " timing: " << fixed << setprecision(3)
      << double(totaltime)/double(CLOCKS_PER_SEC) << " seconds.\n";
   cout << PrgmName << " timing: " << fixed << setprecision(3)
      << double(totaltime)/double(CLOCKS_PER_SEC) << " seconds.\n";

   PIC.oflog.close();

   return iret;
}
catch(FFStreamError& e) { cout << "FFStream exception:\n" << e << endl; }
catch(Exception& e) { cout << "GPSTK exception:\n" << e << endl; }
catch (...) { cout << "Unknown exception in main." << endl; }
}   // end main()