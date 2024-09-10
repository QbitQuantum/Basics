long long pathNumber(int x, int y, int depth) {
	long long result = 0;

	if (depth == 0)
		return 1;

	// try upper cell
	if (!alreadySeenCell.contains(
				QPair<int, int>(x, y - 1)
				)
	)
	{
		alreadySeenCell.insert(
				QPair<int, int>(x, y - 1)
				);
		result += pathNumber(x, y - 1, depth - 1);
		alreadySeenCell.remove(
				QPair<int, int>(x, y - 1)
				);
	}
		

	// try lower cell
	if (!alreadySeenCell.contains(
				QPair<int, int>(x, y + 1)
				)
	)
	{
		alreadySeenCell.insert(
				QPair<int, int>(x, y + 1)
				);
		result += pathNumber(x, y + 1, depth - 1);
		alreadySeenCell.remove(
				QPair<int, int>(x, y + 1)
				);
	}

	// try left cell
	if (!alreadySeenCell.contains(
				QPair<int, int>(x - 1, y)
				)
	)
	{
		alreadySeenCell.insert(
				QPair<int, int>(x - 1, y)
				);
		result += pathNumber(x - 1, y, depth - 1);
		alreadySeenCell.remove(
				QPair<int, int>(x - 1, y)
				);
	}

	// try right cell
	if (!alreadySeenCell.contains(
				QPair<int, int>(x + 1, y)
				)
	)
	{
		alreadySeenCell.insert(
				QPair<int, int>(x + 1, y)
				);
		result += pathNumber(x + 1, y, depth - 1);
		alreadySeenCell.remove(
				QPair<int, int>(x + 1, y)
				);
	}

	return result;
}