/// TwoPointsCorrelation
unsigned int ICoDF_HTM::HTM::TwoPointsCorrelation(double& radius, double& delta)
{
    unsigned int * nbPair = new unsigned int [this->_pointsToCompute.size()];
 	
	double infLimit = radius - delta;
	if (infLimit < 0) infLimit = 0;
	double supLimit = radius + delta;
    
    for (unsigned int i = 0; i < this->_pointsToCompute.size(); ++i)
    {
        PointInfo_t const * pt = this->_pointsToCompute[i];
        nbPair[i] = 0;
		if (IsCorrectRA(pt->_ra) && IsCorrectDEC(pt->_dec))
		{
			Vector3d p = pt->_position;
			double pNorm = p.norm();
            double pDot = p.dot(Vector3d{1,0,0});
            double phi2 = acos(pDot / pNorm);
            
			std::queue<trixel_t*> workingList;
			for (unsigned int i = 0; i < 4; ++i)
                workingList.push(this->_octahedron->_rootTrixels[i]);
            
			while (workingList.size() > 0)
			{
				trixel_t* tmp = workingList.front();
				workingList.pop();
                
                double dist[3] = {
                    p.dot(tmp->_vertices[0]),
                    p.dot(tmp->_vertices[1]),
                    p.dot(tmp->_vertices[2])
                };
                
                unsigned int infInside = (dist[0] > infLimit) + (dist[1] > infLimit) + (dist[2] > infLimit);
                unsigned int supInside = (dist[0] > supLimit) + (dist[1] > supLimit) + (dist[2] > supLimit);
                
				if (supInside == 3 && infInside == 0)
                    nbPair[i]  += tmp->_nbChildObject;
				else if ((supInside == 3 && infInside > 0)
						 || supInside > 0)
				{
					if (tmp->_children != NULL)
					{
						for (unsigned int i = 0; i < 4; ++i)
							if (tmp->_children[i] != NULL)
								workingList.push(tmp->_children[i]);
					}
					else
                        nbPair[i]  += 1;
				}
				else
				{
                    if (tmp->_phi == 0)
                    {
                        Vector3d tmpVec1 = tmp->_vertices[1] - tmp->_vertices[0];
                        Vector3d tmpVec2 = tmp->_vertices[2] - tmp->_vertices[1];
                        Vector3d tmpVec3 = tmpVec1.cross(tmpVec2);
                        
                        tmp->_trixelBoundary = tmpVec3 / tmpVec3.norm();
                        tmp->_phi = acos(tmp->_trixelBoundary.dot(Vector3d{1,0,0}) / (tmp->_trixelBoundary.norm()));
                        tmp->_cross01 = tmp->_vertices[0].cross(tmp->_vertices[1]);
                        tmp->_cross12 = tmp->_vertices[1].cross(tmp->_vertices[2]);
                        tmp->_cross20 = tmp->_vertices[2].cross(tmp->_vertices[0]);
                    }
                    
                    double theta = tmp->_trixelBoundary.dot(p) / tmp->_trixelBoundary.norm();
					if (acos(theta * pNorm) < tmp->_phi + phi2)
					{
						if (!(tmp->_cross01.dot(p) < 0 &&
							  tmp->_cross12.dot(p) < 0 &&
							  tmp->_cross20.dot(p)))
						{
                            nbPair[i] += 1;
						}
					}
				}
			}
		}
    }
    delete nbPair;
    return std::accumulate(nbPair, nbPair + this->_pointsToCompute.size(), 0);
}