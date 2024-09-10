void
LEPlic :: doCellDLS(FloatArray &fvgrad, int ie, bool coord_upd, bool vof_temp_flag)
{
    int i, ineighbr, nneighbr;
    double fvi, fvk, wk, dx, dy;
    bool isBoundaryCell = false;
    LEPlicElementInterface *interface, *ineghbrInterface;
    FloatMatrix lhs(2, 2);
    FloatArray rhs(2), xi(2), xk(2);
    IntArray currCell(1), neighborList;
    ConnectivityTable *contable = domain->giveConnectivityTable();

    if ( ( interface = ( LEPlicElementInterface * ) ( domain->giveElement(ie)->giveInterface(LEPlicElementInterfaceType) ) ) ) {
        if ( vof_temp_flag ) {
            fvi = interface->giveTempVolumeFraction();
        } else {
            fvi = interface->giveVolumeFraction();
        }

        if ( ( fvi > 0. ) && ( fvi <= 1.0 ) ) {
            // potentially boundary cell

            if ( ( fvi > 0. ) && ( fvi < 1.0 ) ) {
                isBoundaryCell = true;
            }

            /* DLS (Differential least square reconstruction)
             *
             * In the DLS method, volume fraction Taylor series expansion of vf (volume fraction)
             * is formed from each reference cell volume fraction vf at element center x(i) to each
             * cell neighbor at point x(k). The sum (vf(i)-vf(k))^2 over all immediate neighbors
             * is then minimized inthe least square sense.
             */
            // get list of neighbours to current cell including current cell
            currCell.at(1) = ie;
            contable->giveElementNeighbourList(neighborList, currCell);
            // loop over neighbors to assemble normal equations
            nneighbr = neighborList.giveSize();
            interface->giveElementCenter(this, xi, coord_upd);
            lhs.zero();
            rhs.zero();
            for ( i = 1; i <= nneighbr; i++ ) {
                ineighbr = neighborList.at(i);
                if ( ineighbr == ie ) {
                    continue;         // skip itself
                }

                if ( ( ineghbrInterface =
                          ( LEPlicElementInterface * ) ( domain->giveElement(ineighbr)->giveInterface(LEPlicElementInterfaceType) ) ) ) {
                    if ( vof_temp_flag ) {
                        fvk = ineghbrInterface->giveTempVolumeFraction();
                    } else {
                        fvk = ineghbrInterface->giveVolumeFraction();
                    }

                    if ( fvk < 1.0 ) {
                        isBoundaryCell = true;
                    }

                    ineghbrInterface->giveElementCenter(this, xk, coord_upd);
                    wk = xk.distance(xi);
                    dx = ( xk.at(1) - xi.at(1) ) / wk;
                    dy = ( xk.at(2) - xi.at(2) ) / wk;
                    lhs.at(1, 1) += dx * dx;
                    lhs.at(1, 2) += dx * dy;
                    lhs.at(2, 2) += dy * dy;

                    rhs.at(1) += ( fvi - fvk ) * dx / wk;
                    rhs.at(2) += ( fvi - fvk ) * dy / wk;
                }
            }

            if ( isBoundaryCell ) {
                // symmetry
                lhs.at(2, 1) = lhs.at(1, 2);

                // solve normal equation for volume fraction gradient
                lhs.solveForRhs(rhs, fvgrad);

                // compute unit normal
                fvgrad.normalize();
                fvgrad.negated();
#ifdef __OOFEG
                /*
                 * EASValsSetLayer(OOFEG_DEBUG_LAYER);
                 * WCRec p[2];
                 * double tx = -fvgrad.at(2), ty=fvgrad.at(1);
                 * p[0].x=xi.at(1)-tx*0.1;
                 * p[0].y=xi.at(2)-ty*0.1;
                 * p[1].x=xi.at(1)+tx*0.1;
                 * p[1].y=xi.at(2)+ty*0.1;
                 * p[0].z = p[1].z = 0.0;
                 * GraphicObj *go = CreateLine3D(p);
                 * EGWithMaskChangeAttributes(LAYER_MASK, go);
                 * EMAddGraphicsToModel(ESIModel(), go);
                 * ESIEventLoop (YES, "Cell DLS finished; Press Ctrl-p to continue");
                 */
#endif
            } else {
                fvgrad.zero();
            }
        }
    }
}