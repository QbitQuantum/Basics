//int main(int argc, char* argv[]) // rTANDEM
// .Call("tandem",RTsexp['param'], RTsexp['peptide'], RTsexp['saps'], RTsexp['mods'], RTsexp['spectrum'])
SEXP tandem(SEXP param, SEXP peptide, SEXP saps, SEXP mods, SEXP spectrum) // rTANDEM
{
	// rTANDEM
	// To make sure the SEXP are ok
//	Rcpp::CharacterVector v_param(param); // rTANDEM
//	Rcpp::CharacterVector v_peptide(peptide); // rTANDEM
//	Rcpp::CharacterVector v_saps(saps); // rTANDEM
//	Rcpp::CharacterVector v_mods(mods); // rTANDEM
//	Rcpp::CharacterVector v_spectrum(spectrum); // rTANDEM
	
//	cout << "param: " << endl; // rTANDEM
//	for (size_t i = 0; i < v_param.size(); i++) { // rTANDEM
//		string toPrint(v_param[i]); // rTANDEM
//		cout << toPrint << endl; // rTANDEM
//	} // rTANDEM
	
//	cout << "peptide: " << endl; // rTANDEM
//	for (size_t i = 0; i < v_peptide.size(); i++) { // rTANDEM
//		string toPrint(v_peptide[i]); // rTANDEM
//		cout << toPrint << endl; // rTANDEM
//	} // rTANDEM
	
//	cout << "saps: " << endl; // rTANDEM
//	for (size_t i = 0; i < v_saps.size(); i++) { // rTANDEM
//		string toPrint(v_saps[i]); // rTANDEM
//		cout << toPrint << endl; // rTANDEM
//	} // rTANDEM
	
//	cout << "mods: " << endl; // rTANDEM
//	for (size_t i = 0; i < v_mods.size(); i++) { // rTANDEM
//		string toPrint(v_mods[i]); // rTANDEM
//		cout << toPrint << endl; // rTANDEM
//	} // rTANDEM
	
//	cout << "spectrum: " << endl; // rTANDEM
//	for (size_t i = 0; i < v_spectrum.size(); i++) { // rTANDEM
//		string toPrint(v_spectrum[i]); // rTANDEM
//		cout << toPrint << endl; // rTANDEM
//	} // rTANDEM
	

	/*
	* Check the argv array for at least one parameter.
	* mprocess checks the validity of the file.
	*/
// rTANDEM : since we don't use argc and argv, usage was disabled
//	if(argc < 2 || argc > 1 && strstr(argv[1],"-L") == argv[1] || argc > 1 && strstr(argv[1],"-h") == argv[1])	{ 
//		cout << "\n\nUSAGE: tandem filename\n\nwhere filename is any valid path to an XML input file.\n\n+-+-+-+-+-+-+\n"; 
// 		cout << "\nX! TANDEM " << VERSION << "\n"; 
//		cout << "\nCopyright (C) 2003-2011 Ronald C Beavis, all rights reserved\n"; 
// 		cout << "This software is a component of the GPM  project.\n"; 
//		cout << "Use of this software governed by the Artistic license.\n"; 
//		cout << "If you do not have this license, you can get a copy at\n"; 
//		cout << "http://www.perl.com/pub/a/language/misc/Artistic.html\n"; 
//		cout << "\n+-+-+-+-+-+-+\n\npress <Enter> to continue ..."; 
//		char *pValue = new char[128]; 
//		cin.getline(pValue,127); 
//		delete pValue; 
//		return -1; 
//	} 
//	cout << "\nX! TANDEM " << VERSION << "\n\n"; 
//
	/*
	* Create an mprocess object array
	*/
	unsigned long lMaxThreads = 16;
	mprocess **pProcess = new mprocess*[lMaxThreads];
	if(pProcess == NULL)	{
//		cout << "An error was detected creating the processing objects.\nPlease contact a GPM administrator.\n";
		Rprintf("An error was detected creating the processing objects.\nPlease contact a GPM administrator.\n");
//		return -2; // rTANDEM
		return R_NilValue; // rTANDEM
	}
#ifdef MSVC
	DWORD *pId = new DWORD[lMaxThreads];
	HANDLE *pHandle = new HANDLE[lMaxThreads];
#else
	int *pId = new int[lMaxThreads];
	int *pHandle = new int[lMaxThreads];
	pthread_t pThreads[lMaxThreads];

#endif
	unsigned long a = 0;
	while(a < lMaxThreads)	{
		pProcess[a] = NULL;
// rTANDEM : There was a warning here during package installation.
//		pHandle[a] = NULL; // rTANDEM
//		pId[a] = NULL; // rTANDEM
		pHandle[a] = 0; // rTANDEM
		pId[a] = 0; // rTANDEM
		a++;
	}
	pProcess[0] = new mprocess;
//	cout << "Loading spectra";
	Rprintf("Loading spectra\n");
	//cout.flush();
	/*
	* Initialize the first mprocess object with the input file name.
	*/
	char *pS = new char[1024];
// rTANDEM: We need to change the code so data is no longer loader from file
//	strcpy(pS,argv[1]); // rTANDEM
//	if(!pProcess[0]->load(pS))	{
	if(!pProcess[0]->load(param, peptide, saps, mods, spectrum));
//		cout << "\n\nAn error was detected while loading the input parameters.\nPlease follow the advice above or contact a GPM administrator to help you."; // rTANDEM
//		delete pProcess[0]; // rTANDEM
//		delete pProcess; // rTANDEM
//		return -4; // rTANDEM
//	} // rTANDEM
//	cout << " loaded.\n";
	Rprintf(" loaded.\n");
	if(pProcess[0]->m_vSpectra.size() == 0)	{
//		cout << "No input spectra met the acceptance criteria.\n";
		Rprintf("No input spectra met the acceptance criteria.\n");
		//cout.flush();
		delete pProcess[0];
		delete pProcess;
//		return 1; // rTANDEM
		return R_NilValue; // rTANDEM
	}
	pProcess[0]->serialize();
//	cout << "Spectra matching criteria = " << (unsigned long)pProcess[0]->m_vSpectra.size() << "\n";
	Rprintf("Spectra matching criteria = %l\n", (unsigned long)pProcess[0]->m_vSpectra.size());
	//cout.flush();
#ifdef PLUGGABLE_SCORING
// 	cout << "Pluggable scoring enabled.\n";
 	Rprintf("Pluggable scoring enabled.\n");
#endif
      /*

        * Start the mprocess object and wait for it to return.

        */
	unsigned long lThread =	pProcess[0]->get_thread();
	unsigned long lThreads = pProcess[0]->get_threads();
	if(lThreads	> lMaxThreads)	{
		lThreads = lMaxThreads;
	}
	if(pProcess[0]->m_vSpectra.size() <	lThreads)	{
		lThreads = (unsigned long)pProcess[0]->m_vSpectra.size();
		if(lThreads	< 1)		{
			lThreads = 1;
		}
		pProcess[0]->set_threads(lThreads);
	}
#ifdef MSVC
	DWORD dCount = lThreads	- 1;
#else
	int	dCount = lThreads -	1;
#endif
	long lSpectra =	lThreads + (long)pProcess[0]->m_vSpectra.size()/lThreads;
	bool bSpectra =	true;
//	cout <<	"Starting threads .";
	Rprintf("Starting threads .");
	//cout.flush();
	if(lThread != 0xFFFFFFFF)		{
		while(dCount > 0)		{
			pProcess[dCount] = new mprocess;
			pProcess[dCount]->set_thread(dCount);						 
			/*

			* initialize the new mprocess objects with	the	spectra	already	loaded into	the	first mprocess

			*/
			pProcess[dCount]->m_vSpectra.reserve(lSpectra);
			dCount--;
		}
		size_t tCount = pProcess[0]->m_vSpectra.size();
		sort(pProcess[0]->m_vSpectra.begin(),pProcess[0]->m_vSpectra.end(),lessThanSpec);

		size_t tProcesses = lThreads;
		size_t tRing = 0;
		vector<mspectrum> vZero;
		vZero.reserve(lSpectra);
		do	{
			if(tRing == 0)	{
				vZero.push_back(pProcess[0]->m_vSpectra.back());
			}
			else	{
				pProcess[tRing]->m_vSpectra.push_back(pProcess[0]->m_vSpectra.back());
			}
			tRing++;
			pProcess[0]->m_vSpectra.pop_back();
			if(tRing == tProcesses)	{
				tRing = 0;

			}
		}	while(pProcess[0]->m_vSpectra.size() != 0);
		pProcess[0]->m_vSpectra.reserve(vZero.size());
		do	{
			pProcess[0]->m_vSpectra.push_back(vZero.back());
			vZero.pop_back();
		}	while(vZero.size() != 0);
		dCount = lThreads - 1;
		while(dCount > 0)		{
			if(!pProcess[dCount]->load(pS,pProcess[0]))	{
//				cout <<	"error pProcess->LoadParameters	returned error (main)\r\n";
				Rprintf("error pProcess->LoadParameters	returned error (main)\r\n");
				delete pProcess;
//				return -4; // rTANDEM
				return R_NilValue; // rTANDEM
			}
			dCount--;
//			cout <<	".";
			Rprintf(".");
			//cout.flush();
		}
	}
	delete pS;
	dCount = 0;
#ifdef MSVC
	pHandle[dCount] = CreateThread(NULL,0,ProcessThread,(void *)pProcess[dCount],0,&pId[dCount]);
#else
	pthread_create(&pThreads[dCount],NULL,ProcessThread,(void*)pProcess[dCount]);
#endif
	dCount++;
	/*
	* Initialize more mprocess objects, if lThread is not 0xFFFFFFFF, which signifies default single
	* threaded operation.
	*/
	if(lThread != 0xFFFFFFFF && bSpectra)	{
		while((unsigned long)(dCount) < lThreads)	{
#ifdef MSVC
			pHandle[dCount] = CreateThread(NULL,0,ProcessThread,(void *)pProcess[dCount],0,&pId[dCount]);
#else
			pthread_create(&pThreads[dCount],NULL,ProcessThread,(void*)pProcess[dCount]);
#endif
			dCount++;
		}
	}
//	cout << " started.\n";
	Rprintf(" started.\n");
	//cout.flush();
//	cout << "Computing models:\n";
	Rprintf("Computing models:\n");
	//cout.flush();
	/*
	* wait until all of the mprocess objects return.
	*/
#ifdef MSVC
//	DWORD wait = WaitForMultipleObjects(dCount,pHandle,true,INFINITE);
	a = 0;
	DWORD dwTime = 100000;
	DWORD wait = WAIT_TIMEOUT;
	int iTics = 0;
	while(a < (unsigned long)(dCount))	{
		wait = WaitForSingleObject(pHandle[a],100);
		if(a > 0 && wait == WAIT_TIMEOUT)	{
			if(a == 1)	{
//				cout << "waiting for " << a+1;
				Rprintf("waiting for %i", a+1);
			}
			else	{
//				cout << a+1;
				Rprintf("%i",a+1);
			}
			while(wait == WAIT_TIMEOUT)	{
				wait = WaitForSingleObject(pHandle[a],dwTime);
				if(wait == WAIT_TIMEOUT)	{
//					cout << ".";
					Rprintf(".");
					//cout.flush();
					iTics++;
					if(iTics > 50)	{
//						cout << "|\n\t\t";
						Rprintf("|\n\t\t");
						//cout.flush();
						iTics = 0;
					}
				}
			}
		}
		else	{
			while(wait == WAIT_TIMEOUT)	{
				wait = WaitForSingleObject(pHandle[a],dwTime);
				if(wait == WAIT_TIMEOUT)	{
//					cout << ":";
					Rprintf(":");
					//cout.flush();
				}
			}
			if(a == 1)	{
//				cout << "waiting for " << a+1;
				Rprintf("waiting for %i", a+1);
			}
			else if(a == 0)	{
//				cout << "\n\t";
				Rprintf("\n\t");
				//cout.flush();
			}
			else	{
//				cout << a+1;
				Rprintf("%i", a+1);
			}
		}
		a++;
	}
	if(dCount > 1)	{
//			cout << " done.\n\n";
			Rprintf(" done.\n\n");
			//cout.flush();
	}
	else	{
//		cout << "\n";
		Rprintf("\n");
		//cout.flush();
	}
#else
	//2003-03-01:note - the declaration below was changed from void **vp;	
	void *vp;
	int x=0;
	int wait;
	for(x=0;x<dCount;x++){
		//2003-03-01:note - the 2nd parameter in the call to pthread_join() was changed from vp
		wait = pthread_join(pThreads[x],&vp);
	}
#endif
//	cout << "\tsequences modelled = "<< (long)(pProcess[0]->get_protein_count()/1000.0 + 0.5) << " ks\n";
	Rprintf("\tsequences modelled = %l ks\n", (long)(pProcess[0]->get_protein_count()/1000.0 + 0.5));
	//cout.flush();
	pProcess[0]->merge_spectra();
	a = 1;
	/*
	* merge the results into the first object
	*/
	while(a < (unsigned long)(dCount))	{
		pProcess[0]->merge_map(pProcess[a]->m_mapSequences);
		pProcess[0]->merge_spectra(pProcess[a]->m_vSpectra);
		a++;
	}
	a = 1;
	pProcess[0]->load_sequences();
	while(a < (unsigned long)(dCount))	{
		pProcess[a]->merge_map(pProcess[0]->m_mapSequences);
		pProcess[a]->m_vseqBest = pProcess[0]->m_vseqBest;
		a++;
	}

	/*
	* Report the contents of the mprocess objects into an XML file as described
	* in the input file.
	*/
//	cout << "Model refinement:\n";
	Rprintf("Model refinement:\n");
	//cout.flush();
	dCount = 0;
#ifdef MSVC
	pHandle[dCount] = CreateThread(NULL,0,RefineThread,(void *)pProcess[dCount],0,&pId[dCount]);
#else
	pthread_create(&pThreads[dCount],NULL,RefineThread,(void*)pProcess[dCount]);
#endif
	dCount++;
	/*
	* Initialize more mprocess objects, if lThread is not 0xFFFFFFFF, which signifies default single
	* threaded operation.
	*/
	if(lThread != 0xFFFFFFFF)	{
		while((unsigned long)(dCount) < lThreads)	{
#ifdef MSVC
			pHandle[dCount] = CreateThread(NULL,0,RefineThread,(void *)pProcess[dCount],0,&pId[dCount]);
#else
			pthread_create(&pThreads[dCount],NULL,RefineThread,(void*)pProcess[dCount]);
#endif
			dCount++;
		}
	}
	/*
	* wait until all of the mprocess objects return.
	*/
#ifdef MSVC
//	wait = WaitForMultipleObjects(dCount,pHandle,true,INFINITE);
	a = 0;
	iTics = 0;
	while(a < (unsigned long)(dCount))	{
		wait = WaitForSingleObject(pHandle[a],10000);
		if(a > 0 && wait == WAIT_TIMEOUT)	{
			if(a == 1)	{
//				cout << "waiting for " << a+1;
				Rprintf("waiting for %i", a+1);
			}
			else	{
//				cout << a+1;
				Rprintf("%i", a+1);
			}
			//cout.flush();
			while(wait == WAIT_TIMEOUT)	{
				wait = WaitForSingleObject(pHandle[a],dwTime);
				if(wait == WAIT_TIMEOUT)	{
//					cout << ".";
					Rprintf(".");
					//cout.flush();
					iTics++;
					if(iTics > 50)	{
//						cout << "|\n\t\t";
						Rprintf("|\n\t\t");
						//cout.flush();
						iTics = 0;
					}
				}
			}
		}
		else	{
			while(wait == WAIT_TIMEOUT)	{
				wait = WaitForSingleObject(pHandle[a],dwTime);
				if(wait == WAIT_TIMEOUT)	{
//					cout << ":";
					Rprintf(":");
					//cout.flush();
				}
			}
			if(a == 1)	{
//				cout << "waiting for " << a+1;
				Rprintf("waiting for %i", a+1);
			}
			else if(a == 0)	{
//				cout << "\n\t";
				Rprintf("\n\t");
				//cout.flush();
			}
			else	{
//				cout << a+1;
				Rprintf("%i", a+1);
			}
		}
		a++;
	}
	if(dCount > 1)	{
//		cout << " done.\n\n";
		Rprintf(" done.\n\n");
		//cout.flush();
	}
	else	{
//		cout << "\n";
		Rprintf("\n");
		//cout.flush();
	}
#else
	//2003-03-01:note - the declaration below was changed from void **vp;	
	x=0;
	for(x=0;x<dCount;x++){
		//2003-03-01:note - the 2nd parameter in the call to pthread_join() was changed from vp
		wait = pthread_join(pThreads[x],&vp);
	}
#endif
	a = 1;
	/*
	* merge the results into the first object
	*/
	if(dCount > 1)	{
//		cout << "Merging results:\n";
		Rprintf("Merging results:\n");
		//cout.flush();
	}
	while(a < (unsigned long)(dCount))	{
		if(a == 1)	{
//			cout << "\tfrom " << a+1;
			Rprintf("\tfrom %i", a+1);
		}
		else	{
//			cout << a+1;
			Rprintf("%i", a+1);
		}
		//cout.flush();
		if(!pProcess[0]->add_spectra(pProcess[a]->m_vSpectra))	{
//			cout << "adding spectra failed.\n";
			Rprintf("adding spectra failed.\n");
		}
		pProcess[0]->merge_statistics(pProcess[a]);
		pProcess[a]->clear();
		pProcess[a]->m_mapSequences.clear();
		a++;
	}
	if(dCount > 1)	{
//		cout << "\n\n";
		Rprintf("\n\n");
		//cout.flush();
	}
	//cout.flush();
//	cout << "Creating report:\n";
	Rprintf("Creating report:\n");
	//cout.flush();
	pProcess[0]->report();
	Rcpp::CharacterVector pathName(pProcess[0]->getPathName()); // rTANDEM
	size_t tValid = pProcess[0]->get_valid();
	size_t tUnique = pProcess[0]->get_unique();
	double dE = pProcess[0]->get_error_estimate();
	unsigned long lE = (unsigned long)(0.5+dE);
	unsigned long lEe = (unsigned long)(0.5 + sqrt(dE));
	if(lEe == 0)	{
		lEe = 1;
	}
	if(dE <= 0.0)	{
		dE = 1.0;
	}
//	cout << "\nValid models = " << (unsigned long)tValid << "\n";
	Rprintf("\nValid models = %l\n", (unsigned long)tValid);
	if(tUnique > 0)	{
//		cout << "Unique models = " << (unsigned long)tUnique << "\n";
		Rprintf("Unique models = %l\n", (unsigned long)tUnique);
//		cout << "Estimated false positives = " << lE << " &#177; ";
		Rprintf("Estimated false positives = %l &#177; ", lE);
//		cout << lEe << "\n";
		Rprintf("%l\n", lEe);
	}
//	lE = pProcess[0]->get_reversed();
	long checkGetReversed = pProcess[0]->get_reversed();
	if(lE != -1)	{
		lE = (unsigned long)(pProcess[0]->get_reversed());
//		cout << "False positive rate (reversed sequences) = " << lE << "\n";
		Rprintf("False positive rate (reversed sequences) = %l\n", lE);
	}
//	cout << "\n\n";
	Rprintf("\n\n");
	/*
	* Delete the mprocess objects and exit
	*/
	a = 0;
	while(a < 16)	{
		if(pProcess[a] != NULL)	{
#ifdef MSVC
			CloseHandle(pHandle[a]);
#endif
			delete pProcess[a];
		}
		a++;
	}
	delete pProcess;
	delete pId;
	delete pHandle;
//	return 0; // rTANDEM
//	return R_NilValue; // rTANDEM
	return pathName;
}