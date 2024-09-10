/*
 * Check the vertex list for adjacent pairs of
 * points which are too close together for the
 * subsequent dot- and cross-product calculations
 * of Girard's theorem.
 */
void RemoveDups() {
  int i, nvnew;
  Vec Vnew[16];
  Vec tmp;
  double lon, lat;

  double separation;

  if (DEBUG >= 4) {
    printf("RemoveDups() TOLERANCE = %13.6e [%13.6e arcsec]\n\n", TOLERANCE,
           TOLERANCE / DEG_TO_RADIANS * 3600.);

    for (i = 0; i < nv; ++i) {
      lon = atan2(V[i].y, V[i].x) / DEG_TO_RADIANS;
      lat = asin(V[i].z) / DEG_TO_RADIANS;

      printf("RemoveDups() orig: %3d [%13.6e,%13.6e,%13.6e] "
             "-> (%10.6f,%10.6f)\n",
             i, V[i].x, V[i].y, V[i].z, lon, lat);

      fflush(stdout);
    }

    printf("\n");
  }

  Vnew[0].x = V[0].x;
  Vnew[0].y = V[0].y;
  Vnew[0].z = V[0].z;

  nvnew = 0;

  for (i = 0; i < nv; ++i) {
    ++nvnew;

    Vnew[nvnew].x = V[(i + 1) % nv].x;
    Vnew[nvnew].y = V[(i + 1) % nv].y;
    Vnew[nvnew].z = V[(i + 1) % nv].z;

    Cross(&V[i], &V[(i + 1) % nv], &tmp);

    separation = Normalize(&tmp);

    if (DEBUG >= 4) {
      printf("RemoveDups(): %3d x %3d: distance = %13.6e "
             "[%13.6e arcsec] (would become %d)\n",
             (i + 1) % nv, i, separation, separation / DEG_TO_RADIANS * 3600.,
             nvnew);

      fflush(stdout);
    }

    if (separation < TOLERANCE) {
      --nvnew;

      if (DEBUG >= 4) {
        printf("RemoveDups(): %3d is a duplicate (nvnew -> %d)\n", i, nvnew);

        fflush(stdout);
      }
    }
  }

  if (DEBUG >= 4) {
    printf("\n");
    fflush(stdout);
  }

  if (nvnew < nv) {
    for (i = 0; i < nvnew; ++i) {
      V[i].x = Vnew[i].x;
      V[i].y = Vnew[i].y;
      V[i].z = Vnew[i].z;
    }

    nv = nvnew;
  }
}