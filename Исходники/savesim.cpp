double CMSaveSimulation::last_timestep_in_interval(const CMTime& t)
{
	wchar_t buffer[128];
	CMTime tm(t);
   tm.inc(outincsteps,outincunits);
   tm.inc(-1,simincunits);
   return _wtof(tm.GetString(buffer, 128));
}