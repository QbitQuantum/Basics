// Function reads in the spectra from the data stored for each PSMClass object
void PepXMLClass::readInSpectra() {
	string curSpectrumFilePath;

	deque<PSMClass>::iterator curPSM;
        SpecStruct *spec = NULL;
        bool status;
        string spectrumFileName;
        int scanNum;
        int ctr = 0;
        int N = (signed) PSMvec->size();
        
        if(g_ext == "mgf") {
            parseMGF();
            return;
        }
        
        // mstoolkit to read MS2 spectra
        MSReader *reader = new MSReader();
        reader->setFilter(MS2);

       // mstoolkit spectrum object
       Spectrum *S = NULL;

	// Extract from each PSM, it's parent spectrum file and scan number
	for(curPSM = PSMvec->begin(); curPSM != PSMvec->end(); curPSM++) {
            spectrumFileName = curPSM->getSpectrumFileName();
            scanNum = curPSM->getScanNumber();
            
            
            // code to get the full path to the input spectrum file
            filesystem::path curFile( spectrumFileName.c_str() );
            filesystem::path spectral_dir( g_srcDir.c_str() );
            filesystem::path curFilePath( spectral_dir/curFile );
            curSpectrumFilePath = curFilePath.file_string();

            // if the source file is not located, drop the spectrum
            if( !boost::filesystem::exists(curSpectrumFilePath) ) {
                curPSM = PSMvec->erase(curPSM);
                continue;
            }
            
            
            // Read the spectrum for 'scanNum' into 'S'
            S = new Spectrum();
            status = reader->readFile(curSpectrumFilePath.c_str(), *S, scanNum);
            if(S->getScanNumber() == 0) {
                cerr << "Failed to get " << curSpectrumFilePath.c_str() << " scan#: " << scanNum << endl;
                exit(0);
            }
            
            spec = new SpecStruct();
            for(int j = 0; j < S->size(); j++) {
                spec->mz.push_back( S->at(j).mz );
                spec->intensity.push_back( S->at(j).intensity );
            }
            delete(S); S = NULL;
            
            // Assign the data in 'S' to curPSM
            curPSM->recordSpectrum(*spec);
            delete(spec); spec = NULL;
            ctr++;
            
            printProgress("Reading in spectra (please be patient)...", ctr, N);
	}
       delete(reader); reader = NULL;
       cerr << endl; // prettier stderr
}