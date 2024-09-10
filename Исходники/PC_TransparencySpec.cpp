void PC_TransparencySpec::QSort(ObjPtrList& a, int lo0, int hi0)
{
    int lo = lo0;
    int hi = hi0;

    // Bubble sort if the number of elements is less than 6
    if ((hi-lo) <= 6)
    {
        QBSort(a, lo, hi);
        return;
    }

    // Pick a pivot and move it out of the way /

    ObjectTransDesc* pivot = a[(lo + hi) / 2];
    a[(lo + hi) / 2] = a[hi];
    a[hi] = pivot;

    const double& pivotDist = pivot->objDist;
    while( lo < hi )
    {
        // Search forward from a[lo] until an element is found that * is greater than the pivot or lo >= hi
        while ((lo < hi) && (a[lo]->objDist <= pivotDist))
        {
            lo++;
        }

        // Search backward from a[hi] until element is found that * is less than the pivot, or hi <= lo
        while ((lo < hi) && (pivotDist <= a[hi]->objDist))
        {
            hi--;
        }
        // Swap elements a[lo] and a[hi]
        if( lo < hi )
        {
            ObjectTransDesc* T = a[lo];
            a[lo] = a[hi];
            a[hi] = T;
        }
    }

    // Put the median in the "center" of the list
    a[hi0] = a[hi];
    a[hi] = pivot;
    // Recursive calls, elements a[lo0] to a[lo-1] are less than or * equal to pivot, elements a[hi+1] to a[hi0] are greater than * pivot.
    QSort(a, lo0, lo-1);
    QSort(a, hi+1, hi0);
}