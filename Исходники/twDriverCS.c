/********************************************************
 * Function: twKey
 * Description: pass this function a null terminated
 * string or char array and it will generate a valid 
 * 96 bit key for the 3-way encryption algorithm. 
 * Method: generate the digest of the passed in string
 * followed by the digest for that digest. concatonate
 * the two arrays and get one big array of 256 bits.
 * Ignore the last 64 bits. take the resulting 192 bits 
 * and fold the last 96 bits over the first 96 bits using
 * and XOR. i.e bit[n]^=bit[n+96]. the resulting array is
 * 96 bits its bit pattern is totaly dependent on the 
 * original strings message digest. If anyone cant think
 * of a better way to do this, let me know.
 * ******************************************************/
void twKey(char * ikey, MemPtr out)
{
       int i;
       char dKey[24], mdKey1[16], mdKey2[16];
      
       // Hash the input string, hash the output, then concatonate 
       MDString(ikey, mdKey1);
       MDBlock(mdKey1, 16, mdKey2);

       //concatanate the arrays
       MemMove(dKey, mdKey1, 16);
       MemMove(dKey+16, mdKey2, 8);

       //now fold dKey over itself at 96 bits, XORing as we go.
       for(i=0; i<12; i++)
       {
           dKey[i]^=dKey[i+BLOCKA];
       }

       MemMove(out, dKey, BLOCKA);
       
            //wipe out keying info.
       MemSet(dKey,0, sizeof(dKey));
       MemSet(mdKey1, 0, sizeof(mdKey1));
       MemSet(mdKey2, 0, sizeof(mdKey2));
}