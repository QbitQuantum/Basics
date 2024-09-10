void sil_reset(void)
{
	const char *args[3] = {mp_argv[0], UDB_HW_RESET_ARG, 0};

	sil_ui_will_reset();

	if (gpsSocket)       UDBSocket_close(gpsSocket);
	if (telemetrySocket) UDBSocket_close(telemetrySocket);
	if (serialSocket)    UDBSocket_close(serialSocket);

#ifdef _MSC_VER
	_execv(mp_argv[0], args);
#else
	execv(mp_argv[0], args);
#endif
	fprintf(stderr, "Failed to reset UDB %s\n", mp_argv[0]);
	exit(1);
}