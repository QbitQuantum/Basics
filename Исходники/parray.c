void *
parray_bsearch(parray *array, const void *key, int(*compare)(const void *, const void *))
{
    return bsearch(&key, array->data, array->used, sizeof(void *), compare);
}