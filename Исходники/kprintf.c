void KLog (const char *format, ...)
{
	va_list ap;
	
	va_start (ap, format);
	
	MutexLock (&dbg_mutex);
	
	Vsnprintf (&klog_entry[current_log][0], KLOG_WIDTH, format, ap);
	
	if (klog_to_screen == TRUE)
		KPrintString (&klog_entry[current_log][0]);

	current_log++;
	current_log %= KLOG_ENTRIES;
//	{ int i = 0; while (i < 5000000) {i++; Vsnprintf (&klog_entry[current_log][0], KLOG_WIDTH, format, ap);}}
			
	MutexUnlock (&dbg_mutex);	
	
	va_end (ap);
}