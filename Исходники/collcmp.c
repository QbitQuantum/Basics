int __collate_range_cmp(int c1, int c2) {
    static char s1[2], s2[2];
    s1[0] = c1;
    s2[0] = c2;
    return (strcoll(s1, s2));
}