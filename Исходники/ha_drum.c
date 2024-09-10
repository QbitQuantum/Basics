int Zoltan_Drum_Create_Model(ZZ *zz) {
  char *yo = "Zoltan_Drum_Create_Model";
  int ierr;
  FILE *fp;
  char buf[80];

  /* check params */
  Zoltan_Drum_Init(zz);

  if (zz->Drum.use_drum && !zz->Drum.dmm) {
    if (zz->Drum.build_tree) {
      zz->Drum.dmm = DRUM_createMachineModel(zz->Communicator,
					     zz->Drum.debug_level);
      if (!zz->Drum.dmm) {
	ZOLTAN_PRINT_ERROR(zz->Proc, yo,
			   "Unable to create DRUM machine model");
	return ZOLTAN_FATAL;
      }

      /* some parameters should be set between machine model creation and
	 machine model initialization */
      sprintf(buf, "%d", zz->Drum.use_flat_model);
      DRUM_setParam(zz->Drum.dmm, "USE_FLAT_MODEL", buf);
      sprintf(buf, "%d", zz->Drum.ignore_rpp);
      DRUM_setParam(zz->Drum.dmm, "IGNORE_RPP", buf);

      ierr = DRUM_initMachineModel(zz->Drum.dmm);
      if (ierr == DRUM_FATAL || ierr == DRUM_MEMERR) {
	ZOLTAN_PRINT_ERROR(zz->Proc, yo,
			   "Unable to initialize DRUM machine model");
	return (ierr == DRUM_FATAL ? ZOLTAN_FATAL : ZOLTAN_MEMERR);
      }

      if( zz->Drum.drum_hier){
	Zoltan_Set_Param(zz, "LB_METHOD", "HIER");
	ierr = DRUM_hierCreateCallbacks(zz->Drum.dmm, zz);
	if(ierr != DRUM_OK){
	  ZOLTAN_PRINT_ERROR(zz->Proc, yo,
			     "DRUM_hier_create_callbacks returned an error");
	  return (ierr == DRUM_FATAL ? ZOLTAN_FATAL : ZOLTAN_MEMERR);
	}
	DRUM_hierSetCallbacks(zz);
      }

      /* print the "power file" if it was requested */
      if (zz->Proc == 0 && strcmp(zz->Drum.power_filename,"")) {
	fp = fopen(zz->Drum.power_filename, "w");
	if (fp) {
	  DRUM_printMachineModel(zz->Drum.dmm, fp);
	  fclose(fp);
	}
	else {
	  ZOLTAN_PRINT_WARN(zz->Proc, yo, "Could not open power file");
	}
      }
      
      DRUM_setMonitoringFrequency(zz->Drum.dmm, zz->Drum.monitoring_frequency);
      sprintf(buf, "%d", zz->Drum.use_snmp);
      DRUM_setParam(zz->Drum.dmm, "USE_SNMP", buf);
      sprintf(buf, "%d", zz->Drum.use_kstat);
      DRUM_setParam(zz->Drum.dmm, "USE_KSTAT", buf);
      sprintf(buf, "%d", zz->Drum.use_nws);
      DRUM_setParam(zz->Drum.dmm, "USE_NWS", buf);
      sprintf(buf, "%d", zz->Drum.nws_method);
      DRUM_setParam(zz->Drum.dmm, "NWS_METHOD", buf);
      sprintf(buf, "%d", zz->Drum.monitor_memory);
      DRUM_setParam(zz->Drum.dmm, "MONITOR_MEMORY", buf);
      sprintf(buf, "%d", zz->Drum.use_network_powers);
      DRUM_setParam(zz->Drum.dmm, "USE_NETWORK_POWERS", buf);
      sprintf(buf, "%f", zz->Drum.fixed_network_weight);
      DRUM_setParam(zz->Drum.dmm, "FIXED_NETWORK_WEIGHT", buf);
    }
    
    if (zz->Drum.start_monitors) {
      ierr = DRUM_startMonitoring(zz->Drum.dmm);
      if (ierr == DRUM_FATAL || ierr == DRUM_MEMERR) {
	ZOLTAN_PRINT_ERROR(zz->Proc, yo,
			   "Unable to start DRUM monitors");
	return (ierr == DRUM_FATAL ? ZOLTAN_FATAL : ZOLTAN_MEMERR);
      }
    }
  }

  return ZOLTAN_OK;
}