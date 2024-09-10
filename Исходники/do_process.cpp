void process_update_display(void)
{
#ifndef DISABLE_NCURSES
	unsigned int i;
	WINDOW *win;
	double pw;
	int tl;
	int tlt; 
	int tlr;

	int show_power;
	int need_linebreak = 0;

	sort(all_power.begin(), all_power.end(), power_cpu_sort);

	show_power = global_power_valid();

	win = get_ncurses_win("Overview");
	if (!win)
		return;

	wclear(win);

	wmove(win, 1,0);

#if 0
	double sum;
	calculate_params();
	sum = 0.0;
	sum += get_parameter_value("base power");
	for (i = 0; i < all_power.size(); i++) {
		sum += all_power[i]->Witts();
	}

	wprintw(win, _("Estimated power: %5.1f    Measured power: %5.1f    Sum: %5.1f\n\n"),
				all_parameters.guessed_power, global_joules_consumed(), sum);
#endif

	pw = global_joules_consumed();
	tl = global_time_left() / 60;
	tlt = (tl /60);
	tlr = tl % 60;

	if (pw > 0.0001) {
		char buf[32];
		wprintw(win, _("The battery reports a discharge rate of %sW\n"),
				fmt_prefix(pw, buf));
		need_linebreak = 1;
	}
	if (tl > 0 && pw > 0.0001) {
		wprintw(win, _("The estimated remaining time is %i hours, %i minutes\n"), tlt, tlr);
		need_linebreak = 1;
	}

	if (need_linebreak)
		wprintw(win, "\n");


	wprintw(win, "%s: %3.1f %s,  %3.1f %s, %3.1f %s %3.1f%% %s\n\n",_("Summary"), total_wakeups(), _("wakeups/second"), total_gpu_ops(), _("GPU ops/seconds"), total_disk_hits(), _("VFS ops/sec and"), total_cpu_time()*100, _("CPU use"));


	if (show_power)
		wprintw(win, "%s              %s       %s    %s       %s\n", _("Power est."), _("Usage"), _("Events/s"), _("Category"), _("Description"));
	else
		wprintw(win, "                %s       %s    %s       %s\n", _("Usage"), _("Events/s"), _("Category"), _("Description"));

	for (i = 0; i < all_power.size(); i++) {
		char power[16];
		char name[20];
		char usage[20];
		char events[20];
		char descr[128];
		format_watts(all_power[i]->Witts(), power, 10);

		if (!show_power)
			strcpy(power, "          ");
		sprintf(name, "%s", all_power[i]->type());
		while (mbstowcs(NULL,name,0) < 14) strcat(name, " ");


		if (all_power[i]->events() == 0 && all_power[i]->usage() == 0 && all_power[i]->Witts() == 0)
			break;

		usage[0] = 0;
		if (all_power[i]->usage_units()) {
			if (all_power[i]->usage() < 1000)
				sprintf(usage, "%5.1f%s", all_power[i]->usage(), all_power[i]->usage_units());
			else
				sprintf(usage, "%5i%s", (int)all_power[i]->usage(), all_power[i]->usage_units());
		}
		while (mbstowcs(NULL,usage,0) < 14) strcat(usage, " ");
		sprintf(events, "%5.1f", all_power[i]->events());
		if (!all_power[i]->show_events())
			events[0] = 0;
		else if (all_power[i]->events() <= 0.3)
			sprintf(events, "%5.2f", all_power[i]->events());

		while (strlen(events) < 12) strcat(events, " ");
		wprintw(win, "%s  %s %s %s %s\n", power, usage, events, name, pretty_print(all_power[i]->description(), descr, 128));
	}
#endif // DISABLE_NCURSES
}