void ToltecsEngine::walk(byte *walkData) {
	int16 xdelta, ydelta, v8, v10, v11;
	int16 xstep, ystep;
	ScriptWalk walkInfo;

	walkInfo.y = READ_LE_UINT16(walkData + 0);
	walkInfo.x = READ_LE_UINT16(walkData + 2);
	walkInfo.y1 = READ_LE_UINT16(walkData + 4);
	walkInfo.x1 = READ_LE_UINT16(walkData + 6);
	walkInfo.y2 = READ_LE_UINT16(walkData + 8);
	walkInfo.x2 = READ_LE_UINT16(walkData + 10);
	walkInfo.yerror = READ_LE_UINT16(walkData + 12);
	walkInfo.xerror = READ_LE_UINT16(walkData + 14);
	walkInfo.mulValue = READ_LE_UINT16(walkData + 16);
	walkInfo.scaling = READ_LE_UINT16(walkData + 18);

	walkInfo.scaling = -_segmap->getScalingAtPoint(walkInfo.x, walkInfo.y);

	if (walkInfo.y1 < walkInfo.y2)
		ystep = -1;
	else
		ystep = 1;
	ydelta = ABS(walkInfo.y1 - walkInfo.y2) * _walkSpeedY;

	if (walkInfo.x1 < walkInfo.x2)
		xstep = -1;
	else
		xstep = 1;
	xdelta = ABS(walkInfo.x1 - walkInfo.x2) * _walkSpeedX;

	debug(0, "ToltecsEngine::walk() xdelta = %d; ydelta = %d", xdelta, ydelta);

	if (xdelta > ydelta)
		SWAP(xdelta, ydelta);

	v8 = 100 * xdelta;
	if (v8 != 0) {
		if (walkInfo.scaling > 0)
			v8 -= v8 * ABS(walkInfo.scaling) / 100;
		else
			v8 += v8 * ABS(walkInfo.scaling) / 100;
		if (ydelta != 0)
			v8 /= ydelta;
	}

	if (ydelta > ABS(walkInfo.x1 - walkInfo.x2) * _walkSpeedX) {
		v10 = 100 - walkInfo.scaling;
		v11 = v8;
  	} else {
		v10 = v8;
  		v11 = 100 - walkInfo.scaling;
	}

	walkInfo.yerror += walkInfo.mulValue * v10;
	while (walkInfo.yerror >= 100 * _walkSpeedY) {
		walkInfo.yerror -= 100 * _walkSpeedY;
		if (walkInfo.y == walkInfo.y1) {
			walkInfo.x = walkInfo.x1;
			break;
		}
		walkInfo.y += ystep;
	}

	walkInfo.xerror += walkInfo.mulValue * v11;
	while (walkInfo.xerror >= 100 * _walkSpeedX) {
		walkInfo.xerror -= 100 * _walkSpeedX;
		if (walkInfo.x == walkInfo.x1) {
			walkInfo.y = walkInfo.y1;
			break;
		}
		walkInfo.x += xstep;
	}

	WRITE_LE_UINT16(walkData + 0, walkInfo.y);
	WRITE_LE_UINT16(walkData + 2, walkInfo.x);
	WRITE_LE_UINT16(walkData + 4, walkInfo.y1);
	WRITE_LE_UINT16(walkData + 6, walkInfo.x1);
	WRITE_LE_UINT16(walkData + 8, walkInfo.y2);
	WRITE_LE_UINT16(walkData + 10, walkInfo.x2);
	WRITE_LE_UINT16(walkData + 12, walkInfo.yerror);
	WRITE_LE_UINT16(walkData + 14, walkInfo.xerror);
	WRITE_LE_UINT16(walkData + 16, walkInfo.mulValue);
	WRITE_LE_UINT16(walkData + 18, walkInfo.scaling);
}