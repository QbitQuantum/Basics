/* ------------------------
   | Load option settings |
   ------------------------ */
void load_options(void)
{
long f_handle;

strcpy(option_file, path);
strcpy(strchr(option_file, '.') - 1, "DSPROG.OPT");

f_handle = Fopen(option_file, FO_READ);
if (f_handle > 0)
	{
	Fread((int)f_handle, 2L, &flt_ovsm);
	Fread((int)f_handle, 2L, &flt_bad);
	Fread((int)f_handle, 2L, &flt_pitch);
	Fread((int)f_handle, 2L, &flt_slice);

	Fread((int)f_handle, 2L, &pck_filt);
	Fread((int)f_handle, 2L, &pck_4plus);
	Fread((int)f_handle, 2L, &pck_4bit);
	Fread((int)f_handle, 2L, &pck_alter);

	Fread((int)f_handle, 2L, &ovsm_typ);

	Fread((int)f_handle, 2L, &ply_speed);
	Fread((int)f_handle, 2L, &play_ovsm);
	Fread((int)f_handle, 2L, &play_dev);

	Fread((int)f_handle, 4L, &spd_table[4]);
	Fread((int)f_handle, sizeof(mw_data), mw_data);

	Fread((int)f_handle, 4L, smp_extension);
	Fread((int)f_handle, 4L, pck_extension);
	Fread((int)f_handle, 4L, avr_extension);
	
	Fclose((int)f_handle);
	
	ltoa(spd_table[4], playopt_dia.tree[MANUSPD].ob_spec.tedinfo->te_ptmplt, 10);
	strcat(playopt_dia.tree[MANUSPD].ob_spec.tedinfo->te_ptmplt, " KHz");
	
	strcpy(mboard_dia.tree[MBMANU].ob_spec.tedinfo->te_ptmplt,
				 playopt_dia.tree[MBMANU].ob_spec.tedinfo->te_ptmplt);
	}
}