void CreateAndLoadTable(LayoutType layout_type) {
  // Initialize settings
  peloton_layout_mode = layout_type;

  CreateTable();

  LoadTable();
}