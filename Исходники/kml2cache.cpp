int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    QString inputFilename;
    int inputIndex = app.arguments().indexOf( "-i" );
    if ( inputIndex > 0 && inputIndex + 1 < argc ) {
        inputFilename = app.arguments().at( inputIndex + 1 );
    } else {
        qDebug( " Syntax: kml2cache -i sourcefile [-o cache-targetfile]" );
        return 1;
    }

    QString outputFilename = "output.cache";
    int outputIndex = app.arguments().indexOf("-o");
    if ( outputIndex > 0 && outputIndex + 1 < argc )
        outputFilename = app.arguments().at( outputIndex + 1 );

    ParsingRunnerManager* manager = new ParsingRunnerManager( new PluginManager );
    GeoDataDocument* document = manager->openFile( inputFilename );
    if (!document) {
        qDebug() << "Could not parse input file. No error message available unfortunately";
        return 2;
    }

    saveFile( outputFilename, document );
}