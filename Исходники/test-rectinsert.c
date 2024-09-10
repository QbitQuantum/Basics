static void PrintState(boolean *state) {
    int x, y;
    
    for (y = 0; y < STATE_HEIGHT; y++) {
        printf("    ");

        for (x = 0; x < STATE_WIDTH; x++) {
            printf(GetPixel(state, x, y) ? "X" : "O");
            printf(x != STATE_WIDTH - 1 ? "," : "");
            printf((x + 1) % 5 == 0 ? " " : "");
        }

        printf("\n");
        printf((y + 1) % 5 == 0 ? "\n" : "");
    }
}