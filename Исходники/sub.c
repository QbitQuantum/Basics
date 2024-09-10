int
devread(Device *d, Off b, void *c)
{
	int e;

	for (;;)
		switch(d->type) {
		case Devcw:
			return cwread(d, b, c);

		case Devjuke:
			d = d->j.m;
			break;

		case Devro:
			return roread(d, b, c);

		case Devwren:
			return wrenread(d, b, c);

		case Devworm:
		case Devlworm:
			return wormread(d, b, c);

		case Devfworm:
			return fwormread(d, b, c);

		case Devmcat:
			return mcatread(d, b, c);

		case Devmlev:
			return mlevread(d, b, c);

		case Devmirr:
			return mirrread(d, b, c);

		case Devpart:
			return partread(d, b, c);

		case Devswab:
			e = devread(d->swab.d, b, c);
			if(e == 0)
				swab(c, 0);
			return e;

		case Devnone:
			print("read from device none(%lld)\n", (Wideoff)b);
			return 1;
		default:
			panic("illegal device in devread: %Z %lld",
				d, (Wideoff)b);
			return 1;
		}
}