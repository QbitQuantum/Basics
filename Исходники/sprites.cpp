//
// R_InstallSpriteLump
// Local function for R_InitSprites.
//
// [RH] Removed checks for coexistance of rotation 0 with other
//		rotations and made it look more like BOOM's version.
//
static bool R_InstallSpriteLump (FTextureID lump, unsigned frame, char rot, bool flipped, spriteframewithrotate *sprtemp, int &maxframe)
{
	unsigned rotation;

	if (rot >= '0' && rot <= '9')
	{
		rotation = rot - '0';
	}
	else if (rot >= 'A')
	{
		rotation = rot - 'A' + 10;
	}
	else
	{
		rotation = 17;
	}

	if (frame >= MAX_SPRITE_FRAMES || rotation > 16)
	{
		Printf (TEXTCOLOR_RED"R_InstallSpriteLump: Bad frame characters in lump %s\n", TexMan[lump]->Name.GetChars());
		return false;
	}

	if ((int)frame > maxframe)
		maxframe = frame;

	if (rotation == 0)
	{
		// the lump should be used for all rotations
        // false=0, true=1, but array initialised to -1
        // allows doom to have a "no value set yet" boolean value!
		int r;

		for (r = 14; r >= 0; r -= 2)
		{
			if (!sprtemp[frame].Texture[r].isValid())
			{
				sprtemp[frame].Texture[r] = lump;
				if (flipped)
				{
					sprtemp[frame].Flip |= 1 << r;
				}
				sprtemp[frame].rotate = false;
			}
		}
	}
	else
	{
		if (rotation <= 8)
		{
			rotation = (rotation - 1) * 2;
		}
		else
		{
			rotation = (rotation - 9) * 2 + 1;
		}

		if (!sprtemp[frame].Texture[rotation].isValid())
		{
			// the lump is only used for one rotation
			sprtemp[frame].Texture[rotation] = lump;
			if (flipped)
			{
				sprtemp[frame].Flip |= 1 << rotation;
			}
			sprtemp[frame].rotate = true;
		}
	}
	return true;
}