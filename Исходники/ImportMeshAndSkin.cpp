bool NifImporter::ImportMultipleGeometry(NiNodeRef parent, vector<NiTriBasedGeomRef>& glist)
{
   bool ok = true;
   if (glist.empty()) return false;

   ImpNode *node = i->CreateNode();
   if(!node) return false;

   INode *inode = node->GetINode();
   TriObject *triObject = CreateNewTriObject();
   node->Reference(triObject);

   string name = parent->GetName();
   node->SetName(wide(name).c_str());

   // Texture
   Mesh& mesh = triObject->GetMesh();

   vector< pair<int, int> > vert_range, tri_range;
   vector<Triangle> tris;
   vector<Vector3> verts;
   int submats = glist.size();

   // Build list of vertices and triangles.  Optional components like normals will be handled later.
   for (vector<NiTriBasedGeomRef>::iterator itr = glist.begin(), end = glist.end(); itr != end; ++itr) {
      NiTriBasedGeomDataRef triGeomData = StaticCast<NiTriBasedGeomData>((*itr)->GetData());

      // Get verts and collapse local transform into them
      int nVertices = triGeomData->GetVertexCount();
      vector<Vector3> subverts = triGeomData->GetVertices();
      Matrix44 transform = (*itr)->GetLocalTransform();
      //Apply the transformations
      if (transform != Matrix44::IDENTITY) {
         for ( unsigned int i = 0; i < subverts.size(); ++i )
            subverts[i] = transform * subverts[i];
      }
      vert_range.push_back( pair<int,int>( verts.size(), verts.size() + subverts.size()) );
      verts.insert(verts.end(), subverts.begin(), subverts.end());

      vector<Triangle> subtris = triGeomData->GetTriangles();
      for (vector<Triangle>::iterator itr = subtris.begin(), end = subtris.end(); itr != end; ++itr) {
         (*itr).v1 += nVertices, (*itr).v2 += nVertices, (*itr).v3 += nVertices;
      }
      tri_range.push_back( pair<int,int>( tris.size(), tris.size() + subtris.size()) );
      tris.insert(tris.end(), subtris.begin(), subtris.end());
   }

   // Transform up-to-parent
   Matrix44 baseTM = (importBones) ? Matrix44::IDENTITY : parent->GetWorldTransform();
   node->SetTransform(0,TOMATRIX3(baseTM));  

   // Set vertices and triangles
   mesh.setNumVerts(verts.size());
   mesh.setNumTVerts(verts.size(), TRUE);
   for (int i=0, n=verts.size(); i < n; ++i){
      Vector3 &v = verts[i];
      mesh.verts[i].Set(v.x, v.y, v.z);
   }
   mesh.setNumFaces(tris.size());
   mesh.setNumTVFaces(tris.size());
   for (int submat=0; submat<submats; ++submat) {
      int t_start = tri_range[submat].first, t_end = tri_range[submat].second;
      for (int i=t_start; i<t_end; ++i) {
         Triangle& t = tris[i];
         Face& f = mesh.faces[i];
         f.setVerts(t.v1, t.v2, t.v3);
         f.Show();
         f.setEdgeVisFlags(EDGE_VIS, EDGE_VIS, EDGE_VIS);
         f.setMatID(-1);
         TVFace& tf = mesh.tvFace[i];
         tf.setTVerts(t.v1, t.v2, t.v3);
      }
   }
   mesh.buildNormals();
   bool bSpecNorms = false;

   MultiMtl *mtl = NULL;
   int igeom = 0;
   for (vector<NiTriBasedGeomRef>::iterator itr = glist.begin(), end = glist.end(); itr != end; ++itr, ++igeom) 
   {
      NiTriBasedGeomDataRef triGeomData = StaticCast<NiTriBasedGeomData>((*itr)->GetData());

      int v_start = vert_range[igeom].first, v_end = vert_range[igeom].second;
      int t_start = tri_range[igeom].first, t_end = tri_range[igeom].second;

      // Normals
      vector<Vector3> subnorms = triGeomData->GetNormals();
      Matrix44 rotation = (*itr)->GetLocalTransform().GetRotation();
      if (rotation != Matrix44::IDENTITY) {
         for ( unsigned int i = 0; i < subnorms.size(); ++i )
            subnorms[i] = rotation * subnorms[i];
      }
      if (!subnorms.empty())
      {
#if VERSION_3DSMAX > ((5000<<16)+(15<<8)+0) // Version 5
         // Initialize normals if necessary
         if (!bSpecNorms) {
            bSpecNorms = true;
            mesh.SpecifyNormals();
            MeshNormalSpec *specNorms = mesh.GetSpecifiedNormals();
            if (NULL != specNorms) {
               specNorms->BuildNormals();
               //specNorms->ClearAndFree();
               //specNorms->SetNumFaces(tris.size());
               //specNorms->SetNumNormals(n.size());
            }
         }
         MeshNormalSpec *specNorms = mesh.GetSpecifiedNormals();
         if (NULL != specNorms)
         {
            Point3* norms = specNorms->GetNormalArray();
            for (int i=0, n=subnorms.size(); i<n; i++){
               Vector3& v = subnorms[i];
               norms[i+v_start] = Point3(v.x, v.y, v.z);
            }
            //MeshNormalFace* pFaces = specNorms->GetFaceArray();
            //for (int i=0; i<tris.size(); i++){
            //   Triangle& tri = tris[i];
            //   MeshNormalFace& face = pFaces[i+t_start];
            //   face.SpecifyNormalID(0, tri.v1);
            //   face.SpecifyNormalID(1, tri.v2);
            //   face.SpecifyNormalID(2, tri.v3);
            //}
#if VERSION_3DSMAX > ((7000<<16)+(15<<8)+0) // Version 7+
			specNorms->SetAllExplicit(true);
#endif
            specNorms->CheckNormals();
         }
#endif
      }
      // uv texture info
      if (triGeomData->GetUVSetCount() > 0) {
         vector<TexCoord> texCoords = triGeomData->GetUVSet(0);
         for (int i=0, n = texCoords.size(); i<n; ++i) {
            TexCoord& texCoord = texCoords[i];
            mesh.tVerts[i+v_start].Set(texCoord.u, (flipUVTextures) ? 1.0f-texCoord.v : texCoord.v, 0);
         }
      }
      vector<Color4> cv = triGeomData->GetColors();
      ImportVertexColor(inode, triObject, tris, cv, v_start);

      if ( StdMat2* submtl = ImportMaterialAndTextures(node, (*itr)) )
      {
         if (mtl == NULL) {
            mtl = NewDefaultMultiMtl();
            gi->GetMaterialLibrary().Add(mtl);
            inode->SetMtl(mtl);
         }
         // SubMatIDs do not have to be contiguous so we just use the offset
         mtl->SetSubMtlAndName(igeom, submtl, submtl->GetName());
         for (int i=t_start; i<t_end; ++i)
            mesh.faces[i].setMatID(igeom);
      }
      if (enableSkinSupport)
         ImportSkin(node, (*itr));
   }

   this->i->AddNodeToScene(node);   

   inode = node->GetINode();
   inode->EvalWorldState(0);

   for (vector<NiTriBasedGeomRef>::iterator itr = glist.begin(), end = glist.end(); itr != end; ++itr) 
   {
      // attach child
      if (INode *parent = GetNode((*itr)->GetParent()))
         parent->AttachChild(inode, 1);
      inode->Hide((*itr)->GetVisibility() ? FALSE : TRUE);
   }
   if (removeDegenerateFaces)
      mesh.RemoveDegenerateFaces();
   if (removeIllegalFaces)
      mesh.RemoveIllegalFaces();
   if (weldVertices)
	   WeldVertices(mesh);
   if (enableAutoSmooth)
      mesh.AutoSmooth(TORAD(autoSmoothAngle), FALSE, FALSE);
   return ok;
}