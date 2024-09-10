void save_principal_axis_properties()
{
	gchar *axesfile;
	FILE *file;

	axesfile = g_strdup_printf("%s%sprincipalAxes",gabedit_directory(),G_DIR_SEPARATOR_S);

	file = FOpen(axesfile, "w");

 	fprintf(file,"%d\n",axis.show);
 	fprintf(file,"%d\n",axis.negative);
 	fprintf(file,"%lf %lf %lf\n",axis.origin[0],axis.origin[1],axis.origin[2]);
 	fprintf(file,"%lf\n",axis.radius);
 	fprintf(file,"%lf\n",axis.scal);
 	fprintf(file,"%lf %lf %lf\n",axis.firstColor[0],axis.firstColor[1],axis.firstColor[2]);
 	fprintf(file,"%lf %lf %lf\n",axis.secondColor[0],axis.secondColor[1],axis.secondColor[2]);
 	fprintf(file,"%lf %lf %lf\n",axis.thirdColor[0], axis.thirdColor[1], axis.thirdColor[2]);

	fclose(file);

	g_free(axesfile);
}