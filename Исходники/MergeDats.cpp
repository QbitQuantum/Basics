int main(int argc, char *argv[])
{
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    std::cout << "Hostname: " << hostname << std::endl;

    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    std::cout << "Current local time and date: " << asctime (timeinfo) << std::endl;

    char *expPath1 = const_cast<char*>(".");
    char *expPath2 = const_cast<char*>(".");
    char *destPath = const_cast<char*>("./converted");
    int dont_retry = 0;
    int ignoreChecksumErrors = 1;
    if (argc <= 6) {
        usage();
    }
    int argcc = 1;
    while (argcc < argc) {
        switch (argv[argcc][1]) {

        case 's':
            argcc++;
            expPath1 = argv[argcc];
            break;

        case 't':
            argcc++;
            expPath2 = argv[argcc];
            break;

        case 'o':
            argcc++;
            destPath = argv[argcc];
            break;

        case 'c':
            ignoreChecksumErrors = 0;
            break;

        case 'z':
            dont_retry = 1;
            break;

        case 'v':
            fprintf (stdout, "%s", IonVersion::GetFullVersion("MergeDats").c_str());
            exit (0);
            break;
        case 'H':
            usage();
            break;

        default:
            argcc++;
            fprintf (stdout, "\n");

        }
        argcc++;
    }

    MergeAcq merger;
    Image top;
    Image bottom;
    Image combo;
    Acq acq;
    top.SetImgLoadImmediate(false);
    bottom.SetImgLoadImmediate(false);

    char name1[MAX_PATH_LENGTH];
    char name2[MAX_PATH_LENGTH];
    char destName[MAX_PATH_LENGTH];
    int i = 0;
    int k = 0;
    int mode = 0;
    bool allocate = true;

    const char *postNameList[] = {
        "beadfind_post_0000.dat", "beadfind_post_0001.dat",
        "beadfind_post_0002.dat", "beadfind_post_0003.dat"
    };


    // Specify if checksum errors should be ignored
    top.SetIgnoreChecksumErrors(ignoreChecksumErrors);
    bottom.SetIgnoreChecksumErrors(ignoreChecksumErrors);

    // if requested...do not bother waiting for the files to show up
    if (dont_retry) {
        top.SetTimeout(1,1);
        bottom.SetTimeout(1,1);
    }

    int postNameListLen = sizeof(postNameList)/sizeof(postNameList[0]);

    // Create results folder
    umask (0);  // make permissive permissions so its easy to delete.
    if (mkdir (destPath, 0777)) {
        if (errno == EEXIST) {
            //already exists? well okay...
        }
        else {
            perror (destPath);
            exit (1);
        }
    }

    // waiting for first acquisition
    sprintf(name1, "%s/acq_%04d.dat", expPath1, 0);
    sprintf(name2, "%s/acq_%04d.dat", expPath2, 0);
    struct stat info1;
    struct stat info2;
    int limit_seconds = 60*60*12;
    int passed_seconds = 0;
    int delta = 3;
    while ((stat(name1, &info1) || stat(name2, &info2)) && passed_seconds < limit_seconds) {
        passed_seconds += delta;
        sleep(delta);
    }  
    std::cout << "continue with merging beadfind files" << std::endl << std::endl;
   
    // merge beadfinds as soon as acq_0000.dat is available

    // beadfind 
    k = 0;
    while (true)
    {
        sprintf(name1, "%s/beadfind_pre_%04d.dat", expPath1, k);
        sprintf(name2, "%s/beadfind_pre_%04d.dat", expPath2, k);
        sprintf(destName, "%s/beadfind_pre_%04d.dat", destPath, k);
        if (stat(name1, &info1) || stat(name2, &info2)) {
            std::cout << "continue with merging prerun files" << std::endl << std::endl;
            break;
        }
        if (! top.LoadRaw(name1, 0, allocate, false)) {
            std::cout << "cannot merge into file: " << destName << std::endl;
            continue;
        }
        if (! bottom.LoadRaw(name2, 0, allocate, false)) {
            std::cout << "cannot merge into file: " << destName << std::endl;
            continue;
        }
        merge(&merger,&acq,&combo,&top,&bottom,destName);
        k++;
    }

    // prerun
    k = 0;
    while (true)
    {
        sprintf(name1, "%s/prerun_%04d.dat", expPath1, k);
        sprintf(name2, "%s/prerun_%04d.dat", expPath2, k);
        sprintf(destName, "%s/prerun_%04d.dat", destPath, k);
        if (stat(name1, &info1) || stat(name2, &info2)) {
            std::cout << "continue with merging acq files" << std::endl << std::endl;
            break;
        }
        if (! top.LoadRaw(name1, 0, allocate, false)) {
            std::cout << "cannot merge into file: " << destName << std::endl;
            continue;
        }
        if (! bottom.LoadRaw(name2, 0, allocate, false)) {
            std::cout << "cannot merge into file: " << destName << std::endl;
            continue;
        }
        merge(&merger,&acq,&combo,&top,&bottom,destName);
        k++;
    }

    while (mode < 2) {
        if (mode == 0) {
            sprintf(name1, "%s/acq_%04d.dat", expPath1, i);
            sprintf(name2, "%s/acq_%04d.dat", expPath2, i);
            sprintf(destName, "%s/acq_%04d.dat", destPath, i);
        } else if (mode == 1) {
            if(i >= postNameListLen)
                break;
            sprintf(name1, "%s/%s", expPath1, postNameList[i]);
            sprintf(name2, "%s/%s", expPath2, postNameList[i]);
            sprintf(destName, "%s/%s", destPath, postNameList[i]);
        } else
            break;

        std::cout << "Loading images." << std::endl;
        if (top.LoadRaw(name1, 0, allocate, false) && bottom.LoadRaw(name2, 0, allocate, false)) {
            allocate = false;

            merge(&merger,&acq,&combo,&top,&bottom,destName);

            fflush (stdout);
            i++;
        }
        else {
            if ((mode == 1 && i >= 12) || (mode == 0)) {
                mode++;
                i = 0;
                allocate = true;
            }
            else
                i++;
        }
    }
    return EXIT_SUCCESS;
}