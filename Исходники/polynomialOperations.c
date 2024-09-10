// sets q equal to the polynomial s.t. a = bq + r
void eucDiv(float a[], float b[], float q[]) {
    if (equalsZero(a) == 1) {
        printf("You are calling eucDiv with a equal to the zero vector\n");
        return;
    }
    if (equalsZero(b) == 1) {
        printf("You are calling a division by 0\n");
        return;
    }

    // printf("a in eucdiv call: ");
    // printPoly(a);

    // printf("b in eucdiv call: ");
    // printPoly(b);
    int i;
    // printf("\narg1 of eucdiv: ");
    // printPoly(a);
    // printf("\narg2 of eucdiv: ");
    // printPoly(b);
    int degA = degree(a);
    int degB = degree(b);
    //printf("\ndeg arg1: %d, deg arg2: %d\n", degA, degB);

    int d = degA - degB;
    if (d < 0) {
        printf("This is a nonsensical call of eucDiv\n");
        return;
    }

    float tempQ;
    setZero(q);

    // creates tempA as a clone of a
    float tempA[maxDegree+1];
    setEquals(tempA, a);
    float tempB[maxDegree+1];
    setEquals(tempB, b);
    // float tempPoly[maxDegree+1];

    // algorithm for euclidean division
    for (i = d; i >= 0; --i) {
        tempQ = tempA[degA + i - d] / tempB[degB];
        q[i] = tempQ;
        if (tempQ != 0) {
            scale(tempB, tempQ);
            polyTimesXn(tempB, i);
            subtract(tempA, tempB);
            polyTimesXn(tempB, -i);
            scale(tempB, 1.0/tempQ);
        }
    }
}