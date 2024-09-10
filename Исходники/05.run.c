int main() {
    int *array = calloc(SIZE, sizeof(int));

    printf("n = %d, k = %d\n", SIZE, K);
    printf("-----------------------------\n");
    TIME("quicksort         ", quicksort);
    TIME("modified-quicksort", modified_quicksort);

    return 0;
}