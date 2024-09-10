SoSeparator *
SceneFileObj::readSceneFile(void)
{
    SoInput input;
    SoSeparator *s;
    FILE *f = NULL;

    if (_sceneFileName[0] == '<') {
	char *p = _sceneFileName+1;

	while (*p) {
	    if (! isdigit(*p))
		break;
	    p++;
	}

	if (*p == '\0') {
	    int fd = atoi(_sceneFileName+1);

	    if ((f = fdopen(fd, "r")) == NULL) {
		return (NULL);
	    }
	    input.setFilePointer(f);
	}
    }

    if (f == NULL) {
	if (!input.openFile(_sceneFileName))
	    return NULL;
    }
    s = SoDB::readAll(&input);
    input.closeFile();

    return s;
}