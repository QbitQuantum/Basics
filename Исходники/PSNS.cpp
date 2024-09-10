//#TPT-Directive ElementHeader Element_PSNS static int update(UPDATE_FUNC_ARGS)
int Element_PSNS::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, rt;
	if ((parts[i].tmp == 0 && sim->pv[y/CELL][x/CELL] > parts[i].temp-273.15f) || (parts[i].tmp == 2 && sim->pv[y/CELL][x/CELL] < parts[i].temp-273.15f))
	{
		parts[i].life = 0;
		for (rx = -2; rx <= 2; rx++)
			for (ry = -2; ry <= 2; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y+ry][x+rx];
					if (!r)
						continue;
					if (sim->parts_avg(i,ID(r),PT_INSL) != PT_INSL)
					{
						rt = TYP(r);
						if ((sim->elements[rt].Properties&PROP_CONDUCTS) && !(rt==PT_WATR||rt==PT_SLTW||rt==PT_NTCT||rt==PT_PTCT||rt==PT_INWR) && parts[ID(r)].life==0)
						{
							parts[ID(r)].life = 4;
							parts[ID(r)].ctype = rt;
							sim->part_change_type(ID(r),x+rx,y+ry,PT_SPRK);
						}
					}
				}
	}
	if (parts[i].tmp == 1)
	{
		parts[i].life = 0;
		bool setFilt = true;
		float photonWl = sim->pv[y / CELL][x / CELL];
		if (setFilt)
		{
			int nx, ny;
			for (rx = -1; rx <= 1; rx++)
				for (ry = -1; ry <= 1; ry++)
					if (BOUNDS_CHECK && (rx || ry))
					{
						r = pmap[y + ry][x + rx];
						if (!r)
							continue;
						nx = x + rx;
						ny = y + ry;
						while (TYP(r) == PT_FILT)
						{
							parts[ID(r)].ctype = 0x10000000 + roundl(photonWl) + 256;
							nx += rx;
							ny += ry;
							if (nx < 0 || ny < 0 || nx >= XRES || ny >= YRES)
								break;
							r = pmap[ny][nx];
						}
					}
		}
	}
	return 0;
}