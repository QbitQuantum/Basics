void UnwrapMod::ApplyGizmo()
{

	if ((fnGetMapMode() == PLANARMAP) || (fnGetMapMode() == PELTMAP) ||
		(fnGetMapMode() == SPHERICALMAP) || (fnGetMapMode() == CYLINDRICALMAP))
	{
		ApplyGizmoPrivate();
	}
	else
	{
  		theHold.Begin();
		//compute the center
			//get our normal list
		for (int ldID = 0; ldID < mMeshTopoData.Count(); ldID++)
		{
			MeshTopoData *ld = mMeshTopoData[ldID];
			ld->HoldFaceSel();
		}

		for (int ldID = 0; ldID < mMeshTopoData.Count(); ldID++)
		{
			MeshTopoData *ld = mMeshTopoData[ldID];
			ld->HoldFaceSel();

			Tab<Point3> fnorms;
			fnorms.SetCount(ld->GetNumberFaces());
			for (int k=0; k< fnorms.Count(); k++) 
				fnorms[k] = Point3(0.0f,0.0f,0.0f);
				
			//get our projection normal
			Point3 projectionNorm(0.0f,0.0f,0.0f);

			//build normals
			for (int k = 0; k < fnorms.Count(); k++) 
			{
				if (ld->GetFaceSelected(k))
				{
							// Grap the three points, xformed
					int pcount = 3;
					//				if (gfaces[k].flags & FLAG_QUAD) pcount = 4;
					pcount = ld->GetFaceDegree(k);//gfaces[k]->count;

					Point3 temp_point[4];
					for (int j=0; j<pcount; j++) 
					{
						int index = ld->GetFaceGeomVert(k,j);//gfaces[k]->t[j];							
						if (j < 4)
							temp_point[j] = ld->GetGeomVert(index);//gverts.d[index].p;
					}
					
					fnorms[k] = Normalize(temp_point[1]-temp_point[0]^temp_point[2]-temp_point[1]);
				}
			}
				
			BitArray front,back,left,right,top,bottom;
			front.SetSize(ld->GetNumberFaces());
			front.ClearAll();
			back = front;
			left = front;
			right = front;
			top = front;
			bottom = front;

			Tab<Point3> norms;

			Matrix3 gtm(1);
			TimeValue t = 0;
			if (ip) t = ip->GetTime();
			if (tmControl)
				tmControl->GetValue(t,&gtm,FOREVER,CTRL_RELATIVE);

			norms.SetCount(6);
			for (int i = 0; i < 3; i++)
			{
				Point3 v = gtm.GetRow(i);
				norms[i*2] = Normalize(v);
				norms[i*2+1] = norms[i*2] * -1.0f;
			}
				
			for (int k=0; k< ld->GetNumberFaces(); k++) 
			{
				if (ld->GetFaceSelected(k))
				{
					int closestFace = -1;
					float closestAngle = -10.0f;
					for (int j = 0; j < 6; j++)
					{
						float dot = DotProd(norms[j],fnorms[k]);
						if (dot > closestAngle)
						{
							closestAngle = dot;
							closestFace = j;
						}
					}
					if (closestFace == 0)
						front.Set(k,TRUE);
					else if (closestFace == 1)
						back.Set(k,TRUE);
					else if (closestFace == 2)
						left.Set(k,TRUE);
					else if (closestFace == 3)
						right.Set(k,TRUE);
					else if (closestFace == 4)
						top.Set(k,TRUE);
					else if (closestFace == 5)
						bottom.Set(k,TRUE);
				}
			}


			gtm.IdentityMatrix();
			if (tmControl)
				tmControl->GetValue(t,&gtm,FOREVER,CTRL_RELATIVE);

			Point3 xvec,yvec,zvec;
			xvec = gtm.GetRow(0);
			yvec = gtm.GetRow(1);
			zvec = gtm.GetRow(2);
  			Point3 center = gtm.GetRow(3);


			for (int k = 0; k < 6; k++)
			{

				Matrix3 tm(1);
				if (k == 0)
				{
					tm.SetRow(0,yvec);
					tm.SetRow(1,zvec);
					tm.SetRow(2,xvec);
					ld->SetFaceSelection(front);
				}
				else if (k == 1)
				{
					tm.SetRow(0,yvec);
					tm.SetRow(1,zvec);
					tm.SetRow(2,(xvec*-1.0f));

					ld->SetFaceSelection(back);
				}
				else if (k == 2)
				{
					tm.SetRow(0,xvec);
					tm.SetRow(1,zvec);
					tm.SetRow(2,yvec);

					ld->SetFaceSelection(left);
				}
				else if (k == 3)
				{
					tm.SetRow(0,xvec);
					tm.SetRow(1,zvec);
					tm.SetRow(2,(yvec *-1.0f));

					ld->SetFaceSelection(right);
				}
				else if (k == 4)
				{
					tm.SetRow(0,xvec);
					tm.SetRow(1,yvec);
					tm.SetRow(2,zvec);

					ld->SetFaceSelection(top);
				}
				else if (k == 5)
				{
					tm.SetRow(0,xvec);
					tm.SetRow(1,yvec);
					tm.SetRow(2,(zvec*-1.0f));

					ld->SetFaceSelection(bottom);
				}

				

				tm.SetRow(3,center);

				if (!fnGetNormalizeMap())
				{
					for (int i = 0; i < 3; i++)
					{
						Point3 vec = tm.GetRow(i);
						vec = Normalize(vec);
						tm.SetRow(i,vec);
					}
				}

				tm = mMeshTopoData.GetNodeTM(t,ldID) * Inverse(tm);
				ld->ApplyMap(fnGetMapMode(), fnGetNormalizeMap(), tm, this);				
			}
			ld->RestoreFaceSel();
		}

		theHold.Accept(GetString(IDS_PW_PLANARMAP));
		
	}

}