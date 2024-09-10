int  main (int     argc,
           char**  argv
          )
{

  ImportFullSizeFromSqlBackUp  mergeFeatureFiles;
  mergeFeatureFiles.InitalizeApplication (argc, argv);
  if  (!mergeFeatureFiles.Abort ())
    mergeFeatureFiles.Main ();

  if  (mergeFeatureFiles.Abort ())
    return 1;
  else
    return 0;
}