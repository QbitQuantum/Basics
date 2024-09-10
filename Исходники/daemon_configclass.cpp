DaemonConfig::DaemonConfig( string ConfigFile )
{
 NORMAL_LOG( "DaemonConfig::DaemonConfig; Reading config file " << ConfigFile );

 ConfigurationXML = ReadStringFromFile( ConfigFile );

 DEBUG_LOG( "DaemonConfig::DaemonConfig; The configuration read in: " << ConfigurationXML );

 ConfigurationXML = NormalizeString( Parse_XML( ConfigurationXML, "LGI" ) );

 if( ConfigurationXML.empty() )
  CRITICAL_LOG( "DaemonConfig::DaemonConfig; No data in LGI tag found" );
}