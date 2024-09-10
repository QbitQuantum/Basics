void pListView::setImageList() {
  auto &list = listView.state.image;

  if(imageList) {
    ImageList_Destroy(imageList);
    imageList = nullptr;
  }

  bool found = false;
  for(auto &row : listView.state.image) {
    for(auto &column : row) {
      if(column.empty() == false) {
        found = true;
        break;
      }
    }
  }
  if(found == false) return;

  imageList = ImageList_Create(15, 15, ILC_COLOR32, 1, 0);
  nall::image image;
  image.allocate(15, 15);
  image.clear(GetSysColor(COLOR_WINDOW));
  ImageList_Add(imageList, CreateBitmap(image), NULL);

  for(unsigned row = 0; row < list.size(); row++) {
    for(unsigned column = 0; column < list(row).size(); column++) {
      nall::image image = list(row)(column);
      if(image.empty()) continue;
      image.transform(0, 32, 255u << 24, 255u << 16, 255u << 8, 255u << 0);
      image.scale(15, 15, Interpolation::Linear);
      ImageList_Add(imageList, CreateBitmap(image), NULL);
    }
  }

  ListView_SetImageList(hwnd, imageList, LVSIL_SMALL);

  unsigned ID = 1;
  for(unsigned row = 0; row < list.size(); row++) {
    for(unsigned column = 0; column < list(row).size(); column++) {
      if(list(row)(column).empty()) continue;  //I_IMAGENONE does not work properly
      LVITEM item;
      item.mask = LVIF_IMAGE;
      item.iItem = row;
      item.iSubItem = column;
      item.iImage = ID++;
      ListView_SetItem(hwnd, &item);
    }
  }
}