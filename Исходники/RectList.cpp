sf::IntRect RectList::findRect(const sf::Vector2i& pixel_pointed, const sf::Image& image) {
	sf::IntRect rect;
	sf::Vector2i p_tmp;
	bool bound_found;

	//LEFT
	bound_found = false;
	p_tmp = pixel_pointed;
	while (true)
		if (image.getPixel(ARG_VECTOR(p_tmp)) != sf::Color::Magenta) {
			rect.width++;
			p_tmp.x -= 1;
			if (p_tmp.x < 0)
				break;
		}
		else {
			bound_found = true;
			rect.left = p_tmp.x+1;
			break;
		}
		
	if (!bound_found)
		return sf::IntRect();

	//RIGHT
	bound_found = false;
	p_tmp = sf::Vector2i(pixel_pointed.x+1, pixel_pointed.y); 
	while (true)
		if (image.getPixel(ARG_VECTOR(p_tmp)) != sf::Color::Magenta) {
			rect.width++;
			p_tmp.x += 1;
			if (p_tmp.x > image.getSize().x-1)
				break;
		}
		else {
			bound_found = true;
			break;
		}

	if (!bound_found)
		return sf::IntRect();

	//UP
	bound_found = false;
	p_tmp = pixel_pointed;
	while (true)
		if (image.getPixel(ARG_VECTOR(p_tmp)) != sf::Color::Magenta) {
			rect.height++;
			p_tmp.y -= 1;
			if (p_tmp.y < 0)
				break;
		}
		else {
			bound_found = true;
			rect.top = p_tmp.y+1;
			break;
		}
		
	if (!bound_found)
		return sf::IntRect();

	//DOWN
	bound_found = false;
	p_tmp = sf::Vector2i(pixel_pointed.x, pixel_pointed.y+1);
	while (true)
		if (image.getPixel(ARG_VECTOR(p_tmp)) != sf::Color::Magenta) {
			rect.height++;
			p_tmp.y += 1;
			if (p_tmp.y > image.getSize().y-1)
				break;
		}
		else {
			bound_found = true;
			break;
		}

	if (!bound_found)
		return sf::IntRect();

	return rect;
}