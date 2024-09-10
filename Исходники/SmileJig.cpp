void
createSmiley()
{
    AcGePoint3d cen;
    struct resbuf rbFrom, rbTo;

    ads_getpoint( NULL, "\nCenter point: ", asDblArray( cen ));

    rbFrom.restype = RTSHORT;
    rbFrom.resval.rint = 1; // from UCS
    rbTo.restype = RTSHORT;
    rbTo.resval.rint = 0; // to WCS

    ads_trans( asDblArray( cen ), &rbFrom, &rbTo, Adesk::kFalse, asDblArray( cen ));

    AcGeVector3d x = acdbHostApplicationServices()->workingDatabase()->ucsxdir();
    AcGeVector3d y = acdbHostApplicationServices()->workingDatabase()->ucsydir();

    AcGeVector3d normalVec = x.crossProduct( y );
    normalVec.normalize();

    SmileyJig jig( cen, normalVec );

    jig.start();
}