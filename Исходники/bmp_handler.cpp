void _bmpImage::setSourceFile(char *path)
{
	_splitpath_s(path, drive, dir, fname, ext );

	workingDir = drive;
	workingDir += dir;
	workingDir += fname;

	sourceFile = path;
}