void upsStatus::Update(StatMgr *statmgr)
{
   // Bail if window is not open
   WaitForSingleObject(_mutex, INFINITE);
   if (!_hwnd)
   {
      ReleaseMutex(_mutex);
      return;
   }

   // Fetch full status from nutupsd
   list<string> keys, values;
   if (!statmgr->GetAll(keys, values) || keys.empty())
   {
	  ReleaseMutex(_mutex);
      return;
   }

   // Update listview
   list<string>* data[] = {&keys, &values};
   _grid->UpdateAll(data);

   // Update battery
   _bmeter->Set(atoi(statmgr->Get("battery.charge").c_str()));

   // Update load
   _lmeter->Set(atoi(statmgr->Get("ups.load").c_str()));

   // Update status
   char str[128];
   string stat = statmgr->Get("ups.status");
   GetDlgItemTextA(_hwnd, IDC_STATUS, str, sizeof(str));
   if (stat != str)
	   SetDlgItemTextA(_hwnd, IDC_STATUS, stat.c_str());

   // Update runtime
   string runtime = statmgr->Get("battery.runtime");
   GetDlgItemTextA(_hwnd, IDC_RUNTIME, str, sizeof(str));
   if (runtime != str)
      SetDlgItemTextA(_hwnd, IDC_RUNTIME, runtime.c_str());

   // Update title bar
   char name[512];
   string upsname = statmgr->Get("UPS");
   snprintf(name, sizeof(name), "Status for UPS: %s", upsname.c_str());
   SetWindowTextA(_hwnd, name);
   
   ReleaseMutex(_mutex);
}