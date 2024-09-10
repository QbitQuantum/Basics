bool BakeRadiosity::CreateNewMesh (INode *orgNode, 
                                    Mesh *orgMesh, 
                                    Matrix3 orgMtx)
{
   if((orgNode == NULL)||(orgMesh == NULL)){
	   DebugPrint(_T("Mesh error\n"));
      return false;
   }
   // Creates an instance of a registered class.
   Object *newObj = (Object*)(ip->CreateInstance(
                                       GEOMOBJECT_CLASS_ID,
                                       Class_ID(TRIOBJ_CLASS_ID, 0)));
   if(newObj == NULL){
	   DebugPrint(_T("CreateInstance error\n"));
      return false;
   }
   // Creates a new node in the scene with the given object. 
   INode *newNode = ip->CreateObjectNode(newObj);
   if(newNode == NULL){
	   DebugPrint(_T("CreateObjectNode error\n"));
      return false;
   }
   // Sets the name of the node. 
   if(keepOrgFlag != true){
      newNode->SetName(orgNode->GetName());
   } else {
      TSTR newName;
      newName.printf(_T("%s_BAKED"), orgNode->GetName());
      newNode->SetName(newName);
   }
   // Sets the renderer material used by the node.
   newNode->SetMtl(orgNode->GetMtl());
   // Returns a reference to the mesh data member of new TriObject.
   TriObject *newTriObj = (TriObject *)newObj;
   Mesh &newMesh = newTriObj->GetMesh();
   // Returns the number of vertices from original mesh. 
   int nbVert = orgMesh->getNumVerts();
   // Sets the number of geometric vertices in the new mesh.
   newMesh.setNumVerts(nbVert);
   // The loop will continue until handling all vertices...
   for(int i=0; i<nbVert; i++) { 
      newMesh.verts[i] = orgMtx * orgMesh->verts[i];//Set new vertices
   }
   // Returns the number of faces in the original mesh.
   int nbFace = orgMesh->getNumFaces();
   // Sets the number of faces in the new mesh 
   // and previous faces are discarded.
   newMesh.setNumFaces(nbFace, FALSE);
   // The loop will continue until handling all faces...
   for(int i=0; i<nbFace; i++){ // Set new faces and Material id
      newMesh.faces[i] = orgMesh->faces[i];
      newMesh.faces[i].setMatID(orgMesh->faces[i].getMatID());
   }
   // Makes a complete copy of the specified channels 
   // of the original Mesh object into new Mesh.
   newMesh.DeepCopy(orgMesh, CNVERT_CHANNELS);

   return true;
}