/* Main FG entry point. This function needs to be called periodically.*/
void fg_process(struct cell_state *cell, short delta_q, short raw_voltage, short norm_voltage,
		short cur, short temperature)
{
	int i, tmp;
	struct timespec now;

	if (!cell->init)
		return;

	/* Update voltage and add it to the buffer, update average*/
	tmp = 0;
	cell->voltage = norm_voltage;
	av_v_index++;
	av_v_index %= AV_SIZE;
	av_v[av_v_index] = norm_voltage;
	for (i = 0; i < AV_SIZE; i++) {
		tmp += av_v[i];
	}
	cell->av_voltage = tmp/AV_SIZE;

	/* Update current and add it to the buffer, update average*/
	tmp = 0;
	cell->cur = cur;
	av_c_index++;
	av_c_index %= AV_SIZE;
	av_c[av_c_index] = cur;
	for (i = 0; i < AV_SIZE; i++)
		tmp += av_c[i];
	cell->av_current = tmp/AV_SIZE;

	/* Update temperature*/
	cell->temperature = temperature;
	/*Update FCC and EDV table from temperature compensation*/
	fg_temperature_compensate(cell);
	/* Check time since last_call */
	getrawmonotonic(&now);
	tmp = now.tv_sec - cell->last_correction.tv_sec;

	/* Check what capacity correction algorithm should we use: OCV or CC */
	if ((tmp > cell->config->ocv->relax_period) &&
	    (abs(cell->cur) < cell->config->ocv->long_sleep_current)) {
#ifdef CONFIG_POWER_SUPPLY_DEBUG
			printk(KERN_DEBUG "OCV check 1\n");
#endif
			fg_ocv(cell);
	} else if (fg_check_relaxed(cell)) {
		/* We are not doing any active CHG/DSG, clear flags
		   this does not compromise learning cycles */
		cell->chg = false;
		cell->dsg = false;

		/* Checking if we can do an OCV correction */
		if (fg_can_ocv(cell))
			fg_ocv(cell);
		else
			fg_cc(cell, delta_q);
	} else /* Not Relaxed: actively charging or discharging */
		fg_cc(cell, delta_q);


	/* Charge / Discharge spesific functionality */
	if (!cell->sleep) {
		if (cell->cur > 0)
			fg_charging(cell, delta_q);
		else if (cell->cur < 0)
			fg_discharging(cell, delta_q);
	}

	/* Update Regular SOC */
	cell->soc = DIV_ROUND_CLOSEST(cell->nac * MAX_PERCENTAGE, cell->fcc);

/* The voltage will vibrate a lot when close to shutdown voltage. This happens especially when running high power
 * consumption app. So need to take care of the end check
*/

	/*Add here to check both nac and EDV0*/
	if(cell->soc > EDV_FIRST_CHECK_POINT+5){
		fg_ocv_check(cell);
	}
	else if(cell->soc==0){
#ifdef BATTERY_DRAIN_CONFIG
		cell->soc=1;
#else
		fg_check_end(cell);
#endif
	}

	/* When SOC is below 15%, check if raw voltage level reached hardware shutdown threshold */
	if(cell->soc < EDV_FIRST_CHECK_POINT+5){
		fg_check_shutdown_voltage(cell, raw_voltage);
	}

	fg_update_edv_flags(cell, false);

	/* Check if battery is full */
	if (cell->cc) {
		cell->full = true;
	}

	if (cell->soc < MAX_PERCENTAGE) {
		cell->full = false;
		if (cell->nac <= (cell->fcc - cell->config->recharge))
			cell->cc = false;
	}

	/* Check if SOC reached 100% and battery is still charging, then keep SOC at 99% */
	if((*cell->charge_status == POWER_SUPPLY_STATUS_CHARGING) &&
			(cell->soc == MAX_PERCENTAGE) && !cell->cc && !cell->full)
	{
#ifdef DEBUG
		printk(KERN_DEBUG "End of charge not reach yet\n");
#endif
		cell->soc = MAX_PERCENTAGE-1;
	}

	/* Checking if we need to set an updated flag (is SOC changed) */
	if (cell->prev_soc != cell->soc) {
		cell->prev_soc = cell->soc;
		cell->updated = true;
	}

	cell->last_correction.tv_sec = now.tv_sec;

#if 0
	//JET-376 test, run calibration every 5-min to check cc_offset value
	cal_cntr++;
	if(cal_cntr >= 30)
	{
		cell->calibrate = true;
		cal_cntr = 0;
		printk(KERN_DEBUG "PMIC Calibrate now! \n");
	}
#endif

#ifdef DEBUG
	/* Printing Debug Data */
	printk(KERN_DEBUG
		"FG:ACC:%2d; RM:%4d,mAh; SOC:%3d%%; VOLT:%4d,%4d,mV; "
		"CUR:%5d,%5d,mA; TEMP:%3d; "
		"EDV:%d,mV,%02d%%; "
		"LLL:%4d,%4d,%4d; "
		"N/O:%4d,%4d; "
		"CS:%4d; EL:%5d; "
		"FCC:%d,%d; CP:%d; \n",
		delta_q, cell->nac, cell->soc, cell->voltage, cell->av_voltage,
		cell->cur, cell->av_current, cell->temperature,
		cell->edv.voltage, cell->edv.percent,
		cell->learn_q, cell->learn_offset, cell->ocv_total_q,
		cell->negative_q, cell->overcharge_q,
		cell->cumulative_sleep, cell->electronics_load,
		cell->fcc, cell->cycle_count, tmp);

	print_flags(cell);
#endif
}