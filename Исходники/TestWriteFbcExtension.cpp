END_TEST

START_TEST(test_FbcExtension_convert_and_write)
{
  string file(TestDataDirectory);
  file += "/fbc_ga_example.xml";

  SBMLDocument* document = readSBMLFromFile(file.c_str());
  document->printErrors();
  fail_unless(document->getNumErrors(LIBSBML_SEV_ERROR) == 0);
  fail_unless(document->getModel() != NULL);

  // convert to v2
  {
    ConversionProperties props;
    props.addOption("convert fbc v1 to fbc v2", true);
    props.addOption("strict", true);

    int result = document->convert(props);

    // ensure that all is well with the model
    fail_unless(result == LIBSBML_OPERATION_SUCCESS);
    fail_unless(document->getLevel() == 3);
    fail_unless(document->getVersion() == 1);
    fail_unless(document->getPlugin("fbc") != NULL);
    fail_unless(document->getPlugin("fbc")->getPackageVersion() == 2);
  }

  // ensure that all the v1 stuff is no longer there
  FbcModelPlugin* mplug = dynamic_cast<FbcModelPlugin*>(
    document->getModel()->getPlugin("fbc"));

  fail_unless(mplug != NULL);

  fail_unless(mplug->isSetStrict());
  fail_unless(mplug->getNumGeneAssociations() == 0);
  fail_unless(mplug->getNumFluxBounds() == 0);


  delete document;
}