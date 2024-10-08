///////////////////////////////////////////////////////////////////////
// Driver
int main(int argc, char* argv[]) {
  if ( argc != 8 ) {
    printf("Set the grid v = a + b*D^c, where d is the D distance to the nearest atom.\n");
    printf("For D < cutDistance, v = a + b*cutDistance^c.\n");
    printf("Usage: %s srcGrid pointFile aOffset bScale cExponent cutDistance outFile\n", argv[0]);
    return 0;
  }

  const char* srcFile = argv[1];
  const char* pointFile = argv[2];
  const double aOffset = strtod(argv[3], NULL);
  const double bScale = strtod(argv[4], NULL);
  const double cExp = strtod(argv[5], NULL);
  const double cutDist = strtod(argv[6], NULL);
  const char* outFile = argv[argc-1];

  // Load the grids.
  Grid src(srcFile);
  src.zero();
  int n = src.length();
  printf("Loaded `%s' which contains %d nodes.\n", srcFile, n); 

  // Load the coordinates.
  printf("Loading the coordinates.\n");
  Scatter pos(pointFile);
  int posNum = pos.length();
  printf("Loaded %d points from `%s'.\n", pos.length(), pointFile);

  int complete = 0;
  for (int i = 0; i < n; i++) {
    Vector3 r = src.getPosition(i);

    Vector3 dr = pos.get(0)-r;
    double minDist = dr.length();
    for (int j = 1; j < posNum; j++) {
      Vector3 dr = pos.get(j)-r;
      double dist = dr.length();

      if (dist < minDist) minDist = dist;
    }
    if (minDist < cutDist) minDist = cutDist;

    double v = powerLaw(minDist, aOffset, bScale, cExp);
    src.setValue(i, v);

    // Write the progress.
    int comp = (100*i)/n;
    if (abs(complete - comp) >= 5) {
      printf("%d percent complete\n", comp);
      complete = comp;
    }
  }
  char comments[256];
  sprintf(comments, "%s distance map", srcFile);
  src.write(outFile, comments);
  printf("Wrote `%s'.\n", outFile);

  return 0;
}