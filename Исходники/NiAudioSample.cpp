int main(int argc, char* argv[])
{
	XnStatus nRetVal = XN_STATUS_OK;

	Context context;
	EnumerationErrors errors;
	Mode mode;

	// default mode
#if XN_PLATFORM == XN_PLATFORM_WIN32
	mode = MODE_PLAY;
#else
	mode = MODE_RECORD;
#endif

	// check if mode was provided by user
	if (argc > 1)
	{
		if (strcmp(argv[1], "play") == 0)
		{
			mode = MODE_PLAY;
		}
		else if (strcmp(argv[1], "record") == 0)
		{
			mode = MODE_RECORD;
		}
		else
		{
			printUsage(argv[0]);
			return -1;
		}
	}

	// make sure mode is valid
#if XN_PLATFORM != XN_PLATFORM_WIN32
	if (mode == MODE_PLAY)
	{
		printf("Playing is not supported on this platform!\n");
		return -1;
	}
#endif

	nRetVal = context.InitFromXmlFile(SAMPLE_XML_PATH);
	if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
		return (nRetVal);
	}
	else if (nRetVal != XN_STATUS_OK)
	{
		printf("Open failed: %s\n", xnGetStatusString(nRetVal));
		return (nRetVal);
	}

	// find audio nodes
	AudioGenerator gens[nSupportedNodes];
	XnUInt32 nNodes = 0;

	NodeInfoList list;
	nRetVal = context.EnumerateExistingNodes(list, XN_NODE_TYPE_AUDIO);
	CHECK_RC(nRetVal, "Enumerate audio nodes");

	for (NodeInfoList::Iterator it = list.Begin(); it != list.End(); ++it)
	{
		NodeInfo info = *it;
		nRetVal = info.GetInstance(gens[nNodes]);
		CHECK_RC(nRetVal, "Get audio node");
		nNodes++;
	}

	if (nNodes == 0)
	{
		printf("No audio node was found!\n");
		return -1;
	}

	if (mode == MODE_PLAY)
	{
		nRetVal = play(context, gens, nNodes);
	}
	else if (mode == MODE_RECORD)
	{
		nRetVal = record(context, gens, nNodes);
	}

	context.Shutdown();

	return nRetVal;
}