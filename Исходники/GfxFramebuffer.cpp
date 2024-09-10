STDMETHODIMP CGfxFB::SetDstRect(const RECT *pRect)
{
	if(EqualRect(pRect,&m_rectDst))
		return S_OK;

	m_rectDst = *pRect;
	IntersectRect(&m_rectDst,&m_rectScn,&m_rectDst);

#ifdef PXA_LINUX
	DP("FB Setdest(%d,%d,%d,%d) \n",m_rectDst.left, m_rectDst.top, m_rectDst.right, m_rectDst.bottom);
	return E_UNEXPECTED;

	m_fbvinfo.xres  = (m_rectDst.right - m_rectDst.left)&(~(DST_ALIGN-1));
	m_fbvinfo.yres  = (m_rectDst.bottom - m_rectDst.top)&(~(DST_ALIGN -1));

	m_fbvinfo.bits_per_pixel = 19;
	m_fbvinfo.nonstd = (FORMAT_PLANAR_420<< 20) | (m_rectDst.top << 10) | m_rectDst.left;

	if (m_pBuff != NULL)
	{
		munmap(m_pBuff, m_iBufSize);
		m_pBuff = NULL;
	}

	DP("Update info: left = %d, top = %d, xres = %d, yres = %d\n", m_fbvinfo.nonstd&0x3ff, (m_fbvinfo.nonstd>>10)&0x3ff, m_fbvinfo.xres, m_fbvinfo.yres);


	int ret = ioctl(m_iHndFB, FBIOPUT_VSCREENINFO, &m_fbvinfo);
	DP("Update()::FBIOPUT_VSCREENINFO :%d \n", ret);
	
	ioctl(m_iHndFB, FBIOGET_FSCREENINFO, &m_fbfinfo);
	m_iBufSize = m_fbfinfo.smem_len;
	DP("Update()::m_iBufSize  :%d \n", m_iBufSize );
	m_pBuff = (unsigned char *)mmap(0, m_iBufSize, PROT_READ | PROT_WRITE, MAP_SHARED, m_iHndFB, 0);
	if(m_pBuff ==NULL)
	{
		DP("Update()::set dest failed \n");
		return E_FAIL;
	}
#endif

	Update();
	return S_OK;
}