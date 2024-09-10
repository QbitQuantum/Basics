// Finds vertical lines in the given list of BLOBNBOXes. bleft and tright
// are the bounds of the image on which the input line_bblobs were found.
// The input line_bblobs list is const really.
// The output vertical_x and vertical_y are the total of all the vectors.
// The output list of TabVector makes no reference to the input BLOBNBOXes.
void LineFinder::FindLineVectors(const ICOORD& bleft, const ICOORD& tright,
                                 BLOBNBOX_LIST* line_bblobs,
                                 int* vertical_x, int* vertical_y,
                                 TabVector_LIST* vectors) {
  BLOBNBOX_IT bbox_it(line_bblobs);
  int b_count = 0;
  // Put all the blobs into the grid to find the lines, and move the blobs
  // to the output lists.
  AlignedBlob blob_grid(kLineFindGridSize, bleft, tright);
  for (bbox_it.mark_cycle_pt(); !bbox_it.cycled_list(); bbox_it.forward()) {
    BLOBNBOX* bblob = bbox_it.data();
    bblob->set_left_tab_type(TT_UNCONFIRMED);
    bblob->set_left_rule(bleft.x());
    bblob->set_right_rule(tright.x());
    bblob->set_left_crossing_rule(bleft.x());
    bblob->set_right_crossing_rule(tright.x());
    blob_grid.InsertBBox(false, true, bblob);
    ++b_count;
  }
  if (textord_debug_tabfind)
    tprintf("Inserted %d line blobs into grid\n", b_count);
  if (b_count == 0)
    return;

  // Search the entire grid, looking for vertical line vectors.
  GridSearch<BLOBNBOX, BLOBNBOX_CLIST, BLOBNBOX_C_IT> lsearch(&blob_grid);
  BLOBNBOX* bbox;
  TabVector_IT vector_it(vectors);
  *vertical_x = 0;
  *vertical_y = 1;
  lsearch.StartFullSearch();
  while ((bbox = lsearch.NextFullSearch()) != NULL) {
    if (bbox->left_tab_type() == TT_UNCONFIRMED) {
      const TBOX& box = bbox->bounding_box();
      if (AlignedBlob::WithinTestRegion(2, box.left(), box.bottom()))
        tprintf("Finding line vector starting at bbox (%d,%d)\n",
                box.left(), box.bottom());
      AlignedBlobParams align_params(*vertical_x, *vertical_y, box.width());
      TabVector* vector = blob_grid.FindVerticalAlignment(align_params, bbox,
                                                          vertical_x,
                                                          vertical_y);
      if (vector != NULL) {
        vector->Freeze();
        vector_it.add_to_end(vector);
      }
    }
  }
  ScrollView* line_win = NULL;
  if (textord_tabfind_show_vlines) {
    line_win = blob_grid.MakeWindow(0, 50, "Vlines");
    blob_grid.DisplayBoxes(line_win);
    line_win = blob_grid.DisplayTabs("Vlines", line_win);
  }
}