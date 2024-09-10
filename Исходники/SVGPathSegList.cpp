void SVGPathSegList::add(PassRefPtrWillBeRawPtr<SVGPropertyBase> other, SVGElement*)
{
    RefPtr<SVGPathSegList> otherList = toSVGPathSegList(other);
    if (length() != otherList->length())
        return;

    byteStream(); // create |m_byteStream| if not exist.
    addToSVGPathByteStream(m_byteStream.get(), otherList->byteStream());
    invalidateList();
}