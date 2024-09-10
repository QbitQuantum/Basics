	IShape* CreateLine(Vector2d p1, Vector2d p2, int r, int g, int b, int size) {
		sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(p1.x, p1.y));
		rect->setPosition(sf::Vector2f(p1.x, p1.y));
		float len = (p1-p2).Len();
		rect->setSize(sf::Vector2f(len, size));

		Vector2d target = p2-p1;
		Vector2d orig = p1; orig.x = int(len); orig.y = 0;
		orig = orig.GetNormalized();
		target = target.GetNormalized();
		float dot = target.Dot(orig);
		//float angle = atan2f(target.y-orig.y, target.x-orig.x) * 57.2957795;
		float angle = acos(dot) * 57.2957795;
		if(p1.y > p2.y)
			angle = -angle;

		rect->rotate(angle);
		SFMLShape * shape = new SFMLShape(rect);
		rect->setFillColor(sf::Color(r,g,b));

		return shape;
	}