void VRML_Begin( FILE *f )
{
	fprintf( f, VRML_header );
	fprintf( f, "children [\n" );
	Fprintf( f, "\t\tNavigationInfo { headlight FALSE }\n" );
	Fprintf( f, "\t\tDirectionalLight {\n\t\t direction 0 -5 1 }\n\n" );
}