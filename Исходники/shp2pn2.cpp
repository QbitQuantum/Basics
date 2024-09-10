int main(int argc, char** argv)
{
    QApplication app(argc,argv);


    qDebug( " Syntax: pnt2svg [-i shp-sourcefile -o pn2-targetfile]" );

    QString inputFilename;
    int inputIndex = app.arguments().indexOf( "-i" );
    if ( inputIndex > 0 && inputIndex + 1 < argc )
        inputFilename = app.arguments().at( inputIndex + 1 );

    QString outputFilename = "output.pn2";
    int outputIndex = app.arguments().indexOf("-o");
    if ( outputIndex > 0 && outputIndex + 1 < argc )
        outputFilename = app.arguments().at( outputIndex + 1 );
    
 
    MarbleModel *model = new MarbleModel;
    ParsingRunnerManager* manager = new ParsingRunnerManager( model->pluginManager() );
 
    GeoDataDocument* document = manager->openFile( inputFilename );

    QFile file( outputFilename );
    file.open( QIODevice::WriteOnly );
    QDataStream stream( &file );

    quint8 fileHeaderVersion;
    quint32 fileHeaderPolygons;

    fileHeaderVersion = 1;
    fileHeaderPolygons = 0; // This variable counts the number of polygons inside the document

    QVector<GeoDataFeature*>::Iterator i = document->begin();
    QVector<GeoDataFeature*>::Iterator const end = document->end();

    for (; i != end; ++i) {
        GeoDataPlacemark* placemark = static_cast<GeoDataPlacemark*>( *i );

        // Types of placemarks
        GeoDataPolygon* polygon = dynamic_cast<GeoDataPolygon*>( placemark->geometry() );
        GeoDataLineString* linestring = dynamic_cast<GeoDataLineString*>( placemark->geometry() );
        GeoDataMultiGeometry* multigeom = dynamic_cast<GeoDataMultiGeometry*>( placemark->geometry() );

        if ( polygon ) {
            fileHeaderPolygons += 1 + polygon->innerBoundaries().size(); // outer boundary + number of inner boundaries of the polygon
        }

        if ( linestring ) {
            ++fileHeaderPolygons;
        }

        if ( multigeom ) {
            fileHeaderPolygons += multigeom->size(); // number of polygons inside the multigeometry
        }
    }

    stream << fileHeaderVersion << fileHeaderPolygons;

    i = document->begin();

    quint32 polyCurrentID = 0;
    quint32 polyParentNodes;
    quint8 polyFlag; 

    for ( ; i != end; ++i ) {
        GeoDataPlacemark* placemark = static_cast<GeoDataPlacemark*>( *i );

        // Types of placemarks
        GeoDataPolygon* polygon = dynamic_cast<GeoDataPolygon*>( placemark->geometry() );
        GeoDataLineString* linestring = dynamic_cast<GeoDataLineString*>( placemark->geometry() );
        GeoDataMultiGeometry* multigeom = dynamic_cast<GeoDataMultiGeometry*>( placemark->geometry() );

        if ( polygon ) {

            // Outer boundary
            ++polyCurrentID;
            QVector<GeoDataCoordinates>::Iterator jBegin = polygon->outerBoundary().begin();
            QVector<GeoDataCoordinates>::Iterator jEnd = polygon->outerBoundary().end();
            polyParentNodes = getParentNodes( jBegin, jEnd );
            polyFlag = OUTERBOUNDARY;

            stream << polyCurrentID << polyParentNodes << polyFlag;

            printAllNodes( jBegin, jEnd, stream );

            // Inner boundaries
            QVector<GeoDataLinearRing>::Iterator inner = polygon->innerBoundaries().begin();
            QVector<GeoDataLinearRing>::Iterator innerEnd = polygon->innerBoundaries().end();

            for ( ; inner != innerEnd; ++inner ) {
                GeoDataLinearRing linearring = static_cast<GeoDataLinearRing>( *inner );

                ++polyCurrentID;
                jBegin = linearring.begin();
                jEnd = linearring.end();
                polyParentNodes = getParentNodes( jBegin, jEnd );
                polyFlag = INNERBOUNDARY;

                stream << polyCurrentID << polyParentNodes << polyFlag;

                printAllNodes( jBegin, jEnd, stream );
               
            }

        }

        if ( linestring ) {
            ++polyCurrentID;
            QVector<GeoDataCoordinates>::Iterator jBegin = linestring->begin();
            QVector<GeoDataCoordinates>::Iterator jEnd = linestring->end();
            polyParentNodes = getParentNodes( jBegin, jEnd );
            if ( linestring->isClosed() )
                polyFlag = LINEARRING;
            else
                polyFlag = LINESTRING;

            stream << polyCurrentID << polyParentNodes << polyFlag;

            printAllNodes( jBegin, jEnd, stream );
        }

        if ( multigeom ) {

            QVector<GeoDataGeometry*>::Iterator multi = multigeom->begin();
            QVector<GeoDataGeometry*>::Iterator multiEnd = multigeom->end();
    
            for ( ; multi != multiEnd; ++multi ) {
                GeoDataLineString* currLineString = dynamic_cast<GeoDataLineString*>( *multi );

                ++polyCurrentID;
                QVector<GeoDataCoordinates>::Iterator jBegin = currLineString->begin();
                QVector<GeoDataCoordinates>::Iterator jEnd = currLineString->end();
                polyParentNodes = getParentNodes( jBegin, jEnd );
                if ( currLineString->isClosed() )
                    polyFlag = LINEARRING;
                else
                    polyFlag = LINESTRING;

                stream << polyCurrentID << polyParentNodes << polyFlag;

                printAllNodes( jBegin, jEnd, stream );
            }
            
        }
    }

}