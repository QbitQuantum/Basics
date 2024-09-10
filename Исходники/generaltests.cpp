    Vector vector;
    FixStation station;
    QList<WallsMessage> messages;
    QString comment;

    QObject::connect(&parser, &WallsSurveyParser::parsedVector, [&](Vector v) { vector = v; });
    QObject::connect(&parser, &WallsSurveyParser::parsedFixStation, [&](FixStation s) { station = s; });
    QObject::connect(&parser, &WallsSurveyParser::message, [&](WallsMessage m) { messages << m; });
    QObject::connect(&parser, &WallsSurveyParser::parsedComment, [&](QString c) { comment = c; });

    SECTION( "vector line parsing tests" ) {
        parser.parseLine("A1 A2 2.5 350 2.3");

        REQUIRE( vector.from() == "A1" );
        REQUIRE( vector.to() == "A2" );
        REQUIRE( vector.distance() == ULength(2.5, Length::Meters) );
        REQUIRE( vector.frontAzimuth() == UAngle(350, Angle::Degrees) );
        REQUIRE( !vector.backAzimuth().isValid() );
        REQUIRE( vector.frontInclination() == UAngle(2.3, Angle::Degrees) );
        REQUIRE( !vector.backInclination().isValid() );

        SECTION( "station prefixes" ) {
            parser.parseLine(":A1 A2 2.5 350 2.3");
            REQUIRE( vector.from() == ":A1" );

            parser.parseLine("::A1 A2 2.5 350 2.3");
            REQUIRE( vector.from() == "::A1" );

            parser.parseLine(":::A1 A2 2.5 350 2.3");
            REQUIRE( vector.from() == ":::A1" );
