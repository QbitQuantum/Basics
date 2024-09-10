int main() {
    zdd_init();
    // The universe is {1, ..., 9^3 = 729}.
    zdd_set_vmax(729);
    // Number rows and columns from 0. Digits are integers [1..9].
    // The digit d at (r, c) is represented by element 81 r + 9 c + d.
    inta_t list;
    inta_init(list);
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            int c = getchar();
            if (EOF == c) die("unexpected EOF");
            if ('\n' == c) die("unexpected newline");
            if (c >= '1' && c <= '9') {
                inta_append(list, 81 * i + 9 * j + c - '0');
            }
        }
        int c = getchar();
        if (EOF == c) die("unexpected EOF");
        if ('\n' != c) die("expected newline");
    }
    inta_append(list, -1);
    contains_all(inta_raw(list));
    inta_clear(list);

    global_one_digit_per_box();
    zdd_intersection();

    // Number of ways you can put nine 1s into a sudoku is
    //   9*6*3*6*3*4*2*2.
    printf("rows\n");
    fflush(stdout);
    for(int i = 1; i <= 9; i++) {
        for(int r = 0; r < 9; r++) {
            unique_digit_per_row(i, r);
            if (r) zdd_intersection();
        }
        zdd_intersection();
    }
    for(int i = 1; i <= 9; i++) {
        for(int c = 0; c < 3; c++) {
            for(int r = 0; r < 3; r++) {
                printf("3x3 %d: %d, %d\n", i, r, c);
                fflush(stdout);
                unique_digit_per_3x3(i, r, c);
                if (r) zdd_intersection();
            }
            if (c) zdd_intersection();
        }
        zdd_intersection();
    }
    for(int i = 1; i <= 9; i++) {
        for(int c = 0; c < 9; c++) {
            printf("cols %d: %d\n", i, c);
            fflush(stdout);
            unique_digit_per_col(i, c);
            if (c) zdd_intersection();
        }
        zdd_intersection();
    }

    void printsol(int *v, int vcount) {
        for(int i = 0; i < vcount; i++) {
            putchar(((v[i] - 1) % 9) + '1');
            if (8 == (i % 9)) putchar('\n');
        }
        putchar('\n');
    }
    zdd_forall(printsol);
    return 0;
}