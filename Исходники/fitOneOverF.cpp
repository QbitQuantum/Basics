/******************************************************************************************
 * Wrapper function based on generic fitOneOverF().
 * It accepts a filename for reference function.
 * Reference function will be used to build ignorePS vector
*******************************************************************************************/
VB_Vector * fitOneOverF(const char *psFile, const char *refFunc, double var3min, double TRin, 
			double sigma, double var1, double var2, double var3, 
			const char * outputFile, bool printFlag)
{
  VB_Vector *psVec = new VB_Vector();
  string psString(psFile);
  if (psVec->ReadFile(psString)) {
    printf("Invalid file format for power spectrum: %s\n", psFile);
    return 0;
  }

  VB_Vector *refLocal = new VB_Vector();
  tokenlist condKey;
  int refStat = getCondVec(refFunc, condKey, refLocal);
  if (refStat == -1) {
    printf("File not readable: %s\n", refFunc);
    return 0;
  }
  else if (refStat == -2) {
    printf("Error: different number of keys in header and content: %s\n", refFunc);
    return 0;
  }
  else if (refStat == 1) {
    printf("Error: different keys in header and content: %s\n", refFunc);
    return 0;
  }
  
  refLocal->meanCenter();
  VB_Vector *psRef = new VB_Vector(refLocal->getLength());
  refLocal->getPS(psRef);

  VB_Vector *ignorePS = new VB_Vector(refLocal->getLength());
  ignorePS->setAll(1.0);
  double refPSmax = psRef->getMaxElement();
  
  for (size_t i = 0; i < ignorePS->getLength(); i++) {
    if (psRef->getElement(i) > refPSmax * 0.01)
      ignorePS->setElement(i, 0);
    else continue;
  }

  return fitOneOverF(psVec, ignorePS, var3min, TRin, sigma, var1, var2, var3, outputFile, printFlag);
}