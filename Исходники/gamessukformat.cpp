  bool GAMESSUKOutputFormat::ReadMolecule(OBBase* pOb, OBConversion* pConv) {

	/*
	 
	Read in coordinates after any reorientation due to the symmetry code
	- if there is a field called "input z-matrix" then we read the initial zmatrix in here
	  This geometry is not needed if we are optimising as we can use the optimised geometry
	  However, we need to keep this geometry as it's the only one we have if it's not an opt.
	  
	- if there is no zmat, we need to read the "molecular geometry" field. This geometry
	  only needs to be used if we are not in an optimisation.
	  
	 Read the RUN TYPE field to work out whether we need to use the first geometry.
	 
	 If it's a single point caculation, we can return the molecule at this point
	 
	 If it's some form of structure search, we need to go and find the final structure

	 */

	OBMol* pmol = dynamic_cast<OBMol*>(pOb);
	if (pmol==NULL)
		return false;

	//Define some references so we can use the old parameter names
	istream& ifs = *pConv->GetInStream();
	OBMol &mol = *pmol;
	
	// Get a default title as the filename
    const char* title = pConv->GetTitle();    
    mol.BeginModify();
    mol.SetTitle(title);
    mol.EndModify();

	vector<string> tokens, geomList; // list of lines and list of tokens on a line
	string line; // For convenience so we can refer to lines from the iterator as 'line'
	//ReadMode_t ReadMode=SKIP;
	
	enum RunType_t { UNKNOWN, SINGLEPOINT, OPTXYZ, OPTZMAT, SADDLE };
	RunType_t RunType=UNKNOWN;
	bool ok;
	
	while (ifs.good() && ifs.getline(buffer, BUFF_SIZE)) {
		
		/* The zmatrix entered by the user
		 * REM:  need to add stuff for "automatic z-matrix generation" as we currently
		 * ignore the zmatrix & just read the cartesian coordinates 
		 */
		
		if (strstr(buffer,"                              input z-matrix") != NULL){
			
			// Set Runtype to SINGLEPOINT so we don't read in the cartesians
			RunType=SINGLEPOINT;
			
			geomList.clear();
			
			// skip 2 lines
			ifs.getline(buffer, BUFF_SIZE) && ifs.getline(buffer, BUFF_SIZE);
			
			// Stick a header line first
			geomList.push_back("zmatrix bohr");
			
			// Read zmatrix into list until blank line 
			while (ifs.good() && ifs.getline(buffer, BUFF_SIZE) && strlen(buffer) != 0){
				line = buffer;
				// transform(method.begin(), method.end(), method.begin(), ::tolower);
				ToLower(line);
				Trim(line);
				geomList.push_back(line);
			}
			
			// Skip 3 lines
			ifs.getline(buffer, BUFF_SIZE) && 
			ifs.getline(buffer, BUFF_SIZE) && 
			ifs.getline(buffer, BUFF_SIZE);
			
			// Read in the variables till we hit blank line
			if (! ReadVariables(ifs, BOHR_TO_ANGSTROM, "")) return false;
			
			// Now go and process the geometry
			ok = ReadGeometry(mol, geomList);
					
		} // End Reading user z-matrix
		
		// Read the cartesian coordinates if we've not read in the ZMATRIX
		if (strstr(buffer,"*            charge       x             y              z       shells") != NULL &&
				RunType==UNKNOWN){
			
			// Skip 3 lines
			ifs.getline(buffer, BUFF_SIZE) && 
			ifs.getline(buffer, BUFF_SIZE) && 
			ifs.getline(buffer, BUFF_SIZE);
			
			// Create regex for the coords
			regex_t *myregex = new regex_t;
			int iok;
			iok = regcomp( myregex,
					//     ------label--------   -------charge-------- < seems enough for a match
					" *\\* *[a-zA-Z]{1,2}[0-9]* *[0-9]{1,3}\\.[0-9]{1}",
					REG_EXTENDED | REG_NOSUB);
			if (iok !=0) cerr << "Error compiling regex in GUK OUTPUT!\n";
			
			// Read in the coordinates - we process them directly rather 
			// then use ReadGeometry as we probably should do...
			mol.BeginModify();
			while (ifs.good() && ifs.getline(buffer, BUFF_SIZE)){
				
				// End of geometry block
				if (strstr(buffer,"*************************")!=NULL)break;
				
				if (regexec( myregex, buffer, 0, 0, 0)==0) {
					//cerr << "Got Coord line: " << buffer << endl;
					OBAtom *atom = mol.NewAtom();
					tokenize(tokens,buffer," ");
					atom->SetAtomicNum(atoi(tokens[2].c_str()));
					double x=atof(tokens[3].c_str())*BOHR_TO_ANGSTROM;
					double y=atof(tokens[4].c_str())*BOHR_TO_ANGSTROM;
					double z=atof(tokens[5].c_str())*BOHR_TO_ANGSTROM;
					atom->SetVector(x, y, z);
				}
			}
			mol.EndModify();			
			regfree(myregex);
			
		} // End Read Cartesian Coords
		
		
		// Determine the RunType - affects how we move on from here.
		if (strstr(buffer," * RUN TYPE") != NULL){
			tokenize(tokens,buffer," \t\n");
			
			if(tokens[3].compare(0,6,"optxyz")==0){
				//cerr << "runtype is optxyz\n";
				RunType=OPTXYZ;
				break;
			} else if (tokens[3].compare(0,8,"optimize")==0){
				//cerr << "runtype is optimise\n";
				RunType=OPTZMAT;
				break;
			} else if (tokens[3].compare(0,6,"saddle")==0){
				//cerr << "runtype is optimise\n";
				RunType=SADDLE;
				break;
			} else {
				RunType=SINGLEPOINT;
				break;
			}
		}
	} // End First Reading loop
	
	
	if(RunType==SINGLEPOINT){
		// We can return the molecule that we've read in
		if (mol.NumAtoms() == 0) { // e.g., if we're at the end of a file PR#1737209
			mol.EndModify();
			return false;
		} else {
			return true;
		}
	}
	
	
	// Clear the Molecule as we're going to start from scratch again.
	mol.BeginModify();
	mol.Clear();
	mol.EndModify();
	
	// Start trundling through the file again - just get the last geometry
	while (ifs.good() && ifs.getline(buffer, BUFF_SIZE)) {
		if (strstr(buffer,"optimization converged") != NULL)
		{	
			if (RunType==OPTXYZ){
				//cerr << "Got converged for OPTXYZ\n";
				
				// FF to start of coordinate specification
				while (ifs.good() && ifs.getline(buffer, BUFF_SIZE)) {
					if (strstr(buffer,
							"atom     znuc       x             y             z") != NULL) break;
				}
				
				// Skip 3 lines - should then be at the coordinates
				ifs.getline(buffer, BUFF_SIZE) && 
				ifs.getline(buffer, BUFF_SIZE) && 
				ifs.getline(buffer, BUFF_SIZE);
				
				// Read in the coordinates - we process them directly rather 
				// then use ReadGeometry as we probably should do...
				mol.BeginModify();
				while (ifs.good() && ifs.getline(buffer, BUFF_SIZE)){
					
					// End of geometry block
					if (strstr(buffer,"*************************")!=NULL)break;
					
					//cerr << "Got Coord line: " << buffer << endl;
					OBAtom *atom = mol.NewAtom();
					tokenize(tokens,buffer," ");
					atom->SetAtomicNum(atoi(tokens[2].c_str()));
					double x=atof(tokens[3].c_str())*BOHR_TO_ANGSTROM;
					double y=atof(tokens[4].c_str())*BOHR_TO_ANGSTROM;
					double z=atof(tokens[5].c_str())*BOHR_TO_ANGSTROM;
					atom->SetVector(x, y, z);
				}
				
				mol.EndModify();
				return true;
				
				
			} else if (RunType==OPTZMAT || RunType==SADDLE) {
				// Original geometry specification should still be in geomList
				// So just update the variables
				//cerr << "Got converged for OPTZMAT\n";				
				
				// FF to variable specification
				while (ifs.good() && ifs.getline(buffer, BUFF_SIZE)) {
					if (strstr(buffer,
							" variable           value                hessian") != NULL) break;
				}
				// Skip a line - should then be at variable specification
				ifs.getline(buffer, BUFF_SIZE);
				
				// Process them
				if (! ReadVariables(ifs, BOHR_TO_ANGSTROM,
						"===============================================")) return false;
				
				// Now go and process with the geometry we read before
				return ReadGeometry(mol, geomList);
				
			}
		}
		
	} // End Second Reading loop		

	return true;

} // End GAMESSUKOutputFormat::ReadMolecule