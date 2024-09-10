/*******************************************************
 * Function: stripCrypt
 * Description: encrypts/decrypts a memory block. puts 
 * the results into an out buffer. dkey is the string
 * ****************************************************/
void stripCryptC(char * ikey, MemPtr str, MemPtr out, int sLen, int enc)
{
       int offset=0;
	   char ivector[BLOCKC], ovector[BLOCKC], k[16]; 
		Boolean e;

		(enc==1)?(e=true):(e=false);
            //generate the key.
       MDString(ikey, k);
		xOrFold(k);

            //encrypt or decrypt block by block
       for(;offset<sLen;)
       {
           MemMove(ivector, str+offset, BLOCKC);
			EncDES(ivector, k, ovector, e);
           MemMove(out+offset, ovector, BLOCKC);
           offset+=BLOCKC;
       }  
       
            // wipeout keying info.
       MemSet(ivector, sizeof(ivector), 0);
       MemSet(ovector, sizeof(ovector), 0);
       MemSet(k,sizeof(k), 0);
}