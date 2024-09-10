static UINT HLS2Int (double n)
{
	return min (255, (UINT) (.5 + n * 255.));
}