string Edge305Device::getDeviceDescription() const {

    if (Log::enabledDbg()) Log::dbg("GpsDevice::getDeviceDescription() "+this->displayName);
/*

<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
<Device xmlns="http://www.garmin.com/xmlschemas/GarminDevice/v2" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.garmin.com/xmlschemas/GarminDevice/v2 http://www.garmin.com/xmlschemas/GarminDevicev2.xsd">

  <Model>
    <PartNumber>006-B0450-00</PartNumber>
    <SoftwareVersion>320</SoftwareVersion>
    <Description>EDGE305 Software Version 3.20</Description>
  </Model>

  <Id>3305091776</Id>
  <DisplayName>Your name</DisplayName>

  <MassStorageMode>
    <DataType>
      <Name>GPSData</Name>
      <File>
        <Specification>
          <Identifier>http://www.topografix.com/GPX/1/1</Identifier>
          <Documentation>http://www.topografix.com/GPX/1/1/gpx.xsd</Documentation>
        </Specification>
        <Location>
          <FileExtension>GPX</FileExtension>
        </Location>
        <TransferDirection>InputOutput</TransferDirection>
      </File>
    </DataType>
    <DataType>
      <Name>FitnessHistory</Name>
      <File>
        <Specification>
          <Identifier>http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2</Identifier>
          <Documentation>http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd</Documentation>
        </Specification>
        <Location>
          <FileExtension>TCX</FileExtension>
        </Location>
        <TransferDirection>OutputFromUnit</TransferDirection>
      </File>
    </DataType>
    <DataType>
      <Name>FitnessUserProfile</Name>
      <File>
        <Specification>
          <Identifier>http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2</Identifier>
          <Documentation>http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd</Documentation>
        </Specification>
        <Location>
          <BaseName>UserProfile</BaseName>
          <FileExtension>TCX</FileExtension>
        </Location>
        <TransferDirection>InputOutput</TransferDirection>
      </File>
    </DataType>
    <DataType>
      <Name>FitnessCourses</Name>
      <File>
        <Specification>
          <Identifier>http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2</Identifier>
          <Documentation>http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd</Documentation>
        </Specification>
        <Location>
          <FileExtension>TCX</FileExtension>
        </Location>
        <TransferDirection>InputOutput</TransferDirection>
      </File>
    </DataType>
    <DataType>
      <Name>FitnessWorkouts</Name>
      <File>
        <Specification>
          <Identifier>http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2</Identifier>
          <Documentation>http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd</Documentation>
        </Specification>
        <Location>
          <FileExtension>TCX</FileExtension>
        </Location>
        <TransferDirection>InputOutput</TransferDirection>
      </File>
    </DataType>
    <UpdateFile>
      <PartNumber>006-B0450-00</PartNumber>
      <Version>
        <Major>0</Major>
        <Minor>0</Minor>
      </Version>
      <Description>Missing</Description>
    </UpdateFile>
    <UpdateFile>
      <PartNumber>006-B0478-00</PartNumber>
      <Version>
        <Major>0</Major>
        <Minor>0</Minor>
      </Version>
      <Description>Missing</Description>
    </UpdateFile>
  </MassStorageMode>

  <GarminMode>
    <Protocols>
      <Application Id="918">
        <DataType>918</DataType>
      </Application>
    </Protocols>
    <Extensions>
      <GarminModeExtension xmlns="http://www.garmin.com/xmlschemas/GarminDeviceExtensions/v3">
        <MemoryRegion>
          <Id>5</Id>
          <Version>
            <Major>0</Major>
            <Minor>0</Minor>
          </Version>
          <Description>Missing</Description>
          <ExpectedPartNumber>006-B0450-00</ExpectedPartNumber>
          <CurrentPartNumber>006-B0450-00</CurrentPartNumber>
          <IsErased>true</IsErased>
          <IsUserUpdateable>true</IsUserUpdateable>
        </MemoryRegion>
        <MemoryRegion>
          <Id>14</Id>
          <Version>
            <Major>3</Major>
            <Minor>20</Minor>
          </Version>
          <Description>EDGE305</Description>
          <ExpectedPartNumber>006-B0450-00</ExpectedPartNumber>
          <CurrentPartNumber>006-B0450-00</CurrentPartNumber>
          <IsUserUpdateable>true</IsUserUpdateable>
        </MemoryRegion>
        <MemoryRegion>
          <Id>246</Id>
          <Version>
            <Major>0</Major>
            <Minor>0</Minor>
          </Version>
          <Description>Missing</Description>
          <ExpectedPartNumber>006-B0478-00</ExpectedPartNumber>
          <CurrentPartNumber>006-B0478-00</CurrentPartNumber>
          <IsErased>true</IsErased>
          <IsUserUpdateable>true</IsUserUpdateable>
        </MemoryRegion>
      </GarminModeExtension>
    </Extensions>
  </GarminMode>

</Device>


*/
    garmin_unit garmin;
    if ( garmin_init(&garmin,0) != 0 ) {
        garmin_close(&garmin);
    } else {
        Log::err("Opening of garmin device failed. No longer attached!?");
        return "";
    }


    TiXmlDocument doc;
    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "no" );
    doc.LinkEndChild( decl );

    /*<Device xmlns="http://www.garmin.com/xmlschemas/GarminDevice/v2"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xsi:schemaLocation="http://www.garmin.com/xmlschemas/GarminDevice/v2 http://www.garmin.com/xmlschemas/GarminDevicev2.xsd">*/

	TiXmlElement * device = new TiXmlElement( "Device" );
    device->SetAttribute("xmlns", "http://www.garmin.com/xmlschemas/GarminDevice/v2");
    device->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    device->SetAttribute("xsi:schemaLocation", "http://www.garmin.com/xmlschemas/GarminDevice/v2 http://www.garmin.com/xmlschemas/GarminDevicev2.xsd");
    doc.LinkEndChild( device );

/*<Model>
    <PartNumber>006-B0450-00</PartNumber>
    <SoftwareVersion>320</SoftwareVersion>
    <Description>EDGE305 Software Version 3.20</Description>
  </Model> */
	TiXmlElement * model = new TiXmlElement( "Model" );
	TiXmlElement * partnumber = new TiXmlElement( "PartNumber" );
	partnumber->LinkEndChild(new TiXmlText("006-B0450-00"));
	TiXmlElement * version = new TiXmlElement( "SoftwareVersion" );
	std::stringstream ss;
	ss << garmin.product.software_version;
	version->LinkEndChild(new TiXmlText( ss.str() ));
	TiXmlElement * descr = new TiXmlElement( "Description" );
	descr->LinkEndChild(new TiXmlText(this->displayName));
	model->LinkEndChild(partnumber);
	model->LinkEndChild(version);
	model->LinkEndChild(descr);
    device->LinkEndChild( model );

/*  <Id>3333333333</Id> */
	TiXmlElement * id = new TiXmlElement( "Id" );
	ss.str(""); // empty stringstream
	ss << garmin.id;
	id->LinkEndChild(new TiXmlText(ss.str()));
	device->LinkEndChild(id);
/*  <DisplayName>Your name</DisplayName>*/
	TiXmlElement * dispName = new TiXmlElement( "DisplayName" );
	dispName->LinkEndChild(new TiXmlText(this->displayName));
	device->LinkEndChild(dispName);

    TiXmlElement * massStorage = new TiXmlElement( "MassStorageMode" );
    device->LinkEndChild(massStorage);

/*
    <DataType>
      <Name>GPSData</Name>
      <File>
        <Specification>
          <Identifier>http://www.topografix.com/GPX/1/1</Identifier>
          <Documentation>http://www.topografix.com/GPX/1/1/gpx.xsd</Documentation>
        </Specification>
        <Location>
          <FileExtension>GPX</FileExtension>
        </Location>
        <TransferDirection>InputOutput</TransferDirection>
      </File>
    </DataType>
*/

    TiXmlElement * dataTypes = new TiXmlElement( "DataType" );
    massStorage->LinkEndChild(dataTypes);
    TiXmlElement * name = new TiXmlElement( "Name" );
   	name->LinkEndChild(new TiXmlText("GPSData"));
    dataTypes->LinkEndChild(name);

    TiXmlElement * file = new TiXmlElement( "File" );
    dataTypes->LinkEndChild(file);
    TiXmlElement * spec = new TiXmlElement( "Specification" );
    file->LinkEndChild(spec);

    TiXmlElement * identifier = new TiXmlElement( "Identifier" );
    identifier->LinkEndChild(new TiXmlText("http://www.topografix.com/GPX/1/1"));
    spec->LinkEndChild(identifier);

    TiXmlElement * docu = new TiXmlElement( "Documentation" );
   	docu->LinkEndChild(new TiXmlText("http://www.topografix.com/GPX/1/1/gpx.xsd"));
    spec->LinkEndChild(docu);

    TiXmlElement * loc = new TiXmlElement( "Location" );
    file->LinkEndChild(loc);

    TiXmlElement * fileEx = new TiXmlElement( "FileExtension" );
   	fileEx->LinkEndChild(new TiXmlText("GPX"));
    loc->LinkEndChild(fileEx);

    TiXmlElement * transferDir = new TiXmlElement( "TransferDirection" );
    transferDir->LinkEndChild(new TiXmlText("InputOutput"));
    file->LinkEndChild(transferDir);


    /*
    <DataType>
      <Name>FitnessHistory</Name>
      <File>
        <Specification>
          <Identifier>http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2</Identifier>
          <Documentation>http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd</Documentation>
        </Specification>
        <Location>
          <FileExtension>TCX</FileExtension>
        </Location>
        <TransferDirection>OutputFromUnit</TransferDirection>
      </File>
    </DataType>
    */
    dataTypes = new TiXmlElement( "DataType" );
    massStorage->LinkEndChild(dataTypes);
    name = new TiXmlElement( "Name" );
   	name->LinkEndChild(new TiXmlText("FitnessHistory"));
    dataTypes->LinkEndChild(name);

    file = new TiXmlElement( "File" );
    dataTypes->LinkEndChild(file);

    spec = new TiXmlElement( "Specification" );
    file->LinkEndChild(spec);

    identifier = new TiXmlElement( "Identifier" );
    identifier->LinkEndChild(new TiXmlText("http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2"));
    spec->LinkEndChild(identifier);

    docu = new TiXmlElement( "Documentation" );
   	docu->LinkEndChild(new TiXmlText("http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd"));
    spec->LinkEndChild(docu);

    loc = new TiXmlElement( "Location" );
    file->LinkEndChild(loc);

    fileEx = new TiXmlElement( "FileExtension" );
   	fileEx->LinkEndChild(new TiXmlText("TCX"));
    loc->LinkEndChild(fileEx);

    transferDir = new TiXmlElement( "TransferDirection" );
    transferDir->LinkEndChild(new TiXmlText("InputOutput"));
    file->LinkEndChild(transferDir);




    TiXmlPrinter printer;
	printer.SetIndent( "\t" );
	doc.Accept( &printer );
    string str = printer.Str();

    if (Log::enabledDbg()) Log::dbg("GpsDevice::getDeviceDescription() Done: "+this->displayName );
    return str;


}