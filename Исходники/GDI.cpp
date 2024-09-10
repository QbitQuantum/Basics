xpr_bool_t DuplicateImgList(CImageList *aSrcImgList, CImageList *aDstImgList)
{
    if (XPR_IS_NULL(aSrcImgList) || XPR_IS_NULL(aDstImgList))
        return XPR_FALSE;

    HIMAGELIST sImgList = ImageList_Duplicate(aSrcImgList->m_hImageList);
    if (XPR_IS_NULL(sImgList))
        return XPR_FALSE;

    if (aDstImgList->m_hImageList)
        aDstImgList->DeleteImageList();

    return aDstImgList->Attach(sImgList);
}