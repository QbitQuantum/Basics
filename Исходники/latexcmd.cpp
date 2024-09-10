// convert character to attribute
CmdAttribute LatexCommands::getCharAttr(QChar ch)
{
	CmdAttribute attr;
	switch(ch.toAscii()) {
		case 'a':
			attr = CmdAttrAmsmath;
		break;
		case 'm':
			attr = CmdAttrMath;
		break;
		case 'l':
			attr = CmdAttrList;
		break;
		case 'v':
			attr = CmdAttrVerbatim;
		break;
		case 't':
			attr = CmdAttrTabular;
		break;
		case 'L':
			attr = CmdAttrLabel;
		break;
		case 'R':
			attr = CmdAttrReference;
		break;
		case 'C':
			attr = CmdAttrCitations;
		break;
		case 'I':
			attr = CmdAttrIncludes;
		break;
		case 'B':
			attr = CmdAttrBibliographies;
		break;
		default:
			KILE_DEBUG() << "\tLatexCommands error: unknown type of env/cmd: " << static_cast<char>(ch.unicode());
			return CmdAttrNone;
	}

	return attr;
}