void ProcessController::SaveConfig(string path)
{
	// add error handling
	Config cfg;
	Setting &root = cfg.getRoot();

	// Raft parameters
	Setting &rs = root.add("RaftSize", Setting::TypeFloat);
	rs = RaftSize;

	Setting &rblc = root.add("RaftBaseLayerCount", Setting::TypeInt);
	rblc = int(RaftBaseLayerCount);
	Setting &rmpdr = root.add("RaftMaterialPrDistanceRatio", Setting::TypeFloat);
	rmpdr = RaftMaterialPrDistanceRatio;
	Setting &rafrot = root.add("RaftRotation", Setting::TypeFloat);
	rafrot = RaftRotation;
	Setting &rbd = root.add("RaftBaseDistance", Setting::TypeFloat);
	rbd = RaftBaseDistance;
	Setting &rbt = root.add("RaftBaseThickness", Setting::TypeFloat);
	rbt = RaftBaseThickness;
	Setting &rbT = root.add("RaftBaseTemperature", Setting::TypeFloat);
	rbT = RaftBaseTemperature;
	Setting &rilc = root.add("RaftInterfaceLayerCount", Setting::TypeInt);
	rilc = int(RaftInterfaceLayerCount);
	Setting &rimpdr = root.add("RaftInterfaceMaterialPrDistanceRatio", Setting::TypeFloat);
	rimpdr = RaftInterfaceMaterialPrDistanceRatio;
	Setting &rrpl = root.add("RaftRotationPrLayer", Setting::TypeFloat);
	rrpl = RaftRotationPrLayer;
	Setting &rid = root.add("RaftInterfaceDistance", Setting::TypeFloat);
	rid = RaftInterfaceDistance;
	Setting &rit = root.add("RaftInterfaceThickness", Setting::TypeFloat);
	rit = RaftInterfaceDistance;
	Setting &riT = root.add("RaftInterfaceTemperature", Setting::TypeFloat);
	riT = RaftInterfaceTemperature;

	// GCode parameters
	Setting &gst = root.add("GCodeStartText", Setting::TypeString);
	gst = GCodeStartText;
	Setting &glt = root.add("GCodeLayerText", Setting::TypeString);
	glt = GCodeLayerText;
	Setting &get = root.add("GCodeEndText", Setting::TypeString);
	get = GCodeEndText;
	Setting &mspn = root.add("msPortName", Setting::TypeString);
	mspn = m_sPortName;
	Setting &vc = root.add("ValidateConnection", Setting::TypeInt);
	vc = int(m_bValidateConnection);

	Setting &cbg = root.add("CustomButtonGcode", Setting::TypeArray);	
	Setting &cbl = root.add("CustomButtonLabel", Setting::TypeArray);
	for (int i = 0; i < 20; i++) {
		cbg.add(Setting::TypeString);
		cbl.add(Setting::TypeString);
		cbg[i] = CustomButtonGcode[i];
		cbl[i] = CustomButtonLabel[i];
	}

	Setting &miss = root.add("miSerialSpeed", Setting::TypeInt);
	miss = m_iSerialSpeed;
	Setting &gds = root.add("GCodeDrawStart", Setting::TypeFloat);
	gds = GCodeDrawStart;

	Setting &gde = root.add("GCodeDrawEnd", Setting::TypeFloat);
	gde = GCodeDrawEnd;
	Setting &se = root.add("ShellOnly", Setting::TypeBoolean);
	se = ShellOnly;
	Setting &sc = root.add("ShellCount", Setting::TypeInt);
	sc = int(ShellCount);

	// Printer parameters
	Setting &mpsxy = root.add("MinPrintSpeedXY", Setting::TypeFloat);
	mpsxy = MinPrintSpeedXY;
	Setting &Mpsxy = root.add("MaxPrintSpeedXY", Setting::TypeFloat);
	Mpsxy = MaxPrintSpeedXY;
	Setting &mpsz = root.add("MinPrintSpeedZ", Setting::TypeFloat);
	mpsz = MinPrintSpeedZ;
	Setting &Mpsz = root.add("MaxPrintSpeedZ", Setting::TypeFloat);
	Mpsz = MaxPrintSpeedZ;
	Setting &dtrfs = root.add("DistanceToReachFullSpeed", Setting::TypeFloat);
	dtrfs = DistanceToReachFullSpeed;
	Setting &ef = root.add("extrusionFactor", Setting::TypeFloat);
	ef = extrusionFactor;
	Setting &ea = root.add("EnableAcceleration", Setting::TypeBoolean);
	ea = EnableAcceleration;
	Setting &uie = root.add("UseIncrementalEcode", Setting::TypeBoolean);
	uie = UseIncrementalEcode;
	Setting &u3g = root.add("Use3DGcode", Setting::TypeBoolean);
	u3g = Use3DGcode;
	Setting &Ea = root.add("EnableAntiooze", Setting::TypeBoolean);
	Ea = EnableAntiooze;
	Setting &ad = root.add("AntioozeDistance", Setting::TypeFloat);
	ad = AntioozeDistance;
	Setting &as = root.add("AntioozeSpeed", Setting::TypeFloat);
	as = AntioozeSpeed;

	Setting &fle = root.add("FileLogginEnabled", Setting::TypeBoolean);
	fle = FileLogginEnabled;
	Setting &tre = root.add("TempReadingEnabled", Setting::TypeBoolean);
	tre = TempReadingEnabled;
	Setting &clwps = root.add("ClearLogfilesWhenPrintStarts", Setting::TypeBoolean);
	clwps = ClearLogfilesWhenPrintStarts;

	Setting &mfvx = root.add("mfVolumeX", Setting::TypeFloat);
	mfvx = m_fVolume.x;
	Setting &mfvy = root.add("mfVolumeY", Setting::TypeFloat);
	mfvy = m_fVolume.y;
	Setting &mfvz = root.add("mfVolumeZ", Setting::TypeFloat);
	mfvz = m_fVolume.z;
	Setting &pmx = root.add("PrintMarginX", Setting::TypeFloat);
	pmx = PrintMargin.x;
	Setting &pmy = root.add("PrintMarginY", Setting::TypeFloat);
	pmy = PrintMargin.y;
	Setting &prinmz = root.add("PrintMarginZ", Setting::TypeFloat);
	prinmz = PrintMargin.z;

	Setting &emw = root.add("ExtrudedMaterialWidth", Setting::TypeFloat);
	emw = ExtrudedMaterialWidth;
	Setting &lt = root.add("LayerThickness", Setting::TypeFloat);
	lt = LayerThickness;

	// CuttingPlane parameters
	Setting &id = root.add("InfillDistance", Setting::TypeFloat);
	id = InfillDistance;
	Setting &ir = root.add("InfillRotation", Setting::TypeFloat);
	ir = InfillRotation;
	Setting &irpl = root.add("InfillRotationPrLayer", Setting::TypeFloat);
	irpl = InfillRotationPrLayer;
	Setting &aid = root.add("AltInfillDistance", Setting::TypeFloat);
	aid = AltInfillDistance;
	Setting &ail = root.add("AltInfillLayersText", Setting::TypeString);
	ail = AltInfillLayersText;
	Setting &po = root.add("PolygonOpasity", Setting::TypeFloat);
	po = PolygonOpasity;

	// GUI parameters
	Setting &cpv = root.add("CuttingPlaneValue", Setting::TypeFloat);
	cpv = CuttingPlaneValue;
	Setting &exam = root.add("Examine", Setting::TypeFloat);
	exam = Examine;

	Setting &de = root.add("DisplayEndpoints", Setting::TypeBoolean);
	de = DisplayEndpoints;
	Setting &dn = root.add("DisplayNormals", Setting::TypeBoolean);
	dn = DisplayNormals;
	Setting &dw = root.add("DisplayWireframe", Setting::TypeBoolean);
	dw = DisplayWireframe;
	Setting &dws = root.add("DisplayWireframeShaded", Setting::TypeBoolean);
	dws = DisplayWireframeShaded;
	Setting &dp = root.add("DisplayPolygons", Setting::TypeBoolean);
	dp = DisplayPolygons;
	Setting &dal = root.add("DisplayAllLayers", Setting::TypeBoolean);
	dal = DisplayAllLayers;
	Setting &dif = root.add("DisplayinFill", Setting::TypeBoolean);
	dif = DisplayinFill;
	Setting &ddif = root.add("DisplayDebuginFill", Setting::TypeBoolean);
	ddif = DisplayDebuginFill;
	Setting &dd = root.add("DisplayDebug", Setting::TypeBoolean);
	dd = DisplayDebug;
	Setting &dcp = root.add("DisplayCuttingPlane", Setting::TypeBoolean);
	dcp = DisplayCuttingPlane;
	Setting &dvn = root.add("DrawVertexNumbers", Setting::TypeBoolean);
	dvn = DrawVertexNumbers;
	Setting &dln = root.add("DrawLineNumbers", Setting::TypeBoolean);
	dln = DrawLineNumbers;
	Setting &pv = root.add("PolygonVal", Setting::TypeFloat);
	pv = PolygonVal;
	Setting &ps = root.add("PolygonSat", Setting::TypeFloat);
	ps = PolygonSat;
	Setting &ph = root.add("PolygonHue", Setting::TypeFloat);
	ph = PolygonHue;
	Setting &wfv = root.add("WireframeVal", Setting::TypeFloat);
	wfv = WireframeVal;
	Setting &wfs = root.add("WireframeSat", Setting::TypeFloat);
	wfs = WireframeSat;
	Setting &wfh = root.add("WireframeHue", Setting::TypeFloat);
	wfh = WireframeHue;
	Setting &ns = root.add("NormalsSat", Setting::TypeFloat);
	ns = NormalsSat;
	Setting &nv = root.add("NormalsVal", Setting::TypeFloat);
	nv = NormalsVal;
	Setting &nh = root.add("NormalsHue", Setting::TypeFloat);
	nh = NormalsHue;
	Setting &es = root.add("EndpointsSat", Setting::TypeFloat);
	es = EndpointsSat;
	Setting &ev = root.add("EndpointsVal", Setting::TypeFloat);
	ev = EndpointsVal;
	Setting &eh = root.add("EndpointsHue", Setting::TypeFloat);
	eh = EndpointsHue;
	Setting &geh = root.add("GCodeExtrudeHue", Setting::TypeFloat);
	geh = GCodeExtrudeHue;
	Setting &ges = root.add("GCodeExtrudeSat", Setting::TypeFloat);
	ges = GCodeExtrudeSat;
	Setting &gev = root.add("GCodeExtrudeVal", Setting::TypeFloat);
	gev = GCodeExtrudeVal;
	Setting &gmh = root.add("GCodeMoveHue", Setting::TypeFloat);
	gmh = GCodeMoveHue;
	Setting &gms = root.add("GCodeMoveSat", Setting::TypeFloat);
	gms = GCodeMoveSat;
	Setting &gmv = root.add("GCodeMoveVal", Setting::TypeFloat);
	gmv = GCodeMoveVal;
	Setting &hil = root.add("Highlight", Setting::TypeFloat);
	hil = Highlight;

	Setting &nl = root.add("NormalsLength", Setting::TypeFloat);
	nl = NormalsLength;
	Setting &eps = root.add("EndPointSize", Setting::TypeFloat);
	eps = EndPointSize;
	Setting &tus = root.add("TempUpdateSpeed", Setting::TypeFloat);
	tus = TempUpdateSpeed;

	Setting &dgc = root.add("DisplayGCode", Setting::TypeBoolean);
	dgc = DisplayGCode;

	Setting &lss = root.add("LuminanceShowsSpeed", Setting::TypeBoolean);
	lss = LuminanceShowsSpeed;

	Setting &rafte = root.add("RaftEnable", Setting::TypeBoolean);
	rafte = RaftEnable;

	Setting &aproe = root.add("ApronEnable", Setting::TypeBoolean);
	aproe = ApronEnable;

	Setting &aprpre = root.add("ApronPreview", Setting::TypeBoolean);
	aprpre = ApronPreview;
	Setting &aprsiz = root.add("ApronSize", Setting::TypeFloat);
	aprsiz = ApronSize;
	
	Setting &aprh = root.add("ApronHeight", Setting::TypeFloat);
	aprh = ApronHeight;
	Setting &acx = root.add("ApronCoverageX", Setting::TypeFloat);
	acx = ApronCoverageX;
	Setting &acy = root.add("ApronCoverageY", Setting::TypeFloat);
	acy = ApronCoverageY;
	Setting &adto = root.add("ApronDistanceToObject", Setting::TypeFloat);
	adto = ApronDistanceToObject;
	Setting &ainfd = root.add("ApronInfillDistance", Setting::TypeFloat);
	ainfd = ApronInfillDistance;

	Setting &shf = root.add("ShrinkFast", Setting::TypeBoolean);
	shf = (m_ShrinkQuality == SHRINK_FAST);
	Setting &shl = root.add("ShrinkLogick", Setting::TypeBoolean);
	shl = (m_ShrinkQuality == SHRINK_LOGICK);
	Setting &optim = root.add("Optimization", Setting::TypeFloat);
	optim = Optimization;
	Setting &rebs = root.add("ReceivingBufferSize", Setting::TypeInt);
	rebs = ReceivingBufferSize;

	Setting &stlp = root.add("STLPath", Setting::TypeString);
	stlp = STLPath;
	Setting &rfop = root.add("RFOPath", Setting::TypeString);
	rfop = RFOPath;
	Setting &gcop = root.add("GCodePath", Setting::TypeString);
	gcop = GCodePath;
	Setting &setp = root.add("SettingsPath", Setting::TypeString);
	setp = SettingsPath;
	
	cfg.writeFile(path.c_str());
}