// List the registered cvars for the given plugin id.
void DLLINTERNAL MRegCvarList::show(int plugin_id) {
	int i, n=0;
	MRegCvar *icvar;
	char bname[30+1], bval[15+1];	// +1 for term null
	
	/*
	// If OS doesn't support DLFNAME, then we can't know what the plugin's
	// registered cvars are.
	DLFNAME(NULL);
	if(meta_errno==ME_OSNOTSUP) {
		META_CONS("Registered cvars: unknown (can't get info under this OS)");
		return;
	}
	*/
	
	META_CONS("%-*s     %*s  %s", 
			sizeof(bname)-1, "Registered cvars:",
			sizeof(bval)-1, "float value",
			"string value");
	for(i=0; i < endlist; i++) {
		icvar = &vlist[i];
		if(icvar->plugid != plugin_id)
			continue;
		STRNCPY(bname, icvar->data->name, sizeof(bname));
		safevoid_snprintf(bval, sizeof(bval), "%f", icvar->data->value);
		META_CONS("   %-*s  %*s  %s", 
				sizeof(bname)-1, bname,
				sizeof(bval)-1, bval,
				icvar->data->string);
		n++;
	}
	META_CONS("%d cvars", n); 
}