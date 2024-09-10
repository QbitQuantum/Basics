void IconList::setIconSize(int size) const
{
	ImageList_SetIconSize(_hImglst, size, size);
	for (int i = 0 ; i < _iconIDArraySize ; ++i)
		addIcon(_pIconIDArray[i]);
}