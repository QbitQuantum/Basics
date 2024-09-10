/* Euler #3:
 * Answer: 6857
 *
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143 ?
 */
int euler3() {
    unsigned long target = 600851475143;
    int i;
    double s = sqrtl(target);
    double c = (long double)ceill(s);
    for (i = c; i > 0; i--) {
        if ((target % i == 0) && (is_prime(i))) {
            return i;
        }
    }
    return -1;
}