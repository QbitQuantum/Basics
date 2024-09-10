// Format the XML corresponding to the FileInfo geolocation info
CNCSError CNCSJP2File::CNCSJP2GMLGeoLocationBox::FormatXML(char *pBuf, UINT32 nBufLen)
{
    if (NCSIsFileInfoExGeoreferenced(&m_GMLFileInfo))
    {
        CNCSGDTEPSG& Epsg = *CNCSGDTEPSG::Instance();
        char szSRSName[32];
        *szSRSName = '\0';
        UINT32 nEPSGCode = Epsg.GetEPSG(m_GMLFileInfo.szProjection, m_GMLFileInfo.szDatum);
        if (nEPSGCode) sprintf(szSRSName," srsName=\"epsg:%u\"",nEPSGCode);
        else if (strnicmp(m_GMLFileInfo.szProjection,"epsg:",5) == 0) //we have an unknown EPSG
        {
            char *pColon = strchr(m_GMLFileInfo.szProjection,':');
            pColon++;
            nEPSGCode = atoi(pColon); //grab EPSG code
            sprintf(szSRSName," srsName=\"epsg:%u\"",nEPSGCode);
        }
        double dRegistrationX = m_GMLFileInfo.fOriginX;
        double dRegistrationY = m_GMLFileInfo.fOriginY;
        double dCellSizeX = m_GMLFileInfo.fCellIncrementX;
        double dCellSizeY = m_GMLFileInfo.fCellIncrementY;
        //move rotation to the (-180,180] interval
        while (m_GMLFileInfo.fCWRotationDegrees <= -180.0)
            m_GMLFileInfo.fCWRotationDegrees += 360.0;
        while (m_GMLFileInfo.fCWRotationDegrees > 180.0)
            m_GMLFileInfo.fCWRotationDegrees -= 360.0;
        double dCWRotationDegrees = m_GMLFileInfo.fCWRotationDegrees;
        UINT32 nImageWidth = m_GMLFileInfo.nSizeX;
        UINT32 nImageHeight = m_GMLFileInfo.nSizeY;
        IEEE8 dMeterFactor = 1.0;

        if(m_GMLFileInfo.eCellSizeUnits == ECW_CELL_UNITS_FEET) {
            dCellSizeX *= NCS_FEET_FACTOR;
            dCellSizeY *= NCS_FEET_FACTOR;
            dRegistrationX *= NCS_FEET_FACTOR;
            dRegistrationY *= NCS_FEET_FACTOR;
        }

        double p1[3] = { (sin(Deg2Rad(dCWRotationDegrees)) * dCellSizeX), (cos(Deg2Rad(dCWRotationDegrees)) * dCellSizeY), 0.0 };
        double p2[3] = { (cos(Deg2Rad(dCWRotationDegrees)) * dCellSizeX), -(sin(Deg2Rad(dCWRotationDegrees)) * dCellSizeY), 0.0 };

        snprintf(pBuf, nBufLen,
                 "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
                 "<JPEG2000_GeoLocation>\r\n"
                 "	<gml:RectifiedGrid xmlns:gml=\"http://www.opengis.net/gml\" gml:id=\"JPEG2000_GeoLocation_1\" dimension=\"2\">\r\n"
                 "		<gml:origin>\r\n"
                 "			<gml:Point gml:id=\"JPEG2000_Origin\"%s>\r\n"
                 "				<gml:coordinates>%.13lf,%.13lf</gml:coordinates>\r\n"
                 "			</gml:Point>\r\n"
                 "			</gml:origin>\r\n"
                 "		<gml:offsetVector gml:id=\"p1\">%.13lf,%.13lf,%.13lf</gml:offsetVector>\r\n"
                 "		<gml:offsetVector gml:id=\"p2\">%.13lf,%.13lf,%.13lf</gml:offsetVector>\r\n"
                 "	</gml:RectifiedGrid>\r\n"
                 "</JPEG2000_GeoLocation>\r\n",
                 szSRSName,
                 dRegistrationX - nImageHeight * p1[0],
                 dRegistrationY - nImageHeight * p1[1],
                 p1[0], p1[1], p1[2],
                 p2[0], p2[1], p2[2]);
        return(NCS_SUCCESS);
    } else {
#ifdef NCS_BUILD_WITH_STDERR_DEBUG_INFO
        fprintf(stderr,"File not georeferenced: no GML box created\n");
#endif
        return(CNCSError(NCS_JP2_GEODATA_NOT_GEOREFERENCED));
    }
}