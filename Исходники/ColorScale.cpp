void ColorScale::draw(sf::Image& img,const sf::Vector2f& start,const sf::Vector2f& end,GradientStyle::GradientStyle style, int size) const
{

	sf::Color (*pFunction)(sf::Color*,int,const sf::Vector2f&,const sf::Vector2f&,int,int);

	sf::Color* tab =new sf::Color[size];
	fillTab(tab,size);

	switch (style)
	{
		case GradientStyle::Linear : pFunction = GradientLinear; break;
		case GradientStyle::Circle : pFunction = GradientCircle; break;
		case GradientStyle::Radial : pFunction = GradientRadial; break;
		case GradientStyle::Reflex : pFunction = GradientReflex; break;

		default: pFunction = GradientLinear;  break;
	}

	for(int i=0;i<img.GetWidth();i++)
	{
		for(int j=0;j<img.GetHeight();j++)
		{
			img.SetPixel(i,j,pFunction(tab,size,start,end,i,j));
		}
	}
	delete[] tab;
}