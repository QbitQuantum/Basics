/*Mainloop*/
void loop() {
	/*Auswertung des anstehenden Aufgaben im Scheduler*/
	int i; unsigned char new_value = 0; unsigned char new_heading = 0; 
	for (i = 0; i < MAX_TASKS; i++) {
		if (scheduler[i].task == NOTHING || get_current_millis() < scheduler[i].tv_msec) {continue;}
		switch (scheduler[i].task) {
			case NOTHING: break;
			case MEASURE:
				/*Fordert den als Parameter uebergebenen Sensor auf eine Messung zu starten und bestimmt den Lese-Zeitpunkt*/			
				srf[scheduler[i].param - SE0_ADDRESS].measure();
				schedule_add((long)srf_speed[scheduler[i].param - SE0_ADDRESS], READ_MEASURE, scheduler[i].param);
				scheduler[i].task = NOTHING;
				break;
			case READ_MEASURE: {
				unsigned short index = scheduler[i].param - SE0_ADDRESS;
				/*Liest die Messdaten des als Parameter uebergebenen Sensors aus und veranlasst erneute Messung*/
				srf[index].read_it(get_current_millis());
				schedule_add((long)srf[index].get_delay(), MEASURE, scheduler[i].param);
				if(state == HOLD_STILL || state == MEASURE_ENVIRONMENT || state == GET_ANCHOR) {
					nvalue[index] = 1;
				}
				/*if (state == HOLD_STILL || state == HEAD_TO_MIDDLE || state = HTM_DELAY) {
					nvalue2[scheduler[i].param - SE0_ADDRESS] = 1;
				}*/
				new_value = scheduler[i].param;
				
				/*Korrektur der Messwerte bei Schieflage des Copters bei glaubhaften Winkeln*/
				if ((index == 0 || index == 1) && (abs(current_roll_rad) < MAX_ROLL_ANGLE))		srf[index].set_mean((unsigned short)(srf[index].get_mean()*cos(current_roll_rad)));
				else if ((index == 2 || index == 3) && (abs(current_pitch_rad) < MAX_PITCH_ANGLE))	srf[index].set_mean((unsigned short)(srf[index].get_mean()*cos(current_roll_rad)));
				
				/*Korrektur der Messwerte, wenn sich ein Sensor im Nahbereich (< SE_MIN_DISTANCE) befindet*/
				static unsigned char 	rm_state[SE_COUNT];
				static short		rm_min[SE_COUNT];
				if (state != IDLE && state != INIT && state != DELAY) {
					if (rm_state[index] == 0 && srf[index].get_mean() < SE_MIN_DISTANCE) {
						rm_state[index] = 1;
						if (index == 0 || index == 2)	rm_min[index] = srf[index+1].get_mean() - SE_MIN_DIFF;
						else				rm_min[index] = srf[index-1].get_mean() - SE_MIN_DIFF;
						srf[index].set_mean(SE_MIN);
					} else if (rm_state[index] == 1) {
						if ((index == 0 || index == 2) && srf[index+1].get_mean() < rm_min[index]) {
							rm_state[index] = 0;
						} else if ((index == 1 || index == 3) && srf[index-1].get_mean() < rm_min[index]) {
							rm_state[index] = 0;
						} else {
							srf[index].set_mean(SE_MIN);
						}
					}
				}
				if (rm_state[0] == 1 && rm_state[1] == 1) {rm_state[0] = 0; rm_state[1] = 0;}
				if (rm_state[2] == 1 && rm_state[3] == 1) {rm_state[2] = 0; rm_state[3] = 0;}
				
				if (state == HOLD_STILL || state ==  GET_ANCHOR || state == HTM_DELAY) {
					if (nvalue2[0] == 1 && nvalue2[1] == 1 && nvalue2[2] == 1 && nvalue2[3] == 1) {
						slam_insert_v((srf[0].get_cm_per_s() + srf[1].get_cm_per_s())/2,(srf[2].get_cm_per_s() + srf[3].get_cm_per_s())/2,current_heading,get_current_millis());
						nvalue2[0] = 0; nvalue2[1] = 0; nvalue2[2] = 0; nvalue2[3] = 0;
					}
				}
				
				/*Speichert den gelesenen Messwert in der entsprechenden Log-Datei*/
				#if LOG > 0
				FILE *fd;
				if (scheduler[i].param == SE0_ADDRESS) 	fd = fd_112;
				else if (scheduler[i].param == SE1_ADDRESS) 	fd = fd_113;
				else if (scheduler[i].param == SE2_ADDRESS) 	fd = fd_114;
				else						fd = fd_115;
				fprintf(fd,"%lu\t%u\t%u\n", srf[scheduler[i].param - SE0_ADDRESS].get_msec(), srf[scheduler[i].param - SE0_ADDRESS].get_data(), srf[scheduler[i].param - SE0_ADDRESS].get_mean());
				#endif
				scheduler[i].task = NOTHING;
				break;
			}
			case SAVE_LOG:
				/*Sichert die bisher geloggten Daten*/
				#if LOG > 0
				fclose(fd_112);
				fclose(fd_113);
				fclose(fd_114);
				fclose(fd_115);
				fclose(fd_data);
				char tmp_dir[32]; strcpy(tmp_dir,log_dir);
				fd_112 = fopen(strcat(tmp_dir,"/112"), "a"); strcpy(tmp_dir,log_dir);
				fd_113 = fopen(strcat(tmp_dir,"/113"), "a"); strcpy(tmp_dir,log_dir);
				fd_114 = fopen(strcat(tmp_dir,"/114"), "a"); strcpy(tmp_dir,log_dir);
				fd_115 = fopen(strcat(tmp_dir,"/115"), "a"); strcpy(tmp_dir,log_dir);
				fd_data= fopen(strcat(tmp_dir,"/data"),"a"); strcpy(tmp_dir,log_dir);
				schedule_add(LOG_SPEED,SAVE_LOG,0);
				#endif
				scheduler[i].task = NOTHING;
				break;   
			case CHECK_STILL:
				/*Prueft auf Stillstand des Copters*/
				if (still && state == HOLD_STILL) {
					if (scheduler[i].param < CHECK_STILL_COUNT) {
						schedule_add(CHECK_STILL_SPEED,CHECK_STILL,scheduler[i].param+1);
					} else {
						state = MEASURE_ENVIRONMENT;
						still = 0;
						schedule_add(CHECK_STILL_SPEED,CHECK_STILL, 0);
					}
				} else {
					schedule_add(CHECK_STILL_SPEED,CHECK_STILL,0);
				}
				scheduler[i].task = NOTHING;
				break;
			case CHANGE_STATE:
				/*Ändert den aktuellen Status zum als Parameter übergebenen Status*/
				state = (states)scheduler[i].param;
				if ((states)scheduler[i].param == HOLD_STILL) hs_state = 0;
				scheduler[i].task = NOTHING;
				break;
			case SHOW_ME: {
				/*Schreibt Messwerte und Neigungswinkel auf das Terminal*/
				char st[16];
				switch (state) {
					case INIT: 			sprintf(st, "INIT"); 		break;
					case MEASURE_ENVIRONMENT: 	sprintf(st, "ME"); 		break;
					case IDLE: 			sprintf(st, "IDLE"); 		break;
					case HOLD_STILL: 		sprintf(st, "HOLD_STILL"); 	break;
					case GET_ALIGNMENT: 		sprintf(st, "GET_ALIGNMENT"); 	break;
					case GET_ANCHOR: 		sprintf(st, "GET_ANCHOR"); 	break;
					case DELAY:			sprintf(st, "DELAY");		break;
					default: 			sprintf(st, "???"); 		break;
				}
					
				if (roll > 9 || roll < 0) 	printf("roll: %d\tpitch: %d\tyaw: %d\theading: %d\tdhead: %d\tSE0: %d\tSE1: %d\tSE2: %d\tSE3:%d\tstate: %s\n", roll, pitch, yaw, current_heading, desired_heading, srf[0].get_mean(), srf[1].get_mean(), srf[2].get_mean(), srf[3].get_mean(),st);
				else 				printf("roll: %d\t\tpitch: %d\tyaw: %d\theading: %d\tdhead. %d\tSE0: %d\tSE1: %d\tSE2: %d\tSE3:%d\tstate: %s\n", roll, pitch, yaw, current_heading, desired_heading, srf[0].get_mean(), srf[1].get_mean(), srf[2].get_mean(), srf[3].get_mean(),st);
				schedule_add(100,SHOW_ME,0);
				scheduler[i].task = NOTHING;
				
				/*Mavlinkkommunikation mit QGroundcontrol (basierend auf Based on http://qgroundcontrol.org/dev/mavlink_linux_integration_tutorial)*/
				mavlink_message_t msg;
				uint16_t len;
				uint8_t buf[MAVLINK_MAX_PACKET_LEN];
				
				static int i; i++;
				if (i == 10) {
					i = 0;
					mavlink_msg_heartbeat_pack(0, 0, &msg, 0, 0, 0, 0, 0);
					len = mavlink_msg_to_send_buffer(buf, &msg);
					sendto(s, buf, len, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
				}
				mavlink_msg_debug_vect_pack(0,0,&msg,"DEBUG",0,roll,srf[0].get_mean(),srf[0].get_data());
				len = mavlink_msg_to_send_buffer(buf, &msg);
				sendto(s, buf, len, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
				break;
			}
			default: if(WARNINGS){perror("LOOP: Unbekannte Aufgabe im Scheduler.");} break; 
		}
	}

	/*Auswertung der Daten, die an der seriellen Schnittstelle anliegen.*/
	struct timeval tv; tv.tv_sec = 0; tv.tv_usec = 0;
	/*Prueft, ob Daten an der seriellen Schnittstelle anliegen*/
	FD_ZERO(&tty_fdset);
	FD_SET(tty_fd, &tty_fdset);
	if (select(tty_fd+1, &tty_fdset, NULL, NULL, &tv) == -1) {perror("LOOP: select() fehlgeschlagen"); exit(1);}

	/*Liest ein einzelnes Byte von der seriellen Schnittstelle und prueft, ob ein Mavlinkpaket vervollstaendigt wurde*/
	if (FD_ISSET(tty_fd, &tty_fdset)) {
		static mavlink_message_t msg;
		static mavlink_status_t status;
		char c[1];
		if (read(tty_fd,c,1) == -1) {if(WARNINGS){perror("LOOP: Fehler beim Lesen aus " TTY_DEVICE);}}
		#if DEBUG_LEVEL > 2
		printf("%#x\n",c[0]);
		#endif
		if (mavlink_parse_char(MAVLINK_COMM_0,(uint8_t) *c, &msg, &status)) {
			#if DEBUG_LEVEL > 1
			printf("%u Mavlinkpaket empfangen: %d\n", get_current_millis(), msg.msgid);
			#endif
			//printf("%lu Mavlinkpaket empfangen: %d\n", get_current_millis(), msg.msgid);
			
			switch (msg.msgid) {
				case MAVLINK_MSG_ID_HEARTBEAT:
					/*Beim Empfang des ersten Heartbeats wird zunaechst ein eventuell vorhandener Datenstream gekuendigt und ein neuer Datenstream abonnemiert*/
					mavlink_heartbeat_t hb;
					mavlink_msg_heartbeat_decode(&msg,&hb);
					if (!first_heartbeat) {
						first_heartbeat = 1;
						request_data_stream(MAV_DATA_STREAM_ALL,0,0);
					}
					//if (state == IDLE) {
					if (state == IDLE && (hb.custom_mode == 13 /*EXT_CTRL*/ || desktop_build)) {
						std::cout << "State changed from IDLE to INIT.\n";
						state = INIT;
						schedule_add(2000,CHANGE_STATE,(int)HOLD_STILL);
						request_data_stream(MAV_DATA_STREAM_EXTRA2/*VFR_HUD*/,DATA_STREAM_SPEED,1);
						init_state = 1;
					}
					break;
				case MAVLINK_MSG_ID_VFR_HUD:
					/*Speichert bei Empfang von HUD-Daten die aktuelle Ausrichtung des Copters*/
					mavlink_vfr_hud_t hud_data;
					mavlink_msg_vfr_hud_decode(&msg, &hud_data);
					old_heading = current_heading;
					current_heading = hud_data.heading;
					new_heading = 1;
					break;
				case MAVLINK_MSG_ID_ATTITUDE:
					mavlink_attitude_t adata;
					mavlink_msg_attitude_decode(&msg,&adata);
					old_heading = current_heading;
					current_heading = ((short)lround(DEG(adata.yaw))+360)%360;
					current_pitch_rad = adata.pitch;
					current_roll_rad = adata.roll;
					new_heading = 1;
					break;
				case MAVLINK_MSG_ID_RAW_IMU:
					/*Speichert die Beschleunigungen auf der x- und y-Achse*/
					mavlink_raw_imu_t raw_imu;
					mavlink_msg_raw_imu_decode(&msg,&raw_imu);
					xacc = raw_imu.xacc;
					yacc = raw_imu.yacc;
					//slam_insert_acc(xacc,yacc,current_heading,get_current_millis());
					std::cout << "xacc: " << xacc << " yacc: " << yacc << "\n";
					break;
				case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
					/*Prüft, ob eine Umstellung auf externe Kontrolle erfolgt ist*/
					/*if (state != IDLE) {break;}
					mavlink_rc_channels_raw_t rc;
					mavlink_msg_rc_channels_raw_decode(&msg,&rc);
					if (desktop_build) init_state = 1; rc.chan5_raw = MODE_SWITCH_RANGE_UP-1;
					if (init_state && rc.chan5_raw < MODE_SWITCH_RANGE_UP && rc.chan5_raw > MODE_SWITCH_RANGE_DOWN) {
						std::cout << "State changed from IDLE to INIT.\n";
						schedule_add(0,CHANGE_STATE,(int)INIT);
						schedule_add(2000,CHANGE_STATE,(int)HOLD_STILL);
						request_data_stream(MAV_DATA_STREAM_RC_CHANNELS,0,0);
						request_data_stream(MAV_DATA_STREAM_EXTRA2,DATA_STREAM_SPEED,1);
						request_data_stream(MAV_DATA_STREAM_RAW_SENSORS,DATA_STREAM_SPEED,1);
					}
					if(rc.chan5_raw > MODE_SWITCH_RANGE_UP || rc.chan5_raw < MODE_SWITCH_RANGE_DOWN) {
						init_state = 1;
					}*/
					break;
				default: break;
			}
		}
	}		

	/*Berechnung der vorgeschlagenen Werte fuer roll, pitch und yaw an Hand der neuen Messwerte*/
	if (state != INIT && !new_value && !new_heading) {/*Wenn keine neuen Daten vorhanden sind -> Abarbeitung überspringen*/return;}
	switch (state) {	
		case IDLE: /*Wartet auf Aktivierung der externen Kontrolle*/	break;
		case INIT:
			std::cout << "INIT\n";
			/*Initialisiert Abarbeitung, wenn externe Kontrolle zum ersten Mal aktiviert wurde*/
			schedule_add(5000,CHECK_STILL,0);
			#if LOG > 0
			schedule_add(LOG_SPEED,SAVE_LOG,0);
			//schedule_add(SLAM_SPEED,SAVE_SLAM,0);
			#endif
			for (int i = 0; i < SE_COUNT; i++) {
				if ((int)pow(2,i) & ENABLED_SENSORS) {
					schedule_add(0, MEASURE, SE0_ADDRESS + i);
				}
			}
			slam_init(current_heading,get_current_millis());
			state = DELAY;
			break;
		case HOLD_STILL:
			if(1) {
				static short set_point[SE_COUNT];
				if (hs_state == 0) {
					hs_state = 1;
					set_point[0] = (srf[0].get_mean() + srf[1].get_mean())/2;
					set_point[1] = set_point[0];
					set_point[2] = (srf[2].get_mean() + srf[3].get_mean())/2;
					set_point[3] = set_point[2];
					//for (int i = 0; i < SE_COUNT; i++) {
					//	set_point[i] = srf[i].get_mean();
					//	std::cout << "Set_Point " << i << ":" << set_point[i] << "\n";
					//}
					/*for (int i = 0; i < SE_COUNT; i++) {
						if (set_point[i] < 100 || set_point[i] > 0) {
							if (i == 0 || i == 2) {
								set_point[i+1] -= (100 - set_point[i]);
							} else {
								set_point[i-1] -= (100 - set_point[i]);
							}
							set_point[i] = 100;
						}
					}*/
					for (int i = 0; i < SE_COUNT; i++) {
						std::cout << "Set_Point " << i << ":" << set_point[i] << "\n";
					}
				}
				/*Veranlasst den Copter auf Grundlage der Änderungen der Messwerte still zu stehen*/
				if (!new_value) break;
				if (nvalue[0] == 1 && nvalue[1] == 1) {
					if (srf[0].get_mean() == SE_MIN)	roll = between<short>(pid_roll.get(0 - srf[1].get_mean() + set_point[1],srf[1].get_msec_diff()),-max_roll,max_roll);
					else if (srf[1].get_mean() == SE_MIN) 	roll = between<short>(pid_roll.get(srf[0].get_mean() - set_point[0],srf[0].get_msec_diff()),-max_roll,max_roll);
					else 					roll = between<short>(pid_roll.get(((srf[0].get_mean() - set_point[0]) - (srf[1].get_mean() - set_point[1]))/2,(srf[0].get_msec_diff() + srf[1].get_msec_diff())/2),-max_roll,max_roll);
					nvalue[0] = 0; nvalue[1] = 0;
				}
				if (nvalue[2] == 1 && nvalue[3] == 1) {
					if (srf[2].get_mean() == SE_MIN)	pitch = between<short>(pid_pitch.get(0 - srf[3].get_mean() + set_point[3],srf[3].get_msec_diff()),-max_pitch,max_pitch);
					else if (srf[3].get_mean() == SE_MIN) 	pitch = between<short>(pid_pitch.get(srf[2].get_mean() - set_point[2],srf[2].get_msec_diff()),-max_pitch,max_pitch);
					else 					pitch = between<short>(pid_pitch.get(((srf[2].get_mean() - set_point[2]) - (srf[3].get_mean() - set_point[3]))/2,(srf[2].get_msec_diff() + srf[3].get_msec_diff())/2),-max_pitch,max_pitch);
					nvalue[2] = 0; nvalue[3] = 0;
				}
				yaw = 0;
				send_ext_ctrl();
				/*Prüfung auf Stillstand*/
				if (abs(roll) <= STILL_FAK_ROLL*max_roll/100 && abs(pitch) <= STILL_FAK_PITCH*max_pitch/100) {
					//still = 1; 
					still = 0; /*FIXME*/
				} else {
					still = 0;
				}
			}
		break;
		case MEASURE_ENVIRONMENT:
			/*Vermisst die Umgebung durch eine Drehung um 360/SE_COUNT Grad*/
			if (breakpoint == 1) {state = HOLD_STILL; hs_state= 0; break;}
			if (abs(xacc) > HOLD_STILL_MAX_XACC || abs(yacc) > HOLD_STILL_MAX_YACC) {/*Wurde der Copter zu stark bewegt: Abbruch*/state = HOLD_STILL; hs_state = 0; std::cout << "State changed to HOLD_STILL\n"; break;}
			if (first_heading == -1) {
				/*Speichert die anfaengliche Ausrichtung und veranlasst den Copter sich zu drehen*/
				std::cout << "State changed to MEASURE_ENVIRONMENT\n";
				first_heading = current_heading;
				roll = 0; pitch = 0; rotation = 0; yaw = rotation_angle_sign*CONST_YAW;
				send_ext_ctrl();
			}
			//if (new_value) slam_insert_measurement(srf[new_value-SE0_ADDRESS].get_mean(),(current_heading + (360/SE_COUNT)*(new_value-SE0_ADDRESS))%360);
			/*Berechnung der aktuellen Drehung*/
			if (new_heading) {
				if (abs(current_heading - old_heading) > 180/SE_COUNT)	rotation += current_heading - old_heading - sign(current_heading - old_heading)*360;
				else 							rotation += current_heading - old_heading;
				for(int i = 0; i < SE_COUNT; i++) {
					if(nvalue[i] == 1) {
						env[(current_heading + srf[i].get_alignment()*(360/SE_COUNT))%360] = srf[i].get_mean();
						nvalue[i] = 0;
					}
				}
				//if (abs(rotation) >= 360/SE_COUNT) {
				if (abs(rotation) >= rotation_angle) {
					/*Copter hat sich ausreichend gedreht, Abbruch der Vermessung*/
					//state = HEAD_TO_MIDDLE;
					state = GET_ALIGNMENT;
					roll = 0; pitch = 0; yaw = 0;
					send_ext_ctrl();
					rotation_angle_sign = sign(rotation);
				}
			}
			break;
		case GET_ALIGNMENT: {
			/*Bestimme für jeden Sensor die Minimalentfernung der letzten Drehung*/
			/*short min_v[SE_COUNT];
			short min_h[SE_COUNT];
			for (int i = 0; i < SE_COUNT; i++) {
				min_v[i] = 0;
				min_h[i] = 0;
			}*/
			short min_v = 0;
			for (int i = 0; i < rotation_angle; i++) {
				if (min_v < env[(first_heading + rotation_angle_sign*i + 360 + srf[align_se].get_alignment()*(360/SE_COUNT))%360]) {
					min_v = env[(first_heading + rotation_angle_sign*i + 360 + srf[align_se].get_alignment()*(360/SE_COUNT))%360];
					desired_heading = (first_heading + rotation_angle_sign*i + 360 + srf[align_se].get_alignment()*(360/SE_COUNT))%360;
				}
				/*for (int j = 0; j < SE_COUNT; j++) {
					if (min_v[j] < env[(first_heading + rotation_angle_sign*i + j*360/SE_COUNT + 360)%360]) {
						min_v[j] = env[(first_heading + rotation_angle_sign*i + j*360/SE_COUNT + 360)%360];
						min_h[j] = (first_heading + rotation_angle_sign*i + 360)%360;
					}
				}*/
			}
			//desired_heading = round((float)(min_h[0]+min_h[1]+min_h[2]+min_h[3])/4);
			/*Bestimmung der künftigen Drehrichtung*/
			for (int k = 0; k < rotation_angle/2; k++) {
				/*Wenn Minimum in der ersten Hälfte der Drehung gefunden wurde, Wechsel der Drehrichtung bzw. Abbruch*/
				if (desired_heading == (first_heading+rotation_angle_sign*k)%360) {
					rotation_angle_sign *= -1;
					if (init_state == 2) init_state = 3;
					break;
				}
			}
			/*Cleanup*/
			first_heading = -1; yaw = 0; pid_roll.reset(); pid_pitch.reset();
			for(int i = 0; i < 360; i++) env[i] = 0;
			
			if (init_state == 1) 	init_state = 2;
			if (init_state == 3) {
				state = GET_ANCHOR;
				pid_yaw.reset();
				pid_yaw.set(HTM_YAW_KP,HTM_YAW_TN,HTM_YAW_TV);
				pid_yaw.set_target(0);
				roll = 0; pitch = 0; yaw = 0;
				std::cout << "State changed to GET_ANCHOR\n";
				tv_old_heading = get_current_millis();
			} else {
				state = HOLD_STILL;
				hs_state = 0;
			}
			break;
		}
		case GET_ANCHOR:
			/*Copter versucht sich stabil auf ANCHOR_DISTANCE und desired_heading zu stellen*/
			if (new_heading) {
				short heading_diff;
				/*Berechnung der Differenz zwischen aktueller Ausrichtung und gewünschter Ausrichtung*/
				if (abs(desired_heading - current_heading) > 180) {
					heading_diff = desired_heading - current_heading - sign(desired_heading - current_heading)*360;
				} else {
					heading_diff = desired_heading - current_heading;
				}
				yaw = pid_yaw.get(heading_diff,get_current_millis() - tv_old_heading);
				tv_old_heading = get_current_millis();
			}
			if (new_value) {
				roll = 0; pitch = 0;
				if (nvalue[align_se] == 1) {
					if (align_se == 0)	roll   = between<short>(pid_roll_anc.get(srf[align_se].get_mean(), srf[align_se].get_msec_diff()), -max_roll,  max_roll);
					else if (align_se == 1)	roll   = between<short>(pid_roll_anc.get((-1)*srf[align_se].get_mean(), srf[align_se].get_msec_diff()), -max_roll,  max_roll);
					else if (align_se == 2)	pitch  = between<short>(pid_pitch_anc.get(srf[align_se].get_mean(), srf[align_se].get_msec_diff()), -max_pitch,  max_pitch);
					else if (align_se == 3)	pitch  = between<short>(pid_pitch_anc.get((-1)*srf[align_se].get_mean(), srf[align_se].get_msec_diff()), -max_pitch,  max_pitch);
					nvalue[align_se] = 0;
				}
				if 	(srf[0].get_mean() < 30) 	roll = 1000;
				else if (srf[1].get_mean() < 30)	roll = -1000;
				else if (srf[2].get_mean() < 30)	pitch = 1000;
				else if (srf[3].get_mean() < 30)	pitch = -1000;
				if (abs(srf[0].get_mean() - ANCHOR_DISTANCE) < 5) {
					for (int i = 0; i < SE_COUNT; i++) nvalue[i] = 0;
					/*state = MOVE_BACKWARD*/
					/*TODO Neuausrichtung des Copters?*/
				}
			}
			if (breakpoint == 3) 		{roll = 0; pitch = 0; send_ext_ctrl();}
			else if (breakpoint != 2) 	{send_ext_ctrl();}
			break;
		case DELAY: 	break;
		case HTM_DELAY:	break;
		default:	break;
	}
	#if LOG > 0
	fprintf(fd_data,"%lu\t%d\t%d\t%d\t%d\t%d\t%f\t%f\n", (unsigned long)get_current_millis(), roll, pitch, yaw, current_heading, state, current_roll_rad, current_pitch_rad);
	#endif	
}