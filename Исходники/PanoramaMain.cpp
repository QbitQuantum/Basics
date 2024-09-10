int AlignPair(int argc, const char *argv[])
{
    // Align two images using feature matching
    if (argc < 7) {
        printf("usage: %s input1.f input2.f matchfile nRANSAC RANSACthresh [sift]\n", argv[1]);
        return -1;
    }
    const char *infile1 = argv[2];
    const char *infile2 = argv[3];
    const char *matchfile = argv[4];
    int nRANSAC         = atoi(argv[5]);
    double RANSACthresh = atof(argv[6]);

    FeatureSet f1, f2;

    // Read in the feature sets
    if ((argc >= 8) && (strcmp(argv[7], "sift") == 0)) {
        f1.load_sift(infile1);
        f2.load_sift(infile2);
    }
    else {
        f1.load(infile1);
        f2.load(infile2);
    }

    CTransform3x3 M;

    // Read in the feature matches
    vector<FeatureMatch> matches;
    bool success = ReadFeatureMatches(matchfile, matches);

    if (!success) {
        printf("Error opening match file %s for reading\n", matchfile);
        return -1;
    }

    // Perform the alignment.
	if (strcmp(argv[1], "alignPairHomography") == 0) {
		alignPair(f1, f2, matches, eHomography, nRANSAC, RANSACthresh, M);
	} else {
		alignPair(f1, f2, matches, eTranslate, nRANSAC, RANSACthresh, M);
	}

    // Print out the result
    CTransform3x3 Mi = M.Inverse();

    /*printf("% 10.3e %10.3e %10.3e\n %10.3e %10.3e %10.3e\n %10.3e %10.3e %10.3e\n",
            Mi[0][0], Mi[0][1], Mi[0][2],
            Mi[1][0], Mi[1][1], Mi[1][2],
            Mi[2][0], Mi[2][1], Mi[2][2]);*/
	printf("%0.8e %0.8e %0.8e %0.8e %0.8e %0.8e %0.8e %0.8e %0.8e",
            Mi[0][0], Mi[0][1], Mi[0][2],
            Mi[1][0], Mi[1][1], Mi[1][2],
            Mi[2][0], Mi[2][1], Mi[2][2]);

    return 0;
}