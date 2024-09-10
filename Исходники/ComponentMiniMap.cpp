ComponentMiniMap::ComponentMiniMap(const char* spriteFilename, int color)
{   
	clock = Clock();

	//Calcula cuantos frames tiene que dejar pasar para repartirse entre todos los frames
	//Estos sprites empiezan a partir del id 4602
	this->spriteFilename = spriteFilename;
	this->color = color;
}