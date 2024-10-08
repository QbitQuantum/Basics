/**
 *  hash(key) = floor(m * (key * A) mod 1)
 *  Translated into machine friendly computations:
 *  A = s/2^w where s = multiplier.
 *  m = 2^p, where m is the number of buckets.
 *  Since S is 2^S number of entries and B = 2^b = number of entries per bucket,
 *  where b is an integer, then p = S/b. 
 *  Thus, p = log2(2^S/B) = S-log2(B).
 */
MHash::MHash(uint multiplier, uint S, uint B){
    s = multiplier;
    p = S-log2(B);
}