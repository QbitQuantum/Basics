void RTC::release()
{
	// set power off time
	regs[POFMI] = TO_BCD(cur_time.minute);
	regs[POFH] = TO_BCD(cur_time.hour);
	regs[POFD] = TO_BCD(cur_time.day);
	
	// save rtc regs image
	FILEIO* fio = new FILEIO();
	if(fio->Fopen(create_local_path(_T("RTC.BIN")), FILEIO_WRITE_BINARY)) {
		fio->Fwrite(regs + 8, 32, 1);
		fio->Fclose();
	}
	delete fio;
}