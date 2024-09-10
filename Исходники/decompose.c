int main() {
    int n;
    int i;
    bool first_print = true;
    init_number();
    scanf("%d", &n);
    for(i = 1; i <= n; i++) {
        decompose(i);
    }
    for(i = 2; i <= n; i++) {
        if(composit_number[i] && record[i] >= 1) {
            if(record[i] == 1) {
                if(first_print) {
                    printf("%d", i);
                    first_print = false;
                }
                else
                    printf("*%d", i);
            }
            else {
                if(first_print) {
                    printf("%d^%d", i, record[i]);
                    first_print = false;
                }
                else
                    printf("*%d^%d", i, record[i]);
            }
        }
    }
    return 0;
}