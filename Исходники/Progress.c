static void calculate_speed(struct progress_bar *prog, unsigned long long copied, unsigned long long current, int done, prog_stat_t *prog_stat){
    char *format = "%H:%M:%S";
    uint64_t speedps = 1;
    uint64_t speed = 1;
    double dspeed = 1.0;
    float percent = 1.0;
    time_t remained;
    time_t elapsed;
    char Rformated[12], Eformated[12];
    char speed_unit[] = "    ";
    struct tm *Rtm, *Etm;
    uint64_t gbyte=1000000000.0;
    uint64_t mbyte=1000000;
    uint64_t kbyte=1000;


    percent  = prog->unit * copied;
    if (percent <= 0)
	percent = 1;
    else if (percent >= 100)
	percent = 99.99;

    elapsed  = (time(0) - prog->initial_time);
    if (elapsed <= 0)
	elapsed = 1;

    speedps  = prog->block_size * copied / elapsed;
    speed = speedps * 60.0;

    prog_stat->percent   = percent;

    if (speed >= gbyte){
	dspeed = (double)speed / (double)gbyte;
	strncpy(speed_unit, "GB", 3);
	strncpy(prog_stat->speed_unit, speed_unit, 3);
    }else if (speed >= mbyte){
	dspeed = (double)speed / (double)mbyte;
	strncpy(speed_unit, "MB", 3);
	strncpy(prog_stat->speed_unit, speed_unit, 3);
    }else if (speed >= kbyte){
	dspeed = (double)speed / (double)kbyte;
	strncpy(speed_unit, "KB", 3);
	strncpy(prog_stat->speed_unit, speed_unit, 3);
    }else{
	dspeed = speed;
	strncpy(speed_unit, "byte", 5);
	strncpy(prog_stat->speed_unit, speed_unit, 5);
    }

    prog_stat->total_percent = prog->total_unit * current;

    prog_stat->speed     = dspeed;

    if (done != 1){
        remained = (time_t)((elapsed/percent*100) - elapsed);

	if ((unsigned int)remained > 86400){
	    snprintf(Rformated, sizeof(Rformated), " > %3i hrs ", ((int)remained/3600));
	}else{
	    Rtm = gmtime(&remained);
	    strftime(Rformated, sizeof(Rformated), format, Rtm);
	}

	if ((unsigned int)elapsed > 86400){
	    snprintf(Eformated, sizeof(Eformated), " > %3i hrs ", ((int)elapsed/3600));
	}else{
	    Etm = gmtime(&elapsed);
	    strftime(Eformated, sizeof(Eformated), format, Etm);
	}

    } else {
        prog_stat->percent=100;
        remained = (time_t)0;
        Rtm = gmtime(&remained);
	strftime(Rformated, sizeof(Rformated), format, Rtm);

	if ((unsigned int)elapsed > 86400){
	    snprintf(Eformated, sizeof(Eformated), " > %3i hrs ", ((int)elapsed/3600));
	}else{
	    Etm = gmtime(&elapsed);
	    strftime(Eformated, sizeof(Eformated), format, Etm);
	}
    }

    strncpy(prog_stat->Eformated, Eformated, sizeof(prog_stat->Eformated));
    strncpy(prog_stat->Rformated, Rformated, sizeof(prog_stat->Rformated));
}