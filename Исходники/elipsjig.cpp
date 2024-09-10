// This function uses the AcEdJig mechanism to create and
// drag an ellipse entity.  The creation criteria are
// slightly different from the AutoCAD command.  In this
// case, the user selects an ellipse center point and then,
// drags to visually select the major and minor axes
// lengths.  This sample is somewhat limited; if the
// minor axis ends up longer than the major axis, then the
// ellipse will just be round because the radius ratio
// cannot be greater than 1.0.
//
void
createEllipse()
{
    // First, have the user select the ellipse center point.
    // We don't use the jig for this because there is
    // nothing to see yet.
    //
    AcGePoint3d tempPt;
    struct resbuf rbFrom, rbTo;

    acedGetPoint(NULL, _T("\nEllipse center point: "),
        asDblArray(tempPt));

    // The point we just got is in UCS coordinates, but
    // AcDbEllipse works in WCS, so convert the point.
    //
    rbFrom.restype = RTSHORT;
    rbFrom.resval.rint = 1; // from UCS
    rbTo.restype = RTSHORT;
    rbTo.resval.rint = 0; // to WCS

    acedTrans(asDblArray(tempPt), &rbFrom, &rbTo,
        Adesk::kFalse, asDblArray(tempPt));

    // Now you need to get the current UCS z-Axis to be used
    // as the normal vector for the ellipse.
    //
    AcGeVector3d x = acdbHostApplicationServices()->workingDatabase()
                     ->ucsxdir();
    AcGeVector3d y = acdbHostApplicationServices()->workingDatabase()
                     ->ucsydir();
    AcGeVector3d normalVec = x.crossProduct(y);
    normalVec.normalize();

    // Create an AsdkEllipseJig object passing in the
    // center point just selected by the user and the normal
    // vector just calculated.
    //
    AsdkEllipseJig *pJig
        = new AsdkEllipseJig(tempPt, normalVec);

    // Now start up the jig to interactively get the major
    // and minor axes lengths.
    //
    pJig->doIt();

    // Now delete the jig object, since it is no longer needed.
    //
    delete pJig;
}