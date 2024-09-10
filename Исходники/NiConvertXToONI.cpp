int main(int argc, char* argv[])
{
	XnStatus nRetVal = XN_STATUS_OK;

	if (argc < 3)
	{
		printUsage(argv[0]);
		return -1;
	}

	const char* strInputFile = argv[1];
	const char* strOutputFile = argv[2];

	// options
	const XnChar* astrNodeNames[MAX_NODES_COUNT];
	XnUInt32 nNodeNames = 0;
	XnProductionNodeType aNodeTypes[MAX_NODES_COUNT];
	XnUInt32 nNodeTypes = 0;
	const XnChar* strPrimaryNode = NULL;
	XnProductionNodeType primaryNodeType = XN_NODE_TYPE_INVALID;
	XnUInt32 nStartFrame = 0;
	XnUInt32 nEndFrame = XN_MAX_UINT32;

	//-----------------------------------------------------------------------
	// Parsing Options
	//-----------------------------------------------------------------------
	for (int i = 3; i < argc; ++i)
	{
		// look for '='
		char* equalSign = strchr(argv[i], '=');
		if (equalSign == NULL)
		{
			printUsage(argv[0]);
			return -1;
		}

		*equalSign = '\0';

		char* option = argv[i];
		char* optionArg = equalSign + 1;

		// now check which option is that
		if (strcmp(option, "--nodes") == 0)
		{
			for (;;)
			{
				char* commaPos = strchr(optionArg, ',');
				if (commaPos != NULL)
				{
					*commaPos = '\0';
				}

				if (strlen(optionArg) == 0)
				{
					printUsage(argv[0]);
					return -1;
				}

				astrNodeNames[nNodeNames++] = optionArg;

				if (commaPos == NULL)
				{
					break;
				}
				else
				{
					optionArg = commaPos + 1;
				}
			}
		}
		else if (strcmp(option, "--types") == 0)
		{
			for (;;)
			{
				char* commaPos = strchr(optionArg, ',');
				if (commaPos != NULL)
				{
					*commaPos = '\0';
				}

				nRetVal = xnProductionNodeTypeFromString(optionArg, &aNodeTypes[nNodeNames]);
				if (nRetVal != XN_STATUS_OK)
				{
					printf("%s is not a valid node type!\n", optionArg);
					return -1;
				}

				++nNodeTypes;

				if (commaPos == NULL)
				{
					break;
				}
				else
				{
					optionArg = commaPos + 1;
				}
			}
		}
		else if (strcmp(option, "--primary-node") == 0)
		{
			strPrimaryNode = optionArg;
		}
		else if (strcmp(option, "--primary-node-type") == 0)
		{
			nRetVal = xnProductionNodeTypeFromString(optionArg, &primaryNodeType);
			if (nRetVal != XN_STATUS_OK)
			{
				printf("%s is not a valid node type!\n", optionArg);
				return -1;
			}
		}
		else if (strcmp(option, "--start-frame") == 0)
		{
			nStartFrame = atoi(optionArg);
		}
		else if (strcmp(option, "--end-frame") == 0)
		{
			nEndFrame = atoi(optionArg);
		}
		else
		{
			printUsage(argv[0]);
			return -1;
		}
	}

	// validate options
	if (nNodeNames > 0 && nNodeTypes > 0)
	{
		printf("Cannot use --nodes and --types together.\n");
		return -1;
	}

	if (primaryNodeType != XN_NODE_TYPE_INVALID && strPrimaryNode != NULL)
	{
		printf("Cannot use --primary-node and --primary-node-type together.\n");
		return -1;
	}

	// start and end requires primary node
	if ((nStartFrame != 0 || nEndFrame != XN_MAX_UINT32) && 
		(strPrimaryNode == NULL && primaryNodeType == XN_NODE_TYPE_INVALID))
	{
		printf("A primary node must be defined for using --start-frame or --end-frame.\n");
		return -1;
	}

	//-----------------------------------------------------------------------
	// Execute
	//-----------------------------------------------------------------------
	Context context;
	nRetVal = context.Init();
	CHECK_RC(nRetVal, "Init");

	// open input file
	Player player;
	nRetVal = context.OpenFileRecording(strInputFile, player);
	CHECK_RC(nRetVal, "Open input file");

	// play as fast as you can
	nRetVal = player.SetPlaybackSpeed(XN_PLAYBACK_SPEED_FASTEST);
	CHECK_RC(nRetVal, "Setting playback speed");

	// don't rewind recording
	nRetVal = player.SetRepeat(FALSE);
	XN_IS_STATUS_OK(nRetVal);

	// get the list of all created nodes
	NodeInfoList nodes;
	nRetVal = player.EnumerateNodes(nodes);
	CHECK_RC(nRetVal, "Enumerate nodes");

	// first of all, find primary node
	ProductionNode primaryNode;
	if (primaryNodeType != XN_NODE_TYPE_INVALID)
	{
		nRetVal = context.FindExistingNode(primaryNodeType, primaryNode);
		if (nRetVal != XN_STATUS_OK)
		{
			printf("Input file does not contain any node of type %s\n", xnProductionNodeTypeToString(primaryNodeType));
			return -1;
		}
	}
	else if (strPrimaryNode != NULL)
	{
		nRetVal = context.GetProductionNodeByName(strPrimaryNode, primaryNode);
		if (nRetVal != XN_STATUS_OK)
		{
			printf("Input file does not contain any node named %s\n", strPrimaryNode);
			return -1;
		}
	}

	XnUInt32 nTotalFrames = 0;

	// first seek to end frame (to calculate total amount of work)
	if (nEndFrame != XN_MAX_UINT32)
	{
		nRetVal = player.SeekToFrame(primaryNode.GetName(), nEndFrame, XN_PLAYER_SEEK_SET);
		CHECK_RC(nRetVal, "Seeking to end frame");

		for (NodeInfoList::Iterator it = nodes.Begin(); it != nodes.End(); ++it)
		{
			NodeInfo nodeInfo = *it;
			XnUInt32 nNodeFrames = 0;
			nRetVal = player.TellFrame(nodeInfo.GetInstanceName(), nNodeFrames);
			CHECK_RC(nRetVal, "Tell frame");

			nTotalFrames += nNodeFrames;
		}
	}
	else
	{
		for (NodeInfoList::Iterator it = nodes.Begin(); it != nodes.End(); ++it)
		{
			NodeInfo nodeInfo = *it;
			XnUInt32 nNodeFrames = 0;
			nRetVal = player.GetNumFrames(nodeInfo.GetInstanceName(), nNodeFrames);
			CHECK_RC(nRetVal, "Get number of frames");

			nTotalFrames += nNodeFrames;
		}
	}

	// seek to start frame
	if (nStartFrame > 0)
	{
		nRetVal = player.SeekToFrame(primaryNode.GetName(), nStartFrame, XN_PLAYER_SEEK_SET);
		CHECK_RC(nRetVal, "Seeking to start frame");

		// remove skipped frames from total
		for (NodeInfoList::Iterator it = nodes.Begin(); it != nodes.End(); ++it)
		{
			NodeInfo nodeInfo = *it;
			XnUInt32 nNodeFrames = 0;
			nRetVal = player.TellFrame(nodeInfo.GetInstanceName(), nNodeFrames);
			CHECK_RC(nRetVal, "Tell frame");

			nTotalFrames -= nNodeFrames;
		}
	}
	
	// create recorder
	Recorder recorder;
	nRetVal = recorder.Create(context);
	CHECK_RC(nRetVal, "Create recorder");

	nRetVal = recorder.SetDestination(XN_RECORD_MEDIUM_FILE, strOutputFile);
	CHECK_RC(nRetVal, "Set recorder destination file");

	// add nodes to recorder
	if (nNodeNames > 0)
	{
		for (XnUInt32 i = 0; i < nNodeNames; ++i)
		{
			ProductionNode node;
			nRetVal = context.GetProductionNodeByName(astrNodeNames[i], node);
			if (nRetVal != XN_STATUS_OK)
			{
				printf("Input file does not contain any node named %s\n", astrNodeNames[i]);
				return -1;
			}

			nRetVal = recorder.AddNodeToRecording(node);
			CHECK_RC(nRetVal, "Add to recording");
		}
	}
	else if (nNodeTypes > 0)
	{
		XnBool bAnyNodeAdded = FALSE;

		for (NodeInfoList::Iterator it = nodes.Begin(); it != nodes.End(); ++it)
		{
			NodeInfo nodeInfo = *it;
			const XnProductionNodeDescription& description = nodeInfo.GetDescription();

			for (XnUInt32 i = 0; i < nNodeTypes; ++i)
			{
				if (description.Type == aNodeTypes[i])
				{
					ProductionNode node;
					nRetVal = nodeInfo.GetInstance(node);
					CHECK_RC(nRetVal, "Get Instance");

					nRetVal = recorder.AddNodeToRecording(node);
					CHECK_RC(nRetVal, "Add to recording");

					bAnyNodeAdded = TRUE;
					break;
				}
			}
		}

		if (!bAnyNodeAdded)
		{
			printf("No node was found in input which matches requested types.\n");
			return -1;
		}
	}
	else
	{
		// add all nodes
		for (NodeInfoList::Iterator it = nodes.Begin(); it != nodes.End(); ++it)
		{
			NodeInfo nodeInfo = *it;
			ProductionNode node;
			nRetVal = nodeInfo.GetInstance(node);
			CHECK_RC(nRetVal, "Get Instance");

			nRetVal = recorder.AddNodeToRecording(node);
			CHECK_RC(nRetVal, "Add to recording");
		}
	}

	XnUInt32 nFrame = 0;
	XnDouble fPercentageFraction = 100.0 / nTotalFrames;

	while ((nRetVal = context.WaitAnyUpdateAll()) != XN_STATUS_EOF)
	{
		CHECK_RC(nRetVal, "Read next frame");
		printf("Recording: %.1f%%\r", nFrame * fPercentageFraction);

		if (primaryNode.IsValid())
		{
			XnUInt32 nCurrentFrame;
			nRetVal = player.TellFrame(primaryNode.GetName(), nCurrentFrame);
			CHECK_RC(nRetVal, "Tell frame");

			if (nCurrentFrame == nEndFrame)
			{
				break;
			}
		}

		++nFrame;
	}

	recorder.Release();
	player.Release();
	context.Release();

	return 0;
}