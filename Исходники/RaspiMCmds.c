void process_cmd(char *readbuf, int length) {
   typedef enum pipe_cmd_type{ca,im,tl,px,bo,tv,an,as,at,ac,ab,sh,co,br,sa,is,vs,rl,ec,em,wb,mm,ie,ce,ro,fl,ri,ss,qu,pv,bi,ru,md,sc,rs,bu,mn,mt,mi,mb,me,mx,mf,vm,vp,wd,sy,cn,st} pipe_cmd_type;
   char pipe_cmds[] = "ca,im,tl,px,bo,tv,an,as,at,ac,ab,sh,co,br,sa,is,vs,rl,ec,em,wb,mm,ie,ce,ro,fl,ri,ss,qu,pv,bi,ru,md,sc,rs,bu,mn,mt,mi,mb,me,mx,mf,vm,vp,wd,sy,cn,st";
   pipe_cmd_type pipe_cmd;
   int parcount;
   char pars[128][10];
   long int par0;
   char cmd[3];
   char par[MAX_COMMAND_LEN];
   char *parstring=0, *temp;
   int key = -1;
   
   if (length < 2 || length > (MAX_COMMAND_LEN - 2)) return;
   
   //Get cmd
   strncpy(cmd, readbuf, 2);
    //find 2 letter command and translate into enum
   temp = strstr(pipe_cmds, cmd);
   if (temp == NULL) return;
   pipe_cmd = (pipe_cmd_type)((temp - pipe_cmds) / 3);
  
   if(length > 3) {
      strcpy(par, readbuf + 3);
      par[length-3] = 0;
      //extract space separated numeric parameters
      // and make separate string parameter (strtok changes the original)
      asprintf(&parstring, "%s", par);
      parcount = 0;
      temp = strtok(par, " ");
      while(parcount<10 && temp != NULL) {
         strcpy(pars[parcount], temp);
         parcount++;
         temp = strtok(NULL, " ");
      }
      par0 = strtol(pars[0], NULL, 10);
   } else {
      par0 = 0;
   }
   
   switch(pipe_cmd) {
      case ca:
         if(par0 == 1) {
            if (parcount > 1) {
               long vtime = strtol(pars[1], NULL, 10);
               video_stoptime = time(NULL) + vtime;
               printLog("Capturing %d seconds\n", vtime);
            }
            start_video(0);
         }  else {
            stop_video(0);
         }
         break;
      case im:
         capt_img();
         break;
      case tl:
         if(par0) {
            timelapse = 1;
            lapse_cnt = 1;
            updateStatus();
            printLog("Timelapse started\n");
         }
         else {
            image2_cnt++;
            timelapse = 0;
            updateStatus();
            printLog("Timelapse stopped\n");
         }
         break;
      case px:
         stop_all();
         addUserValue(c_video_width, pars[0]);
         addUserValue(c_video_height, pars[1]);
         addUserValue(c_video_fps, pars[2]);
         addUserValue(c_MP4Box_fps, pars[3]);
         addUserValue(c_image_width, pars[4]);
         addUserValue(c_image_height, pars[5]);
         start_all(0);
         break;
      case bo:
         addUserValue(c_MP4Box, pars[0]);
         break;
      case tv:
         addUserValue(c_tl_interval, pars[0]);
         break;
      case an:
         addUserValue(c_annotation, parstring);
         break;
      case as:
         addUserValue(c_anno_text_size, pars[0]);
         break;
      case at:
         addUserValue(c_anno3_custom_text_colour, pars[0]);
         addUserValue(c_anno3_custom_text_Y, pars[1]);
         addUserValue(c_anno3_custom_text_U, pars[2]);
         addUserValue(c_anno3_custom_text_V, pars[3]);
         break;
      case ac:
         addUserValue(c_anno3_custom_background_colour, pars[0]);
         addUserValue(c_anno3_custom_background_Y, pars[1]);
         addUserValue(c_anno3_custom_background_U, pars[2]);
         addUserValue(c_anno3_custom_background_V, pars[3]);
         break;
      case ab:
         addUserValue(c_anno_background, pars[0]);
         break;
      case sh:
         key = c_sharpness;
         break;
      case co:
         key = c_contrast;
         break;
      case br:
         key = c_brightness;
         break;
      case sa:
         key = c_saturation;
         break;
      case is:
         key = c_iso;
         break;
      case vs:
         key = c_video_stabilisation;
         break;
      case rl:
         key = c_raw_layer;
         break;
      case ec:
         key = 1000 + c_exposure_compensation;
         break;
      case em:
         key = 1000 + c_exposure_mode;
         break;
      case wb:
         key = 1000 + c_white_balance;
         break;
      case mm:
         key = 1000 + c_metering_mode;
         break;
      case ie:
         key = 1000 + c_image_effect;
         break;
      case ce:
         addUserValue(c_colour_effect_u, pars[1]);
         addUserValue(c_colour_effect_v, pars[2]);
         key = c_colour_effect_en;
         break;
      case ro:
         key = c_rotation;
         break;
      case fl:
         if(par0 & 1) addUserValue(c_hflip, "1"); else addUserValue(c_hflip, "0"); 
         if((par0 >> 1) & 1) addUserValue(c_vflip, "1"); else addUserValue(c_vflip, "0"); 
         cam_set(c_hflip);
         break;
      case ri:
         addUserValue(c_sensor_region_y, pars[1]);
         addUserValue(c_sensor_region_w, pars[2]);
         addUserValue(c_sensor_region_h, pars[3]);
         key = c_sensor_region_x;
         break;
      case ss:
         addUserValue(c_shutter_speed, pars[0]);
         key = c_shutter_speed;
         break;
      case qu:
         key = c_image_quality;
         break;
      case pv:
         stop_all();
         addUserValue(c_quality, pars[0]);
         addUserValue(c_width, pars[1]);
         addUserValue(c_divider, pars[2]);
         start_all(0);
         break;
      case bi:
         stop_all();
         addUserValue(c_video_bitrate, pars[0]);
         start_all(0);
         break;
      case st:
         stop_all();
         addUserValue(c_stat_pass, pars[0]);
         start_all(0);
         break;
      case wd:
         addUserValue(c_watchdog_interval, pars[0]);
         addUserValue(c_watchdog_errors, pars[1]);
         break;
      case ru:
         if (par0 == 0) {
            stop_all();
            idle = 1;
            printLog("Stream halted\n");
         } else {
            start_all(1);
            idle = 0;
            printLog("Stream continued\n");
         }
         updateStatus();
         break;
      case mx:
         key = c_motion_external;
         //If switching to internal with motion detection on then try to kill external motion
         if (cfg_val[c_motion_detection] != 0 && !par0) {
            if(system("killall motion") == -1) error("Could not stop external motion", 1);
            printLog("External motion detection stopped\n");
         }
         break;
      case md:
         exec_macro(cfg_stru[c_do_cmd], readbuf);
         stop_all();
         if (cfg_val[c_motion_external]) {
            if(par0 == 0) {
               if(system("killall motion") == -1) error("Could not stop external motion", 1);
               printLog("External motion detection stopped\n");
            }
            else {
               if (cfg_val[c_motion_detection] == 0) {
                  if(system("motion") == -1) error("Could not start external motion", 1);
                  printLog("External motion detection started\n");
               } else {
                  printLog("Motion already running. md 1 ignored\n");
               }
            }
         } else {
            if(par0 == 0) {
               printLog("Internal motion detection stopped\n");
            }
            else {
               printLog("Internal motion detection started\n");
            }
         }
         cfg_val[c_motion_detection] = par0?1:0;
         start_all(0);
         updateStatus();
         break;
      case sc:
         set_counts();
         printLog("Scan for highest count\n");
         break;
      case rs:
         printLog("Reset settings to defaults\n");
         stop_all();
         read_config("/etc/raspimjpeg", 1);
         saveUserConfig(cfg_stru[c_user_config]);
         start_all(0);
         break;
      case bu:
         key = c_video_buffer;
         break;
      case vp:
         stop_all();
         addUserValue(c_vector_preview, pars[0]);
         start_all(0);
         break;
      case mn:
         key = c_motion_noise;
         break;
      case mt:
         key = c_motion_threshold;
         break;
      case mi:
         key = c_motion_image + 1000;
         break;
      case mb:
         key = c_motion_startframes;
         break;
      case me:
         key = c_motion_stopframes;
         break;
      case mf:
         key = c_motion_file;
         break;
      case vm:
         key = c_vector_mode;
         break;
      case sy:
         exec_macro(parstring, NULL);
         break;
      case cn:
         stop_all();
         addUserValue(c_camera_num, pars[0]);
         start_all(0);
         break;
      default:
         printLog("Unrecognised pipe command\n");
         break;
   }