DrawList::Item::Item(const Body &body, Point pos, Point blur, float cloak, float clip, int swizzle, int step)
	: position{static_cast<float>(pos.X()), static_cast<float>(pos.Y())}, clip(clip), flags(swizzle)
{
	Body::Frame frame = body.GetFrame(step);
	tex0 = frame.first;
	tex1 = frame.second;
	flags |= static_cast<uint32_t>(frame.fade * 256.f) << 8;
	
	double width = body.Width();
	double height = body.Height();
	Point unit = body.Facing().Unit();
	Point uw = unit * width;
	Point uh = unit * height;
	
	if(clip < 1.)
	{
		// "clip" is the fraction of its height that we're clipping the sprite
		// to. We still want it to start at the same spot, though.
		pos -= uh * ((1. - clip) * .5);
		position[0] = static_cast<float>(pos.X());
		position[1] = static_cast<float>(pos.Y());
		uh *= clip;
	}
	
	// (0, -1) means a zero-degree rotation (since negative Y is up).
	transform[0] = -uw.Y();
	transform[1] = uw.X();
	transform[2] = -uh.X();
	transform[3] = -uh.Y();
	
	// Calculate the blur vector, in texture coordinates.
	this->blur[0] = unit.Cross(blur) / (width * 4.);
	this->blur[1] = -unit.Dot(blur) / (height * 4.);

	if(cloak > 0.)
		Cloak(cloak);
}