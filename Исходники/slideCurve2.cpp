// COMPUTE ======================================
MStatus gear_slideCurve2::deform( MDataBlock& data, MItGeometry& iter, const MMatrix &mat, unsigned int mIndex )
{
    MStatus returnStatus;
	
    // Inputs ---------------------------------------------------------
    // Input NurbsCurve
	// Curve
	MFnNurbsCurve crv( data.inputValue( master_crv ).asNurbsCurve() );
    MMatrix m = data.inputValue(master_mat).asMatrix();
        
    // Input Sliders
    double in_sl = (double)data.inputValue(slave_length).asFloat();
    double in_ml = (double)data.inputValue(master_length).asFloat();
    double in_position = (double)data.inputValue(position).asFloat();
    double in_maxstretch = (double)data.inputValue(maxstretch).asFloat();
	double in_maxsquash = (double)data.inputValue(maxsquash).asFloat();
    double in_softness = (double)data.inputValue(softness).asFloat();
	
    // Init -----------------------------------------------------------
    double mstCrvLength = crv.length();

    int slvPointCount = iter.exactCount(); // Can we use .count() ? 
    int mstPointCount = crv.numCVs();
	
    // Stretch --------------------------------------------------------
	double expo = 1;
    if ((mstCrvLength > in_ml) && (in_maxstretch > 1)){
        if (in_softness != 0){
            double stretch = (mstCrvLength - in_ml) / (in_sl * in_maxstretch);
            expo = 1 - exp(-(stretch) / in_softness);
		}

        double ext = min(in_sl * (in_maxstretch - 1) * expo, mstCrvLength - in_ml);

        in_sl += ext;
	}
    else if ((mstCrvLength < in_ml) && (in_maxsquash < 1)){
        if (in_softness != 0){
            double squash = (in_ml - mstCrvLength) / (in_sl * in_maxsquash);
            expo = 1 - exp(-(squash) / in_softness);
		}

        double ext = min(in_sl * (1 - in_maxsquash) * expo, in_ml - mstCrvLength);

        in_sl -= ext;
	}
		
    // Position --------------------------------------------------------
    double size = in_sl / mstCrvLength;
    double sizeLeft = 1 - size;

    double start = in_position * sizeLeft;
    double end = start + size;

	double tStart, tEnd;
	crv.getKnotDomain(tStart, tEnd);
	
    // Process --------------------------------------------------------
    double step = (end - start) / (slvPointCount - 1.0);
    MPoint pt;
	MVector tan;
    while (! iter.isDone()){
        double perc = start + (iter.index() * step);

        double u = crv.findParamFromLength(perc * mstCrvLength);

        if ((0 <= perc) && (perc <= 1))
            crv.getPointAtParam(u, pt, MSpace::kWorld);
        else{
			double overPerc;
            if (perc < 0){
                overPerc = perc;
                crv.getPointAtParam(0, pt, MSpace::kWorld);
                tan = crv.tangent(0);
			}
            else{
                overPerc = perc - 1;
                crv.getPointAtParam(mstPointCount-3.0, pt, MSpace::kWorld);
                tan = crv.tangent(mstPointCount-3.0);

            tan.normalize();
            tan *= mstCrvLength * overPerc;

            pt += tan;
			}
		}

        pt *= mat.inverse();
        pt *= m;
        iter.setPosition(pt);
        iter.next();
	}
 
    return MS::kSuccess;
}