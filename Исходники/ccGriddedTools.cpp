bool ccGriddedTools::ComputeNormals(ccPointCloud* cloud,
									const std::vector<int>& indexGrid,
									int width,
									int height,
									bool* canceledByUser/*=0*/,
									int kernelWidth/*=3*/ )
{
	//init
	bool result = true;
	if (canceledByUser)
		*canceledByUser = false;

	//try to compute normals
	if (cloud->reserveTheNormsTable())
	{
		//progress dialog
		ccProgressDialog pdlg(true);
		CCLib::NormalizedProgress nprogress(&pdlg,cloud->size());
		pdlg.setMethodTitle("Compute normals");
		pdlg.setInfo(qPrintable(QString("Number of points: %1").arg(cloud->size())));
		pdlg.start();

		const int* _indexGrid = &(indexGrid[0]);
		CCLib::ReferenceCloud knn(cloud);
		
		//neighborhood 'half-width' (total width = 1 + 2*kernelWidth) 
		//max number of neighbours: (1+2*nw)^2
		knn.reserve((1+2*kernelWidth)*(1+2*kernelWidth));

		//for each grid cell
		for (int j=0; j<height; ++j)
		{
			for (int i=0; i<width; ++i, ++_indexGrid)
			{
				if (*_indexGrid >= 0)
				{
					unsigned pointIndex = static_cast<unsigned>(*_indexGrid);
					//add the point itself
					knn.clear(false);
					knn.addPointIndex(pointIndex); //warning: indexes are shifted (0 = no point)
					const CCVector3* P = cloud->getPoint(pointIndex);

					//look for neighbors
					for (int v=std::max(0,j-kernelWidth); v<std::min<int>(height,j+kernelWidth); ++v)
					{
						if (v != j)
						{
							for (int u=std::max(0,i-kernelWidth); u<std::min<int>(width,i+kernelWidth); ++u)
							{
								if (u != i)
								{
									int indexN = indexGrid[v*width + u];
									if (indexN >= 0)
									{
										//we don't consider points with a too much different depth than the central point
										const CCVector3* Pn = cloud->getPoint(static_cast<unsigned>(indexN));
										if (fabs(Pn->z - P->z) <= std::max(fabs(Pn->x - P->x),fabs(Pn->y - P->y)))
											knn.addPointIndex(static_cast<unsigned>(indexN)); //warning: indexes are shifted (0 = no point)
									}
								}
							}
						}
					}

					CCVector3 N(0,0,1);
					if (knn.size() >= 3)
					{
						CCLib::Neighbourhood Z(&knn);

						//compute normal with quadratic func. (if we have enough points)
						if (false/*knn.size() >= 6*/)
						{
							uchar hfDims[3];
							const PointCoordinateType* h = Z.getHeightFunction(hfDims);
							if (h)
							{
								const CCVector3* gv = Z.getGravityCenter();
								assert(gv);

								const uchar& iX = hfDims[0];
								const uchar& iY = hfDims[1];
								const uchar& iZ = hfDims[2];

								PointCoordinateType lX = P->u[iX] - gv->u[iX];
								PointCoordinateType lY = P->u[iY] - gv->u[iY];

								N.u[iX] = h[1] + (2 * h[3] * lX) + (h[4] * lY);
								N.u[iY] = h[2] + (2 * h[5] * lY) + (h[4] * lX);
								N.u[iZ] = -PC_ONE;

								N.normalize();
							}
						}
						else
#define USE_LSQ_PLANE
#ifdef USE_LSQ_PLANE
						{
							//compute normal with best fit plane
							const CCVector3* _N = Z.getLSQPlaneNormal();
							if (_N)
								N = *_N;
						}
#else
						{
							//compute normals with 2D1/2 triangulation
							CCLib::GenericIndexedMesh* theMesh = Z.triangulateOnPlane();
							if (theMesh)
							{
								unsigned faceCount = theMesh->size();
								N.z = 0;

								//for all triangles
								theMesh->placeIteratorAtBegining();
								for (unsigned j=0; j<faceCount; ++j)
								{
									const CCLib::TriangleSummitsIndexes* tsi = theMesh->getNextTriangleIndexes();
									//we look if the central point is one of the triangle's vertices
									if (tsi->i1 == 0 || tsi->i2 == 0|| tsi->i3 == 0)
									{
										const CCVector3 *A = knn.getPoint(tsi->i1);
										const CCVector3 *B = knn.getPoint(tsi->i2);
										const CCVector3 *C = knn.getPoint(tsi->i3);

										CCVector3 no = (*B - *A).cross(*C - *A);
										//no.normalize();
										N += no;
									}
								}

								delete theMesh;
								theMesh = 0;

								//normalize the 'mean' vector
								N.normalize();
							}
						}
#endif
					}

					//check normal vector sign
					CCVector3 viewVector = *P /*- cloudTrans.getTranslationAsVec3D()*/; //clouds are still in their local coordinate system!
					if (viewVector.dot(N) > 0)
						N *= -PC_ONE;
					cloud->addNorm(N);

					//progress
					if (!nprogress.oneStep())
					{
						result = false;
						if (canceledByUser)
							*canceledByUser = true;
						ccLog::Warning("[ComputeNormals] Process canceled by user!");
						//early stop
						j = height;
						break;
					}
				}
			}
		}

		if (!result)
		{
			cloud->unallocateNorms();
		}
	}
	else
	{
		ccLog::Warning("[ComputeNormals] Not enough memory!");
	}

	return result;
}