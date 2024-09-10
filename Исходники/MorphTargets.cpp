void MorphTargets::LoadAnimations(void)
{
    double time = glfwGetTime();

    static const char *folder = "Resources/Animations/";
    char currentIndex[256] = "";

    std::vector<OBJModel> idle;
    for (unsigned int i = 1; i <= 10; ++i)
    {
        char filePath[256] = "";

        //Load the file
        strcat_s(filePath, folder);
        strcat_s(filePath, "IdleAnimation/idle");
        _itoa_s(i, currentIndex, 10);
        strcat_s(filePath, currentIndex);
        strcat_s(filePath,".obj");

        idle.push_back(OBJModel(filePath, false));
    }

    animations.push_back(idle);

    std::vector<OBJModel> move;
    for (unsigned int i = 1; i <= 10; ++i)
    {
        char filePath[256] = "";

        //Load the file
        strcat_s(filePath, folder);
        strcat_s(filePath, "RunAnimation/run");
        _itoa_s(i, currentIndex, 10);
        strcat_s(filePath, currentIndex);
        strcat_s(filePath, ".obj");

        move.push_back(OBJModel(filePath, false));
    }

    animations.push_back(move);

    std::vector<OBJModel> punch;
    for (unsigned int i = 1; i <= 10; ++i)
    {
        char filePath[256] = "";

        //Load the file
        strcat_s(filePath, folder);
        strcat_s(filePath, "PunchAnimation/punch");
        _itoa_s(i, currentIndex, 10);
        strcat_s(filePath, currentIndex);
        strcat_s(filePath, ".obj");

        punch.push_back(OBJModel(filePath, false));
    }

    animations.push_back(punch);

    std::vector<OBJModel> block;
    for (unsigned int i = 1; i <= 10; ++i)
    {
        char filePath[256] = "";

        //Load the file
        strcat_s(filePath, folder);
        strcat_s(filePath, "BlockAnimation/block");
        _itoa_s(i, currentIndex, 10);
        strcat_s(filePath, currentIndex);
        strcat_s(filePath, ".obj");

        block.push_back(OBJModel(filePath, false));
    }

    animations.push_back(block);

    std::vector<OBJModel> stagger;
    for (unsigned int i = 1; i <= 10; ++i)
    {
        char filePath[256] = "";

        //Load the file
        strcat_s(filePath, folder);
        strcat_s(filePath, "StaggerAnimation/stagger");
        _itoa_s(i, currentIndex, 10);
        strcat_s(filePath, currentIndex);
        strcat_s(filePath, ".obj");

        stagger.push_back(OBJModel(filePath, false));
    }

    animations.push_back(stagger);

    std::vector<OBJModel> groundKick;
    for (unsigned int i = 1; i <= 10; ++i)
    {
        char filePath[256] = "";

        //Load the file
        strcat_s(filePath, folder);
        strcat_s(filePath, "GroundKickAnimation/groundkick");
        _itoa_s(i, currentIndex, 10);
        strcat_s(filePath, currentIndex);
        strcat_s(filePath, ".obj");

        groundKick.push_back(OBJModel(filePath, false));
    }

    animations.push_back(groundKick);

    std::vector<OBJModel> airKick;
    for (unsigned int i = 1; i <= 10; ++i)
    {
        char filePath[256] = "";

        //Load the file
        strcat_s(filePath, folder);
        strcat_s(filePath, "DiveKickAnimation/divekick");
        _itoa_s(i, currentIndex, 10);
        strcat_s(filePath, currentIndex);
        strcat_s(filePath, ".obj");

        airKick.push_back(OBJModel(filePath, false));
    }

    animations.push_back(airKick);
}