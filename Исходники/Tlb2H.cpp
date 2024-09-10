static VOID SortTypeList(__in ITypeLib *lpTypeLib, __inout TYPEINFO_LIST &aTypeInfoList)
{
  qsort_s(aTypeInfoList.GetBuffer(), aTypeInfoList.GetCount(), sizeof(TYPEINFO_ITEM*),
          &SortTypeList_Compare, NULL);
  return;
}