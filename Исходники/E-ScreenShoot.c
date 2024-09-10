static void
load_config(void)
{
   opt.quality = atoi(Epplet_query_config_def("QUALITY", "75"));
   invquality = (100 - opt.quality);
   opt.win = atoi(Epplet_query_config_def("WIN_AREA", "0"));
   opt.do_ftp = atoi(Epplet_query_config_def("DO_FTP", "0"));
   opt.ftp_passive = atoi(Epplet_query_config_def("FTP_PASSIVE", "1"));
   opt.run_script = atoi(Epplet_query_config_def("RUN_SCRIPT", "0"));
   opt.view_shot = atoi(Epplet_query_config_def("VIEW_SHOT", "1"));
   opt.frame = atoi(Epplet_query_config_def("WM_FRAME", "1"));
   opt.do_cloak = atoi(Epplet_query_config_def("DO_CLOAK", "1"));
   opt.beep = atoi(Epplet_query_config_def("BEEP", "1"));
   opt.cloak_anim = atoi(Epplet_query_config_def("CLOAK_ANIM", "8"));
   if (opt.cloak_anim == 25)
     {
	opt.rand_cloak = 1;
	choose_random_cloak(NULL);
     }
   else
     {
	opt.rand_cloak = 0;
     }
   opt.delay = atof(Epplet_query_config_def("SHOT_DELAY", "0"));
   opt.cloak_delay = atof(Epplet_query_config_def("CLOAK_DELAY", "4"));
   opt.rand_delay = atof(Epplet_query_config_def("RAND_DELAY", "60"));
   opt.draw_interval = atof(Epplet_query_config_def("DRAW_INTERVAL", "0.1"));
   if (opt.dir)
      free(opt.dir);
   opt.dir = _Strdup(Epplet_query_config_def("DIRECTORY", "$HOME/"));
   if (opt.file_prefix)
      free(opt.file_prefix);
   opt.file_prefix = _Strdup(Epplet_query_config_def("FILE_PREFIX", "shot_"));
   if (opt.file_stamp)
      free(opt.file_stamp);
   opt.file_stamp =
      _Strdup(Epplet_query_config_def("FILE_STAMP", "`date +%d-%m-%y_%H%M%S`"));
   if (opt.file_type)
      free(opt.file_type);
   opt.file_type = _Strdup(Epplet_query_config_def("FILE_TYPE", "jpg"));
   if (opt.script)
      free(opt.script);
   opt.script =
      _Strdup(Epplet_query_config_def("SCRIPT_TO_RUN", "scrshot_script"));
   if (opt.viewer)
      free(opt.viewer);
   opt.viewer = _Strdup(Epplet_query_config_def("SHOT_VIEWER", "ee"));
   if (opt.ftp_user)
      free(opt.ftp_user);
   opt.ftp_user = _Strdup(Epplet_query_config_def("FTP_USER", "username"));
   if (opt.ftp_pass)
      free(opt.ftp_pass);
   opt.ftp_pass = _Strdup(Epplet_query_config_def("FTP_PASS", "password"));
   if (opt.ftp_host)
      free(opt.ftp_host);
   opt.ftp_host =
      _Strdup(Epplet_query_config_def("FTP_HOST", "ftp.myhost.com"));
   if (opt.ftp_dir)
      free(opt.ftp_dir);
   opt.ftp_dir = _Strdup(Epplet_query_config_def("FTP_DIR", "/images/"));
   if (opt.ftp_file)
      free(opt.ftp_file);
   opt.ftp_file = _Strdup(Epplet_query_config_def("FTP_FILE", "shot.jpg"));
   if (opt.ftp_temp)
      free(opt.ftp_temp);
   opt.ftp_temp = _Strdup(Epplet_query_config_def("FTP_TEMP", "uploading.jpg"));
   if (opt.grabber)
      free(opt.grabber);
   opt.grabber = _Strdup(Epplet_query_config_def("SHOT_GRABBER", "import"));
}