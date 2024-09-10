void
NetworkObject::predrawEdges(QGLViewer *viewer,
			    double *Xform,
			    Vec pn,
			    QList<Vec> clipPos,
			    QList<Vec> clipNormal,
			    QList<CropObject> crops)
{
  Vec bmin, bmax;
  Global::bounds(bmin, bmax);

  m_Eovertices.resize(2*m_edgeNeighbours.count());
  m_Eocolor.resize(m_edgeNeighbours.count());

  QVector<float> rad;
  rad.resize(m_edgeNeighbours.count());

  int stopsCount = m_resampledEstops.count()-1;
  float aint = (m_userEminmax[m_Eatt].second-m_userEminmax[m_Eatt].first);
  if (aint <= 0.0001) aint = 1;

  int nv = 0;
  for(int i=0; i<m_edgeNeighbours.count(); i++)
    {
      bool ok = true;

      if (m_edgeAttribute[m_Eatt].second[i] < m_userEminmax[m_Eatt].first ||
	  m_edgeAttribute[m_Eatt].second[i] > m_userEminmax[m_Eatt].second)
	ok = false;

      if (ok)
	{
	  int a = m_edgeNeighbours[i].first;
	  int b = m_edgeNeighbours[i].second;

	  Vec pa = m_vertexCenters[a];
	  Vec pb = m_vertexCenters[b];

	  for(int c=0; c<clipPos.count(); c++)
	    {
	      if ((pa-clipPos[c])*clipNormal[c] > 0 ||
		  (pb-clipPos[c])*clipNormal[c] > 0)
		{
		  ok = false;
		  break;
		}
	    }

	  if (ok)
	    {
	      for(int ci=0; ci<crops.count(); ci++)
		{
		  ok &= crops[ci].checkCropped(pa);
		  if (!ok) break;
		  ok &= crops[ci].checkCropped(pb);
		  if (!ok) break;
		}
	    }

	  if (ok)
	    {
	      pa = Matrix::xformVec(Xform, pa);
	      pb = Matrix::xformVec(Xform, pb);
	      
	      if (m_vertexCenters[a].x >= bmin.x &&
		  m_vertexCenters[a].y >= bmin.y &&
		  m_vertexCenters[a].z >= bmin.z &&
		  m_vertexCenters[a].x <= bmax.x &&
		  m_vertexCenters[a].y <= bmax.y &&
		  m_vertexCenters[a].z <= bmax.z &&
		  m_vertexCenters[b].x >= bmin.x &&
		  m_vertexCenters[b].y >= bmin.y &&
		  m_vertexCenters[b].z >= bmin.z &&
		  m_vertexCenters[b].x <= bmax.x &&
		  m_vertexCenters[b].y <= bmax.y &&
		  m_vertexCenters[b].z <= bmax.z)
		{
		  if (m_Vopacity > 0.5)
		    {
		      Vec p = pb-pa;
		      p.normalize();
		      pa = pa + p*m_vertexAttribute[m_vertexRadiusAttribute].second[a];
		      pb = pb - p*m_vertexAttribute[m_vertexRadiusAttribute].second[b];
		    }
		  
		  m_Eovertices[2*nv] = pa;
		  m_Eovertices[2*nv+1] = pb;		  
		  
		  //rad[nv] = m_edgeAttribute[m_edgeRadiusAttribute].second[i];
		  rad[nv] = m_scaleE * m_edgeAttribute[m_edgeRadiusAttribute].second[i];

		  float stp = (m_edgeAttribute[m_Eatt].second[i] -
			     m_userEminmax[m_Eatt].first) / aint;
		  QColor col = m_resampledEstops[stp*stopsCount].second;
		  float r = col.red()/255.0;
		  float g = col.green()/255.0;
		  float b = col.blue()/255.0;
		  m_Eocolor[nv] = Vec(r,g,b);

		  nv ++;
		}
	    }
	}
    }
  m_Eovertices.resize(2*(nv+1));  

  m_EtexValues.resize(m_Eovertices.count());
  for(int i=0; i<m_Eovertices.count(); i++)
    m_EtexValues[i] = pn*m_Eovertices[i];


  Vec p = pn^viewer->camera()->upVector();
  Vec q = pn^p;
  p.normalize();
  q.normalize();

  m_Evertices.resize(2*m_Eovertices.count());
  for(int i=0; i<m_Eovertices.count()/2; i++)
    {
      Vec pa = m_Eovertices[2*i];
      Vec pb = m_Eovertices[2*i+1];
      Vec p = pn^(pa-pb);
      p.normalize();

      p *= rad[i];

      m_Evertices[4*i+0] = pa-p;
      m_Evertices[4*i+1] = pb-p;
      m_Evertices[4*i+2] = pb+p;
      m_Evertices[4*i+3] = pa+p;
    }
  
}