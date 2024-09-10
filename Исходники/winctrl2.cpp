BOOL CImageList::Create(CImageList& imagelist1, int nImage1,
        CImageList& imagelist2, int nImage2, int dx, int dy)
{
        return Attach(ImageList_Merge(imagelist1.m_hImageList, nImage1,
                imagelist2.m_hImageList, nImage2, dx, dy));
}