/*------------------------------------------------------------------------
 * move_pu - move pen up function.
 *
 *  input: lat, lon - beginning of a new segment
 *
 * result: previous segment is written, a new segment index entry is started,
 *         and the map is recentered.
 *
 * return: FALSE on success
 *         TRUE if fatal error occurs (unabel to allocate enough memory)
 *------------------------------------------------------------------------*/
 int move_pu(double lat, double lon)
{
  double nlon;

/*
 *	write current segment
 */

  if (dest->npoints > 0) write_segment_data(dest->seg_count);
    
/*
 *	make sure index is big enough
 */
  if (dest->seg_count >= max_index_entries)
  { max_index_entries += 1000;
    dest->index = 
      (cdb_index_entry *) realloc(dest->index, 
				  sizeof(cdb_index_entry) *  max_index_entries);
    if(NULL == dest->index)
    {
      fprintf(stderr,"move_pu: Unable to allocate %d index entries\n", 
	      max_index_entries);
      return -1;
    }
    if (verbose) fprintf(stderr,">allocating %d index entries.\n",
			 max_index_entries);
  }


/*
 *	start a new segment
 */
  dest->index[dest->seg_count].ID = dest->seg_count;
  dest->index[dest->seg_count].ilat0 = nint(lat/CDB_LAT_SCALE);
  nlon = lon;
  NORMALIZE(nlon);
  dest->index[dest->seg_count].ilon0 = nint(nlon/CDB_LON_SCALE);
  dest->index[dest->seg_count].ilat_max = dest->index[dest->seg_count].ilat0;
  dest->index[dest->seg_count].ilon_max = dest->index[dest->seg_count].ilon0;
  dest->index[dest->seg_count].ilat_min = dest->index[dest->seg_count].ilat0;
  dest->index[dest->seg_count].ilon_min = dest->index[dest->seg_count].ilon0;

/*
 * recenter map
 */

  map->center_lat = lat;
  map->center_lon = nlon;
  map->lat0 = lat;
  map->lon0 = nlon;
  reinit_mapx(map);
  dest->npoints = 0;
  if (very_very_verbose)fprintf(stderr,">>> recentered map to %lf %lf.\n",
				map->lat0,  map->lon0);
  return 0;
  }