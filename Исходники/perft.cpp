int
runTests(
			int		argc,
			char*	argv[])
{
	// Just hoist everything...
	XALAN_CPP_NAMESPACE_USE

	MemoryManagerType& theManager = XalanMemMgrs::getDefaultXercesMemMgr();

	XalanFileUtility	h(theManager);

	// Set the program help string,  then get the command line parameters.
	//
	setHelp(h);

	bool setGold = false;

	const XalanDOMString	processorType(XALAN_STATIC_UCODE_STRING("XalanC"));

	if (h.getParams(argc, argv, "PERFT-RESULTS", setGold) == true)
	{
		XalanTransformer xalan;

		// Generate Unique Run id and processor info
		XalanDOMString UniqRunid;
		h.generateUniqRunid(UniqRunid);


		// Defined basic constants for file manipulation and open results file
		const XalanDOMString  resultFilePrefix("cpp");
		XalanDOMString  resultsFile= h.args.output;
		resultsFile += resultFilePrefix;
		resultsFile += UniqRunid;
		resultsFile += XalanFileUtility::s_xmlSuffix;


		XalanXMLFileReporter	logFile(theManager, resultsFile);
		logFile.logTestFileInit("Performance Testing - Reports various performance metrics using the Transformer");

		// Get the list of sub-directories below "base" and iterate through them
		bool foundDir = false;		// Flag indicates directory found. Used in conjunction with -sub cmd-line arg.

		typedef XalanFileUtility::FileNameVectorType		FileNameVectorType;

		FileNameVectorType dirs;
		h.getDirectoryNames(h.args.base, dirs);

		for(FileNameVectorType::size_type	j = 0; j < dirs.size(); j++)
		{
			// Run specific category of files from given directory
			if (length(h.args.sub) > 0 && !equals(dirs[j], h.args.sub))
			{
				continue;
			}

			cout << "Processing files in Directory: " << dirs[j] << endl;

			// Check that output directory is there.
			XalanDOMString  theOutputDir = h.args.output;
			theOutputDir += dirs[j];
			h.checkAndCreateDir(theOutputDir);

					
			// Indicate that directory was processed and get test files from the directory
			foundDir = true;
			FileNameVectorType files;
			h.getTestFileNames(h.args.base, dirs[j], false, files);
			XalanDOMString logEntry;
			logEntry = "Performance Directory: ";
			logEntry += dirs[j];
			logFile.logTestCaseInit(logEntry);

			const long	iterCount = h.args.iters;

			for(FileNameVectorType::size_type i = 0; i < files.size(); i++)
			{
				// Define  variables used for timing and reporting ...
				clock_t startTime, endTime, accmTime, avgEtoe;
				double timeinMilliseconds = 0, theAverage =0;
				int transformResult = 0;

				typedef XalanXMLFileReporter::Hashtable	Hashtable;

				Hashtable attrs(theManager);

				attrs.insert(Hashtable::value_type(XalanDOMString("idref"), files[i]));
				attrs.insert(Hashtable::value_type(XalanDOMString("UniqRunid"),UniqRunid));
				attrs.insert(Hashtable::value_type(XalanDOMString("processor"),processorType));
				logFile.addMetricToAttrs("Iterations",iterCount, attrs);
								
				if (h.args.skip)
				{
					if (checkForExclusion(files[i]))
						continue;
				}

				XalanDOMString  theXSLFile = h.args.base;
				theXSLFile += dirs[j];
				theXSLFile += XalanFileUtility::s_pathSep;
				theXSLFile += files[i];

				XalanDOMString  theXMLFile; 
				h.generateFileName(theXSLFile,"xml", theXMLFile);

				XalanDOMString  outbase = h.args.output;
				outbase += dirs[j];
				outbase += XalanFileUtility::s_pathSep;
				outbase += files[i]; 
				XalanDOMString  theOutputFile;
				h.generateFileName(outbase, "out", theOutputFile);

				const XSLTInputSource	xslInputSource(theXSLFile);
				const XSLTInputSource	xmlInputSource(theXMLFile);
				const XSLTResultTarget	theResultTarget(theOutputFile);

				attrs.insert(Hashtable::value_type(XalanDOMString("href"), theXSLFile));
				cout << endl << files[i] << endl;

				// Time the parsing(compile) of the XSL stylesheet and report the results..
				//
				startTime = clock();
				const XalanCompiledStylesheet*	compiledSS = 0;
				xalan.compileStylesheet(xslInputSource, compiledSS);
				endTime = clock();

				if (compiledSS == 0)
				{
					continue;
				}

				timeinMilliseconds = calculateElapsedTime(startTime, endTime);
				cout << "   XSL: " << timeinMilliseconds << " milliseconds, Parse" << endl;
				logFile.addMetricToAttrs("parsexsl",timeinMilliseconds, attrs);	

				// Time the parsing of the input XML and report the results..
				//
				startTime = clock();
				const XalanParsedSource*	parsedSource = 0;
				xalan.parseSource(xmlInputSource, parsedSource);
				endTime = clock();

				if (parsedSource == 0)
				{
					continue;
				}

				timeinMilliseconds = calculateElapsedTime(startTime, endTime);
				cout << "   XML: " << timeinMilliseconds << " milliseconds, Parse" <<endl;
				logFile.addMetricToAttrs("parsexml",timeinMilliseconds, attrs);

				// Perform One transform using parsed stylesheet and unparsed xml source, report results...
				// 
				startTime = clock();
					transformResult = xalan.transform(xmlInputSource, compiledSS, theResultTarget);
				endTime = clock();
				if(!transformResult)
				{
					timeinMilliseconds = calculateElapsedTime(startTime, endTime);
					cout << endl << "   One: " << timeinMilliseconds << " w/Parsed XSL." << endl;
					logFile.addMetricToAttrs("single", timeinMilliseconds, attrs);	
				}
				else
				{
					cout << xalan.getLastError();
					return -1;
				}

				// Do One eTOe transform with no pre parsing of either xsl or xml files.
				// And output metrics to console and result log
				startTime = clock();
					transformResult = xalan.transform(xmlInputSource, xslInputSource, theResultTarget);
				endTime = clock();
				if(!transformResult)
				{
					timeinMilliseconds = calculateElapsedTime(startTime, endTime);
					cout << "   One: " << timeinMilliseconds << " eTOe." << endl;
					logFile.addMetricToAttrs("etoe", timeinMilliseconds, attrs);	
				}
				else
				{
					cout << xalan.getLastError();
					return -1;
				}


				// Perform multiple transforms and calculate the average time ..
				// These are done 3 different ways.
				//
				// FIRST: Parsed XSL Stylesheet and Parsed XML Source.
				//
				accmTime = 0;
				for(int j = 0; j < iterCount; ++j)
				{	
					startTime = clock();
						transformResult = xalan.transform(*parsedSource, compiledSS, theResultTarget);
					endTime = clock();
					
					accmTime += endTime - startTime;
				}

				theAverage = calculateAvgTime(accmTime, iterCount); 
				cout << endl << "   Avg: " << theAverage << " for " << iterCount << " iter's w/Parsed files" << endl;
				logFile.addMetricToAttrs("avgparsedxml",theAverage, attrs);
				

				// SECOND: Parsed Stylesheet and UnParsed XML Source.
				// This is currently how the XalanJ 2.0 is performing transforms
				//
				accmTime = 0;
				for(int k = 0; k < iterCount; ++k)
				{
					startTime = clock();
						transformResult = xalan.transform(xmlInputSource, compiledSS, theResultTarget);
					endTime = clock();
					
					accmTime += endTime - startTime;						
				}
				theAverage = calculateAvgTime(accmTime, iterCount);
				cout << "   Avg: " << theAverage << " for " << iterCount << " iter's w/UnParsed XML" << endl;
				logFile.addMetricToAttrs("avgunparsedxml",theAverage, attrs);


				// THIRD: Neither Stylesheet nor XML Source are parsed.
				// Perform multiple etoe transforms and calculate the average ...
				//
				avgEtoe = 0;
				for(int jj = 0; jj < iterCount; ++jj)
				{	
					startTime = clock();
						transformResult = xalan.transform(xmlInputSource, xslInputSource, theResultTarget);
					endTime = clock();
					
					avgEtoe += endTime - startTime;						
				}
				theAverage = calculateAvgTime(avgEtoe,iterCount);

				// Output average transform time to console and result log
				cout << "   Avg: " << theAverage << " for " << iterCount << " iter's of eToe" << endl;
				logFile.addMetricToAttrs("avgetoe",theAverage, attrs);

				logFile.logElementWAttrs(10, "perf", attrs, "xxx");

				xalan.destroyParsedSource(parsedSource);
				xalan.destroyStylesheet(compiledSS);

			}

			logEntry = "Performance Directory: ";
			logEntry += dirs[j];
 			logFile.logTestCaseClose(logEntry, XalanDOMString("Done"));
		}

		// Check to see if -sub cmd-line directory was processed correctly.
		if (!foundDir)
		{
			cout << "Specified test directory: \"" << c_str(TranscodeToLocalCodePage(h.args.sub)) << "\" not found" << endl;
		}

		h.reportPassFail(logFile, UniqRunid);
		logFile.logTestFileClose("Performance", "Done");
		logFile.close();
	}

	return 0;
}