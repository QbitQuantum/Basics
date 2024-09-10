void KH::TextDrawer::Out(const char * str)
{ 
	//DrawEngString(str);return;

	int len=0, i=0; wchar_t * wstring; 
	HDC hDC=wglGetCurrentDC(); 
	GLuint list=glGenLists( 1 ); //计算字符的个数 
								// 如果是双字节字符的（比如中文字符），两个字节才算一个字符     
								// 否则一个字节算一个字符 
	for( i=0; str[i]!='\0'; i++ ) {    //判断字符str[i]是否由两个字节组成    
		if( IsDBCSLeadByte( str[i] ))     
			i++;    
		len++; 
	} //将混合字符转化为宽字符 
	wstring=(wchar_t*)malloc((len+1)*sizeof(wchar_t)); 
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len ); 
	wstring[len]=L'\0'; //逐个输出字符 
	for( i=0; i<len; i++ ) {    
		wglUseFontBitmapsW( hDC, wstring[i], 1, list );    
		glCallList( list ); 
	} //资源回收 
	free( wstring ); 
	glDeleteLists( list, 1 ); 
}