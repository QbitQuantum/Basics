Adesk::Boolean
AsdkTextStyleSamp::worldDraw(AcGiWorldDraw* pW)
{
    AcGePoint3d pos(4.0, 4.0, 0.0);
    AcGeVector3d norm(0.0, 0.0, 1.0);
    AcGeVector3d dir(-1.0, -0.2, 0.0);
    char *pStr = "This is a percent, '%%%'.";
    int len = strlen(pStr);
    AcGiTextStyle style;

    AcGeVector3d vec = norm;
    vec = vec.crossProduct(dir);
    dir = vec.crossProduct(norm);

    style.setFileName("txt.shx");
    style.setBigFontFileName("");
    int status;
    if (!((status = style.loadStyleRec()) & 1))
        pStr = "Font not found.";

    pW->geometry().text(pos, norm, dir, pStr, len,
        Adesk::kFalse, style);

    pos.y += 2.0;

    style.setTrackingPercent(0.8); 
	style.setObliquingAngle(0.5);

    AcGePoint2d ext = style.extents(pStr, Adesk::kFalse,
        strlen(pStr), Adesk::kFalse);

    pW->geometry().text(pos, norm, dir, pStr, len,
        Adesk::kFalse, style);

    // Draw a rectangle around the last text drawn.
    // First you have to create a polyline the size of the
    // bounding box, then you have to transform it to the
    // correct orientation, and then to the location of the
    // text.
    
    // Compute the matrix that orients the box.
    //
    AcGeMatrix3d textMat;
    norm.normalize();
    dir.normalize();
    AcGeVector3d yAxis = norm;
    yAxis = yAxis.crossProduct(dir);
    yAxis.normalize();
    textMat.setCoordSystem(AcGePoint3d(0.0, 0.0, 0.0), dir,
        yAxis, norm);

    // Create the bounding box and enlarge it somewhat.
    //
    double offset = ext.y / 2.0;
    AcGePoint3d verts[5];
    verts[0] = verts[4] = AcGePoint3d(-offset, -offset, 0.0);
    verts[1] = AcGePoint3d(ext.x + offset, -offset, 0.0);
    verts[2] = AcGePoint3d(ext.x + offset, ext.y + offset, 0.0);
    verts[3] = AcGePoint3d(-offset, ext.y + offset, 0.0);

    // Orient and then translate each point in the
    // bounding box.
    //
    for (int i = 0; i < 5; i++) {
        verts[i].transformBy(textMat);
        verts[i].x += pos.x;
        verts[i].y += pos.y;
        verts[i].z += pos.z;
    }
    pW->geometry().polyline(5, verts);

    return Adesk::kTrue;
}