const TIFFFieldInfo*
_TIFFFindFieldInfoByName(TIFF* tif, const char *field_name, TIFFDataType dt)
{
        TIFFFieldInfo key = {0, 0, 0, TIFF_NOTYPE, 0, 0, 0, 0};
	TIFFFieldInfo* pkey = &key;
	const TIFFFieldInfo **ret;

	if (tif->tif_foundfield
	    && streq(tif->tif_foundfield->field_name, field_name)
	    && (dt == TIFF_ANY || dt == tif->tif_foundfield->field_type))
		return (tif->tif_foundfield);

	/* If we are invoked with no field information, then just return. */
	if ( !tif->tif_fieldinfo ) {
		return NULL;
	}

	/* NB: use sorted search (e.g. binary search) */
        key.field_name = (char *)field_name;
        key.field_type = dt;

        ret = (const TIFFFieldInfo **) lfind(&pkey,
					     tif->tif_fieldinfo, 
					     &tif->tif_nfields,
					     sizeof(TIFFFieldInfo *),
					     tagNameCompare);
	return tif->tif_foundfield = (ret ? *ret : NULL);
}