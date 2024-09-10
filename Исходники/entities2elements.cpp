void coord(entity *ent, int precision,char* delim, char * units, double scaling, char *out){
	// Pairs of coords with units will be used so often build a function build a dedicated function for returning such
	
	char temp[20];
	if (units != NULL) scaling = 1;  // If units have been defined then ignore the scaling parameter
	strcat(out, gcvt(scaling*ent->ret_x(),precision,temp) );  // There must be a better function for double to ascii conversion that is defined in most libraries
	if (units != NULL) strcat(out, units);
	strcat(out, delim);
	strcat(out, gcvt(-scaling*ent->ret_y(),precision,temp) ); // Because SVG has a the Y-axis pointed down multiply by -1
	if (units != NULL) strcat(out, units);
	strcat(out, " ");
}