//parse the config file
void ConfigSettings::parse_config(char *config_file){
	//first set the defaults
	apply_defaults();
	//store the filename
	strcpy(_config_file, config_file);
	
	FILE *cfile = fopen(_config_file, "r");	
	if (!cfile){
		fprintf(stdout, _("Cannot read file: %s\nUsing defaults...\n"), _config_file);
		return;
	}
	
	char buffer[256];
	char *tmpptr;
	while (fgets(buffer, 256, cfile)){
		//use the # as a comment, and ignore newlines
		if (buffer[0] == '#' || buffer[0] == '\n'){
			continue;
		}
		tmpptr=strtok(buffer, "=\n");
		if (strcmp(tmpptr, "card")==0){
			tmpptr=strtok(NULL, "=\"\n");
			strcpy(card, tmpptr);
		} else if (strcmp(tmpptr, "scaling")==0){
			tmpptr=strtok(NULL, "=\n");
			scaling=atoi(tmpptr);
			if (scaling < 0 || scaling > NUM_SCALE_T - 1){ scaling = _d_scaling; }  //if out of bounds, use default
		} else if (strcmp(tmpptr, "auto_mute")==0){
			tmpptr=strtok(NULL, "=\n");
			auto_mute=(bool)atoi(tmpptr);
		} else if (strcmp(tmpptr, "vertical")==0){
			tmpptr=strtok(NULL, "=\n");
			vertical=(bool)atoi(tmpptr);
		} else if (strcmp(tmpptr, "window_x")==0){
			tmpptr=strtok(NULL, "=\n");
			window_x=atoi(tmpptr);
		} else if (strcmp(tmpptr, "window_y")==0){
			tmpptr=strtok(NULL, "=\n");
			window_y=atoi(tmpptr);
		} else if (strcmp(tmpptr, "window_width")==0){
			tmpptr=strtok(NULL, "=\n");
			window_width=atoi(tmpptr);
		} else if (strcmp(tmpptr, "window_height")==0){
			tmpptr=strtok(NULL, "=\n");
			window_height=atoi(tmpptr);
		} else if (strcmp(tmpptr, "slider_width")==0){
			tmpptr=strtok(NULL, "=\n");
			slider_width=atoi(tmpptr);
		} else if (strcmp(tmpptr, "slider_height")==0){
			tmpptr=strtok(NULL, "=\n");
			slider_height=atoi(tmpptr);
		} else if (strcmp(tmpptr, "slider_margin")==0){
			tmpptr=strtok(NULL, "=\n");
			slider_margin=atoi(tmpptr);
		} else if (strcmp(tmpptr, "seg_thickness")==0){
			tmpptr=strtok(NULL, "=\n");
			seg_thickness=atoi(tmpptr);
		} else if (strcmp(tmpptr, "seg_spacing")==0){
			tmpptr=strtok(NULL, "=\n");
			seg_spacing=atoi(tmpptr);
		} else if (strcmp(tmpptr, "background_color")==0){
			tmpptr=strtok(NULL, "=\n");
			htonf(background_color, tmpptr);
		} else if (strcmp(tmpptr, "border_color")==0){
			tmpptr=strtok(NULL, "=\n");
			htonf(border_color, tmpptr);
		} else if (strcmp(tmpptr, "unlit_color")==0){
			tmpptr=strtok(NULL, "=\n");
			htonf(unlit_color, tmpptr);
		} else if (strcmp(tmpptr, "lit_color")==0){
			tmpptr=strtok(NULL, "=\n");
			htonf(lit_color, tmpptr);
		} else if (strcmp(tmpptr, "enable_tray_icon")==0){
			tmpptr=strtok(NULL, "=\n");
			enable_tray_icon=(bool)atoi(tmpptr);
		} else if (strcmp(tmpptr, "enable_tray_menu")==0){
			tmpptr=strtok(NULL, "=\n");
			enable_tray_menu=(bool)atoi(tmpptr);
		} else if (strcmp(tmpptr, "tray_icon_background_color")==0){
			tmpptr=strtok(NULL, "=\n");
			htonf(tray_icon_background_color, tmpptr);
			enable_tray_icon_background_color=true;
		} else if (strcmp(tmpptr, "tray_slider_vertical")==0){
			tmpptr=strtok(NULL, "=\n");
			tray_slider_vertical=(bool)atoi(tmpptr);
		} else if (strcmp(tmpptr, "tray_slider_width")==0){
			tmpptr=strtok(NULL, "=\n");
			tray_slider_width=atoi(tmpptr);
		} else if (strcmp(tmpptr, "tray_slider_height")==0){
			tmpptr=strtok(NULL, "=\n");
			tray_slider_height=atoi(tmpptr);
		} else if (strcmp(tmpptr, "tray_slider_offset")==0){
			tmpptr=strtok(NULL, "=\n");
			tray_slider_offset=atoi(tmpptr);
		} else if (strcmp(tmpptr, "tray_control")==0){
			tmpptr=strtok(NULL, "=\n");
			tray_control_numid=atoi(tmpptr);
		} else if (strcmp(tmpptr, "sliders:")==0){
			int n;
			for (n=0; fgets(buffer, 256, cfile); n++){
				char *buff = buffer;
				//skip over any whitespace
				while (buff[0] && (buff[0] == ' ' || buff[0] == '\t')){ buff++; }
				//skip any commented lines or newlines
				if (buff[0] == '#' || buff[0] == '\n'){
					n--;
					continue;
				}

				//save the numid and initialize the name to an empty string
				numid_list[n] = atoi(buff);
				name_list[n][0] = '\0';
			}
			num_numids=n;
		}
	}
	
	fclose(cfile);
	
}