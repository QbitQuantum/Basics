/*!
  Tries to load the shape primitives file for the grasped object.  It uses
  the same file name as the current object, but looks in the primitives folder
  within the objects directory. If the primitives are not found, it uses
  the original geometry of the object, the \a IVGeomRoot.  
*/
void
grasp_manager::loadPrimitives()
{
 
  SoInput myInput;
  char prDir[256];
  QString directory = QString(getenv("GRASPIT"))+
    QString("/models/objects/primitives/");
  QString filename = my_body->getFilename().section('/',-1);
  //make sure the extension is iv, as this is how primitives
  //are stored for now
  filename = filename.section('.',-2,-2) + ".iv";
  QString path = directory + filename;

  printf("Loading primitive %s.\n",path.latin1());

  if (!(myInput.openFile(path.latin1()))) {
    pr_error("could not open primitives file!");
    primitives = my_body->getIVGeomRoot();
    printf ("%s\n",prDir);
    printf("Setting primitive root node to original object.\n");
  }
  else {
      primitives = SoDB::readAll(&myInput);
	  myInput.closeFile();
      if (primitives == NULL) {
	  printf("Load Primitive didnt work, although file seems to exist.\n");
	  printf("Setting primitive root node to original object.\n");
	  primitives = my_body->getIVGeomRoot();
      }
      else {
	primitives->ref();
      }
  }

}