void
Lattice2d :: drawSpecial(oofegGraphicContext &gc, TimeStep *tStep)
{
    WCRec l [ 2 ];
    GraphicObj *tr;
    GaussPoint *gp;
    FloatArray crackStatuses, cf;

    if ( !gc.testElementGraphicActivity(this) ) {
        return;
    }

    if ( gc.giveIntVarType() == IST_CrackState ) {
        gp = integrationRulesArray [ 0 ]->getIntegrationPoint(0);
        this->giveIPValue(crackStatuses, gp, IST_CrackStatuses, tStep);
        if ( crackStatuses(0) == 1. || crackStatuses(0) == 2. || crackStatuses(0) == 3 || crackStatuses(0) == 4 ) {
            double x1, y1, x2, y2;
            x1 = this->giveNode(1)->giveCoordinate(1);
            y1 = this->giveNode(1)->giveCoordinate(2);
            x2 = this->giveNode(2)->giveCoordinate(1);
            y2 = this->giveNode(2)->giveCoordinate(2);

            //Compute normal and shear direction
            FloatArray normalDirection;
            FloatArray shearDirection;
            normalDirection.resize(2);
            normalDirection.zero();
            shearDirection.resize(2);
            shearDirection.zero();
            normalDirection.at(1) = x2 - x1;
            normalDirection.at(2) = y2 - y1;
            normalDirection.normalize();
            if ( normalDirection.at(2) == 0. ) {
                shearDirection.at(1) = 0.;
                shearDirection.at(2) = 1.;
            } else {
                shearDirection.at(1) = 1.0;
                shearDirection.at(2) =
                    -normalDirection.at(1) / normalDirection.at(2);
            }

            shearDirection.normalize();

            l [ 0 ].x = ( FPNum ) this->gpCoords.at(1) - shearDirection.at(1) * this->width / 2.;
            l [ 0 ].y = ( FPNum ) this->gpCoords.at(2) - shearDirection.at(2) * this->width / 2.;
            l [ 0 ].z = 0.;
            l [ 1 ].x = ( FPNum ) this->gpCoords.at(1) + shearDirection.at(1) * this->width / 2.;
            ;
            l [ 1 ].y = ( FPNum ) this->gpCoords.at(2) + shearDirection.at(2) * this->width / 2.;
            l [ 1 ].z = 0.;

            EASValsSetLayer(OOFEG_CRACK_PATTERN_LAYER);
            EASValsSetLineWidth(OOFEG_CRACK_PATTERN_WIDTH);
            if ( ( crackStatuses(0) == 1. ) ) {
                EASValsSetColor( gc.getActiveCrackColor() );
            } else if ( crackStatuses(0) == 2. ) {
                EASValsSetColor( gc.getCrackPatternColor() );
            } else if ( crackStatuses(0) == 3. ) {
                EASValsSetColor( gc.getActiveCrackColor() );
            } else if ( crackStatuses(0) == 4. ) {
                EASValsSetColor( gc.getActiveCrackColor() );
            }


            tr = CreateLine3D(l);
            EGWithMaskChangeAttributes(WIDTH_MASK | COLOR_MASK | LAYER_MASK, tr);
            EMAddGraphicsToModel(ESIModel(), tr);
        }
    }
}