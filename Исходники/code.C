int main (int argc, string argv[])
#endif
{
#ifndef SIM_SOCLIB
   long c;

   while ((c = getopt(argc, argv, "h")) != -1) {
     switch(c) {
      case 'h':
	Help();
	exit(-1);
	break;
      default:
	fprintf(stderr, "Only valid option is \"-h\".\n");
	exit(-1);
	break;
     }
   }
#endif

   Global = NULL;
   initparam(defv);
   startrun();
   initoutput();
   tab_init();

   Global->tracktime = 0;
   Global->partitiontime = 0;
   Global->treebuildtime = 0;
   Global->forcecalctime = 0;
   Global->current_id = 0;

   CLOCK(Global->computestart);

   printf("COMPUTESTART  = %12lu\n",Global->computestart);

   CREATE(SlaveStart, NPROC);

   WAIT_FOR_END(NPROC);

   CLOCK(Global->computeend);

   printf("COMPUTEEND    = %12lu\n",Global->computeend);
   printf("COMPUTETIME   = %12lu\n",Global->computeend - Global->computestart);
   printf("TRACKTIME     = %12lu\n",Global->tracktime);
   printf("PARTITIONTIME = %12lu\t%5.2f\n",Global->partitiontime,
	  ((float)Global->partitiontime)/Global->tracktime);
   printf("TREEBUILDTIME = %12lu\t%5.2f\n",Global->treebuildtime,
	  ((float)Global->treebuildtime)/Global->tracktime);
   printf("FORCECALCTIME = %12lu\t%5.2f\n",Global->forcecalctime,
	  ((float)Global->forcecalctime)/Global->tracktime);
   printf("RESTTIME      = %12lu\t%5.2f\n",
	  Global->tracktime - Global->partitiontime -
	  Global->treebuildtime - Global->forcecalctime,
	  ((float)(Global->tracktime-Global->partitiontime-
		   Global->treebuildtime-Global->forcecalctime))/
	  Global->tracktime);
   MAIN_END;
}