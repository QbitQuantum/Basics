void Incident::save(TiXmlDocument* xmlDocument)
{
    std::string data;

    // create incident node
    TiXmlElement* incidentElement = new TiXmlElement( "incident" );
    incidentElement->SetAttribute( "name", _name.c_str() );
    incidentElement->SetAttribute( "location", _locationId );

    // create virtues node        
    TiXmlElement* virtuesElement = new TiXmlElement( "virtues" );
    virtuesElement->SetAttribute( "checksum", checksum( &_virtues, sizeof(Virtues) ) );
    encrypt( data, &_virtues, sizeof(Virtues), _name.c_str() );
    virtuesElement->SetAttribute( "data", data.c_str() );
    incidentElement->InsertEndChild( *virtuesElement );
    delete virtuesElement;

    xmlDocument->InsertEndChild( *incidentElement );
    delete incidentElement;
}