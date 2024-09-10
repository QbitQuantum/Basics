int
main() {
    int width = 32;
    for (int i = 2 ; i < width ; i ++) {
        printf(" %d   or %d(chain[%d], in[%d], chain[%d);\n", i, i, i, i, i-1);
    }
}