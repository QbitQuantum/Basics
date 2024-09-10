bool BObject::process(Game& game)
{
	Common& common = *game.common;
	
	pos += vel;
	
	auto ipos = ftoi(pos);
	
	if(!game.level.inside(ipos))
	{
		return false;
	}
	else
	{
		PalIdx c = game.level.pixel(ipos);
		Material m = game.level.mat(ipos);
		
		if(m.background())
			vel.y += LC(BObjGravity);

		LTRACE(blod, c, xpos, ipos.x);
		LTRACE(blod, c, ypos, ipos.y);
			
		if((c >= 1 && c <= 2)
		|| (c >= 77 && c <= 79)) // TODO: Read from EXE
		{
			game.level.setPixel(ipos, 77 + game.rand(3), common);
			return false;
		}
		else if(m.anyDirt())
		{
			game.level.setPixel(ipos, 82 + game.rand(3), common);
			return false;
		}
		else if(m.rock())
		{
			game.level.setPixel(ipos, 85 + game.rand(3), common);
			return false;
		}
	}
	
	return true;
}