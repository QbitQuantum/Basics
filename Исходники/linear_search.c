int main(int argc, char **argv)
{
    /* Set up an integer array*/
    int arr[] = {1, 2, -100, 100, 200, 500};

    assert(lsearch(arr, sizeof(arr)/sizeof(int), 100) == 3);
    assert(lsearch(arr, sizeof(arr)/sizeof(int), 1) == 0);
    assert(lsearch(arr, sizeof(arr)/sizeof(int), 1000) == -1);

    return 0;
}