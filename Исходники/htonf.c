int main() {
    float f= 3.1415926;
    printf("the before float is:%f\n", f);
    uint32_t i = htonf(f);
    printf("the int is:%d\n", i);
    f = ntohf(i);
    printf("hte float is:%f\n", f);
    return 0;
}