bool XfemStructuralElementInterface :: XfemElementInterface_updateIntegrationRule()
{
    const double tol2 = 1.0e-18;

    bool partitionSucceeded = false;


    if ( mpCZMat != NULL ) {
        mpCZIntegrationRules.clear();
        mCZEnrItemIndices.clear();
        mCZTouchingEnrItemIndices.clear();
    }

    XfemManager *xMan = this->element->giveDomain()->giveXfemManager();
    if ( xMan->isElementEnriched(element) ) {
        if ( mpCZMat == NULL && mCZMaterialNum > 0 ) {
            initializeCZMaterial();
        }


        MaterialMode matMode = element->giveMaterialMode();

        bool firstIntersection = true;

        std :: vector< std :: vector< FloatArray > >pointPartitions;
        mSubTri.clear();

        std :: vector< int >enrichingEIs;
        int elPlaceInArray = xMan->giveDomain()->giveElementPlaceInArray( element->giveGlobalNumber() );
        xMan->giveElementEnrichmentItemIndices(enrichingEIs, elPlaceInArray);


        for ( size_t p = 0; p < enrichingEIs.size(); p++ ) {
            // Index of current ei
            int eiIndex = enrichingEIs [ p ];

            // Indices of other ei interaction with this ei through intersection enrichment fronts.
            std :: vector< int >touchingEiIndices;
            giveIntersectionsTouchingCrack(touchingEiIndices, enrichingEIs, eiIndex, * xMan);

            if ( firstIntersection ) {
                // Get the points describing each subdivision of the element
                double startXi, endXi;
                bool intersection = false;
                this->XfemElementInterface_prepareNodesForDelaunay(pointPartitions, startXi, endXi, eiIndex, intersection);

                if ( intersection ) {
                    firstIntersection = false;

                    // Use XfemElementInterface_partitionElement to subdivide the element
                    for ( int i = 0; i < int ( pointPartitions.size() ); i++ ) {
                        // Triangulate the subdivisions
                        this->XfemElementInterface_partitionElement(mSubTri, pointPartitions [ i ]);
                    }


                    if ( mpCZMat != NULL ) {
                        Crack *crack = dynamic_cast< Crack * >( xMan->giveEnrichmentItem(eiIndex) );
                        if ( crack == NULL ) {
                            OOFEM_ERROR("Cohesive zones are only available for cracks.")
                        }

                        // We have xi_s and xi_e. Fetch sub polygon.
                        std :: vector< FloatArray >crackPolygon;
                        crack->giveSubPolygon(crackPolygon, startXi, endXi);

                        ///////////////////////////////////
                        // Add cohesive zone Gauss points
                        size_t numSeg = crackPolygon.size() - 1;

                        for ( size_t segIndex = 0; segIndex < numSeg; segIndex++ ) {
                            int czRuleNum = 1;
                            mpCZIntegrationRules.emplace_back( new GaussIntegrationRule(czRuleNum, element) );

                            // Add index of current ei
                            mCZEnrItemIndices.push_back(eiIndex);

                            // Add indices of other ei, that cause interaction through
                            // intersection enrichment fronts
                            mCZTouchingEnrItemIndices.push_back(touchingEiIndices);

                            // Compute crack normal
                            FloatArray crackTang;
                            crackTang.beDifferenceOf(crackPolygon [ segIndex + 1 ], crackPolygon [ segIndex ]);

                            if ( crackTang.computeSquaredNorm() > tol2 ) {
                                crackTang.normalize();
                            }

                            FloatArray crackNormal = {
                                -crackTang.at(2), crackTang.at(1)
                            };

                            mpCZIntegrationRules [ segIndex ]->SetUpPointsOn2DEmbeddedLine(mCSNumGaussPoints, matMode,
                                                                                           crackPolygon [ segIndex ], crackPolygon [ segIndex + 1 ]);

                            for ( GaussPoint *gp: *mpCZIntegrationRules [ segIndex ] ) {
                                double gw = gp->giveWeight();
                                double segLength = crackPolygon [ segIndex ].distance(crackPolygon [ segIndex + 1 ]);
                                gw *= 0.5 * segLength;
                                gp->setWeight(gw);

                                // Fetch material status and set normal
                                StructuralInterfaceMaterialStatus *ms = dynamic_cast< StructuralInterfaceMaterialStatus * >( mpCZMat->giveStatus(gp) );
                                if ( ms == NULL ) {
                                    OOFEM_ERROR("Failed to fetch material status.");
                                }

                                ms->letNormalBe(crackNormal);

                                // Give Gauss point reference to the enrichment item
                                // to simplify post processing.
                                crack->AppendCohesiveZoneGaussPoint(gp);
                            }
                        }
                    }



                    partitionSucceeded = true;
                }
            } // if(firstIntersection)
            else {
                // Loop over triangles
                std :: vector< Triangle >allTriCopy;
                for ( size_t triIndex = 0; triIndex < mSubTri.size(); triIndex++ ) {
                    // Call alternative version of XfemElementInterface_prepareNodesForDelaunay
                    std :: vector< std :: vector< FloatArray > >pointPartitionsTri;
                    double startXi, endXi;
                    bool intersection = false;
                    XfemElementInterface_prepareNodesForDelaunay(pointPartitionsTri, startXi, endXi, mSubTri [ triIndex ], eiIndex, intersection);

                    if ( intersection ) {
                        // Use XfemElementInterface_partitionElement to subdivide triangle j
                        for ( int i = 0; i < int ( pointPartitionsTri.size() ); i++ ) {
                            this->XfemElementInterface_partitionElement(allTriCopy, pointPartitionsTri [ i ]);
                        }


                        // Add cohesive zone Gauss points

                        if ( mpCZMat != NULL ) {
                            Crack *crack = dynamic_cast< Crack * >( xMan->giveEnrichmentItem(eiIndex) );
                            if ( crack == NULL ) {
                                OOFEM_ERROR("Cohesive zones are only available for cracks.")
                            }

                            // We have xi_s and xi_e. Fetch sub polygon.
                            std :: vector< FloatArray >crackPolygon;
                            crack->giveSubPolygon(crackPolygon, startXi, endXi);

                            int numSeg = crackPolygon.size() - 1;

                            for ( int segIndex = 0; segIndex < numSeg; segIndex++ ) {
                                int czRuleNum = 1;
                                mpCZIntegrationRules.emplace_back( new GaussIntegrationRule(czRuleNum, element) );
                                size_t newRuleInd = mpCZIntegrationRules.size() - 1;
                                mCZEnrItemIndices.push_back(eiIndex);

                                mCZTouchingEnrItemIndices.push_back(touchingEiIndices);

                                // Compute crack normal
                                FloatArray crackTang;
                                crackTang.beDifferenceOf(crackPolygon [ segIndex + 1 ], crackPolygon [ segIndex ]);

                                if ( crackTang.computeSquaredNorm() > tol2 ) {
                                    crackTang.normalize();
                                }

                                FloatArray crackNormal = {
                                    -crackTang.at(2), crackTang.at(1)
                                };

                                mpCZIntegrationRules [ newRuleInd ]->SetUpPointsOn2DEmbeddedLine(mCSNumGaussPoints, matMode,
                                                                                                 crackPolygon [ segIndex ], crackPolygon [ segIndex + 1 ]);

                                for ( GaussPoint *gp: *mpCZIntegrationRules [ newRuleInd ] ) {
                                    double gw = gp->giveWeight();
                                    double segLength = crackPolygon [ segIndex ].distance(crackPolygon [ segIndex + 1 ]);
                                    gw *= 0.5 * segLength;
                                    gp->setWeight(gw);

                                    // Fetch material status and set normal
                                    StructuralInterfaceMaterialStatus *ms = dynamic_cast< StructuralInterfaceMaterialStatus * >( mpCZMat->giveStatus(gp) );
                                    if ( ms == NULL ) {
                                        OOFEM_ERROR("Failed to fetch material status.");
                                    }

                                    ms->letNormalBe(crackNormal);

                                    // Give Gauss point reference to the enrichment item
                                    // to simplify post processing.
                                    crack->AppendCohesiveZoneGaussPoint(gp);
                                }
                            }
                        }
                    } else {
                        allTriCopy.push_back(mSubTri [ triIndex ]);
                    }
                }