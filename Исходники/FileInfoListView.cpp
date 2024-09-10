FileInfoListView::~FileInfoListView()
{
  if (m_smallImageList != 0) {
    ImageList_Destroy(m_smallImageList);
  }
}