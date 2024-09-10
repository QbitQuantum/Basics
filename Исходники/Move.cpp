const QString Move::saveMove(bool isRoot)
{
	QString str;
	
	if (!isRoot)
		str += ";"; //"\n;";
	
	if (x != -1 && y != -1 && gameMode != modeEdit)
	{
		// Write something like 'B[aa]'
		str += stoneColor == stoneBlack ? "B" : "W";
 		str += "[" + Matrix::coordsToString(x-1, y-1) + "]";
	}
	
	// Save edited moves
	str += matrix->saveEditedMoves(parent != NULL ? parent->getMatrix() : 0);
	
	// Save marks
	str += matrix->saveMarks();
	
	// Add nodename, if we have one
	if (!nodeName.isNull() && !nodeName.isEmpty())
	{
		// simpletext
		str += "N[";
		str += nodeName;
		str += "]";
	}

	// Add next move's color
	if (PLinfo)
	{
		if (PLnextMove == stoneBlack)
			str += "PL[B]";
		else
			str += "PL[W]";
	}

	// Add comment, if we have one
	if (!comment.isNull() && !comment.isEmpty())
	{
		// text
		QString tmp = comment;
		int pos = 0;
		while ((pos = tmp.find("]", pos)) != -1 && static_cast<unsigned int>(pos) < tmp.length())
		{
			tmp.replace(pos, 1, "\\]");
			pos += 2;
		}
		str += "C[";
		str += tmp;
		str += "]";
	}

	// time info
	if (timeinfo && !isRoot && (int) timeLeft)
	{
		if (stoneColor == stoneBlack)
			str += "BL[";
		else
			str += "WL[";
		str += QString::number(timeLeft);
		str += "]";

		// open moves info
		if (openMoves > 0)
		{
			if (stoneColor == stoneBlack)
				str += "OB[";
			else
				str += "OW[";
			str += QString::number(openMoves);
			str += "]";
		}
	}

	// Add unknown properties, if we have some
	if (!unknownProperty.isNull() && !unknownProperty.isEmpty())
	{
		// complete property
		str += unknownProperty;
	}
	
	return str;
}