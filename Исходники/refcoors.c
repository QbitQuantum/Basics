int32 refc_find_ref_coors_convex(FMField *ref_coors,
                                 int32 *cells, int32 n_cells,
                                 int32 *status, int32 n_status,
                                 FMField *coors,
                                 Mesh *mesh,
                                 FMField *centroids,
                                 FMField *normals0,
                                 FMField *normals1,
                                 int32 *ics, int32 n_ics,
                                 FMField *eref_coors,
                                 int32 *nodes, int32 n_nodes, int32 n_nodes_col,
                                 FMField *mtx_i,
                                 int32 allow_extrapolation,
                                 float64 close_limit, float64 qp_eps,
                                 int32 i_max, float64 newton_eps)
{
  int32 ip, ic, icell, icell_max = 0, ii, imin, ik, ok, ret = RET_OK;
  int32 xi_ok, hexa_reverse;
  int32 D = mesh->topology->max_dim;
  int32 dim = D - 1;
  int32 nc = mesh->geometry->dim;
  uint32 tri0[] = {0, 1, 3};
  uint32 tri1[] = {2, 3, 1};
  uint32 cell, cell0, cell00, facet;
  uint32 *noffs, *foffs, aux[2];
  uint32 *cell_types = mesh->topology->cell_types;
  float64 vmin, vmax, d_min, tmin, tt, dist;
  float64 *mesh_coors = mesh->geometry->coors;
  float64 buf3[3];
  float64 buf9[9];
  float64 buf_ec_max[8 * 3]; // Max. n_ep * dim.
  FMField point[1], centroid[1], _normals0[1], _normals1[1], e_coors[1], xi[1];
  FMField bc[1];
  Indices cell_vertices[1];
  MeshEntity cell_ent[1];
  MeshConnectivity *cD0 = 0; // D -> 0
  MeshConnectivity *c0D = 0; // 0 -> D
  MeshConnectivity *cDd = 0; // cell -> facet
  MeshConnectivity *cdD = 0; // facet -> cell
  MeshConnectivity *loc = 0;
  MeshConnectivity **locs = 0;

  mesh_setup_connectivity(mesh, D, 0);
  cD0 = mesh->topology->conn[IJ(D, D, 0)];

  mesh_setup_connectivity(mesh, 0, D);
  c0D = mesh->topology->conn[IJ(D, 0, D)];

  mesh_setup_connectivity(mesh, D, dim);
  cDd = mesh->topology->conn[IJ(D, D, dim)];
  noffs = cDd->offsets;

  mesh_setup_connectivity(mesh, dim, D);
  cdD = mesh->topology->conn[IJ(D, dim, D)];

  // Local entities - reference cell edges or faces.
  locs = (dim == 1) ? mesh->entities->edges : mesh->entities->faces;

  fmf_pretend_nc(point, coors->nRow, 1, 1, nc, coors->val);
  fmf_pretend_nc(centroid, centroids->nRow, 1, 1, nc, centroids->val);

  fmf_pretend_nc(xi, 1, 1, 1, nc, buf3);
  fmf_fillC(xi, 0.0);

  vmin = eref_coors->val[0];
  vmax = eref_coors->val[nc];

  for (ip = 0; ip < coors->nRow; ip++) {
    ic = ics[ip];
    /* output("***** %d %d\n", ip, ic); */

    FMF_SetCell(point, ip);
    /* fmf_print(point, stdout, 0); */

    cell = cell0 = cell00 = c0D->indices[c0D->offsets[ic]];

    ok = icell = hexa_reverse = imin = 0;
    d_min = 1e10;
    while (1) {
      /* output("*** %d %d %d\n", icell, cell, hexa_reverse); */
      FMF_SetCell(centroid, cell);
      /* fmf_print(centroid, stdout, 0); */

      cell_ent->ii = cell;
      me_get_incident2(cell_ent, cell_vertices, cD0);

      loc = locs[cell_types[cell]];
      foffs = loc->offsets;

      if (cell_types[cell] != 4) { // No hexahedron -> planar facet.
        fmf_pretend_nc(_normals0, noffs[cell+1] - noffs[cell], 1, 1, nc,
                       normals0->val + nc * noffs[cell]);

        tmin = 1e10;
        for (ii = 0; ii < loc->num; ii++) {
          FMF_SetCell(_normals0, ii);
          ik = loc->indices[foffs[ii]];

          _intersect_line_plane(&tt, centroid->val, point->val,
                                mesh_coors + nc * cell_vertices->indices[ik],
                                _normals0->val, nc);
          if ((tt >= -qp_eps) && (tt < (tmin + qp_eps))) {
            imin = ii;
            tmin = tt;
          }
        }

        if (tmin >= (1.0 - qp_eps)) {
          _get_cell_coors(e_coors, cell_vertices, mesh_coors, nc, buf_ec_max);
          /* fmf_print(e_coors, stdout, 0); */

          xi_ok = _get_xi_dist(&dist, xi,  cell_vertices->num, nc, D,
                               point, e_coors, eref_coors, bc,
                               nodes, n_nodes_col, mtx_i, vmin, vmax,
                               i_max, newton_eps);

          d_min = Min(dist, d_min);
          if (xi_ok && (dist < qp_eps)) {
            ok = 1;
          }
          break;
        }

      } else { // Hexahedron -> non-planar facet in general.
        fmf_pretend_nc(_normals0, noffs[cell+1] - noffs[cell], 1, 1, nc,
                       normals0->val + nc * noffs[cell]);
        fmf_pretend_nc(_normals1, noffs[cell+1] - noffs[cell], 1, 1, nc,
                       normals1->val + nc * noffs[cell]);
        for (ii = 0; ii < loc->num; ii++) {
          FMF_SetCell(_normals0, ii);
          _get_tri_coors(buf9, loc->indices, foffs[ii],
                         tri0, mesh_coors, cell_vertices->indices);
          _intersect_line_triangle(&tt, centroid->val, point->val,
                                   buf9, _normals0->val);
          if ((tt >= -qp_eps) && (tt < 1e10)) {
            ok = 2;
            imin = ii;
            if ((tt >= (1.0 - qp_eps)) || hexa_reverse) {
              _get_cell_coors(e_coors, cell_vertices, mesh_coors, nc,
                              buf_ec_max);

              xi_ok = _get_xi_dist(&dist, xi,  cell_vertices->num, nc, D,
                                   point, e_coors, eref_coors, bc,
                                   nodes, n_nodes_col, mtx_i, vmin, vmax,
                                   i_max, newton_eps);

              d_min = Min(dist, d_min);
              if (xi_ok && (dist < qp_eps)) {
                ok = 1;
              } else {
                hexa_reverse = 1;
              }
            }
            break;
          }

          FMF_SetCell(_normals1, ii);
          _get_tri_coors(buf9, loc->indices, foffs[ii],
                         tri1, mesh_coors, cell_vertices->indices);
          _intersect_line_triangle(&tt, centroid->val, point->val,
                                   buf9, _normals1->val);
          if ((tt >= -qp_eps) && (tt < 1e10)) {
            ok = 2;
            imin = ii;
            if ((tt >= (1.0 - qp_eps)) || hexa_reverse) {
              _get_cell_coors(e_coors, cell_vertices, mesh_coors, nc,
                              buf_ec_max);

              xi_ok = _get_xi_dist(&dist, xi,  cell_vertices->num, nc, D,
                                   point, e_coors, eref_coors, bc,
                                   nodes, n_nodes_col, mtx_i, vmin, vmax,
                                   i_max, newton_eps);

              d_min = Min(dist, d_min);
              if (xi_ok && (dist < qp_eps)) {
                ok = 1;
              } else {
                hexa_reverse = 1;
              }
            }
            break;
          }
        }
        if (ok == 1) {
          break;
        }
        if (ok == 0) {
          errput("cannot intersect bilinear faces!\n");
          ERR_CheckGo(ret);
        }
      }

      facet = cDd->indices[cDd->offsets[cell] + imin];
      if ((cdD->offsets[facet+1] - cdD->offsets[facet]) == 2) {
        aux[0] = cdD->indices[cdD->offsets[facet]];
        aux[1] = cdD->indices[cdD->offsets[facet]+1];
        cell00 = cell0;
        cell0 = cell;
        cell = (aux[0] == cell) ? aux[1] : aux[0];

        if (cell == cell00) { // Ping-pong between two cells.
          hexa_reverse = 1;
        }

      } else { // Boundary facet.
        cell_ent->ii = cell;
        me_get_incident2(cell_ent, cell_vertices, cD0);

        _get_cell_coors(e_coors, cell_vertices, mesh_coors, nc,
                        buf_ec_max);
        xi_ok = _get_xi_dist(&dist, xi,  cell_vertices->num, nc, D,
                             point, e_coors, eref_coors, bc,
                             nodes, n_nodes_col, mtx_i, vmin, vmax,
                             i_max, newton_eps);
        d_min = Min(dist, d_min);
        if (xi_ok && (dist < qp_eps)) {
          ok = 1;
        } else {
          ok = 0;
        }
        break;
      }

      icell++;
      icell_max = Max(icell, icell_max);
      if (icell > 10000) {
        errput("cannot find containing cell!\n");
        ERR_CheckGo(ret);
      }
    }

    /* fmf_print(xi, stdout, 0); */
    /* output("-> %d %d %d %.3e\n", cell, xi_ok, ok, d_min); */

    cells[ip] = cell;

    if (ok != 1) {
      if (!xi_ok) {
        status[ip] = 4;
      } else if (allow_extrapolation) {
        // Try using minimum distance xi.
        if (sqrt(d_min) < close_limit) {
          status[ip] = 1;
        } else {
          status[ip] = 2;
        }
      } else {
        status[ip] = 3;
      }
    } else {
      status[ip] = 0;
    }

    for (ii = 0; ii < nc; ii++) {
      ref_coors->val[nc*ip+ii] = xi->val[ii];
    }
  }
  /* output("%d\n", icell_max); */

 end_label:
  return(ret);
}