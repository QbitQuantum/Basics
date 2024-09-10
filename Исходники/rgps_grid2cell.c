static void rgps_grid2cell(char *line, rgps_grid_t *grid, int nGrids, 
  rgps_cell_t *cell, int nCells, dbf_header_t *dbf, FILE *fpOut)
{
  char **col;
  int ii, nCols, nCoords=0, cell_id=0, obs_year;
  double obs_time, x_disp, y_disp;

  // Extract information from line
  split_into_array(line, ',', &nCols, &col);
  for (ii=0; ii<nCols; ii++) {
    if (dbf[ii].format == CSV_STRING)
      dbf[ii].sValue = STRDUP(col[ii]);
    else if (dbf[ii].format == CSV_DOUBLE)
      dbf[ii].fValue = atof(col[ii]);
    else if (dbf[ii].format == CSV_INTEGER)
      dbf[ii].nValue = atoi(col[ii]);
    if (strcmp_case(dbf[ii].shape, "CELL_ID") == 0)
      cell_id = dbf[ii].nValue;
    else if (strcmp_case(dbf[ii].shape, "OBS_YEAR") == 0)
      obs_year = dbf[ii].nValue;
    else if (strcmp_case(dbf[ii].shape, "OBS_TIME") == 0) {
      obs_time = dbf[ii].fValue;
      if (obs_year > grid[0].obs_year)
        obs_time += date_getDaysInYear(grid[0].obs_year);
    }
    else if (strcmp_case(dbf[ii].shape, "X_DISP") == 0)
      x_disp = dbf[ii].fValue;
    else if (strcmp_case(dbf[ii].shape, "Y_DISP") == 0)
      y_disp = dbf[ii].fValue;
  }
  free_char_array(&col, nCols);

  // Extract information from connectivity table
  int *grid_id = (int *) MALLOC(sizeof(int)*50);
  double *grid_order = (double *) MALLOC(sizeof(double)*50);
  size_t *p = (size_t *) MALLOC(sizeof(size_t)*50);
  for (ii=0; ii<nCells; ii++) {
    if (cell_id == cell[ii].cell_id) {
      grid_id[nCoords] = cell[ii].grid_id;
      grid_order[nCoords] = cell[ii].cell_id + (double) cell[ii].order / 100;
      nCoords++;
    }
  }
  gsl_sort_index(p, grid_order, 1, nCoords);
  double disp_mag = sqrt(x_disp*x_disp + y_disp*y_disp);

  // Extract grid information from motion product
  int kk, index;
  double diff, grid_time, birth_time, death_time;
  char image_id[30];
  char *tmp = (char *) MALLOC(sizeof(char)*25);
  char *coordStr = (char *) MALLOC(sizeof(char)*50*nCoords);
  strcpy(coordStr, "");
  for (kk=0; kk<nCoords; kk++) {
    index = -1;
    for (ii=0; ii<nGrids; ii++) {
      grid_time = grid[ii].obs_time;
      if (grid[ii].obs_year > grid[0].obs_year)
        grid_time += date_getDaysInYear(grid[0].obs_year);
      diff = fabs(grid_time - obs_time);
      if ((grid_id[p[kk]] == grid[ii].gpid) && (diff < 0.01)) {
        birth_time = grid[ii].birth_time;
        if (grid[ii].birth_year > grid[0].obs_year)
          birth_time += date_getDaysInYear(grid[0].obs_year);
        index = ii;
      }
    }
    if (index > 0 && birth_time <= grid_time) {
      sprintf(tmp, ",%.4f,%.4f", grid[index].x, grid[index].y);
      strcat(coordStr, tmp);
      strcpy(image_id, grid[index].image_id);
    }
  }

  // Check cell death time    
  int n, cell_death_year;
  double cell_death_time;
  split_into_array(line, ',', &n, &col);
  for (ii=0; ii<nCells; ii++) {
    if (cell[ii].cell_id == atoi(col[0])) {
      cell_death_time = death_time = cell[ii].death_time;
      cell_death_year = cell[ii].death_year;
      if (cell[ii].death_year > cell[0].birth_year)
        death_time += date_getDaysInYear(cell[0].birth_year);
      if (cell[ii].death_year == -1)
        death_time = -1;
    }
  }
  if (death_time < 0 || obs_time < (death_time + 0.01)) {
    fprintf(fpOut, "%.6f,%s,%s,%s", obs_time, col[0], col[1], col[2]);
    fprintf(fpOut, ",%s,%d,%.6f", col[3], cell_death_year, cell_death_time);
    for (kk=4; kk<n; kk++)
      fprintf(fpOut, ",%s", col[kk]);
    fprintf(fpOut, ",%s,%.6f%s\n", image_id, disp_mag, coordStr);
  }
  free_char_array(&col, n);

  // Clean up
  FREE(grid_id);
  FREE(grid_order);
  FREE(p);
  FREE(tmp);
  FREE(coordStr);

  return;
}