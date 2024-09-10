//
// Add the given value to the list of suggested values for this parameter 
//
bool ParameterDefinition::addValueOption(const char *value)
{
    int position;

    if (!this->valueOptions) {
	int size = 4;
	this->valueOptions = (char**)MALLOC(size * sizeof(char*));
	memset(this->valueOptions,0, size * sizeof(char*));
	position = 0;
    } else {
	position = 0;
	while (this->valueOptions[position])
	    position++;	
	int nextpos = position + 1;
	switch (nextpos) {
	    case 4:
	    case 8:
	    case 16:
	    case 32:
	    case 64:
		this->valueOptions = (char**)REALLOC((void*)this->valueOptions,
					2 * nextpos * sizeof(char*));
		memset(this->valueOptions + nextpos, 0, nextpos*sizeof(char*));
		break;
	    default:
		if (nextpos > 64) {
		    fprintf(stderr,
			"Too many value options for parameter (ignoring)");
		    position = -1;
		}
		break;
	}
    }
    if (position >= 0) {
	this->valueOptions[position] = DuplicateString(value);
	return true;
    } else {
	return false;
    }

}