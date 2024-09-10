int SphereObjCreateCallBack::proc(ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat ) 
{
   float r;
   Point3 p1,center;

   if (msg == MOUSE_FREEMOVE)
   {
      vpt->SnapPreview(m,m,NULL, SNAP_IN_3D);
   }

   if (msg==MOUSE_POINT||msg==MOUSE_MOVE) 
   {
      switch(point) 
      {
      case 0:  // only happens with MOUSE_POINT msg
         // Find the node and plug in the wire color
         {
            ULONG handle;
            ob->NotifyDependents(FOREVER, (PartID)&handle, REFMSG_GET_NODE_HANDLE);
            INode *node = GetCOREInterface()->GetINodeByHandle(handle);
            if (node) node->SetWireColor(RGB(255, 0, 0));
         }
         ob->pblock2->SetValue(PB_RADIUS,0,0.0f);
         ob->suspendSnap = TRUE;				
         sp0 = m;
         p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_3D);
         mat.SetTrans(p0);
         break;
      case 1:
         mat.IdentityMatrix();
         //mat.PreRotateZ(HALFPI);
         p1 = vpt->SnapPoint(m,m,NULL,SNAP_IN_3D);
         r = Length(p1-p0) / 7.0f;
         mat.SetTrans(p0);

         ob->pblock2->SetValue(PB_RADIUS,0,r);
         ob->pmapParam->Invalidate();

         if (flags&MOUSE_CTRL) 
         {
            float ang = (float)atan2(p1.y-p0.y,p1.x-p0.x);					
            mat.PreRotateZ(ob->ip->SnapAngle(ang));
         }

         if (msg==MOUSE_POINT) 
         {
            ob->suspendSnap = FALSE;
            return (Length(m-sp0)<3 || Length(p1-p0)<0.1f)?CREATE_ABORT:CREATE_STOP;
         }
         break;					   
      }
   }
   else
      if (msg == MOUSE_ABORT) 
      {		
         return CREATE_ABORT;
      }

      return TRUE;
}