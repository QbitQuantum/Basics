RectF TextureFilm::get(int id)
{
	std::map<int, RectF>::iterator itr = frames.find(id);
	if (itr != frames.end()) return itr->second;

	return RectF();
}