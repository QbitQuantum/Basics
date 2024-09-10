void
ibs_stop(int cid)
{
    if (!ibs_enabled)
	return;
    cid = lcpu_to_pcpu[cid];
    char path[512];
    // set opctl to stop
    sprintf(path, "/sys/kernel/amd10h-ibs/cpu%d/opctl", cid);
    writefile(path, "0");
    sprintf(path, "/sys/kernel/amd10h-ibs/cpu%d/record", cid);
    readsamples(path);
}