OSUInventorScene::OSUInventorScene(char *filename) {

   SoSeparator *root = ReadScene(filename);
   int numNodes = 0;

   SoCallbackAction ca;
   SoSearchAction SA;
   SA.setType(SoLight::getClassTypeId(), TRUE);
   SA.setInterest(SoSearchAction::ALL);
   SA.apply(root);
   SoPathList &paths = SA.getPaths();
#ifdef DEBUG
   cerr << "There are " << paths.getLength() << " lights " << endl;
#endif
   int i;
   for (i = 0; i < paths.getLength(); i++) {
       Lights.append(paths[i]->getTail()->copy());
   }

   SA.setType(SoCamera::getClassTypeId(), TRUE);
   SA.setInterest(SoSearchAction::FIRST);
   SA.apply(root);
   if (SA.getPath()) {
       Camera = (SoCamera *)SA.getPath()->getTail()->copy();
#ifdef DEBUG
       cerr << "Found a camera!\n";
#endif
   } else
       Camera = NULL;

   ca.addPreCallback(SoNode::getClassTypeId(), processNodesCB, (void *)
       &Objects);
   ca.apply(root);
   // Now lets find the lights and camera!
   //

#ifdef DEBUG
   cerr << "There are " << Objects.getLength() << " shape objects left!\n";
#endif
}