void NifImporter::AlignBiped(IBipMaster* master, NiNodeRef node)
{
#ifdef USE_BIPED
   NiNodeRef parent = node->GetParent();
   string name = node->GetName();
   vector<NiAVObjectRef> children = node->GetChildren();
   vector<NiNodeRef> childNodes = DynamicCast<NiNode>(children);

   TSTR s1 = FormatText("Processing %s:", name.c_str());
   TSTR s2 = FormatText("Processing %s:", name.c_str());
   INode *bone = GetNode(node);
   if (bone != NULL) 
   {
      if (uncontrolledDummies)
         BuildControllerRefList(node, ctrlCount);

      Matrix44 m4 = node->GetWorldTransform();
      Vector3 pos; Matrix33 rot; float scale;
      m4.Decompose(pos, rot, scale);
      Matrix3 m = TOMATRIX3(m4);
      Point3 p = m.GetTrans();
      Quat q(m);

      s1 += FormatText(" ( %s)", PrintMatrix3(m).data());
      if (strmatch(name, master->GetRootName()))
      {
         // Align COM
         //PosRotScaleNode(bone, p, q, 1.0f, prsPos);
         PosRotScaleBiped(master, bone, p, q, 1.0f, prsPos);
      }
      else if (INode *pnode = bone->GetParentNode())
      {
         // Reparent if necessary
         if (!strmatch(parent->GetName(), pnode->GetName())) {
            if (pnode = FindNode(parent)) {
               bone->Detach(0);
               pnode->AttachChild(bone);
            }
         }

         // Hack to scale the object until it fits
         for (int i=0; i<10; ++i) {
            float s = CalcScale(bone, node, childNodes);
            if (fabs(s-1.0f) < (FLT_EPSILON*100.0f))
               break;
            s1 += FormatText(" (%g)", s);
            master->SetBipedScale(TRUE, ScaleValue(Point3(s,s,s)), 0, bone);
         }
         PosRotScale prs = prsDefault;
         PosRotScaleBiped(master, bone, p, q, scale, prs);

         // Rotation with Clavicle is useless in Figure Mode using the standard interface
         //   I was tring unsuccessfully to correct for it
         //if (wildcmpi("Bip?? ? Clavicle", name.c_str())) {
         //   AngAxis a1 = CalcTransform(bone, node, childNodes);
         //   Matrix3 tm1 = GenerateRotMatrix(a1);
         //   Quat nq = TransformQuat(tm1, q);
         //   PosRotScaleNode(bone, p, nq, scale, prsRot);
         //}
      }
      s2 += FormatText(" ( %s)", PrintMatrix3(bone->GetNodeTM(0)).data());
   }
   else
   {
      ImportBones(node, false);
   }
   for (char *p = s1; *p != 0; ++p) if (isspace(*p)) *p = ' ';
   for (char *p = s2; *p != 0; ++p) if (isspace(*p)) *p = ' ';
   OutputDebugString(s1 + "\n");
   OutputDebugString(s2 + "\n");

   for (vector<NiNodeRef>::iterator itr = childNodes.begin(), end = childNodes.end(); itr != end; ++itr){
      AlignBiped(master, *itr);
   }
#endif
}