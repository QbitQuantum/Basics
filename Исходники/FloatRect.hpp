inline void CRectTplt<T>::operator|=(const CRectTplt& rect)
{
   UnionRect(this, &rect);
}