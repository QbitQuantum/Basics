static Vector *FindTextPositions(const ElementType *SC,const CHAR_TYPE *text)
{
    Vector *result = NULL;
    CHAR_TYPE *p;
    size_t i,idx;

    for (i=0; i<SC->count;i++) {
        if (NULL != (p=STRSTR(SC->contents[i],text))) {
            if (result == NULL) {
                result = iVector.Create(sizeof(size_t),10);
                if (result == NULL)
                    return NULL;
            }
            idx = p - SC->contents[i];
            if (iVector.Add(result,&i) <= 0)
                break;
            if (iVector.Add(result,&idx) <=0)
                break;
        }
    }
    return result;
}