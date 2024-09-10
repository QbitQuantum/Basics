static void LoadHeader(LoadState* S)
{
    lu_byte h[LUAC_HEADERSIZE];
    lu_byte s[LUAC_HEADERSIZE];
    luaU_header(h);
    MEMCPY(s,h,sizeof(char));			/* first char already read */
    LoadBlock(S,s+sizeof(char),LUAC_HEADERSIZE-sizeof(char));
    if (MEMCMP(h,s,N0)==0) return;
    if (MEMCMP(h,s,N1)!=0) error(S,"not a");
    if (MEMCMP(h,s,N2)!=0) error(S,"version mismatch in");
    if (MEMCMP(h,s,N3)!=0) error(S,"incompatible");
    else error(S,"corrupted");
}