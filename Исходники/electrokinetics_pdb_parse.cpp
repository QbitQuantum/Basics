int populate_lattice(particle_data* atom_data) {
  /*
   * This routine will populate the lattice using the
   * values read from the pdb and itp files.
   * WARNING: It contains much logic and interpolation stuff!
   */
#ifdef DEBUG
  printf("pdb_n_particles=%u, itp_n_particles=%u, itp_n_parameters=%u\n",atom_data->pdb_n_particles,atom_data->itp_n_particles,atom_data->itp_n_parameters);
#endif
  // TODO: Check if bounding box fits into simbox
  bounding_box bbox;
  calculate_bounding_box(&bbox, atom_data);

  // calculate the shift of the bounding box
  float shift[3];
  shift[0] = ek_parameters.agrid / 2.0 * ek_parameters.dim_x - bbox.center[0];
  shift[1] = ek_parameters.agrid / 2.0 * ek_parameters.dim_y - bbox.center[1];
  shift[2] = ek_parameters.agrid / 2.0 * ek_parameters.dim_z - bbox.center[2];

#ifdef DEBUG
  printf("bbox.max_x=%f, bbox.max_y=%f, bbox.max_z=%f, bbox.min_x=%f, bbox.min_y=%f, bbox.min_z=%f, bbox->center=[%f; %f; %f]\n", bbox.max_x, bbox.max_y, bbox.max_z, bbox.min_x, bbox.min_y, bbox.min_z, bbox.center[0], bbox.center[1], bbox.center[2]);
  printf("agrid=%f, dim_x=%d, dim_y=%d, dim_z=%d\n",ek_parameters.agrid, ek_parameters.dim_x, ek_parameters.dim_y, ek_parameters.dim_z);
  printf("shift=[%f; %f; %f]\n",shift[0], shift[1], shift[2]);
#endif

  // joining the array
  int lowernode[3];
  float cellpos[3];
  float gridpos;
  float a_x_shifted, a_y_shifted, a_z_shifted;

  for (unsigned int i = 0; i <= atom_data->pdb_n_particles-1; i++) {
    pdb_ATOM* a = &atom_data->pdb_array_ATOM[i];
    itp_atoms* b;
    itp_atomtypes* c;
    for (unsigned int j = 0; j <= atom_data->itp_n_particles-1; j++) {
      b = &atom_data->itp_array_atoms[j];
      if (a->i == b->i) {
        for (unsigned int k = 0; k <= atom_data->itp_n_parameters-1; k++) {
          c = &atom_data->itp_array_atomtypes[k];
          if (strcmp(b->type,c->type) == 0) {
#ifdef DEBUG
            printf("i=%d x=%f y=%f z=%f type=%s charge=%f sigma=%f epsilon=%f\n",a->i,a->x,a->y,a->z,b->type,b->charge,c->sigma,c->epsilon);
#endif

            // Interpolate the charge to the lattice
            gridpos      = (a->x + shift[0]) / ek_parameters.agrid - 0.5f;
            lowernode[0] = (int) floorf( gridpos );
            cellpos[0]   = gridpos - lowernode[0];
                                                
            gridpos      = (a->y + shift[1]) / ek_parameters.agrid - 0.5f;
            lowernode[1] = (int) floorf( gridpos );
            cellpos[1]   = gridpos - lowernode[1];
                                                
            gridpos      = (a->z + shift[2]) / ek_parameters.agrid - 0.5f;
            lowernode[2] = (int) floorf( gridpos );
            cellpos[2]   = gridpos - lowernode[2];
                                                
            lowernode[0] = (lowernode[0] + ek_parameters.dim_x) % ek_parameters.dim_x;
            lowernode[1] = (lowernode[1] + ek_parameters.dim_y) % ek_parameters.dim_y;
            lowernode[2] = (lowernode[2] + ek_parameters.dim_z) % ek_parameters.dim_z;

            pdb_charge_lattice[pdb_rhoindex_cartesian2linear( lowernode[0],lowernode[1],lowernode[2] )]
              += b->charge * ( 1 - cellpos[0] ) * ( 1 - cellpos[1] ) * ( 1 - cellpos[2] );

            pdb_charge_lattice[pdb_rhoindex_cartesian2linear( ( lowernode[0] + 1 ) % ek_parameters.dim_x,lowernode[1],lowernode[2] )]
              += b->charge * cellpos[0] * ( 1 - cellpos[1] ) * ( 1 - cellpos[2] );

            pdb_charge_lattice[pdb_rhoindex_cartesian2linear( lowernode[0],( lowernode[1] + 1 ) % ek_parameters.dim_y,lowernode[2] )]
              += b->charge * ( 1 - cellpos[0] ) * cellpos[1] * ( 1 - cellpos[2] );

            pdb_charge_lattice[pdb_rhoindex_cartesian2linear( lowernode[0],lowernode[1],( lowernode[2] + 1 ) % ek_parameters.dim_z )]
              += b->charge * ( 1 - cellpos[0] ) * ( 1 - cellpos[1] ) * cellpos[2];

            pdb_charge_lattice[pdb_rhoindex_cartesian2linear( ( lowernode[0] + 1 ) % ek_parameters.dim_x,( lowernode[1] + 1 ) % ek_parameters.dim_y,lowernode[2] )]
              += b->charge * cellpos[0] * cellpos[1] * ( 1 - cellpos[2] );

            pdb_charge_lattice[pdb_rhoindex_cartesian2linear( ( lowernode[0] + 1 ) % ek_parameters.dim_x,lowernode[1],( lowernode[2] + 1 ) % ek_parameters.dim_z )]
              += b->charge * cellpos[0] * ( 1 - cellpos[1] ) * cellpos[2];

            pdb_charge_lattice[pdb_rhoindex_cartesian2linear( lowernode[0],( lowernode[1] + 1 ) % ek_parameters.dim_y,( lowernode[2] + 1 ) % ek_parameters.dim_z )]
              += b->charge * ( 1 - cellpos[0] ) * cellpos[1] * cellpos[2];

            pdb_charge_lattice[pdb_rhoindex_cartesian2linear( ( lowernode[0] + 1 ) % ek_parameters.dim_x,( lowernode[1] + 1 ) % ek_parameters.dim_y,( lowernode[2] + 1 ) % ek_parameters.dim_z )]
              += b->charge * cellpos[0] * cellpos[1] * cellpos[2];
            // Interpolate lennard-jones parameters to boundary
            float r = pow(2,1./6.)*c->sigma;

            a_x_shifted = (a->x + shift[0]) / ek_parameters.agrid - 0.5f;
            a_y_shifted = (a->y + shift[1]) / ek_parameters.agrid - 0.5f;
            a_z_shifted = (a->z + shift[2]) / ek_parameters.agrid - 0.5f;

            for (float z = a->z - r; z <= a->z + r + ek_parameters.agrid; z += ek_parameters.agrid) {
              for (float y = a->y - r; y <= a->y + r + ek_parameters.agrid; y += ek_parameters.agrid) {
                for (float x = a->x - r; x <= a->x + r + ek_parameters.agrid; x += ek_parameters.agrid) {
                  gridpos      = (x + shift[0]) / ek_parameters.agrid - 0.5f;
                  lowernode[0] = (int) floorf( gridpos );

                  gridpos      = (y + shift[1]) / ek_parameters.agrid - 0.5f;
                  lowernode[1] = (int) floorf( gridpos );

                  gridpos      = (z + shift[2]) / ek_parameters.agrid - 0.5f;
                  lowernode[2] = (int) floorf( gridpos );

                  lowernode[0] = (lowernode[0] + ek_parameters.dim_x) % ek_parameters.dim_x;
                  lowernode[1] = (lowernode[1] + ek_parameters.dim_y) % ek_parameters.dim_y;
                  lowernode[2] = (lowernode[2] + ek_parameters.dim_z) % ek_parameters.dim_z;
#ifdef DEBUG
                  printf("shifted: %f %f %f\n", a_x_shifted, a_y_shifted, a_z_shifted);
                  printf("lowernode: %d %d %d\n", lowernode[0], lowernode[1], lowernode[2]);
                  printf("distance: %f %f %f\n", lowernode[0] - a_x_shifted, lowernode[1] - a_y_shifted, lowernode[2] - a_z_shifted);
                  printf("distance: %f <= %f\n\n", pow(lowernode[0] - a_x_shifted,2) + pow(lowernode[1] - a_y_shifted,2) + pow(lowernode[2] - a_z_shifted,2), pow(r/ek_parameters.agrid,2));
#endif
                  if ( pow(lowernode[0] - a_x_shifted,2) + pow(lowernode[1] - a_y_shifted,2) + pow(lowernode[2] - a_z_shifted,2) <= pow(r/ek_parameters.agrid,2) ) {
                    pdb_boundary_lattice[ek_parameters.dim_y*ek_parameters.dim_x*lowernode[2] + ek_parameters.dim_x*lowernode[1] + lowernode[0]] = 1;
                  }
                }
              }
            }

            break;
          }
        }
      }
    }
  }

  return pdb_SUCCESS;
}