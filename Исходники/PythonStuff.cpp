static void remove_block(int x, int y, int z, int xw, int yw, int zw)
{
	lpoint3d p1;
	p1.x = 1024-y;
	p1.y = 1024-x;
	p1.z = 256 - z;
	lpoint3d p2;
	p2.x = 1024-(y + yw);
	p2.y = 1024-(x + xw);
	p2.z = 256 - (z + zw);
	setrect(&p1, &p2, -1);
	updatevxl();
}