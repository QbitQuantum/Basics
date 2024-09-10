void init_all(int argc, char **argv)
{
   cpu_info();

   char *config = 0, *bpx = 0, *labels = 0;

   char opt;
   while ((opt = getopt(argc, argv, "i:l:b:")) != EOF)
       switch (opt)
       {
       case 'i':
           config = optarg;
           break;
       case 'b':
           bpx = optarg;
           break;
       case 'l':
           labels = optarg;
       }

   temp.Minimized = false;

   init_z80tables();
   init_ie_help();
   load_config(config);
   //make_samples();
   #ifdef MOD_GS
   init_gs();
   #endif
   init_leds();
   init_tape();
   init_hdd_cd();
   start_dx();
   init_debug();
   applyconfig();
   main_reset();
   autoload();
   init_bpx(bpx);
   init_labels(labels);
   temp.Gdiplus = GdiplusStartup();
   if (!temp.Gdiplus)
   {
       color(CONSCLR_WARNING);
       printf("warning: gdiplus.dll was not loaded, only SCR and BMP screenshots available\n");
   }

   if (comp.ts.vdac2)
   {
     if (!vdac2::open_ft8xx())
     {
       color(CONSCLR_WARNING);
       printf("warning: ft8xx library was not loaded\n");
       comp.ts.vdac2 = false;
     }
   }
   
   load_errors = 0;
   trd_toload = 0;
   *(DWORD*)trd_loaded = 0; // clear loaded flags, don't see autoload'ed images

   for (; optind < argc; optind++)
   {
      char fname[0x200], *temp;
      GetFullPathName(argv[optind], sizeof fname, fname, &temp);

      trd_toload = DefaultDrive; // auto-select
      if (!loadsnap(fname)) errmsg("error loading <%s>", argv[optind]), load_errors = 1;
   }

   if (load_errors) {
      int code = MessageBox(wnd, "Some files, specified in\r\ncommand line, failed to load\r\n\r\nContinue emulation?", "File loading error", MB_YESNO | MB_ICONWARNING);
      if (code != IDYES) exit();
   }

   SetCurrentDirectory(conf.workdir);
//   timeBeginPeriod(1);

   InitializeCriticalSection(&tsu_toggle_cr);
}