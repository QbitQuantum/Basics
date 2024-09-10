 int MMFFOptimizeMolecule(ROMol &mol, std::string mmffVariant = "MMFF94",
   int maxIters = 200, double nonBondedThresh = 100.0, int confId = -1,
   bool ignoreInterfragInteractions = true)
 {
   int res = -1;
   
   MMFF::MMFFMolProperties mmffMolProperties(mol, mmffVariant);
   if (mmffMolProperties.isValid()) {
     ForceFields::ForceField *ff = MMFF::constructForceField(mol,
       &mmffMolProperties, nonBondedThresh, confId, ignoreInterfragInteractions);
     ff->initialize();
     res = ff->minimize(maxIters);
     delete ff;
   }
   
   return res;
 }