void CheckList::draw() {
	Component::draw();
	CONSOLE_CURSOR_INFO cci = { 100, TRUE };
	SetConsoleCursorInfo(_handle, &cci);
	int vector_size = _data.size();
	COORD temp = _position.getStartCord();
	temp.X++;
	temp.Y++;
	SetConsoleCursorPosition(_handle, temp);

	for (int i = 0; i < vector_size;i++){
		if (i == 0) {
	
			DWORD wAttr;
			if (needFirstYellow) {
				 wAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
				SetConsoleTextAttribute(_handle, wAttr);
				needFirstYellow = false;
			}
			cout << _data[i]<<endl;
			wAttr = _textColor | _backgroundColor;
			SetConsoleTextAttribute(_handle, wAttr);
			temp.Y++;
			
		}
		else {//next 
			SetConsoleCursorPosition(_handle, temp);
			cout << _data[i] << endl;
			temp.Y++;
		}
	}
}