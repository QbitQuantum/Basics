///=========================================================
int main (int argc, char* argv[])
{
	// Filter addSearchPath
	NLMISC::createDebug();
	InfoLog->addNegativeFilter ("adding the path");

	TShapeMap shapeMap;

	// Check number of args
	if (argc<5)
	{
		// Help message
		printf ("zone_dependencies [properties.cfg] [firstZone.zone] [lastzone.zone] [output_dependencies.cfg]\n");
	}
	else
	{
		NL3D::registerSerial3d();
		// Light direction
		CVector lightDirection;

		// Config file handler
		try
		{
			// Read the properties file
			CConfigFile properties;
			
			// Load and parse the properties file
			properties.load (argv[1]);

			// Get the light direction
			CConfigFile::CVar &sun_direction = properties.getVar ("sun_direction");
			lightDirection.set (sun_direction.asFloat(0), sun_direction.asFloat(1), sun_direction.asFloat(2));
			lightDirection.normalize();


			// Get the search pathes
			CConfigFile::CVar &search_pathes = properties.getVar ("search_pathes");
			uint path;
			for (path = 0; path < (uint)search_pathes.size(); path++)
			{
				// Add to search path
				CPath::addSearchPath (search_pathes.asString(path));
			}
/*
			CConfigFile::CVar &ig_path = properties.getVar ("ig_path");
			NLMISC::CPath::addSearchPath(ig_path.asString(), true, true);

			CConfigFile::CVar &shapes_path = properties.getVar ("shapes_path");
			NLMISC::CPath::addSearchPath(shapes_path.asString(), true, true);
*/
			CConfigFile::CVar &compute_dependencies_with_igs = properties.getVar ("compute_dependencies_with_igs");
			bool computeDependenciesWithIgs = compute_dependencies_with_igs.asInt() != 0;								


			// Get the file extension
			string ext=getExt (argv[2]);

			// Get the file directory
			string dir=getDir (argv[2]);

			// Get output extension
			string outExt=getExt (argv[4]);

			// Get output directory
			string outDir=getDir (argv[4]);

			// Get the first and last name
			string firstName=getName (argv[2]);
			string lastName=getName (argv[3]);

			// Get the coordinates
			uint16 firstX, firstY;
			uint16 lastX, lastY;
			if (getZoneCoordByName (firstName.c_str(), firstX, firstY))
			{
				// Last zone
				if (getZoneCoordByName (lastName.c_str(), lastX, lastY))
				{
					// Take care
					if (lastX<firstX)
					{
						uint16 tmp=firstX;
						firstX=lastX;
						lastX=firstX;
					}
					if (lastY<firstY)
					{
						uint16 tmp=firstY;
						firstY=lastY;
						lastY=firstY;
					}

					// Min z
					float minZ=FLT_MAX;

					// Make a quad grid
					CQuadGrid<CZoneDescriptorBB>	quadGrid;
					quadGrid.create (256, 100);

					// The dependencies list
					vector< CZoneDependencies > dependencies;
					dependencies.resize ((lastX-firstX+1)*(lastY-firstY+1));

					// Ryzom specific: build bbox for villages
					TString2LightingBBox villagesBBox;					
					computeIGBBoxFromContinent(properties, shapeMap, villagesBBox);		


					// Insert each zone in the quad tree
					sint y, x;
					for (y=firstY; y<=lastY; y++)
					for (x=firstX; x<=lastX; x++)
					{
						

						// Progress
						progress ("Build bounding boxes", (float)(x+y*lastX)/(float)(lastX*lastY));

						// Make a zone file name
						string zoneName;
						getZoneNameByCoord (x, y, zoneName);

						// Open the file
						CIFile file;
						if (file.open (dir+zoneName+ext))
						{							
							// The zone
							CZone zone;

							try
							{
								// Serial the zone
								file.serial (zone);

								/// get bbox from the ig of this zone
								CLightingBBox igBBox;								
								if (computeDependenciesWithIgs)
								{
									computeZoneIGBBox(zoneName.c_str(), igBBox, shapeMap, villagesBBox);
								}								
								// Create a zone descriptor
								

								
								NLMISC::CAABBox zoneBox;
								zoneBox.setCenter(zone.getZoneBB().getCenter());
								zoneBox.setHalfSize(zone.getZoneBB().getHalfSize());

								CLightingBBox zoneLBox;
								zoneLBox.OccludingBox = zoneLBox.ReceivingBox = zoneBox; // can't be void
								zoneLBox.makeUnion(igBBox);								
								nlassert(!zoneLBox.ReceivingBox.IsVoid);
								//
								CZoneDescriptorBB zoneDesc;
								zoneDesc.X=x;
								zoneDesc.Y=y;
								zoneDesc.BBox=zoneLBox.ReceivingBox.Box;
								//
								if (!zoneLBox.OccludingBox.IsVoid)
								{
									quadGrid.insert (zoneLBox.ReceivingBox.Box.getMin(), zoneLBox.ReceivingBox.Box.getMax(), zoneDesc);
								}
																								
								// Insert in the dependencies
								// Index 
								uint index=(x-firstX)+(y-firstY)*(lastX-firstX+1);
								

								// Loaded
								dependencies[index].Loaded=true;
								dependencies[index].X=x;
								dependencies[index].Y=y;
								dependencies[index].BBox=zoneLBox.OccludingBox.Box;

								// ZMin
								float newZ=zoneLBox.ReceivingBox.Box.getMin().z;
								if (newZ<minZ)
									minZ=newZ;
							}
							catch (Exception& e)
							{
								// Error handling
								nlwarning ("ERROR in file %s, %s", (dir+zoneName+ext).c_str(), e.what ());
							}
						}
					}

					// Now select each zone in others and make a depencies list
					for (y=firstY; y<=lastY; y++)
					for (x=firstX; x<=lastX; x++)
					{
						// Progress
						progress ("Compute dependencies", (float)(x+y*lastX)/(float)(lastX*lastY));

						// Index 
						uint index=(x-firstX)+(y-firstY)*(lastX-firstX+1);

						// Loaded ?
						if (dependencies[index].Loaded)
						{
							// Min max vectors
							CVector vMin (dependencies[index].BBox.getMin());
							CVector vMax (dependencies[index].BBox.getMax());

							// Make a corner array 
							CVector corners[4] = 
							{
								CVector (vMin.x, vMin.y, vMax.z), CVector (vMax.x, vMin.y, vMax.z), 
								CVector (vMax.x, vMax.y, vMax.z), CVector (vMin.x, vMax.y, vMax.z)
							};

							// Extended bbox
							CAABBox	bBox=dependencies[index].BBox.getAABBox();

							// For each corner
							uint corner;
							for (corner=0; corner<4; corner++)
							{
								// Target position
								CVector target;
								if (lightDirection.z!=0)
								{
									// Not horizontal target
									target=corners[corner]+(lightDirection*((minZ-corners[corner].z)/lightDirection.z));
								}
								else
								{
									// Horizontal target, select 500 meters around.
									target=(500*lightDirection)+corners[corner];
								}

								// Extend the bbox
								bBox.extend (target);
							}

							// Clear quad tree selection
							quadGrid.clearSelection ();

							// Select
							quadGrid.select (bBox.getMin(), bBox.getMax());

							// Check selection
							CQuadGrid<CZoneDescriptorBB>::CIterator it=quadGrid.begin();
							while (it!=quadGrid.end())
							{
								// Index 
								uint targetIndex=((*it).X-firstX)+((*it).Y-firstY)*(lastX-firstX+1);

								// Not the same
								if (targetIndex!=index)
								{
									// Target min z
									float targetMinZ=dependencies[targetIndex].BBox.getMin().z;
									if (targetMinZ<vMax.z)
									{
										// Min z inf to max z ?
										// Target optimized bbox
										CAABBox	bBoxOptimized=dependencies[index].BBox.getAABBox();

										// For each corner
										for (corner=0; corner<4; corner++)
										{
											// Target position
											CVector target;
											if (lightDirection.z!=0)
											{
												// Not horizontal target
												target=corners[corner]+(lightDirection*((targetMinZ-corners[corner].z)
													/lightDirection.z));
											}
											else
											{
												// Horizontal target, select 500 meters around.
												target=(500*lightDirection)+corners[corner];
											}

											// Extend the bbox
											bBoxOptimized.extend (target);
										}

										// Check it more presisly
										//if ((*it).BBox.intersect (bBoxOptimized))
										if ((*it).BBox.intersect (bBox))
										{
											// Insert in the set
											dependencies[targetIndex].Dependences.insert (CZoneDependenciesValue (x, y));
										}
									}
								}

								// Next selected
								it++;
							}
						}
					}

					// For each zone
					for (y=firstY; y<=lastY; y++)
					for (x=firstX; x<=lastX; x++)
					{
						// Progress
						progress ("Save depend files", (float)(x+y*lastX)/(float)(lastX*lastY));

						// Index 
						uint index=(x-firstX)+(y-firstY)*(lastX-firstX+1);

						// Loaded ?
						if (dependencies[index].Loaded)
						{
							// Make a file name
							string outputFileName;
							getZoneNameByCoord(x, y, outputFileName);
							outputFileName=outDir+outputFileName+outExt;

							// Write the dependencies file
							FILE *outputFile;
							if ((outputFile=fopen (toLower (outputFileName).c_str(), "w")))
							{
								// Add a dependency entry
								fprintf (outputFile, "dependencies =\n{\n");

								// Add dependent zones
								set<CZoneDependenciesValue>::iterator ite=dependencies[index].Dependences.begin();
								while (ite!=dependencies[index].Dependences.end())
								{
									// Name of the dependent zone
									std::string zoneName;
									getZoneNameByCoord(ite->first, ite->second, zoneName);

									// Write it
									string message="\t\""+zoneName+"\"";
									fprintf (outputFile, "%s", toLower (message).c_str());

									// Next ite;
									ite++;
									if (ite!=dependencies[index].Dependences.end())
										fprintf (outputFile, ",\n");
								}

								// Close the variable
								fprintf (outputFile, "\n};\n\n");
							}
							else
							{
								nlwarning ("ERROR can't open %s for writing.\n", outputFileName.c_str());
							}

							// Close the file
							fclose (outputFile);
						}
					}

				}
				else
				{
					// Not valid
					nlwarning ("ERROR %s is not a valid zone name.\n", lastName.c_str());
				}
			}
			else
			{
				// Not valid
				nlwarning ("ERROR %s is not a valid zone name.\n", firstName.c_str());
			}
		}
		catch (Exception &ee)
		{
			nlwarning ("ERROR %s\n", ee.what());
		}
	}

	return 0;
}