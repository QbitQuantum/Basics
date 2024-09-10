std::vector<std::unique_ptr<EnrichmentItem>> NCPrincipalStress::nucleateEnrichmentItems() {


	SpatialLocalizer *octree = this->mpDomain->giveSpatialLocalizer();
	XfemManager *xMan = mpDomain->giveXfemManager();

	std::vector<std::unique_ptr<EnrichmentItem>> eiList;

	// Center coordinates of newly inserted cracks
	std::vector<FloatArray> center_coord_inserted_cracks;

	// Loop over all elements and all bulk GP.
	for(auto &el : mpDomain->giveElements() ) {

		int numIR = el->giveNumberOfIntegrationRules();

		int csNum = el->giveCrossSection()->giveNumber();

		if(csNum == mCrossSectionInd || true) {

			for(int irInd = 0; irInd < numIR; irInd++) {
				IntegrationRule *ir = el->giveIntegrationRule(irInd);



				int numGP = ir->giveNumberOfIntegrationPoints();

				for(int gpInd = 0; gpInd < numGP; gpInd++) {
					GaussPoint *gp = ir->getIntegrationPoint(gpInd);

	//				int csNum = gp->giveCrossSection()->giveNumber();
	//				printf("csNum: %d\n", csNum);


						StructuralMaterialStatus *ms = dynamic_cast<StructuralMaterialStatus*>(gp->giveMaterialStatus());

						if(ms != NULL) {

							const FloatArray &stress = ms->giveTempStressVector();

							FloatArray principalVals;
							FloatMatrix principalDirs;
							StructuralMaterial::computePrincipalValDir(principalVals, principalDirs, stress, principal_stress);

							if(principalVals[0] > mStressThreshold) {



		//						printf("\nFound GP with stress above threshold.\n");
		//						printf("principalVals: "); principalVals.printYourself();

								FloatArray crackNormal;
								crackNormal.beColumnOf(principalDirs, 1);
		//						printf("crackNormal: "); crackNormal.printYourself();

								FloatArray crackTangent = {-crackNormal(1), crackNormal(0)};
								crackTangent.normalize();
		//						printf("crackTangent: "); crackTangent.printYourself();



								// Create geometry
								FloatArray pc = {gp->giveGlobalCoordinates()(0), gp->giveGlobalCoordinates()(1)};
		//						printf("Global coord: "); pc.printYourself();


								FloatArray ps = pc;
								ps.add(-0.5*mInitialCrackLength, crackTangent);

								FloatArray pe = pc;
								pe.add(0.5*mInitialCrackLength, crackTangent);

								if(mCutOneEl) {
									// If desired, ensure that the crack cuts exactly one element.
									Line line(ps, pe);
									std::vector<FloatArray> intersecPoints;
		//							line.computeIntersectionPoints(el.get(), intersecPoints);

									for ( int i = 1; i <= el->giveNumberOfDofManagers(); i++ ) {
//										int n1 = i;
//										int n2 = 0;
//										if ( i < el->giveNumberOfDofManagers() ) {
//											n2 = i + 1;
//										} else {
//											n2 = 1;
//										}

		//						        const FloatArray &p1 = *(el->giveDofManager(n1)->giveCoordinates());
		//						        const FloatArray &p2 = *(el->giveDofManager(n2)->giveCoordinates());


									}

		//							printf("intersecPoints.size(): %lu\n", intersecPoints.size());

									if(intersecPoints.size() == 2) {
										ps = std::move(intersecPoints[0]);
										pe = std::move(intersecPoints[1]);
									}
									else {
										OOFEM_ERROR("intersecPoints.size() != 2")
									}
								}

								FloatArray points = {ps(0), ps(1), pc(0), pc(1), pe(0), pe(1)};

		//						double diffX = 0.5*(ps(0) + pe(0)) - pc(0);
		//						printf("diffX: %e\n", diffX);

		//						double diffY = 0.5*(ps(1) + pe(1)) - pc(1);
		//						printf("diffY: %e\n", diffY);


								// TODO: Check if nucleation is allowed, by checking for already existing cracks close to the GP.
								// Idea: Nucleation is not allowed if we are within an enriched element. In this way, branching is not
								// completely prohibited, but we avoid initiating multiple similar cracks.
								bool insertionAllowed = true;

								Element *el_s = octree->giveElementContainingPoint(ps);
								if(el_s) {
									if( xMan->isElementEnriched(el_s) ) {
										insertionAllowed = false;
									}
								}

								Element *el_c = octree->giveElementContainingPoint(pc);
								if(el_c) {
									if( xMan->isElementEnriched(el_c) ) {
										insertionAllowed = false;
									}
								}

								Element *el_e = octree->giveElementContainingPoint(pe);
								if(el_e) {
									if( xMan->isElementEnriched(el_e) ) {
										insertionAllowed = false;
									}
								}

								for(const auto &x: center_coord_inserted_cracks) {
									if( x.distance(pc) <  2.0*mInitialCrackLength) {
										insertionAllowed = false;
										break;
										printf("Preventing insertion.\n");
									}
								}

								if(insertionAllowed) {
									int n = xMan->giveNumberOfEnrichmentItems() + 1;
									std::unique_ptr<Crack> crack = std::make_unique<Crack>(n, xMan, mpDomain);


									// Geometry
									std::unique_ptr<BasicGeometry> geom = std::make_unique<PolygonLine>();
									geom->insertVertexBack(ps);
									geom->insertVertexBack(pc);
									geom->insertVertexBack(pe);
									crack->setGeometry(std::move(geom));

									// Enrichment function
									EnrichmentFunction *ef = new HeavisideFunction(1, mpDomain);
									crack->setEnrichmentFunction(ef);

									// Enrichment fronts
//									EnrichmentFront *efStart = new EnrFrontLinearBranchFuncOneEl();
									EnrichmentFront *efStart = new EnrFrontCohesiveBranchFuncOneEl();
									crack->setEnrichmentFrontStart(efStart);

//									EnrichmentFront *efEnd = new EnrFrontLinearBranchFuncOneEl();
									EnrichmentFront *efEnd = new EnrFrontCohesiveBranchFuncOneEl();
									crack->setEnrichmentFrontEnd(efEnd);




									///////////////////////////////////////
									// Propagation law

									// Options
			//					    double radius = 0.5*mInitialCrackLength, angleInc = 10.0, incrementLength = 0.5*mInitialCrackLength, hoopStressThreshold = 0.0;
			//					    bool useRadialBasisFunc = true;

			//						PLHoopStressCirc *pl = new PLHoopStressCirc();
			//						pl->setRadius(radius);
			//						pl->setAngleInc(angleInc);
			//						pl->setIncrementLength(incrementLength);
			//						pl->setHoopStressThreshold(hoopStressThreshold);
			//						pl->setUseRadialBasisFunc(useRadialBasisFunc);

			//					    PLDoNothing *pl = new PLDoNothing();

									PLMaterialForce *pl = new PLMaterialForce();
									pl->setRadius(mMatForceRadius);
									pl->setIncrementLength(mIncrementLength);
//									pl->setIncrementLength(0.25);
//									pl->setCrackPropThreshold(0.25);
									pl->setCrackPropThreshold(mCrackPropThreshold);

									crack->setPropagationLaw(pl);

									crack->updateDofIdPool();

									center_coord_inserted_cracks.push_back(pc);
									eiList.push_back( std::unique_ptr<EnrichmentItem>(std::move(crack)) );

//									printf("Nucleating a crack in NCPrincipalStress::nucleateEnrichmentItems.\n");
//									printf("el->giveGlobalNumber(): %d\n", el->giveGlobalNumber() );

									// We only introduce one crack per element in a single time step.
									break;
								}
							}
						}

				}
			}
		} // If correct csNum
	}