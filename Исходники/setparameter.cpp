void Painting::SetParameter(std::string p, std::string v)
{
	if(p == "file")
	{
        file = std::atoi(v.c_str());
        std::string canvasFileName = "saves/game";
        canvasFileName += Itoa(file + 1);
        canvasFileName += ".bmp";
        canvas = load_bitmap(canvasFileName.c_str(), 0);
		return;
	}
	Entity::SetParameter(p, v);
}