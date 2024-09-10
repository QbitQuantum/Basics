void printATrans(ATrans3 const& atrans) {
  Vector3 rpy = rotationMatrixToEulerXyz(atrans.rotation());
  cout << fixed << "(("
       << setprecision (3) << pruneXyz(atrans.translation().x()) << ", "
       << setprecision (3) << pruneXyz(atrans.translation().y()) << ", "
       << setprecision (3) << pruneXyz(atrans.translation().z())
       << "), (";
  for (size_t y = 0; y < 3; ++y) {
    for (size_t x = 0; x < 3; ++x) {
      if (x > 0 || y > 0) {
        cout << ", ";
      }
      cout << setprecision (8) << pruneXyz(atrans.rotation()(y, x));
    }
  }
  //  cout << "))" << endl;
   cout << "), ("
        << setprecision (3) << pruneRpy(rpy.x()) * 180./M_PI << " deg, "
        << setprecision (3) << pruneRpy(rpy.y()) * 180./M_PI << " deg, "
        << setprecision (3) << pruneRpy(rpy.z()) * 180./M_PI << " deg))"
        << endl;
}