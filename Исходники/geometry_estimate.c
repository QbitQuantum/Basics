/**
 * This function is called by the analyze function iff
 * the geometry_analyze() function give it its pointer
 * (this is always the case so far).
 * The geometry_analyze() function is also responsible
 * of deciding the number of "sample" rows we will receive
 * here. It is able to give use other 'custom' data, but we
 * won't use them so far.
 *
 * Our job is to build some statistics on the sample data
 * for use by operator estimators.
 *
 * Currently we only need statistics to estimate the number of rows
 * overlapping a given extent (estimation function bound
 * to the && operator).
 *
 */
static void
compute_geometry_stats(VacAttrStats *stats, AnalyzeAttrFetchFunc fetchfunc,
                       int samplerows, double totalrows)
{
	MemoryContext old_context;
	int i;
	int geom_stats_size;
	GBOX **sampleboxes;
	GEOM_STATS *geomstats;
	bool isnull;
	int null_cnt=0, notnull_cnt=0, examinedsamples=0;
	GBOX *sample_extent=NULL;
	double total_width=0;
	double total_boxes_area=0;
	int total_boxes_cells=0;
	double cell_area;
	double cell_width;
	double cell_height;
#if USE_STANDARD_DEVIATION
	/* for standard deviation */
	double avgLOWx, avgLOWy, avgHIGx, avgHIGy;
	double sumLOWx=0, sumLOWy=0, sumHIGx=0, sumHIGy=0;
	double sdLOWx=0, sdLOWy=0, sdHIGx=0, sdHIGy=0;
	GBOX *newhistobox=NULL;
#endif
	double geow, geoh; /* width and height of histogram */
	int histocells;
	int cols, rows; /* histogram grid size */
	GBOX histobox;

	/*
	 * This is where geometry_analyze
	 * should put its' custom parameters.
	 */
	/* void *mystats = stats->extra_data; */

	/*
	 * We'll build an histogram having from 40 to 400 boxesPerSide
	 * Total number of cells is determined by attribute stat
	 * target. It can go from  1600 to 160000 (stat target: 10,1000)
	 */
	histocells = 160*stats->attr->attstattarget;


	POSTGIS_DEBUG(2, "compute_geometry_stats called");
	POSTGIS_DEBUGF(3, " samplerows: %d", samplerows);
	POSTGIS_DEBUGF(3, " histogram cells: %d", histocells);

	/*
	 * We might need less space, but don't think
	 * its worth saving...
	 */
	sampleboxes = palloc(sizeof(GBOX *)*samplerows);

	/*
	 * First scan:
	 *  o find extent of the sample rows
	 *  o count null-infinite/not-null values
	 *  o compute total_width
	 *  o compute total features's box area (for avgFeatureArea)
	 *  o sum features box coordinates (for standard deviation)
	 */
	for (i=0; i<samplerows; i++)
	{
		Datum datum;
		GSERIALIZED *geom;
		GBOX box;

		datum = fetchfunc(stats, i, &isnull);

		/*
		 * Skip nulls
		 */
		if ( isnull )
		{
			null_cnt++;
			continue;
		}

		geom = (GSERIALIZED *)PG_DETOAST_DATUM(datum);

		if ( LW_FAILURE == gserialized_datum_get_gbox_p(datum, &box) )
		{
			/* Skip empty geometry */
			POSTGIS_DEBUGF(3, " skipped empty geometry %d", i);

			continue;
		}

		/*
		 * Skip infinite geoms
		 */
		if ( ! finite(box.xmin) ||
		        ! finite(box.xmax) ||
		        ! finite(box.ymin) ||
		        ! finite(box.ymax) )
		{
			POSTGIS_DEBUGF(3, " skipped infinite geometry %d", i);

			continue;
		}

		/*
		 * Cache bounding box
		 * TODO: reduce BOX2DFLOAT4 copies
		 */
		sampleboxes[notnull_cnt] = palloc(sizeof(GBOX));
		memcpy(sampleboxes[notnull_cnt], &box, sizeof(GBOX));

		/*
		 * Add to sample extent union
		 */
		if ( ! sample_extent )
		{
			sample_extent = palloc(sizeof(GBOX));
			memcpy(sample_extent, &box, sizeof(GBOX));
		}
		else
		{
			sample_extent->xmax = Max(sample_extent->xmax,
			                                  box.xmax);
			sample_extent->ymax = Max(sample_extent->ymax,
			                                  box.ymax);
			sample_extent->xmin = Min(sample_extent->xmin,
			                                  box.xmin);
			sample_extent->ymin = Min(sample_extent->ymin,
			                                  box.ymin);
		}

		/** TODO: ask if we need geom or bvol size for stawidth */
		total_width += geom->size;
		total_boxes_area += (box.xmax-box.xmin)*(box.ymax-box.ymin);

#if USE_STANDARD_DEVIATION
		/*
		 * Add bvol coordinates to sum for standard deviation
		 * computation.
		 */
		sumLOWx += box.xmin;
		sumLOWy += box.ymin;
		sumHIGx += box.xmax;
		sumHIGy += box.ymax;
#endif

		notnull_cnt++;

		/* give backend a chance of interrupting us */
		vacuum_delay_point();

	}

	if ( ! notnull_cnt )
	{
		elog(NOTICE, " no notnull values, invalid stats");
		stats->stats_valid = false;
		return;
	}

#if USE_STANDARD_DEVIATION

	POSTGIS_DEBUGF(3, " sample_extent: xmin,ymin: %f,%f",
	               sample_extent->xmin, sample_extent->ymin);
	POSTGIS_DEBUGF(3, " sample_extent: xmax,ymax: %f,%f",
	               sample_extent->xmax, sample_extent->ymax);

	/*
	 * Second scan:
	 *  o compute standard deviation
	 */
	avgLOWx = sumLOWx/notnull_cnt;
	avgLOWy = sumLOWy/notnull_cnt;
	avgHIGx = sumHIGx/notnull_cnt;
	avgHIGy = sumHIGy/notnull_cnt;
	for (i=0; i<notnull_cnt; i++)
	{
		GBOX *box;
		box = (GBOX *)sampleboxes[i];

		sdLOWx += (box->xmin - avgLOWx) * (box->xmin - avgLOWx);
		sdLOWy += (box->ymin - avgLOWy) * (box->ymin - avgLOWy);
		sdHIGx += (box->xmax - avgHIGx) * (box->xmax - avgHIGx);
		sdHIGy += (box->ymax - avgHIGy) * (box->ymax - avgHIGy);
	}
	sdLOWx = sqrt(sdLOWx/notnull_cnt);
	sdLOWy = sqrt(sdLOWy/notnull_cnt);
	sdHIGx = sqrt(sdHIGx/notnull_cnt);
	sdHIGy = sqrt(sdHIGy/notnull_cnt);

	POSTGIS_DEBUG(3, " standard deviations:");
	POSTGIS_DEBUGF(3, "  LOWx - avg:%f sd:%f", avgLOWx, sdLOWx);
	POSTGIS_DEBUGF(3, "  LOWy - avg:%f sd:%f", avgLOWy, sdLOWy);
	POSTGIS_DEBUGF(3, "  HIGx - avg:%f sd:%f", avgHIGx, sdHIGx);
	POSTGIS_DEBUGF(3, "  HIGy - avg:%f sd:%f", avgHIGy, sdHIGy);

	histobox.xmin = Max((avgLOWx - SDFACTOR * sdLOWx),
	                       sample_extent->xmin);
	histobox.ymin = Max((avgLOWy - SDFACTOR * sdLOWy),
	                       sample_extent->ymin);
	histobox.xmax = Min((avgHIGx + SDFACTOR * sdHIGx),
	                       sample_extent->xmax);
	histobox.ymax = Min((avgHIGy + SDFACTOR * sdHIGy),
	                       sample_extent->ymax);

	POSTGIS_DEBUGF(3, " sd_extent: xmin,ymin: %f,%f",
	               histobox.xmin, histobox.ymin);
	POSTGIS_DEBUGF(3, " sd_extent: xmax,ymax: %f,%f",
	               histobox.xmin, histobox.ymax);

	/*
	 * Third scan:
	 *   o skip hard deviants
	 *   o compute new histogram box
	 */
	for (i=0; i<notnull_cnt; i++)
	{
		GBOX *box;
		box = (GBOX *)sampleboxes[i];

		if ( box->xmin > histobox.xmax ||
		        box->xmax < histobox.xmin ||
		        box->ymin > histobox.ymax ||
		        box->ymax < histobox.ymin )
		{
			POSTGIS_DEBUGF(4, " feat %d is an hard deviant, skipped", i);

			sampleboxes[i] = NULL;
			continue;
		}
		if ( ! newhistobox )
		{
			newhistobox = palloc(sizeof(GBOX));
			memcpy(newhistobox, box, sizeof(GBOX));
		}
		else
		{
			if ( box->xmin < newhistobox->xmin )
				newhistobox->xmin = box->xmin;
			if ( box->ymin < newhistobox->ymin )
				newhistobox->ymin = box->ymin;
			if ( box->xmax > newhistobox->xmax )
				newhistobox->xmax = box->xmax;
			if ( box->ymax > newhistobox->ymax )
				newhistobox->ymax = box->ymax;
		}
	}

	/*
	 * Set histogram extent as the intersection between
	 * standard deviation based histogram extent
	 * and computed sample extent after removal of
	 * hard deviants (there might be no hard deviants).
	 */
	if ( histobox.xmin < newhistobox->xmin )
		histobox.xmin = newhistobox->xmin;
	if ( histobox.ymin < newhistobox->ymin )
		histobox.ymin = newhistobox->ymin;
	if ( histobox.xmax > newhistobox->xmax )
		histobox.xmax = newhistobox->xmax;
	if ( histobox.ymax > newhistobox->ymax )
		histobox.ymax = newhistobox->ymax;


#else /* ! USE_STANDARD_DEVIATION */

	/*
	* Set histogram extent box
	*/
	histobox.xmin = sample_extent->xmin;
	histobox.ymin = sample_extent->ymin;
	histobox.xmax = sample_extent->xmax;
	histobox.ymax = sample_extent->ymax;
#endif /* USE_STANDARD_DEVIATION */


	POSTGIS_DEBUGF(3, " histogram_extent: xmin,ymin: %f,%f",
	               histobox.xmin, histobox.ymin);
	POSTGIS_DEBUGF(3, " histogram_extent: xmax,ymax: %f,%f",
	               histobox.xmax, histobox.ymax);


	geow = histobox.xmax - histobox.xmin;
	geoh = histobox.ymax - histobox.ymin;

	/*
	 * Compute histogram cols and rows based on aspect ratio
	 * of histogram extent
	 */
	if ( ! geow && ! geoh )
	{
		cols = 1;
		rows = 1;
		histocells = 1;
	}
	else if ( ! geow )
	{
		cols = 1;
		rows = histocells;
	}
	else if ( ! geoh )
	{
		cols = histocells;
		rows = 1;
	}
	else
	{
		if ( geow<geoh)
		{
			cols = ceil(sqrt((double)histocells*(geow/geoh)));
			rows = ceil((double)histocells/cols);
		}
		else
		{
			rows = ceil(sqrt((double)histocells*(geoh/geow)));
			cols = ceil((double)histocells/rows);
		}
		histocells = cols*rows;
	}

	POSTGIS_DEBUGF(3, " computed histogram grid size (CxR): %dx%d (%d cells)", cols, rows, histocells);


	/*
	 * Create the histogram (GEOM_STATS)
	 */
	old_context = MemoryContextSwitchTo(stats->anl_context);
	geom_stats_size=sizeof(GEOM_STATS)+(histocells-1)*sizeof(float4);
	geomstats = palloc(geom_stats_size);
	MemoryContextSwitchTo(old_context);

	geomstats->avgFeatureArea = total_boxes_area/notnull_cnt;
	geomstats->xmin = histobox.xmin;
	geomstats->ymin = histobox.ymin;
	geomstats->xmax = histobox.xmax;
	geomstats->ymax = histobox.ymax;
	geomstats->cols = cols;
	geomstats->rows = rows;

	/* Initialize all values to 0 */
	for (i=0; i<histocells; i++) geomstats->value[i] = 0;

	cell_width = geow/cols;
	cell_height = geoh/rows;
	cell_area = cell_width*cell_height;

	POSTGIS_DEBUGF(4, "cell_width: %f", cell_width);
	POSTGIS_DEBUGF(4, "cell_height: %f", cell_height);


	/*
	 * Fourth scan:
	 *  o fill histogram values with the number of
	 *    features' bbox overlaps: a feature's bvol
	 *    can fully overlap (1) or partially overlap
	 *    (fraction of 1) an histogram cell.
	 *
	 *  o compute total cells occupation
	 *
	 */
	for (i=0; i<notnull_cnt; i++)
	{
		GBOX *box;
		int x_idx_min, x_idx_max, x;
		int y_idx_min, y_idx_max, y;
		int numcells=0;

		box = (GBOX *)sampleboxes[i];
		if ( ! box ) continue; /* hard deviant.. */

		/* give backend a chance of interrupting us */
		vacuum_delay_point();

		POSTGIS_DEBUGF(4, " feat %d box is %f %f, %f %f",
		               i, box->xmax, box->ymax,
		               box->xmin, box->ymin);

		/* Find first overlapping column */
		x_idx_min = (box->xmin-geomstats->xmin) / geow * cols;
		if (x_idx_min <0) x_idx_min = 0;
		if (x_idx_min >= cols) x_idx_min = cols-1;

		/* Find first overlapping row */
		y_idx_min = (box->ymin-geomstats->ymin) / geoh * rows;
		if (y_idx_min <0) y_idx_min = 0;
		if (y_idx_min >= rows) y_idx_min = rows-1;

		/* Find last overlapping column */
		x_idx_max = (box->xmax-geomstats->xmin) / geow * cols;
		if (x_idx_max <0) x_idx_max = 0;
		if (x_idx_max >= cols ) x_idx_max = cols-1;

		/* Find last overlapping row */
		y_idx_max = (box->ymax-geomstats->ymin) / geoh * rows;
		if (y_idx_max <0) y_idx_max = 0;
		if (y_idx_max >= rows) y_idx_max = rows-1;

		POSTGIS_DEBUGF(4, " feat %d overlaps columns %d-%d, rows %d-%d",
		               i, x_idx_min, x_idx_max, y_idx_min, y_idx_max);

		/*
		 * the {x,y}_idx_{min,max}
		 * define the grid squares that the box intersects
		 */
		for (y=y_idx_min; y<=y_idx_max; y++)
		{
			for (x=x_idx_min; x<=x_idx_max; x++)
			{
				geomstats->value[x+y*cols] += 1;
				numcells++;
			}
		}

		/*
		 * before adding to the total cells
		 * we could decide if we really
		 * want this feature to count
		 */
		total_boxes_cells += numcells;

		examinedsamples++;
	}

	POSTGIS_DEBUGF(3, " examined_samples: %d/%d", examinedsamples, samplerows);

	if ( ! examinedsamples )
	{
		elog(NOTICE, " no examined values, invalid stats");
		stats->stats_valid = false;

		POSTGIS_DEBUG(3, " no stats have been gathered");

		return;
	}

	/** TODO: what about null features (TODO) */
	geomstats->avgFeatureCells = (float4)total_boxes_cells/examinedsamples;

	POSTGIS_DEBUGF(3, " histo: total_boxes_cells: %d", total_boxes_cells);
	POSTGIS_DEBUGF(3, " histo: avgFeatureArea: %f", geomstats->avgFeatureArea);
	POSTGIS_DEBUGF(3, " histo: avgFeatureCells: %f", geomstats->avgFeatureCells);


	/*
	 * Normalize histogram
	 *
	 * We divide each histogram cell value
	 * by the number of samples examined.
	 *
	 */
	for (i=0; i<histocells; i++)
		geomstats->value[i] /= examinedsamples;

	{
		int x, y;
		for (x=0; x<cols; x++)
		{
			for (y=0; y<rows; y++)
			{
				POSTGIS_DEBUGF(4, " histo[%d,%d] = %.15f", x, y, geomstats->value[x+y*cols]);
			}
		}
	}


	/*
	 * Write the statistics data
	 */
	stats->stakind[0] = STATISTIC_KIND_GEOMETRY;
	stats->staop[0] = InvalidOid;
	stats->stanumbers[0] = (float4 *)geomstats;
	stats->numnumbers[0] = geom_stats_size/sizeof(float4);

	stats->stanullfrac = (float4)null_cnt/samplerows;
	stats->stawidth = total_width/notnull_cnt;
	stats->stadistinct = -1.0;

	POSTGIS_DEBUGF(3, " out: slot 0: kind %d (STATISTIC_KIND_GEOMETRY)",
	               stats->stakind[0]);
	POSTGIS_DEBUGF(3, " out: slot 0: op %d (InvalidOid)", stats->staop[0]);
	POSTGIS_DEBUGF(3, " out: slot 0: numnumbers %d", stats->numnumbers[0]);
	POSTGIS_DEBUGF(3, " out: null fraction: %d/%d=%g", null_cnt, samplerows, stats->stanullfrac);
	POSTGIS_DEBUGF(3, " out: average width: %d bytes", stats->stawidth);
	POSTGIS_DEBUG(3, " out: distinct values: all (no check done)");

	stats->stats_valid = true;
}