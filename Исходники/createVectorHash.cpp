int main(int argc, char *argv[]) {


	// Parse commandline options
	Options opt = setupOptions(argc,argv);

	cout << "READ LIST"<<endl;
	vector<string> pdbs;  
	ifstream fs;

	fs.open(opt.list.c_str());
	if (fs.fail()){
		cerr<<"Cannot open file "<<opt.list<<endl;
		exit(1);
	}

	while(true){
		string line;
		getline(fs, line);

		if(fs.fail()){
			//no more lines to read, quite the while.
			break;
		}

		if(line==""){
			continue;
		}
		pdbs.push_back(line);
	}

	fs.close();


	// Read a list of PDBs into a single atom vector.
	Timer t;
	VectorHashing testHash;
	MSLOUT.turnOff("VectorHashing");
	for (uint i = 0; i < pdbs.size();i++){

	  double startHashTime = t.getWallTime();
	  System testSys;
	  //testSys.readPdb("/Users/dwkulp/work/DandD/test_section.pdb");
	  //testSys.readPdb("/Users/dwkulp/work/VaccineDesign_PGT128/tertFragSearch/pgt128_noGlycans.pdb");
	  testSys.readPdb(pdbs[i]);


	  MSLOUT.stream() << "Build VectorHash from PDB: "<<pdbs[i]<<"\n";
	  testHash.addToVectorHash(testSys,pdbs[i]);
	  MSLOUT.stream() << "done building hash\n";
	  double endTimeHash = t.getWallTime();
	  MSLOUT.fprintf(stdout,"Time %8.3f for building hash with test system\n",(endTimeHash - startHashTime));

	}


	testHash.save_checkpoint(opt.outfile);
}