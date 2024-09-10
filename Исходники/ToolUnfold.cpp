Point3*	UnwrapMod::fnGetNormal(int faceIndex)
	{
	//check for type
	ModContextList mcList;		
	INodeTab nodes;
	
	Point3 norm(0.0f,0.0f,0.0f);

	n = norm;
	if (!ip) return &n;
	ip->GetModContexts(mcList,nodes);

	int objects = mcList.Count();

	

	faceIndex--;


	if (objects != 0)
		{
		MeshTopoData *md = (MeshTopoData*)mcList[0]->localData;

		if (md == NULL) 
			{
			return NULL;
			}


		Tab<Point3> objNormList;
		BuildNormals(md,objNormList);
		if ((faceIndex >= 0) && (faceIndex < objNormList.Count()))
			norm = objNormList[faceIndex];
		else
			{
			faceIndex = 0;
			int ct = 1;
			for (int i =0; i < md->faceSel.GetSize(); i++)
				{
				if (md->faceSel[i])
					{
					faceIndex = i;
					norm = objNormList[faceIndex];
					TSTR normstr;
					normstr.printf("norm%d = Point3 %f %f %f",ct,norm.x,norm.y,norm.z);
					ct++;
					macroRecorder->ScriptString(normstr);
					macroRecorder->EmitScript();
					}
				}
			}
		}
	n = norm;
	return &n;
	}