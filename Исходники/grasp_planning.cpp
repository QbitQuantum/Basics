int main(int argc, char **argv)
{
    signal(SIGSEGV, handler);
    signal(SIGABRT, handler);

    PRINT_INIT_STD();

    std::string worldFilename;
    std::string robotFilename;
    std::string objectFilename;
    std::string outputDirectory;

    if (!loadParams(argc, argv, worldFilename, robotFilename, objectFilename, outputDirectory))
    {
        return 1;
    }

    PRINTMSG("Creating planner");

    std::string name = "EigenGraspPlanner1";  // TODO make parameter
    SHARED_PTR<GraspIt::GraspItSceneManager> graspitMgr(new GraspIt::GraspItSceneManagerNoGui());

#ifdef USE_EIGENGRASP_NOQT
    SHARED_PTR<GraspIt::EigenGraspPlannerNoQt> p(new GraspIt::EigenGraspPlannerNoQt(name, graspitMgr));
#else
    SHARED_PTR<GraspIt::EigenGraspPlanner> p(new GraspIt::EigenGraspPlanner(name, graspitMgr));
#endif

    if (!worldFilename.empty())
    {
        PRINTMSG("Loading world");
        graspitMgr->loadWorld(worldFilename);
    }
    else
    {
        // TODO add an option to set the transforms.
        // For now, they're put in the origin. For the planning, this should not really matter...
        GraspIt::EigenTransform robotTransform;
        GraspIt::EigenTransform objectTransform;
        robotTransform.setIdentity();
        objectTransform.setIdentity();
        // objectTransform.translate(Eigen::Vector3d(100,0,0));
        std::string robotName("Robot1");  // TODO parameterize
        std::string objectName("Object1");
        if ((graspitMgr->loadRobot(robotFilename, robotName, robotTransform) != 0) ||
                (graspitMgr->loadObject(objectFilename, objectName, true, objectTransform)))
        {
            PRINTERROR("Could not load robot or object");
            return 1;
        }

        // in case one wants to view the initial world before planning, save it:
        graspitMgr->saveGraspItWorld(outputDirectory + "/worlds/startWorld.xml");
        graspitMgr->saveInventorWorld(outputDirectory + "/worlds/startWorld.iv");
    }

    // now save the world again as inventor file, to test
    // p->saveIVWorld("test.iv");

    int maxPlanningSteps = 50000;
    int repeatPlanning = 1;
    int keepMaxPlanningResults = 3;
    bool finishWithAutograsp = false;
    p->plan(maxPlanningSteps, repeatPlanning, keepMaxPlanningResults, finishWithAutograsp);

    PRINTMSG("Saving results as world files");

    bool createDir = true;
    bool saveIV = true;
    bool saveWorld = true;

    std::string resultsWorldDirectory = outputDirectory;
    std::string filenamePrefix = "world";
    p->saveResultsAsWorldFiles(resultsWorldDirectory, filenamePrefix, saveWorld, saveIV, createDir);

    std::vector<GraspIt::EigenGraspResult> allGrasps;
    p->getResults(allGrasps);

    PRINTMSG("Grasp results:");
    std::vector<GraspIt::EigenGraspResult>::iterator it;
    for (it = allGrasps.begin(); it != allGrasps.end(); ++it)
    {
        PRINTMSG(*it);
    }

    PRINTMSG("Quitting program.");
    return 1;
}