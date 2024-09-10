// Multi-cell callback. Finds intersections with the current cell and
// stores results in data.
void MCCallback(OctCell cell, const floatn& a, const floatn& b,
                  const vector<OctNode>& octree, const Resln& resln,
                  void* data) {
  // const static float EPSILON = 1e-6;

  using namespace Karras;
  MCData* d = static_cast<MCData*>(data);
  const int octant = cell.get_octant();

  // // debug
  // OctCell test_cell;
  // stringstream ss("8796416 6561024 256 22009 3 -1");
  // ss >> test_cell;
  // if (cell == test_cell || cell == fnode) {
  //   cout << "here in MCCallback" << endl;
  // }

  // Get the intersections between the segment and octree cell.
  const vector<OctreeUtils::CellIntersection> intersections =
      OctreeUtils::FindIntersections(a, b, cell, /*octree,*/ resln);
  if (intersections.size() > 2) {
    error_log(cell, a, b, octree, resln);
    cerr << "More than 2 intersections with a cell" << endl;
    for (const OctreeUtils::CellIntersection& ci : intersections) {
      cerr << "  " << ci.p << endl;
    }
    throw logic_error("More than 2 intersections with a cell");
  }
  if (intersections.size() == 2) {
    FloatSegment seg(intersections[0].p,
                  intersections[1].p);
    CellIntersections& cell_intersections = d->labels[cell.get_parent_idx()];
    cell_intersections.set(octant, d->cur_label, seg);
  } else if (intersections.size() == 1) {
    // Find which endpoint is in cell
    const BoundingBox<intn> bb = cell.bb();
    const floatn p = intersections[0].p;
    floatn q;
    bool degenerate = false;
    // if (bb.in_half_open(convert_intn(a), EPSILON)) {
    if (bb.in_half_open(convert_intn(a))) {
      q = a;
    // } else if (bb.in_half_open(convert_intn(b), EPSILON)) {
    } else if (bb.in_half_open(convert_intn(b))) {
      q = b;
    } else if ((within(p.x, bb.min().x, EPSILON) ||
                within(p.x, bb.max().x, EPSILON)) &&
               (within(p.y, bb.min().y, EPSILON) ||
                within(p.y, bb.max().y, EPSILON))) {
      degenerate = true;
    } else {
      degenerate = true;
      // error_log(cell, a, b, octree, resln);
      // throw logic_error("Only one intersection but neither endpoint is"
      //                   " in bounding box");
    }
    if (!degenerate) {
      FloatSegment seg(p, q);
      CellIntersections& cell_intersections = d->labels[cell.get_parent_idx()];
      cell_intersections.set(octant, d->cur_label, seg);
    }
  }
}