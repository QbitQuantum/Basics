void
MMALeastSquareProjection :: __init(Domain *dold, IntArray &type, FloatArray &coords, Set &elemSet, TimeStep *tStep, bool iCohesiveZoneGP)
//(Domain* dold, IntArray& varTypes, GaussPoint* gp, TimeStep* tStep)
{
    GaussPoint *sourceIp;
    Element *sourceElement;
    SpatialLocalizer *sl = dold->giveSpatialLocalizer();
    IntegrationRule *iRule;

    IntArray patchList;

    this->patchDomain = dold;
    // find the closest IP on old mesh
    sourceElement = sl->giveElementContainingPoint(coords, elemSet);

    if ( !sourceElement ) {
        OOFEM_ERROR("no suitable source element found");
    }

    // determine the type of patch
    Element_Geometry_Type egt = sourceElement->giveGeometryType();
    if ( egt == EGT_line_1 ) {
        this->patchType = MMALSPPatchType_1dq;
    } else if ( ( egt == EGT_triangle_1 ) || ( egt == EGT_quad_1 ) ) {
        this->patchType = MMALSPPatchType_2dq;
    } else {
        OOFEM_ERROR("unsupported material mode");
    }

    /* Determine the state of closest point.
     * Only IP in the neighbourhood with same state can be used
     * to interpolate the values.
     */
    FloatArray dam;
    int state = 0;
    if ( this->stateFilter ) {
        iRule = sourceElement->giveDefaultIntegrationRulePtr();
        for ( GaussPoint *gp: *iRule ) {
            sourceElement->giveIPValue(dam, gp, IST_PrincipalDamageTensor, tStep);
            if ( dam.computeNorm() > 1.e-3 ) {
                state = 1; // damaged
            }
        }
    }

    // from source neighbours the patch will be constructed
    Element *element;
    IntArray neighborList;
    patchList.resize(1);
    patchList.at(1) = sourceElement->giveNumber();
    int minNumberOfPoints = this->giveNumberOfUnknownPolynomialCoefficients(this->patchType);
    int actualNumberOfPoints = sourceElement->giveDefaultIntegrationRulePtr()->giveNumberOfIntegrationPoints();
    int nite = 0;
    int elemFlag;
    // check if number of IP in patchList is sufficient
    // some recursion control would be appropriate
    while ( ( actualNumberOfPoints < minNumberOfPoints ) && ( nite <= 2 ) ) {
        //if not,  construct the neighborhood
        dold->giveConnectivityTable()->giveElementNeighbourList(neighborList, patchList);
        // count number of available points
        patchList.clear();
        actualNumberOfPoints = 0;
        for ( int i = 1; i <= neighborList.giveSize(); i++ ) {
            if ( this->stateFilter ) {
                element = patchDomain->giveElement( neighborList.at(i) );
                // exclude elements in different regions
                if ( !elemSet.hasElement( element->giveNumber() ) ) {
                    continue;
                }

                iRule = element->giveDefaultIntegrationRulePtr();
                elemFlag = 0;
                for ( GaussPoint *gp: *iRule ) {
                    element->giveIPValue(dam, gp, IST_PrincipalDamageTensor, tStep);
                    if ( state && ( dam.computeNorm() > 1.e-3 ) ) {
                        actualNumberOfPoints++;
                        elemFlag = 1;
                    } else if ( ( state == 0 ) && ( dam.computeNorm() < 1.e-3 ) ) {
                        actualNumberOfPoints++;
                        elemFlag = 1;
                    }
                }

                if ( elemFlag ) {
                    // include this element with corresponding state in neighbor search.
                    patchList.followedBy(neighborList.at(i), 10);
                }
            } else { // if (! yhis->stateFilter)
                element = patchDomain->giveElement( neighborList.at(i) );
                // exclude elements in different regions
                if ( !elemSet.hasElement( element->giveNumber() ) ) {
                    continue;
                }

                actualNumberOfPoints += element->giveDefaultIntegrationRulePtr()->giveNumberOfIntegrationPoints();

                patchList.followedBy(neighborList.at(i), 10);
            }
        } // end loop over neighbor list

        nite++;
    }

    if ( nite > 2 ) {
        // not enough points -> take closest point projection
        patchGPList.clear();
        sourceIp = sl->giveClosestIP(coords, elemSet);
        patchGPList.push_front(sourceIp);
        //fprintf(stderr, "MMALeastSquareProjection: too many neighbor search iterations\n");
        //exit (1);
        return;
    }

#ifdef MMALSP_ONLY_CLOSEST_POINTS
    // select only the nval closest IP points
    GaussPoint **gpList = ( GaussPoint ** ) malloc(sizeof( GaussPoint * ) * actualNumberOfPoints);
    FloatArray dist(actualNumberOfPoints), srcgpcoords;
    int npoints = 0;
    // check allocation of gpList
    if ( gpList == NULL ) {
        OOFEM_FATAL("memory allocation error");
    }

    for ( int ielem = 1; ielem <= patchList.giveSize(); ielem++ ) {
        element = patchDomain->giveElement( patchList.at(ielem) );
        iRule = element->giveDefaultIntegrationRulePtr();
        for ( GaussPoint *srcgp: *iRule ) {
            if ( element->computeGlobalCoordinates( srcgpcoords, * ( srcgp->giveNaturalCoordinates() ) ) ) {
                element->giveIPValue(dam, srcgp, IST_PrincipalDamageTensor, tStep);
                if ( this->stateFilter ) {
                    // consider only points with same state
                    if ( ( ( state == 1 ) && ( norm(dam) > 1.e-3 ) ) || ( ( ( state == 0 ) && norm(dam) < 1.e-3 ) ) ) {
                        npoints++;
                        dist.at(npoints) = coords.distance(srcgpcoords);
                        gpList [ npoints - 1 ] = srcgp;
                    }
                } else {
                    // take all points into account
                    npoints++;
                    dist.at(npoints) = coords.distance(srcgpcoords);
                    gpList [ npoints - 1 ] = srcgp;
                }
            } else {
                OOFEM_ERROR("computeGlobalCoordinates failed");
            }
        }
    }

    if ( npoints != actualNumberOfPoints ) {
        OOFEM_ERROR("internal error");
    }

    //minNumberOfPoints = min (actualNumberOfPoints, minNumberOfPoints+2);

    patchGPList.clear();
    // now find the minNumberOfPoints with smallest distance
    // from point of interest
    double swap, minDist;
    int minDistIndx = 0;
    // loop over all points
    for ( int i = 1; i <= minNumberOfPoints; i++ ) {
        minDist = dist.at(i);
        minDistIndx = i;
        // search for point with i-th smallest distance
        for ( j = i + 1; j <= actualNumberOfPoints; j++ ) {
            if ( dist.at(j) < minDist ) {
                minDist = dist.at(j);
                minDistIndx = j;
            }
        }

        // remember this ip
        patchGPList.push_front(gpList [ minDistIndx - 1 ]);
        swap = dist.at(i);
        dist.at(i) = dist.at(minDistIndx);
        dist.at(minDistIndx) = swap;
        srcgp = gpList [ i - 1 ];
        gpList [ i - 1 ] = gpList [ minDistIndx - 1 ];
        gpList [ minDistIndx - 1 ] = srcgp;
    }

    if ( patchGPList.size() != minNumberOfPoints ) {
        OOFEM_ERROR("internal error 2");
        exit(1);
    }

    free(gpList);

#else

    // take all neighbors
    patchGPList.clear();
    for ( int ielem = 1; ielem <= patchList.giveSize(); ielem++ ) {
        element = patchDomain->giveElement( patchList.at(ielem) );
        iRule = element->giveDefaultIntegrationRulePtr();
        for ( GaussPoint *gp: *iRule ) {
            patchGPList.push_front( gp );
        }
    }

#endif
}