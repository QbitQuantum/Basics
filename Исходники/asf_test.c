void cu_difftext(char *testFile, char *referenceFile, char *exceptFile)
{
  char line[1024], tLine[1024], rLine[1024];
  int ii, nExcept = 0;

  // Read exceptions
  FILE *fp = FOPEN(exceptFile, "r");
  while(fgets(line, 1024, fp)) {
    chomp(line);
    nExcept++;
  }
  FCLOSE(fp);
  char **exception = (char **) MALLOC(sizeof(char *)*nExcept);
  fp = FOPEN(exceptFile, "r");
  for (ii=0; ii<nExcept; ii++) {
    exception[ii] = (char *) MALLOC(sizeof(char)*1024);
    fgets(exception[ii], 1024, fp);
  }
  FCLOSE(fp);

  // Go through both text files simultaneously
  FILE *fpTest = FOPEN(testFile, "r");
  FILE *fpRef = FOPEN(referenceFile, "r");
  while (fgets(tLine, 1024, fpTest)) {
    fgets(rLine, 1024, fpRef);
    for (ii=0; ii<nExcept; ii++) {
      if (strcmp_case(rLine, exception[ii]) != 0) {
	if (strcmp_case(tLine, rLine) != 0) {
	  asfForcePrintStatus("\ntest: %sreference: %s", tLine, rLine);
	  CU_ASSERT_TRUE(strcmp_case(tLine, rLine) == 0);
	}
      }
    }
  }

  // Clean up
  for (ii=0; ii<nExcept; ii++)
    FREE(exception[ii]);
  FREE(exception);
}