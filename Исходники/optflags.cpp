void getOptions(int &argc, char** &argv, optFlags &flags)
{
   string progname;
   progname=":-)  ";
   progname+=argv[0];
   progname+="  (-:";
   size_t pos;
   pos=progname.find("./");
   if (!(pos==string::npos)) {
      progname.erase(pos,2);
   }
   if (argc<2) {
      setScrRedBoldFont();
      cout << "\nError: Not enough arguments." << endl;
      setScrNormalFont();
      cout << "\nTry: \n\t" << argv[0] << " -h\n" << endl << "to view the help menu.\n\n";
      exit(1);
   }
   if (string(argv[1])==string("-h")) {
      printHelpMenu(argc,argv);
      exit(1);
   }
   for (int i=1; i<argc; i++){
      if (argv[i][0] == '-'){
         switch (argv[i][1]){
            case 'a':
               if ((i+2)>=argc) {printErrorMsg(argv,'a');}
               flags.setats=(++i);
               i++;
               break;
            case 'k':
               flags.kpgnp=i;
               break;
            case 'l':
               flags.showatlbls=i;
               break;
            case 'L':
               flags.uponbp=0;
               flags.uponsl=i;
               break;
            case 'n':
               flags.setn1=(++i);
               if (i>=argc) {printErrorMsg(argv,'n');}
               break;
            case 's':
               flags.setstep=(++i);
               if (i>=argc) {printErrorMsg(argv,'s');}
               break;
            case 'o':
               flags.outfname=(++i);
               if (i>=argc) {printErrorMsg(argv,'o');}
               break;
            case 'p':
               flags.prop2plot=(++i);
               if (i>=argc) {printErrorMsg(argv,'p');}
               break;
            case 'P':
               flags.mkplt=i;
               break;
            case 'z':
               flags.zipdat=i;
               break;
            case 'v':
               flags.quiet=0;
               break;
            case 'V':
               progname=argv[0];
               pos=progname.find("./");
               if (!(pos==string::npos)) {progname.erase(pos,2);}
               cout << progname << " " << CURRENTVERSION << endl;
               exit(0);
               break;
            case 'h':
               printHelpMenu(argc,argv);
               exit(1);
               break;
            case '-':
               processDoubleDashOptions(argc,argv,flags,i);
               break;
            default:
               cout << "\nCommand line error. Unknown switch: " << argv[i] << endl;
               cout << "\nTry: \n\t" << argv[0] << " -h\n" << endl << "to view the help menu.\n\n";
               exit(1);
         }
      }
   }
   return;
}//end updateFlags