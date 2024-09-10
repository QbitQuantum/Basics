char getFilterData(int tile, int read, int cycle, int region)
{
	int itile, i, cycleLength=0, totalCycleLength=0;
	void *pitile;
	for (i=0; i < read; i++) cycleLength += _hdr->readLength[i];
	for (i=0; i < _hdr->nreads; i++) totalCycleLength += _hdr->readLength[i];
	size_t nelem = _hdr->ntiles;
	pitile = lfind(&tile, _hdr->tileArray, &nelem, sizeof(int), &keyComp);
	if (!pitile) return 0;	// if tile not found in filter
	itile = ((int*)pitile - _hdr->tileArray);
	return filterData[ (itile * totalCycleLength * _hdr->nregions) + ((cycleLength + cycle) * _hdr->nregions) + region];
}