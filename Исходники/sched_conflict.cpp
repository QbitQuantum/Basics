void runConflictRefinerWithPreferences(IloCP cp, 
                                       IloConstraintArray preferredCts, 
                                       IloConstraintArray otherCts) {
  IloEnv env = cp.getEnv();
  IloConstraintArray cts(env);  
  IloNumArray prefs(env);
  IloInt i;
  for (i=0; i<otherCts.getSize(); ++i) {
    cts.add(otherCts[i]);
    prefs.add(1.0); // Normal preference
  }
  for (i=0; i<preferredCts.getSize(); ++i) {
    cts.add(preferredCts[i]);
    prefs.add(2.0); // Higher preference
  }
  if (cp.refineConflict(cts, prefs)) {
    cp.writeConflict(cp.out());
  } 
  cts.end();
  prefs.end();
}