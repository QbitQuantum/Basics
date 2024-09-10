sf::Image transform(sf::Image image, LFSR lfsr)
{
	 sf::Vector2u size = image.getSize();
	 int x,y;
	 sf::Color p;

	 for(int x=0; x<size.x; x++)
	 {
		  for(int y=0; y<size.y; y++)
		  {
				p = image.getPixel(x,y);
				p.r = p.r^lfsr.generate(8);
			   p.g = p.g^lfsr.generate(16);
				p.b = p.b^lfsr.generate(20);
				image.setPixel(x,y,p);
		  }
	 }

	 return image;

}