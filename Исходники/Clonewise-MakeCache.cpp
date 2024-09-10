static void
MakeCache(const std::string &prefix, int argc, char *argv[], bool _doEmbedded)
{
	MPI_Status status;
	int xi;
 	std::map<std::string, std::list<std::string> >::const_iterator pIter;
	int np, me; 

	cachePath = prefix;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);

	doEmbedded = _doEmbedded;

	LoadEverything();
//	outputFormat = CLONEWISE_OUTPUT_XML;
	printf("# loaded everything\n");
	fflush(stdout);

	if (embeddedOnly) {
		std::map<std::string, std::set<std::string> >::const_iterator eIter;

		if (embeddedList.size() == 0) {
			char s[1024];

		        snprintf(s, sizeof(s), "/var/lib/Clonewise/clones/distros/%s/embedded-code-copies", distroString);
		        LoadEmbeddedCodeCopiesList(s);
		}
		for (	eIter  = embeddedList.begin(), xi = 0;
			eIter != embeddedList.end();
			eIter++)
		{
			vPackages.push_back(eIter->first);
			packageQueue.push_back(xi++);
		}
	} else {
		for (	pIter  = packages.begin(), xi = 0;
			pIter != packages.end();
			pIter++)
		{
			vPackages.push_back(pIter->first);
			packageQueue.push_back(xi++);
		}
	}

	printf("# going to scan %i packages\n", xi);
	fflush(stdout);
	if (me == 0) {
		while (packageQueue.size() != 0) {
			int index, which;

			MPI_Recv(&which, 1, MPI_INT, MPI_ANY_SOURCE, TAG1, MPI_COMM_WORLD, &status); 
			index = packageQueue.front();
			packageQueue.pop_front();
			MPI_Send(&index, 1, MPI_INT, which, TAG1, MPI_COMM_WORLD); 
		}
		for (int i = 1; i < np; i++) {
			int which, neg = -1;

			MPI_Recv(&which, 1, MPI_INT, i, TAG1, MPI_COMM_WORLD, &status); 
			MPI_Send(&neg, 1, MPI_INT, i, TAG1, MPI_COMM_WORLD); 
		}
		for (size_t i = 0; i < vPackages.size(); i++) { 
			int which;
			int r[2], size;
			char *result;
			FILE *f;
			char s[1024];

			MPI_Recv(&which, 1, MPI_INT, MPI_ANY_SOURCE, TAG1, MPI_COMM_WORLD, &status); 
			MPI_Recv(r, 2, MPI_INT, which, TAG1, MPI_COMM_WORLD, &status); 

			size = r[1];
			result = new char[size];

			MPI_Recv(result, size, MPI_CHAR, which, TAG1, MPI_COMM_WORLD, &status); 

			snprintf(s, sizeof(s), "/var/lib/Clonewise/clones/distros/%s/%s/%s", distroString, prefix.c_str(), vPackages[r[0]].c_str());
			f = fopen(s, "w");
			fwrite(result, 1, size, f);
			fclose(f), f = NULL;

			delete [] result;
		}
	} else {
		DoWorkLoop(me);
	}

	MPI_Finalize(); 
	exit(0); 
}