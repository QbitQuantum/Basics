AboutView::AboutView()
	: BView("aboutview", B_WILL_DRAW | B_PULSE_NEEDED),
	fLastActionTime(system_time()),
	fScrollRunner(NULL)
{
	// Begin Construction of System Information controls

	system_info systemInfo;
	get_system_info(&systemInfo);

	// Create all the various labels for system infomation

	// OS Version

	char string[1024];
	strcpy(string, B_TRANSLATE("Unknown"));

	// the version is stored in the BEOS:APP_VERSION attribute of libbe.so
	BPath path;
	if (find_directory(B_BEOS_LIB_DIRECTORY, &path) == B_OK) {
		path.Append("libbe.so");

		BAppFileInfo appFileInfo;
		version_info versionInfo;
		BFile file;
		if (file.SetTo(path.Path(), B_READ_ONLY) == B_OK
			&& appFileInfo.SetTo(&file) == B_OK
			&& appFileInfo.GetVersionInfo(&versionInfo,
				B_APP_VERSION_KIND) == B_OK
			&& versionInfo.short_info[0] != '\0')
			strcpy(string, versionInfo.short_info);
	}

	// Add revision from uname() info
	utsname unameInfo;
	if (uname(&unameInfo) == 0) {
		long revision;
		if (sscanf(unameInfo.version, "r%ld", &revision) == 1) {
			char version[16];
			snprintf(version, sizeof(version), "%ld", revision);
			strlcat(string, " (", sizeof(string));
			strlcat(string, B_TRANSLATE("Revision"), sizeof(string));
			strlcat(string, " ", sizeof(string));
			strlcat(string, version, sizeof(string));
			strlcat(string, ")", sizeof(string));
		}
	}

	BStringView* versionView = new BStringView("ostext", string);
	versionView->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT,
		B_ALIGN_VERTICAL_UNSET));

	// GCC version
	BEntry gccFourHybrid("/boot/system/lib/gcc2/libstdc++.r4.so");
	BEntry gccTwoHybrid("/boot/system/lib/gcc4/libsupc++.so");
	if (gccFourHybrid.Exists() || gccTwoHybrid.Exists())
		snprintf(string, sizeof(string), B_TRANSLATE("GCC %d Hybrid"),
			__GNUC__);
	else
		snprintf(string, sizeof(string), "GCC %d", __GNUC__);

	BStringView* gccView = new BStringView("gcctext", string);
	gccView->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT,
		B_ALIGN_VERTICAL_UNSET));

	// CPU count, type and clock speed
	char processorLabel[256];
	if (systemInfo.cpu_count > 1) {
		snprintf(processorLabel, sizeof(processorLabel),
			B_TRANSLATE("%ld Processors:"), systemInfo.cpu_count);
	} else
		strlcpy(processorLabel, B_TRANSLATE("Processor:"),
			sizeof(processorLabel));

	BString cpuType;
	cpuType << get_cpu_vendor_string(systemInfo.cpu_type)
		<< " " << get_cpu_model_string(&systemInfo);

	BStringView* cpuView = new BStringView("cputext", cpuType.String());
	cpuView->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT,
		B_ALIGN_VERTICAL_UNSET));

	int32 clockSpeed = get_rounded_cpu_speed();
	if (clockSpeed < 1000)
		sprintf(string, B_TRANSLATE("%ld MHz"), clockSpeed);
	else
		sprintf(string, B_TRANSLATE("%.2f GHz"), clockSpeed / 1000.0f);

	BStringView* frequencyView = new BStringView("frequencytext", string);
	frequencyView->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT,
		B_ALIGN_VERTICAL_UNSET));

	// RAM
	BStringView *memSizeView = new BStringView("ramsizetext",
		MemSizeToString(string, sizeof(string), &systemInfo));
	memSizeView->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT,
		B_ALIGN_VERTICAL_UNSET));
	fMemView = new BStringView("ramtext",
		MemUsageToString(string, sizeof(string), &systemInfo));
	fMemView->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT,
		B_ALIGN_VERTICAL_UNSET));

	// Kernel build time/date
	snprintf(string, sizeof(string), "%s %s",
		systemInfo.kernel_build_date, systemInfo.kernel_build_time);

	BStringView* kernelView = new BStringView("kerneltext", string);
	kernelView->SetExplicitAlignment(BAlignment(B_ALIGN_LEFT,
		B_ALIGN_VERTICAL_UNSET));

	// Uptime
	fUptimeView = new BTextView("uptimetext");
	fUptimeView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	fUptimeView->MakeEditable(false);
	fUptimeView->MakeSelectable(false);
	fUptimeView->SetWordWrap(true);

	fUptimeView->SetText(UptimeToString(string, sizeof(string)));

	const float offset = 5;

	SetLayout(new BGroupLayout(B_HORIZONTAL));

	BLayoutBuilder::Group<>((BGroupLayout*)GetLayout())
		.AddGroup(B_VERTICAL)
			.Add(new LogoView())
			.AddGroup(B_VERTICAL)
				.Add(_CreateLabel("oslabel", B_TRANSLATE("Version:")))
				.Add(versionView)
				.Add(gccView)
				.AddStrut(offset)
				.Add(_CreateLabel("cpulabel", processorLabel))
				.Add(cpuView)
				.Add(frequencyView)
				.AddStrut(offset)
				.Add(_CreateLabel("memlabel", B_TRANSLATE("Memory:")))
				.Add(memSizeView)
				.Add(fMemView)
				.AddStrut(offset)
				.Add(_CreateLabel("kernellabel", B_TRANSLATE("Kernel:")))
				.Add(kernelView)
				.AddStrut(offset)
				.Add(_CreateLabel("uptimelabel",
					B_TRANSLATE("Time running:")))
				.Add(fUptimeView)
				.SetInsets(5, 5, 5, 5)
			.End()
			// TODO: investigate: adding this causes the time to be cut
			//.AddGlue()
		.End()
		.Add(_CreateCreditsView());

	float min = fMemView->MinSize().width * 1.1f;
	fCreditsView->SetExplicitMinSize(BSize(min, min));
}