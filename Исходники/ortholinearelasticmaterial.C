IRResultType
OrthotropicLinearElasticMaterial :: initializeFrom(InputRecord *ir)
{
    IRResultType result;                // Required by IR_GIVE_FIELD macro

    double value;
    int size;
    FloatArray triplets;


    result = LinearElasticMaterial :: initializeFrom(ir);
    if ( result != IRRT_OK ) return result;

    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_ex);
    propertyDictionary.add(Ex, value);

    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_ey);
    propertyDictionary.add(Ey, value);

    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_ez);
    propertyDictionary.add(Ez, value);


    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_nyyz);
    propertyDictionary.add(NYyz, value);

    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_nyxz);
    propertyDictionary.add(NYxz, value);

    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_nyxy);
    propertyDictionary.add(NYxy, value);


    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_gyz);
    propertyDictionary.add(Gyz, value);

    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_gxz);
    propertyDictionary.add(Gxz, value);

    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_gxy);
    propertyDictionary.add(Gxy, value);



    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_talphax);
    propertyDictionary.add(tAlphax, value);

    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_talphay);
    propertyDictionary.add(tAlphay, value);

    IR_GIVE_FIELD(ir, value, _IFT_OrthotropicLinearElasticMaterial_talphaz);
    propertyDictionary.add(tAlphaz, value);

    // check for suspicious parameters
    // ask for dependent parameters (symmetry conditions) and check if reasonable
    /*
     * nyzx = this->give(NYzx);
     * nyzy = this->give(NYzy);
     * nyyx = this->give(NYyx);
     * if ( ( nyzx < 0. ) || ( nyzx > 0.5 ) || ( nyzy < 0. ) || ( nyzy > 0.5 ) || ( nyyx < 0. ) || ( nyyx > 0.5 ) ) {
     *  OOFEM_WARNING("suspicious parameters", 1);
     * }
     */

    // Read local coordinate system of principal axes of ortotrophy
    // in localCoordinateSystem the unity vectors are stored
    // COLUMNWISE (this is exception, but allows faster numerical
    // implementation)
    // if you wish to align local material orientation with element, use "lcs" keyword as an element parameter

    // try to read lcs section
    triplets.clear();
    IR_GIVE_OPTIONAL_FIELD(ir, triplets, _IFT_OrthotropicLinearElasticMaterial_lcs);

    size = triplets.giveSize();
    if ( !( ( size == 0 ) || ( size == 6 ) ) ) {
        OOFEM_WARNING("Warning: lcs in material %d is not properly defined, will be assumed as global",
                  this->giveNumber() );
    }

    if ( size == 6 ) {
        cs_type = localCS;
        double n1 = 0.0, n2 = 0.0;

        localCoordinateSystem = new FloatMatrix(3, 3);
        for ( int j = 1; j <= 3; j++ ) {
            localCoordinateSystem->at(j, 1) = triplets.at(j);
            n1 += triplets.at(j) * triplets.at(j);
            localCoordinateSystem->at(j, 2) = triplets.at(j + 3);
            n2 += triplets.at(j + 3) * triplets.at(j + 3);
        }

        n1 = sqrt(n1);
        n2 = sqrt(n2);
        for ( int j = 1; j <= 3; j++ ) { // normalize e1' e2'
            localCoordinateSystem->at(j, 1) /= n1;
            localCoordinateSystem->at(j, 2) /= n2;
        }

        // vector e3' computed from vector product of e1', e2'
        localCoordinateSystem->at(1, 3) =
            ( localCoordinateSystem->at(2, 1) * localCoordinateSystem->at(3, 2) -
             localCoordinateSystem->at(3, 1) * localCoordinateSystem->at(2, 2) );
        localCoordinateSystem->at(2, 3) =
            ( localCoordinateSystem->at(3, 1) * localCoordinateSystem->at(1, 2) -
             localCoordinateSystem->at(1, 1) * localCoordinateSystem->at(3, 2) );
        localCoordinateSystem->at(3, 3) =
            ( localCoordinateSystem->at(1, 1) * localCoordinateSystem->at(2, 2) -
             localCoordinateSystem->at(2, 1) * localCoordinateSystem->at(1, 2) );
    }

    // try to read ElementCS section
    if ( cs_type == unknownCS ) {
        triplets.clear();
        IR_GIVE_OPTIONAL_FIELD(ir, triplets, _IFT_OrthotropicLinearElasticMaterial_scs); // cs for shells.
        // first three numbers are direction of normal n - see orthoelasticmaterial.h for description
        // shellCS  - coordinate system of principal axes is specified in shell  coordinate system
        //            this is defined as follows: principal z-axis is perpendicular to mid-section
        //            x-axis is perpendicular to z-axis and normal to user specified vector n.
        //            (so x-axis is parallel to plane, with n beeing normal to this plane).
        //            y-axis is then perpendicular both to x and z axes.
        //            WARNING: this definition of cs is valid only for plates and shells
        //            when vector n is paralel to z-axis an error occurs and program is terminated.
        //
        size = triplets.giveSize();
        if ( !( ( size == 0 ) || ( size == 3 ) ) ) {
            OOFEM_WARNING("scs in material %d is not properly defined, will be assumed as global",
                      this->giveNumber() );
        }

        if ( size == 3 ) {
            cs_type = shellCS;
            triplets.normalize();
            helpPlaneNormal = new FloatArray(triplets);

            //
            // store normal defining help plane into row matrix
            // localCoordinateSystemmust be computed on demand from specific element
            //
        }
    } //

    if ( cs_type == unknownCS ) {
        //
        // if no cs defined assume global one
        //
        cs_type = localCS;
        localCoordinateSystem = new FloatMatrix(3, 3);
        localCoordinateSystem->beUnitMatrix();
    }

    return IRRT_OK;
}