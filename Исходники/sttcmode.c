void pkg_sttc_writeReadme(struct UPKGOptions_ *o, const char *libName, UErrorCode *status)
{
  char tmp[1024];
  FileStream  *out;

  if(U_FAILURE(*status))
  {
      return;
  }

  /* Makefile pathname */
  uprv_strcpy(tmp, o->targetDir);
  uprv_strcat(tmp, U_FILE_SEP_STRING "README_");
  uprv_strcat(tmp, o->shortName);
  uprv_strcat(tmp, ".txt");

  out = T_FileStream_open(tmp, "w");
  if (!out) {
      fprintf(stderr, "err: couldn't create README file %s\n", tmp);
      *status = U_FILE_ACCESS_ERROR;
      return;
  }

  sprintf(tmp, "## README for \"%s\"'s static data (%s)\n"
               "## created by pkgdata, ICU Version %s\n",
             o->shortName,
             libName,
             U_ICU_VERSION);

  T_FileStream_writeLine(out, tmp);

  sprintf(tmp, "\n\nTo use this data in your application:\n\n"
               "1. At the top of your source file, add the following lines:\n"
               "\n"
               "     #include \"unicode/utypes.h\"\n"
               "     #include \"unicode/udata.h\"\n"
               "     U_CFUNC char %s_dat[];\n",
               o->cShortName);
  T_FileStream_writeLine(out, tmp);

  sprintf(tmp, "2. *Early* in your application, call the following function:\n"
               "\n"
               "     UErrorCode myError = U_ZERO_ERROR;\n"
               "     udata_setAppData( \"%s\", (const void*) %s_dat, &myError);\n"
               "     if(U_FAILURE(myError))\n"
               "     {\n"
               "          handle error condition ...\n"
               "     }\n"
               "\n",
               o->cShortName, o->cShortName);
  T_FileStream_writeLine(out, tmp);

  sprintf(tmp, "3. Link your application against %s\n"
               "\n\n"
               "4. Now, you may access this data with a 'path' of \"%s\" as in the following example:\n"
               "\n"
               "     ... ures_open( \"%s\", \"%s\", &err ); \n",
               libName, o->shortName, o->shortName, uloc_getDefault());
  T_FileStream_writeLine(out, tmp);

  T_FileStream_close(out);
}