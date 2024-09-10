int
main(int argc, char ** argv)
{
  fprintf(stderr, "ivcp v0.1\n");

  SoDB::init();
  SoNodeKit::init();
  SoInteraction::init();

  if (argc != 3 ) {
    fprintf(stdout, "Usage: %s infile outfile\n", argv[0]);
    return 0;
  }

  SoInput * in = new SoInput;
  if (!in->openFile(argv[1])) {
    fprintf(stderr, "error: could not open file '%s'\n", argv[1]);
    delete in;
    SoDB::cleanup();
    return -1;
  }

  SoNode * scene = SoDB::readAll(in);

  if (!scene) {
    fprintf(stderr, "error: could not read file '%s'\n", argv[1]);
    delete in;
    SoDB::cleanup();
    return -1;
  }
  FileType inputFileType;
  if (in->isFileVRML1())
    inputFileType = VRML1;
  else if (in->isFileVRML2())
    inputFileType = VRML2;
  else
    inputFileType = INVENTOR;

  delete in;
  scene->ref();

  SoNode * firstChild = static_cast<SoSeparator*>(scene)->getNumChildren()?
    static_cast<SoSeparator*>(scene)->getChild(0)
    :NULL;

  if (firstChild && firstChild->isOfType(SoForeignFileKit::getClassTypeId())) {
    SoForeignFileKit * kit = (SoForeignFileKit *) firstChild;
    if (kit->canWriteScene() ) {
      SoNode * subscene = NULL;
      kit->writeScene(subscene);
      if (!subscene ) {
        return -1;
      }
      subscene->ref();
      scene->unref();
      scene = subscene;
    }
  }

  SoOutput * out = new SoOutput;
  if (!out->openFile(argv[2])) {
    fprintf(stderr, "error: could not open file '%s' for writing\n");
    scene->unref();
    delete out;
    SoDB::cleanup();
    return -1;
  }
  switch (inputFileType) {
  case VRML1:
    out->setHeaderString("#VRML V1.0 ascii");
    break;
  case VRML2:
    out->setHeaderString("#VRML V2.0 utf8");
  }

  SoWriteAction wa(out);
  wa.apply(scene);

  out->closeFile();
  delete out;

  scene->unref();

  // with actions on the stack, cleanup can't be called...
  // SoDB::cleanup();
  return 0;
}