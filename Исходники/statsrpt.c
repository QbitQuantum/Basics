void writeSubcatchLoads()
{
    int i, j, p;
    double x;
    double* totals; 
    char  units[15];
    char  subcatchLine[] = "--------------------";
    char  pollutLine[]   = "--------------";

    // --- create an array to hold total loads for each pollutant
    totals = (double *) calloc(Nobjects[POLLUT], sizeof(double));
    if ( totals )
    {
        // --- print the table headings 
        WRITE("");
        WRITE("****************************");
        WRITE("Subcatchment Washoff Summary");
        WRITE("****************************");
        WRITE("");
        fprintf(Frpt.file, "\n  %s", subcatchLine);
        for (p = 0; p < Nobjects[POLLUT]; p++) fprintf(Frpt.file, "%s", pollutLine);
        fprintf(Frpt.file, "\n                      ");
        for (p = 0; p < Nobjects[POLLUT]; p++) fprintf(Frpt.file, "%14s", Pollut[p].ID);
        fprintf(Frpt.file, "\n  Subcatchment        ");
        for (p = 0; p < Nobjects[POLLUT]; p++)
        {
            i = UnitSystem;
            if ( Pollut[p].units == COUNT ) i = 2;
            strcpy(units, LoadUnitsWords[i]);
            fprintf(Frpt.file, "%14s", units);
            totals[p] = 0.0;
        }
        fprintf(Frpt.file, "\n  %s", subcatchLine);
        for (p = 0; p < Nobjects[POLLUT]; p++) fprintf(Frpt.file, "%s", pollutLine);

        // --- print the pollutant loadings from each subcatchment
        for ( j = 0; j < Nobjects[SUBCATCH]; j++ )
        {
            fprintf(Frpt.file, "\n  %-20s", Subcatch[j].ID);
            for (p = 0; p < Nobjects[POLLUT]; p++)
            {
                x = Subcatch[j].totalLoad[p];
                totals[p] += x;
                if ( Pollut[p].units == COUNT ) x = LOG10(x);
				fprintf(Frpt.file, "%14.3f", x); 
            }
        }

        // --- print the total loading of each pollutant
        fprintf(Frpt.file, "\n  %s", subcatchLine);
        for (p = 0; p < Nobjects[POLLUT]; p++) fprintf(Frpt.file, "%s", pollutLine);
        fprintf(Frpt.file, "\n  System              ");
        for (p = 0; p < Nobjects[POLLUT]; p++)
        {
            x = totals[p];
            if ( Pollut[p].units == COUNT ) x = LOG10(x);
			fprintf(Frpt.file, "%14.3f", x); 
        }
        free(totals);
        WRITE("");
    }
}