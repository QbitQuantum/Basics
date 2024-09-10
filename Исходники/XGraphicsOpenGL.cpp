// 백버퍼의 픽셀을 읽어서 pBuffer에 담아줌.
// m_nWidth는 논리적서피스의 크기이고 work와 같고, back,frame 버퍼는 실제물리적 해상도인것으로 구분해줄 필요 있다.
void*	XGraphicsOpenGL::ReadBackBuffer( int phywidth, int phyheight, void *pBuffer )
{
	if( GetPixelFormat() != xPIXELFORMAT_RGB565 )
		XERROR( "아직은 RGB565포맷만 사용가능함." );

//	glReadBufferOES( GL_BACK );	// gl1.2 ES엔 없는듯.
    // gl1.x에선 프론트가 아니고 백버퍼만 읽을수 있는듯 하다. 잘못알고 있었음-_-;;
	glReadPixels(0, 0, phywidth, phyheight, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, pBuffer );
	return pBuffer;
}