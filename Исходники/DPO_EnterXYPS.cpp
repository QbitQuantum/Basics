void XYArray::SetAtGrow(int nIndex, XYItem& newVal)
{
    if (nIndex >= AllocSize())
        ReAlloc(AllocSize() * 2 + 1);
    (*this)[nIndex] = newVal;
    if (nIndex >= Size())
        SetSize(nIndex + 1);
}