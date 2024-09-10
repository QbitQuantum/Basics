/*
  =======================================================================================
  Map coordinates of the edge by first marking the first coordinate, and then using
  the following mapping, all of the remaining coordinates using 1 byte each.

  4 | 3 | 2
  5 | 0 | 1
  6 | 7 | 8
  =======================================================================================
*/
bool PixelChain::write(HANDLE fh, int id)
{
	char buff[256], temp[32];
	unsigned long bytesWritten;
	int len;
	
	if (!fh) {
		return false;
	}

	memset(buff, 0, sizeof(buff));
	sprintf_s(buff, sizeof(buff), "%d,%d", id, _numPoints);
	
	if (_numPoints > 1) {
		sprintf_s(temp, sizeof(temp), ",%d,%d", _pt[0].x, _pt[0].y);
		strncat_s(buff, sizeof(buff), temp, _TRUNCATE);

		len = strlen(buff);
		memset(buff + len, 0, sizeof(buff) - len);

		if (_numPoints > 2) {
			buff[len] = ',';
			len++;
		
			for (int i = 1; i < _numPoints; i++) {
				buff[len] = '0' + mapPointMovement(i - 1);
				len++;

				if (len > sizeof(buff) - 4) {
					WriteFile(fh, buff, len, &bytesWritten, NULL);
					memset(buff, 0, sizeof(buff));
					len = 0;
				}
			}
		}
	}

	strncat_s(buff, sizeof(buff), "\r\n", _TRUNCATE);

	WriteFile(fh, buff, strlen(buff), &bytesWritten, NULL);

	return true;
}