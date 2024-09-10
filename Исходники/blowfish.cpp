//Decrypt Buffer in Place
//Returns false if n is multiple of 8
void CBlowFish::Decrypt(unsigned char* buf, size_t n, int iMode)
{
    //Check the buffer's length - should be > 0 and multiple of 8
    if((n==0)||(n%8!=0))
        throw std::exception("Incorrect buffer length");
    SBlock work;
    if(iMode == CBC) //CBC mode, using the Chain
    {
        SBlock crypt, chain(m_oChain);
        for(; n >= 8; n -= 8)
        {
            BytesToBlock(buf, work);
            crypt = work;
            Decrypt(work);
            work ^= chain;
            chain = crypt;
            BlockToBytes(work, buf+=8);
        }
    }
    else if(iMode == CFB) //CFB mode, using the Chain, not using Decrypt()
    {
        SBlock crypt, chain(m_oChain);
        for(; n >= 8; n -= 8)
        {
            BytesToBlock(buf, work);
            Encrypt(chain);
            crypt = work;
            work ^= chain;
            chain = crypt;
            BlockToBytes(work, buf+=8);
        }
    }
    else //ECB mode, not using the Chain
    {
        for(; n >= 8; n -= 8)
        {
            BytesToBlock(buf, work);
            Decrypt(work);
            BlockToBytes(work, buf+=8);
        }
    }
}