 void GSClut::init()
 {
	g_pbyGSClut = (u8*)_aligned_malloc(256 * 8, 1024); // need 512 alignment!
	memset(g_pbyGSClut, 0, 256*8);
 }