char *toString(BigInt *num) {
    num = trim(num);
    char *result = calloc(num->length+1, sizeof(char));
    int i;
    int ifnegative = 0;
    if (num->sign == -1) {
        ifnegative = 1;
        result[num->length] = '-';
    }
    for (i=0; i<= num->length-1 ;i++) {
        result[i] = '0' + num->digits[i];
    }
    return strrev(result);
}