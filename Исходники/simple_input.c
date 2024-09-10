int CopyDataSet(void *s, void *d, int count)
{
    DataSet *src = (DataSet *)s;
    DataSet *dst = (DataSet *)d;
    int i;
    int j;

    if(count > SizeOf(src))
    {
        return(0);
    }

    if(src->fields != dst->fields)
    {
        return(0);
    }

    while(SizeOf(dst) < count)
    {
        ExpandData((void *)dst);
    }

    for(i=0; i < count; i++)
    {
        for(j=0; j < src->fields; j++)
        {
            dst->data[j][i] = src->data[j][i];
        }
    }
    dst->data_c = count;
    Rewind(dst);

    return(1);
}