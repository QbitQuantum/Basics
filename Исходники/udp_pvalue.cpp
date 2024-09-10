char* pValue::toStr()
{
    int i1, i2;
    char *tval = new char[16];
    switch(type) {
	case SHORTINT:
	    return fcvt(*(short*)data, 0, &i1, &i2);
	    break;
	case INTEGER:
	    return fcvt(*(int*)data, 0, &i1, &i2);
	    break;
	case DOUBLE:
	    gcvt(*(double*)data, 8, tval);
	    return tval;
	    break;
	case STRING:
	    return data;
	    break;
	default:
	    //BUG
	    
	    return NULL;
    };
    
}