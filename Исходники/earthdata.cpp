void EarthData::LoadCities()
{
    float startTime = GetHighResTime();

    m_cities.EmptyAndDelete();

    TextReader *cities = g_fileSystem->GetTextReader( "data/earth/cities.dat" );
    AppAssert( cities && cities->IsOpen() );
    
    int numCities = 0;
    
    while( cities->ReadLine() )
    {
        char *line = cities->GetRestOfLine();

        char name[256];
        char country[256];
        float latitude, longitude;
        int population;
        int capital;
        
        strncpy( name, line, 40 );
        for( int i = 39; i >= 0; --i )
        {
            if( name[i] != ' ' ) 
            {
                name[i+1] = '\x0';
                break;
            }
        }

        strncpy( country, line+41, 40 );
        for( int i = 39; i >= 0; --i )
        {
            if( country[i] != ' ' )
            {
                country[i+1] = '\x0';
                break;
            }
        }

        sscanf( line+82, "%f %f %d %d", &longitude, &latitude, &population, &capital );

        City *city = new City();
        city->m_name = strdup( strupr(name) );
        city->m_country = strdup( strupr(country) );
        city->m_longitude = Fixed::FromDouble(longitude);
        city->m_latitude = Fixed::FromDouble(latitude);
        city->m_population = population;
        city->m_capital = capital;         
        city->SetRadarRange( Fixed::FromDouble(sqrtf( sqrtf(city->m_population) ) / 4.0f) );

        m_cities.PutData( city );
        ++numCities;
    }
    
    delete cities;

    float totalTime = GetHighResTime() - startTime;
    AppDebugOut( "Parsing City data (%d cities) : %dms\n", numCities, int( totalTime * 1000.0f ) );
}