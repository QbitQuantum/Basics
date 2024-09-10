bool place(int x[], list<int> d, int n, int left, int right)
{
    int dmax;
    bool found = false;

    if(d.empty())
        return true;

    dmax = max(d);

    for (1<=j<left && right<j<=n)
    {
        if (isIn(d,x[j]))
        {
            x[right] = dmax;
            for (1<=j<left, right<j<=n)
                d.remove(x[j]-dmax);
            found = place (x, d, n, left, right-1);
        }

        if (!found)
            for (1<=j<left, right<j<=n)
                d.insert(x[j]-dmax);
    }

    for (1<=j<left && right<j<=n)
    {
        if (!found && isIn(abs(x[n]-dmax-x[j])))
        {
            x[left] = x[n]-dmax;
            for (1<=j<left, right<j<=n)
                d.remove(abs(x[j]-dmax-x[j]));
            found = place (x, d, n, left+1, right);
        }

        if (!found)
            for (1<=j<left, right<j<=n)
                d.insert(abs(x[j]-dmax-x[j]));
    }