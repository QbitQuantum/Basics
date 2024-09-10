static int GCol_TextChanged(GGadget *g, GEvent *e) {
    if ( e->type==et_controlevent && e->u.control.subtype == et_textchanged ) {
	struct gcol_data *d = GDrawGetUserData(GGadgetGetWindow(g));
	double *offs[7] = { &d->col.h, &d->col.s, &d->col.v, &d->col.r, &d->col.g, &d->col.b, &d->col.alpha };
	int i, err = false;
	int low, high;
	double val;
	char text[50];

	if ( GGadgetGetCid(g)==CID_Alpha ) {
	    low = 3; high=7;
	    /* Didn't actually change the rgb values, but parse them */
	    /*  This is in case we need to clear the error flag */
	    d->col.hsv = false;
	    d->col.rgb = true;
	} else if ( GGadgetGetCid(g)>=CID_Hue ) {
	    low = 0; high=3;
	    d->col.hsv = true;
	    d->col.rgb = false;
	} else {
	    low = 3; high=6;
	    d->col.hsv = false;
	    d->col.rgb = true;
	}
	for ( i=low; i<high; ++i ) {
	    val = GetCalmReal8(d->gw,cids[i],_(labnames[i]),&err);
	    if ( err )
	break;
	    if ( i==0 ) {
		val = fmod(val,360);
		if ( val<0 ) val += 360;
	    } else {
		if ( val<0 || val>1 ) {
		    err = true;
	break;
		}
	    }
	    *offs[i] = val;
	}
	if ( err ) {
	    d->col.hsv = d->col.rgb = false;
	} else if ( d->col.hsv ) {
	    gHSV2RGB((struct hslrgb *) &d->col);
	    for ( i=3; i<6; ++i ) {
		sprintf( text, "%.2f", *offs[i]);
		GGadgetSetTitle8(GWidgetGetControl(d->gw,cids[i]),text);
	    }
	} else {
	    gRGB2HSV((struct hslrgb *) &d->col);
	    sprintf( text, "%3.0f", *offs[0]);
	    GGadgetSetTitle8(GWidgetGetControl(d->gw,cids[0]),text);
	    for ( i=1; i<3; ++i ) {
		sprintf( text, "%.2f", *offs[i]);
		GGadgetSetTitle8(GWidgetGetControl(d->gw,cids[i]),text);
	    }
	}
	GDrawRequestExpose(d->wheelw,NULL,false);
	GDrawRequestExpose(d->gradw,NULL,false);
	GDrawRequestExpose(d->colw,NULL,false);
    }
return( true );
}