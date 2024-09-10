int main() {
    FILE *in = fopen("task.in", "r");
    FILE *out = fopen("task.out", "w");
    int array[LIMIT];
    int needle;
    int size = 1;
    
    fscanf(in, "%d", &needle);
    
    for ( int i = 0; i < LIMIT && fscanf(in, "%d", &array[i]) == 1; i++ ) {
        size += 1;
    }
    fclose(in);
    
    fprintf(out, "%d\n", lsearch(array, size, needle));
    fclose(out);
    
    return 0;
}