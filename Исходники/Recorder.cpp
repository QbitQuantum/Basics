int recorder::record()
{
    Recording = true;
    qDebug("//////////////////////////////////////");
    qDebug("/// Welcome to the Kinect Recorder!///");
    qDebug("/// Press any key to STOP recording!//\n");

    bool record_rgb=true;

    //Metadata
    QFileInfo MetadataFile;
    MetadataFile.setFile(QDir::currentPath() + "/Metadata.txt");

    ofstream Metadata_file;

    if(MetadataFile.exists()){
        qDebug("Metadata File exists ");
        Metadata_file.open(MetadataFile.absoluteFilePath().toLocal8Bit(), ofstream::out | ofstream::app);
        Metadata_file.close();
    }
    else{
        qDebug("Metadata File doesn't exist ");
        Metadata_file.open(MetadataFile.absoluteFilePath().toLocal8Bit(), ofstream::out | ofstream::app);
        Metadata_file.close();
    }

    //Status variable
    XnStatus nRetVal = XN_STATUS_OK;

    //Context
    Context context;
    nRetVal = context.Init();

    //Vectors of Generators
    DepthGenerator DepthsGen[MAXGENERATORS];
    ImageGenerator ImagesGen[MAXGENERATORS];
    Recorder Recorders[MAXGENERATORS];

    //Node list.
    NodeInfoList node_info_list;
    NodeInfoList depth_nodes;
    NodeInfoList img_nodes;

    int nKinects = 0;
    int nDepths = 0;
    int nImg = 0;
    int Frames=0;

    //Enumeramos los nodos
    nRetVal = context.EnumerateProductionTrees(XN_NODE_TYPE_DEVICE, NULL,node_info_list);

    //Comprobamos la enumeración
    if(nRetVal != XN_STATUS_OK && node_info_list.Begin() != node_info_list.End()){
        qDebug ("Enumerating devices failed. Reason: %s", xnGetStatusString(nRetVal));
        return -1;
    }

    else if(node_info_list.Begin () == node_info_list.End()){
        qDebug("No devices found.\n");
        return -1;
    }

    for (xn::NodeInfoList::Iterator nodeIt = node_info_list.Begin(); nodeIt != node_info_list.End(); ++nodeIt){
        NodeInfo info = *nodeIt;
        const XnProductionNodeDescription& description = info.GetDescription();
        qDebug("Info: vendor %s name %s , instance %s",description.strVendor,description.strName, info.GetInstanceName());
    }

    //Count number of devices available for recording
    for (NodeInfoList::Iterator nodeIt = node_info_list.Begin(); nodeIt != node_info_list.End(); ++nodeIt){
        nKinects++;
    }
    qDebug("Number of Devices %d", nKinects);

    //Enumerate depth Devices
    nRetVal = context.EnumerateProductionTrees(XN_NODE_TYPE_DEPTH, NULL, depth_nodes, NULL);
    if (nRetVal != XN_STATUS_OK && depth_nodes.Begin () != depth_nodes.End ()) {
        qDebug ("Enumerating devices failed. Reason: %s", xnGetStatusString (nRetVal));
        return -1;
    }
    else if (depth_nodes.Begin () == depth_nodes.End ()) {
        qDebug("No devices found.\n");
        return -1;
    }

    //Enumerate RGB Devices
    if(record_rgb){
        //IMAGE devices
        nRetVal = context.EnumerateProductionTrees(XN_NODE_TYPE_IMAGE, NULL, img_nodes, NULL);
        if (nRetVal != XN_STATUS_OK && img_nodes.Begin () != img_nodes.End ()) {
            qDebug ("Enumerating devices failed. Reason: %s", xnGetStatusString (nRetVal));
            return -1;
        }
        else if (img_nodes.Begin () == img_nodes.End ()) {
            qDebug("No devices found.\n");
            return -1;
        }
    }

    //Show depth devices
    int i = 0;
    for (xn::NodeInfoList::Iterator nodeIt = depth_nodes.Begin(); nodeIt != depth_nodes.End(); ++nodeIt, i++) {
        NodeInfo info = *nodeIt;
        const XnProductionNodeDescription& description = info.GetDescription();
        qDebug("Depth: vendor %s name %s, instance %s",description.strVendor,description.strName, info.GetInstanceName());
        nDepths++;
    }

    //Show RGB Devices
    if(record_rgb){
        //RGB devices
        i = 0;
        for (xn::NodeInfoList::Iterator nodeIt = img_nodes.Begin(); nodeIt != img_nodes.End(); ++nodeIt, i++) {
            NodeInfo info = *nodeIt;
            const XnProductionNodeDescription& description = info.GetDescription();
            qDebug("RGB: vendor %s name %s, instance %s",description.strVendor,description.strName, info.GetInstanceName());
            nImg++;
        }

    }

    //Init everything
    i=0;
    char date[20];
    strcpy(date,QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss").toLocal8Bit());
    qDebug() << date;

    //Init depth devices & 'recorders'
    DepthGenerator depthaux[MAXGENERATORS];
    Recorder recorderaux[MAXGENERATORS];

    for (xn::NodeInfoList::Iterator nodeIt = depth_nodes.Begin(); nodeIt != depth_nodes.End(); ++nodeIt, i++) {
        //DepthGenerator depthaux;
        //Recorder recorderaux;
        XNFiles AuxFile;
        NodeInfo info = *nodeIt;
        const XnProductionNodeDescription& description = info.GetDescription();

        nRetVal = context.CreateProductionTree(info,depthaux[i]);
        nRetVal = info.GetInstance(depthaux[i]);
        qDebug("Instance Name %s",info.GetInstanceName());

        XnFieldOfView field;
        nRetVal= depthaux[i].GetFieldOfView(field);

        DepthsGen[i]=depthaux[i];
        qDebug("Depth Generator %i", i);

        Recorders[i]=recorderaux[i];
        nRetVal = Recorders[i].Create(context);

        XnChar recording_fileXnaux[300];
        strcpy(recording_fileXnaux,QDir::currentPath().toLocal8Bit());

        if(record_rgb)
            sprintf(recording_fileXnaux,"%s%s%s%d%s%s.oni",recording_fileXnaux,"/","DC-",i,"_",date);
        else
            sprintf(recording_fileXnaux,"%s%s%s%d%s%s.oni",recording_fileXnaux,"/","D-",i,"_",date);

        strcpy(AuxFile.name,recording_fileXnaux);
        qDebug(AuxFile.name);

        nRetVal = Recorders[i].SetDestination(XN_RECORD_MEDIUM_FILE,recording_fileXnaux);
        nRetVal = Recorders[i].AddNodeToRecording(DepthsGen[i], XN_CODEC_16Z_EMB_TABLES);
    }

    //Init RGB devices
    if(record_rgb){
        i=0;
        ImageGenerator imgaux[MAXGENERATORS];

        for (xn::NodeInfoList::Iterator nodeIt = img_nodes.Begin(); nodeIt != img_nodes.End(); ++nodeIt, i++) {
            //ImageGenerator imgaux;
            NodeInfo info = *nodeIt;
            const XnProductionNodeDescription& description = info.GetDescription();
            nRetVal = context.CreateProductionTree(info,imgaux[i]);
            nRetVal = info.GetInstance(imgaux[i]);
            qDebug("Instance Name %s",info.GetInstanceName());
            ImagesGen[i]=imgaux[i];
            qDebug("Image Generator %i", i);
            nRetVal = Recorders[i].AddNodeToRecording(ImagesGen[i],XN_CODEC_JPEG);
        }
    }

    XnMapOutputMode Mode;
    Mode.nFPS  = FPS;
    Mode.nXRes = RES_X;
    Mode.nYRes = RES_Y;

    if(record_rgb){
        if(nDepths==nImg ){

            for(int j=0;j<nDepths;j++){

                DepthsGen[j].SetMapOutputMode(Mode);
                CHECK_RC(nRetVal, "SetMap output for depth generator");
                ImagesGen[j].SetMapOutputMode(Mode);
                CHECK_RC(nRetVal, "SetMap output for image generator");

                if(DepthsGen[j].IsCapabilitySupported("AlternativeViewPoint")){
                    nRetVal = DepthsGen[j].GetAlternativeViewPointCap().SetViewPoint(ImagesGen[j]);
                    CHECK_RC(nRetVal, "SetViewPoint for depth generator");
                    qDebug("Alinged Depth and Image %d",j);
                }
            }
        }
    }

    // Context Generating all
    nRetVal = context.StartGeneratingAll();

    qDebug("Starting to record!");

    //For the first time
    qDebug() <<  MetadataFile.absoluteFilePath();
    write_metadata(MetadataFile.absoluteFilePath(),date,START);

    while(Recording){
        nRetVal = context.WaitAndUpdateAll();
        QCoreApplication::processEvents();
        Frames++;
        //if (Frames > 300) Recording = 0;
        //qDebug() << "Recording:" << Recording << "\tFrames:" <<Frames;
    }

    //last file
    char date_last[20];
    strcpy(date_last,QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss").toLocal8Bit());
    write_metadata(MetadataFile.absoluteFilePath(),date_last,STOP);

    //Liberamos
    context.Release();

    qDebug("Finished");
    return 0;
}