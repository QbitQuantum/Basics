static int64_t alignTimeDown(int64_t ts, int unit, int count)
{
	switch (unit) {
	case FT_SECOND:
		ts = FLOOR(ts, count * 1000);
		break;
	case FT_MINUTE:
		ts = FLOOR(ts, count * 60 * 1000);
		break;
	case FT_HOUR:
		ts = FLOOR(ts, count * 3600 * 1000);
	default:
		// TODO: more FT_XXX
		break;
	}

	return ts;
}