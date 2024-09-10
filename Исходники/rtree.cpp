void dbRtreePage::remove_branch(int i)
{
    n -= 1;
    memmove(&b[i], &b[i+1], (n-i)*sizeof(branch));
}