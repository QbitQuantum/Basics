int set_meter_file(char *meter_buf)
{
	if(meter_buf == NULL)
		return 0;
#ifdef CONFIG_BCMWL5 
        FILE *fp;
        if (fp=fopen(ISP_METER_FILE, "w")) {
               fprintf(fp, "%s", meter_buf);
               fclose(fp);
	}
#else
	FWrite(meter_buf, RA_OFFSET_ISP_METER, sizeof(meter_buf));
#endif
	return 1;
}