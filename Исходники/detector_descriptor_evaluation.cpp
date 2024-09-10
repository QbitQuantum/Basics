void OneWayDescriptorQualityTest::processRunParamsFile ()
{
    string filename = getRunParamsFilename();
    FileStorage fs = FileStorage (filename, FileStorage::READ);
    FileNode fn = fs.getFirstTopLevelNode();
    fn = fn[DEFAULT_PARAMS];

    string pcaFilename = data_path + (string)fn["pcaFilename"];
    string trainPath = data_path + (string)fn["trainPath"];
    string trainImagesList = (string)fn["trainImagesList"];
    int patch_width = fn["patchWidth"];
    int patch_height = fn["patchHeight"];
    Size patchSize = cvSize (patch_width, patch_height);
    int poseCount = fn["poseCount"];

    if (trainImagesList.length () == 0 )
        return;

    fs.release ();

    readAllDatasetsRunParams();

    Ptr<OneWayDescriptorBase> base(
        new OneWayDescriptorBase(patchSize, poseCount, pcaFilename,
                                 trainPath, trainImagesList));

    Ptr<OneWayDescriptorMatch> match = makePtr<OneWayDescriptorMatch>();
    match->initialize( OneWayDescriptorMatch::Params (), base );
    defaultDescMatcher = match;
    writeAllDatasetsRunParams();
}