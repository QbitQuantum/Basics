int main(int argc, char *argv[]) {
    char needle[20];
    struct Entry *result;

    int action, i = 0;

    if (argc < 2) {
        fprintf(stderr, "Path to database omitted!\n");
        exit(-1);
    }

    struct List entries = parse_db(argv[1]); /* parse database */

    /* ask for criterium */
    printf("What do you want to do?:\n1) sort by name\n2) sort by residents\n3) sort by area\n4) sort by distance\n5) search for entry\nYour choice: ");
    scanf("%d", &action);

    switch(action) {
    case 1:
        quicksort(entries.start, entries.end, cmp_name);
        break;
    case 2:
        quicksort(entries.start, entries.end, cmp_residents);
        break;
    case 3:
        quicksort(entries.start, entries.end, cmp_area);
        break;
    /*case 4:
    	quicksort(entries.start, entries.end, cmp_distance);
    	break;*/
    case 5:
        printf("what are you searching: ");
        scanf("%s", needle);
        result = lsearch(needle, entries.start, entries.end);
        print_entry(result);

    default:
        fprintf(stderr, "Invalid sort criteria!\n");
    }

    /* show result */
    if (action != 5) {
        struct Node *node;
        for (node = entries.start; node != entries.end && i++ < 100; node = node->next) {
            print_entry(node->data);
        }
    }

    return 0;
}