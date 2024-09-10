int main(int argc, char* argv[])
{
    XnStatus nRetVal = XN_STATUS_OK;
    nRetVal = xnLogInitFromXmlFile(SAMPLE_XML_PATH);
    if (nRetVal != XN_STATUS_OK)
    {
        printf("Log couldn't be opened: %s. Running without log", xnGetStatusString(nRetVal));
    }

    if (argc < 3)
    {
        printf("usage: %s <inputFile> <outputFile>\n", argv[0]);
        return -1;
    }

    const char* strInputFile = argv[1];
    const char* strOutputFile = argv[2];

    Context context;
    nRetVal = context.Init();
    CHECK_RC(nRetVal, "Init");

    // open input file
    nRetVal = context.OpenFileRecording(strInputFile);
    CHECK_RC(nRetVal, "Open input file");

    Player player;
    nRetVal = context.FindExistingNode(XN_NODE_TYPE_PLAYER, player);
    CHECK_RC(nRetVal, "Get player node");

    // Get depth node from recording
    DepthGenerator depth;
    nRetVal = context.FindExistingNode(XN_NODE_TYPE_DEPTH, depth);
    CHECK_RC(nRetVal, "Find depth generator");

    // Create mock node based on depth node from recording
    MockDepthGenerator mockDepth;
    nRetVal = mockDepth.CreateBasedOn(depth);
    CHECK_RC(nRetVal, "Create mock depth node");

    // create recorder
    Recorder recorder;

    nRetVal = recorder.Create(context);
    CHECK_RC(nRetVal, "Create recorder");

    nRetVal = recorder.SetDestination(XN_RECORD_MEDIUM_FILE, strOutputFile);
    CHECK_RC(nRetVal, "Set recorder destination file");

    // add depth node to recorder
    nRetVal = recorder.AddNodeToRecording(mockDepth, XN_CODEC_16Z);
    CHECK_RC(nRetVal, "Add node to recording");

    nRetVal = player.SetRepeat(FALSE);
    XN_IS_STATUS_OK(nRetVal);

    XnUInt32 nNumFrames = 0;

    nRetVal = player.GetNumFrames(depth.GetName(), nNumFrames);
    CHECK_RC(nRetVal, "Get player number of frames");

    DepthMetaData depthMD;

    while ((nRetVal = depth.WaitAndUpdateData()) != XN_STATUS_EOF)
    {
        CHECK_RC(nRetVal, "Read next frame");

        // Get depth meta data
        depth.GetMetaData(depthMD);

        //-----------------------------------------------//
        // Transform depth! This is the interesting part //
        //-----------------------------------------------//

        /* Enable the depth data to be modified. This is done implicitly by depthMD.WritableDepthMap(),
           but we're calling it just to be clear. */
        nRetVal = depthMD.MakeDataWritable();
        CHECK_RC(nRetVal, "Make depth data writable");

        transformDepthMD(depthMD);

        // Pass the transformed data to the mock depth generator
        nRetVal = mockDepth.SetData(depthMD);
        CHECK_RC(nRetVal, "Set mock node new data");

        /* We need to call recorder.Record explicitly because we're not using WaitAndUpdateAll(). */
        nRetVal = recorder.Record();
        CHECK_RC(nRetVal, "Record");

        printf("Recorded: frame %u out of %u\r", depthMD.FrameID(), nNumFrames);
    }

    printf("\n");

    recorder.Release();
    context.Shutdown();

    return 0;
}