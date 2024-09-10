void Win32Helper::writeText(const string & text, float x,float y)
{
	if( fontBase < 0 )
		setFont("Arial");
	glPushMatrix();
	glTranslatef(x,y,0);
	glScalef(15,15,15);
	glListBase(fontBase - __toascii(' '));
	glColor3f(0,1,0);
	glCallLists(GLsizei(text.length()), GL_UNSIGNED_BYTE, text.c_str());
	glPopMatrix();
}