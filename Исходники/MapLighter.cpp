//----------------------------------------------------------------------
void MapLighter::CalcMapShadow (const Vector3 &sun)
{
    uint  height = MapUtil::getSingleton().getMapHeight ();
    uint  width = MapUtil::getSingleton().getMapWidth ();
    Real *heightMap = MapUtil::getSingleton().getHeightData ();

    std::cout << "Shadow Map Calc : ";
	std::cout << "Dir: " << sun.x << "," << sun.y << "," << sun.z << std::endl;

	/* Allocate space for the shadow map */
    const uint size = width * height;
    uchar *ShadowMap = new uchar[size];
    memset (ShadowMap, 0, size * sizeof (uchar));
    // Assign the color texture
    mShadowMap.loadDynamicImage  (ShadowMap, 
        static_cast <size_t> (width), 
        static_cast <size_t> (height), 1, 
        PF_L8, true);

    /* Make sure the light source is normalised */
    const Vector3 LightDirection = sun.normalisedCopy();

//    LightDirection.x /= PagingLandScapeOptions::getSingleton().scale.x;
//    LightDirection.y /= PagingLandScapeOptions::getSingleton().scale.y;
//    LightDirection.z /= PagingLandScapeOptions::getSingleton().scale.z;


    if (LightDirection.y == 0.0f ) 
    {
        /* light vector horizontal*/
        /* all in shadow */
        return;
    }

    /* For each heightmap location */ 
    uint index_pixel = 0;
    for (uint j = 0; j < height; j++) 
     { 
        DEBUG_PROGRESS_OUTPUT(".")
        for (uint i = 0; i < width; i++) 
        {
            /* If already in shadow no need to compute again ?
             what if we store precise height at which it is not shadowed ?*/
            if (ShadowMap[index_pixel] == 0)
            {
                /* a line passing starting from heightmap point 
                    and following light direction*/
                Real terrain_height = heightMap[ index_pixel ];
                    
                if (fabs(LightDirection.x) < fabs(LightDirection.z))
                { 
                    int index_z = 1;
                    float index_x = LightDirection.x / LightDirection.z;
                    float index_y = LightDirection.y / LightDirection.z;
                    if (LightDirection.z < 0) 
                    {
                        index_x = -index_x; 
                        index_y = -index_y;
                        index_z = -index_z; 
                    }
                    int z = j + index_z;
                    float x = i + index_x;
                    terrain_height += index_y;
                    uint zmap = ((uint)z);
                    uint xmap = ((uint)x);
                    while  (//terrain_height >= 0.0f &&
                            xmap < width &&
                            zmap < height)
                    {        
                        if ((zmap < height) && 
                             heightMap[xmap + zmap*width] <= terrain_height)
                             ShadowMap[xmap + zmap*width] = 255; 
                    
                        x += index_x;
                        z += index_z;
                        terrain_height += index_y;

                        zmap = ((uint)z);
                        xmap = ((uint)x);
                     }
                }
                else 
                {
                    int index_x = 1;
                    float index_z = LightDirection.z / LightDirection.x;
                    float index_y = LightDirection.y / LightDirection.x;
                    if (LightDirection.x < 0) 
                    {
                        index_x = -index_x;  
                        index_y = -index_y;
                        index_z = -index_z;
                    }

                    float z = j + index_z;
                    int x = i + index_x;
                    terrain_height += index_y;
                    uint zmap = ((uint)z);
                    uint xmap = ((uint)x);
                    while (//terrain_height >= 0.0f &&
                            xmap < width &&
                            zmap < height)
                    {
                        if ((zmap < height) && 
                            heightMap[xmap + zmap*width] <= terrain_height)
                            ShadowMap[xmap + zmap*width] = 255;   
                        x += index_x; 
                        z += index_z;
                        terrain_height += index_y;
                        zmap = ((uint)z);
                        xmap = ((uint)x);
                    }
                 }
            }
            index_pixel++;
        }
    }

    std::cout << "\n";
}