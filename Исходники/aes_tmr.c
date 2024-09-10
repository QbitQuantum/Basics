u4byte d_cycles(const u4byte key_len, AESREF alg)
{   u1byte  pt[16], ct[16], key[32];
    u4byte  i, cy0, cy1, cy2, c1, c2;

    // set up a random key of 256 bits

    block_rndfill(key, 32);

    // set up a random plain text

    block_rndfill(pt, 16);

    // do a set_key in case it is necessary

    alg.set_key(key, key_len, both); c1 = c2 = 0xffffffff;

    // do an decrypt to remove any 'first time through' effects

    alg.decrypt(pt, ct);
 
    for(i = 0; i < loops; ++i)
    {
        block_rndfill(pt, 16);

        // time one and two encryptions

        cycles(&cy0);
        alg.decrypt(pt, ct);
        cycles(&cy1);
        alg.decrypt(pt, ct);
        alg.decrypt(pt, ct);
        cycles(&cy2);

        cy2 -= cy1; cy1 -= cy0;     // time for one and two calls

        c1 = (c1 > cy1 ? cy1 : c1); // find minimum values over the loops

        c2 = (c2 > cy2 ? cy2 : c2);
    }

    return c2 - c1; // return one call timing
}