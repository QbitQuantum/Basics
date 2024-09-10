void qt_widget_test::onCheck()
{
	QString filePath = ui.lineEdit->text();
	QByteArray ba = filePath.toLocal8Bit();

 	if(PathFileExistsA(ba.constData()))
	{
		::MessageBoxA(NULL, "exist!", "xx", MB_OK);
	}
	else
	{
		::MessageBoxA(NULL, "not exist!", "xx", MB_OK);
	}
}