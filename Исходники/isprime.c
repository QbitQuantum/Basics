/**
 * Returns 1 (true) if the specified number is a prime number, 0 (false)
 * otherwise.
 */
int is_prime(unsigned long num)
{
    unsigned int *sieve;
    char num_bit;
    unsigned long start_pos, i, ptr_size;
    ldiv_t qr;

    /* Edge cases */
    if ((num == 0) || (num == 1)) return 0;

    /* The sieve we'll use to determine if num is a prime or not. */
    sieve = new_sieve(num);
    ptr_size = sizeof(sieve[0])*CHAR_BIT;

    /* sieve[2] represents the number 2. We only have to find multiples/factors up to sqrt(num). */
    for (start_pos = 2; start_pos <= (unsigned long)sqrt(num); ++start_pos)
    {
        /* If this number is cleared, then so will all of its multiples, in which
           case there is nothing needed to be done. */
        qr = ldiv(start_pos, ptr_size);
        if (( sieve[qr.quot] & (1 << qr.rem) ) != 0) {
            /* Clear all numbers that are multiples of 'sieve[start_pos]' */
            for (i = start_pos; i <= num; i = i + start_pos)
            {
                qr = ldiv(i, ptr_size);
                sieve[qr.quot] &= ~(1 << qr.rem);

                if (i == num)
                {
                    /* We've cleared 'sieve[num]' we now know it's not a prime number */
                    break;
                }
            }

            if (i == num)
            {
                printf("Divisible by %lu\n", start_pos);
                /* We've cleared 'sieve[num]' we now know it's not a prime number */
                break;
            }
        }
    }

    /* Get the value of the bit at position 'num' */
    qr = ldiv(num, ptr_size);
    num_bit = ( sieve[qr.quot] & (1 << qr.rem) ) != 0;

    free(sieve);

    // 'num' is a prime if the bit 'sieve[num]' was still set.
    return num_bit;
}