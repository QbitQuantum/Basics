// A tet is organized in the following fashion:
//
//       0
//       
//       3       (3 is in the background; 1 and 2 are in the foreground)
//  2        1
//
// So the faces (with counterclockwise normals) are:
// (0 1 3)
// (0 2 1)
// (3 2 0)
// (1 2 3)
//
//
// This method will perform three steps:
// 1. Add all faces, duplicating ones on the interior
// 2. Remove all duplicate verts (might have been caused during #1)
// 3. Remove all duplicate faces
void marching_tets(
  const Eigen::MatrixXd& V,
  const Eigen::MatrixXi& T,
  const Eigen::VectorXd& H,
  double offset,
  Eigen::MatrixXd& NV,
  Eigen::MatrixXi& NF,
  Eigen::VectorXi& I)
{
  min_how_much = 1;
  max_how_much = 0;
  using namespace Eigen;
  using namespace std;

  // Count the faces.
  std::map<std::vector<int>, int> face_counts;
  for (int i = 0; i < T.rows(); ++i) {
    std::vector<std::vector<int> > fs;
    fs.push_back({T(i, 0), T(i, 1), T(i, 3)});
    fs.push_back({T(i, 0), T(i, 2), T(i, 1)});
    fs.push_back({T(i, 3), T(i, 2), T(i, 0)});
    fs.push_back({T(i, 1), T(i, 2), T(i, 3)});
    for (auto &f : fs) {
      std::sort(f.begin(), f.end());
      // Add it to the map.
      face_counts[f]++;
    }
  }

  vector<Eigen::RowVector3i> faces;
  vector<int> faces_markers;
  vector<Eigen::RowVector3d> new_verts;
  int times[6];
  for (int i = 0; i < 6; i++) {
    times[i] = 0;
  }

  // Create data structure.
  MarchingTetsDat dd(V, H, faces, faces_markers, face_counts, new_verts, offset);

  int numEq = 0;

  // Check each tet face, add as needed.
  for (int i = 0; i < T.rows(); ++i) {
    // See if the tet is entirely inside.
    vector<int> inside, outside, inside_t, outside_t, identical;
    for (int j = 0; j < T.cols(); ++j) {
      //if (H(T(i, j)) > offset + 1e-4) {
      if (H(T(i, j)) > offset) {
        outside.push_back(j);
      } else if (H(T(i, j)) < offset) {
        inside.push_back(j);
      } else {
        numEq++;
        identical.push_back(j);
      }

      if (H(T(i, j)) == GLOBAL::outside_temp) {
        outside_t.push_back(j);
      } else if (H(T(i, j)) == GLOBAL::inside_temp) {
        inside_t.push_back(j);
      }
    }

    // Ignore this tet if it's entirely outside.
    if (outside.size() == 4) {
      continue;
    }


    if (outside.size() == 0 && inside.size() == 0) {
      // degenerate, ignore.
      printf("WARNING: degenerate tet face found!!\n");
    } else if (inside.size() == 0 && identical.size() < 3) {
      // Nothing to add.
    } else if (identical.size() == 3) {
      //addOrig(T.row(i), 7, dd.faces, dd.faces_markers);
      // Ignore it if there's only one on the outside.
      //if (inside.size() == 0) continue;
      if (outside.size() == 0) continue;
      times[1]++;
      // Add just a single face (always)
      int i1 = T(i,identical[0]), i2 = T(i,identical[1]), i3 = T(i,identical[2]);
      Eigen::RowVector3i f({i1, i2, i3});
      dd.faces.push_back(f);
      dd.faces_markers.push_back(1);
    } else if (outside.size() == 0) {
      // (these are colored blue)
      times[0]++;
      // (A) Takes care of:
      //   inside: 1, identical: 3 (remove three duplicated faces later)
      //   inside: 2, identical: 2 (remove all four duplicated faces later)
      //   inside: 3, identical: 1 (remove all four duplicated faces later)
      //   inside: 4, identical: 0 (remove all four duplicated faces later)
      case0Out(dd, T.row(i), inside, outside, identical, inside_t, outside_t);
    } else if (inside.size() == 1) {
      // (these are colored green)
      times[2]++;
      // (B) Takes care of:
      //   inside: 1 outside: 3
      //   inside: 1 outside: 2 identical: 1
      //   inside: 1 outside: 1 identical: 2
      //
      case1In(dd, T.row(i), inside, outside, identical, inside_t, outside_t);
    } else if (inside.size() == 3 && outside.size() == 1) {
      // (these are colored orange)
      times[3]++;
      // (C) takes care of:
      //   inside: 3 outside: 1
      //
      case3In1Out(dd, T.row(i), inside, outside, identical, inside_t, outside_t);
    } else if (inside.size() == 2 && outside.size() >= 1) {
      // (these are colored red)
      times[4]++;
      // (D) takes care of:
      //   inside: 2 outside: 1 identical: 1
      //   inside: 2 outside: 2 identical: 0
      //
      case2In2Out(dd, T.row(i), inside, outside, identical, inside_t, outside_t);
    } else {
      times[5]++;
      fprintf(stderr, "WARN: marching tets found something weird, with in:%lu out:%lu\n",
              inside.size(), outside.size());
    }
  }

  printf("Finished marching tets with usages:\n");
  for (int i = 0; i < 6; ++i) {
    printf("  %d: %d\n", i, times[i]);
  }
  printf("how_much is %lf and EPS is %lf\n", min_how_much, GLOBAL::EPS);
  printf("     max is %lf\n", max_how_much);
  printf("Num equal is %d\n", numEq);

  // Copy verts
  NV.resize(V.rows() + new_verts.size(), 3);
  for (int i = 0; i < V.rows(); ++i) {
    NV.row(i) = V.row(i);
  }
  for (int i = 0; i < new_verts.size(); ++i) {
    NV.row(i + V.rows()) = new_verts[i];
  }
  // Set I
  I.resize(NV.rows());
  for (int i = 0; i < I.rows(); ++i) {
    if (i < V.rows()) {
      I(i) = i;
    } else {
      I(i) = -1;
    }
  }
  Eigen::VectorXi facesMarkers;
  facesMarkers.resize(faces.size());
  // Copy faces
  NF.resize(faces.size(), 3);
  for (int i = 0; i < faces.size(); ++i) {
    NF.row(i) = faces[i];
    facesMarkers(i) = faces_markers[i];
  }
  
  Eigen::MatrixXd newV;
  Eigen::MatrixXi newF;
  Eigen::VectorXi SVJ, SVI, I2;
  // Helpers::viewTriMesh(NV, NF, facesMarkers);
  //igl::writeOFF("offset_mesh.off", NV, NF)
  Helpers::writeMeshWithMarkers("offset_mesh", NV, NF, facesMarkers);

  /*
  igl::collapse_small_triangles(NV, NF, 1e-8, newF);
  printf("Collapsed %d small triangles\n", NF.rows() - newF.rows());
  NF = newF;
  */

  ///*
  igl::remove_duplicate_vertices(NV, NF, 1e-20, newV, SVI, SVJ, newF);
  I2.resize(newV.rows());
  I2.setConstant(-1);
  for (int i = 0; i < NV.rows(); ++i) {
    if (I2(SVJ(i)) == -1) {
      I2(SVJ(i)) = I(i);
    } else {
      I2(SVJ(i)) = std::min(I2(SVJ(i)), I(i));
    }
  }
  NF = newF;
  NV = newV;
  I = I2;

  // Now see if we have duplicated faces.
  //igl::resolve_duplicated_faces(NF, newF, SVJ);
  //NF = newF;
  //*/

  // Other option is to do these two:
  // These are bad because sometimes the "small" triangles are not area zero,
  // and doing the removeDuplicates will delete these triangles and make the
  // mesh non-manifold. Better to wait for remeshing later.
  //Helpers::removeDuplicates(NV, NF, I);
  //Helpers::collapseSmallTriangles(NV, NF);

  igl::remove_unreferenced(NV, NF, newV, newF, SVI, SVJ);
  I2.resize(newV.rows());
  I2.setConstant(-1);
  for (int i = 0; i < I2.rows(); ++i) {
    I2(i) = I(SVJ(i));
  }
  I = I2;
  NV = newV;
  NF = newF;


  // orient everything correctly.
  Eigen::VectorXi C;
  igl::orientable_patches(NF, C);
  igl::bfs_orient(NF, newF, C);
  NF = newF;
  igl::orient_outward(NV, NF, C, newF, SVJ);
  NF = newF;
  //igl::writeOFF("offset_mesh_normals.off", NV, NF);

#ifdef DEBUG_MESH
  if (!Helpers::isMeshOkay(NV, NF)) {
    printf("Error: Mesh is not okay at first...\n");
  }
  if (!Helpers::isManifold(NV, NF, I)) {
    printf("Error: Mesh from marching tets not manifold!\n");
    Eigen::VectorXi temp;
    temp.resize(I.rows());
    temp.setZero();
    Helpers::isManifold(NV, NF, temp, true);
    Helpers::viewTriMesh(NV, NF, temp);
    Helpers::writeMeshWithMarkers("marching_tets_manifold", NV, NF, temp);
    cout << "See marching_tets_manifold.off for problems.\n";
    exit(1);
  }
#endif
}