void Gage::drawStatic(){
	getGLCD()->drawRoundRect(getLeft(), getTop(), getLeft() + getWidth() - 1, getTop() + getHeight() - 1);
	_cursor = getCursor(_value.getValue());
	if(isHorizontal()){
		getGLCD()->fillRect(getLeft() + 2, getTop() + 2, _cursor, getTop() + getHeight() - 3);

		getGLCD()->setColor(_colorBck);
		getGLCD()->fillRect(_cursor, getTop() + 2, getLeft() + getWidth() - 3, getTop() + getHeight() - 3);
	}
	else{
		getGLCD()->fillRect(getLeft() + 2, _cursor , getLeft() + getWidth() - 3, getTop() + getHeight() - 3);

		getGLCD()->setColor(_colorBck);
		getGLCD()->fillRect(getLeft() + 2, getTop() + 2, getLeft() + getWidth() - 3, _cursor);
	}
}