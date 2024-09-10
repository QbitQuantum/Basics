int solve(int si, int sj)
{
    if (cache[si][sj] != -1)
        return cache[si][sj];

    int mi[] = { -1, 1, 0, 0 };
    int mj[] = { 0, 0, -1, 1 };

    int max = 1;

    for (int i = 0; i < 4; i++)
    {
        int ei = si + mi[i];
        int ej = sj + mj[i];

        if (!isLower(si, sj, ei, ej))
            continue;

        int dist = solve(ei, ej) + 1;
        if (dist > max)
            max = dist;
    }

    cache[si][sj] = max;
    return max;
}