// Core Function doing the actual mesh processing.
bool RangeMapPlugin::applyFilter(QAction *filter, MeshDocument &m, FilterParameterSet & par, vcg::CallBackPos *cb)
{
	CMeshO::FaceIterator   fi;

	switch(ID(filter))
  {
		case FP_SELECTBYANGLE : 
		{
			bool usecam = par.getBool("usecamera");
			Point3f viewpoint = par.getPoint3f("viewpoint");	

			// if usecamera but mesh does not have one
			if( usecam && !m.mm()->hasDataMask(MeshModel::MM_CAMERA) ) 
			{
				errorMessage = "Mesh has not a camera that can be used to compute view direction. Please set a view direction."; // text
				return false;
			}
			if(usecam)
			{
				viewpoint = m.mm()->cm.shot.GetViewPoint();
			}

			// angle threshold in radians
			float limit = cos( math::ToRad(par.getDynamicFloat("anglelimit")) );
			Point3f viewray;

			for(fi=m.mm()->cm.face.begin();fi!=m.mm()->cm.face.end();++fi)
				if(!(*fi).IsD())
				{
					viewray = viewpoint - Barycenter(*fi);
					viewray.Normalize();

					if((viewray.dot((*fi).N().Normalize())) < limit)
						fi->SetS();
				}

		}
		break;

	}

	return true;
}