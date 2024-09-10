int main() {
	writePdbFile();

	System sys;
	sys.readPdb("/tmp/xtalLattice.pdb");

	PolymerSequence pseq(sys);

	System outSys;
	string topfile = SYSENV.getEnv("MSL_CHARMM_TOP");
	string parfile = SYSENV.getEnv("MSL_CHARMM_PAR");
	CharmmSystemBuilder CSB(outSys,topfile,parfile);

	CSB.setBuildNonBondedInteractions(false); // Don't build non-bonded terms.
	CSB.buildSystem(pseq);  // this builds atoms with emtpy coordinates. It also build bonds,angles and dihedral energy terms in the energyset (energyset lives inside system).

	int numAssignedAtoms = outSys.assignCoordinates(sys.getAtomPointers(),false);
	fprintf(stdout,"Number of assigned atoms: %d",numAssignedAtoms);

	// Build the all atoms without coordinates (not in initial PDB)
	outSys.buildAllAtoms();

	outSys.writePdb("/tmp/preEA.pdb");
	EnergeticAnalysis ea;

	cout << "Analyze "<<outSys.getResidue(15).toString()<<endl;
	ea.analyzePosition(outSys, 15);
}