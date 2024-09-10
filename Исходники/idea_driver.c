/*******************************************************
 * Function: stripCrypt
 * Description: encrypts/decrypts a memory block. puts 
 * the results into an out buffer. ikey is the string
 * ****************************************************/
void stripCrypt(md5_hash * ikey, MemPtr str, MemPtr out, int sLen, int enc)
{
       Idea_Data ivector, ovector;
       Idea_UserKey k;
       Idea_Key ekey;
       int offset=0;

            //generate the key.
       MemMove(k, ikey, sizeof(md5_hash));

       Idea_ExpandUserKey(k, ekey);
       
       if(!enc)
            Idea_InvertKey(ekey, ekey);

            //encrypt or decrypt block by block
       for(;offset<sLen;)
       {
           MemMove(ivector, str+offset, BLOCK);
           Idea_Crypt(ivector, ovector, ekey);
           MemMove(out+offset, ovector, BLOCK);
           offset+=BLOCK;
       }  
       
            // wipeout keying info.
       MemSet(ivector, sizeof(ivector), 0);
       MemSet(ovector, sizeof(ovector), 0);
       MemSet(k,sizeof(k), 0);
       MemSet(ekey,sizeof(ekey), 0);   
}