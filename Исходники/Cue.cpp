CString CCue::ToString()
{
    int i = ptr->GetIndex();
    int     decimal,   sign, precision;

    if (i > 10)
    {
        precision = 2;
    }
    else
    {
        precision = 1;
    }

    CString index = _ecvt(i, precision, &decimal, &sign);
    return index + " **LOCATION OF THE POINTER**";
}