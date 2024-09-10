QUrl ImdbParser::Parse( const QByteArray& data )
{
    DebugPrintFunc( "ImdbParser::Parse", data.size() );

    QString foundedPage( data );
    RegExpTools::SimplifyText( foundedPage );

    QRegExp reRedirect( "class=\"number\">1.</td><td class=\"title\"><a href=\"(.*)\">");
    QString redirectUrl( RegExpTools::ParseItem( foundedPage, reRedirect ) );

    QUrl posterUrl;

    if( !redirectUrl.isEmpty() )
    {
        redirectUrl = "http://www.imdb.com" + redirectUrl;

        QString str( request.runSync( QUrl( redirectUrl ) ) );
        RegExpTools::SimplifyText( str );

        DebugPrint( QString( "Simpified to: %1 bytes" ).arg( str.size() ) );

          // Title
        QRegExp reTitle( "h1 itemprop=\"name\".*>(.*)<span" );
        film.SetColumnData( FilmItem::TitleColumn, RegExpTools::ParseItem( str, reTitle ) );

          // Original title
        QRegExp reOriginalTitle( "div class=\"originalTitle\">(.*)<span" );
        film.SetColumnData( FilmItem::OriginalTitleColumn, RegExpTools::ParseItem( str, reOriginalTitle ) );

          // Tagline
        QRegExp reTagline( "Taglines:</h4>(.*)<" );
        film.SetColumnData( FilmItem::TaglineColumn, RegExpTools::ParseItem( str, reTagline ) );

          // Year
        QRegExp reYear( "Release Date:</h4>.*([0-9]{4})" );
        film.SetColumnData( FilmItem::YearColumn, RegExpTools::ParseItem( str, reYear ).toInt() );

          // Budget
        QRegExp reBudget( "Budget:</h4> \\$(.*)<span" );
        film.SetColumnData( FilmItem::BudgetColumn, RegExpTools::ParseItem( str, reBudget ).replace( " ", "" ).toDouble() );

          // Rating
        QRegExp reRating( "itemprop=\"ratingValue\">(.*)</span>" );
        film.SetColumnData( FilmItem::RatingColumn, RegExpTools::ParseItem( str, reRating ).replace( ",", "." ).toDouble() );

          // Country
        QRegExp reCountryList( "Countr.*</h4>(.*)</div>" );
        QRegExp reCountry( "href=\"/country/.*>(.*)</a>" );
        film.SetColumnData( FilmItem::CountryColumn, RegExpTools::ParseList( str, reCountryList, reCountry ) );

          // Genre
        QRegExp reGenreList( "Genres:</h4>(.*)</div>" );
        QRegExp reGenre( "href=\"/genre/.*>(.*)</a>" );
        film.SetColumnData( FilmItem::GenreColumn, RegExpTools::ParseList( str, reGenreList, reGenre ) );

          // Description
        QRegExp reDescription( "Storyline</h2><.*><p>(.*)<em class=\"nobr\">" );
        film.SetColumnData( FilmItem::DescriptionColumn, RegExpTools::ParseItem( str, reDescription ).replace( "<br><br>", "<br>\n" ) );

          // Advanced information

        QRegExp reName( "itemprop=\"name\">(.*)</span>" );

        if( AlexandraSettings::GetInstance()->GetParsersLoadAdvancedInfo() )
        {
            QString str( request.runSync( QUrl( redirectUrl + "fullcredits" ) ) );
            RegExpTools::SimplifyText( str );
            DebugPrint( QString( "Simpified to: %1 bytes" ).arg( str.size() ) );

              // Starring
            QRegExp reStarringList( "Cast <span>(.*)Produced by" );
            film.SetColumnData( FilmItem::StarringColumn, RegExpTools::ParseList( str, reStarringList, reName, 20 ) );  // 20 first actors

              // Director
            QRegExp reDirectorList( "Directed by(.*)Writing Credits" );
            reName = QRegExp( "href=\"/name/.*>(.*)</a>" );
            film.SetColumnData( FilmItem::DirectorColumn, RegExpTools::ParseList( str, reDirectorList, reName, 10 ) );  // 10 first directors

              // Screenwriter
            QRegExp reScreenwriterList( "Writing Credits(.*)Cast" );
            film.SetColumnData( FilmItem::ScreenwriterColumn, RegExpTools::ParseList( str, reScreenwriterList, reName, 10 ) ); // 10 first writers

              // Producer
            QRegExp reProducerList( "Produced by(.*)Music by" );
            film.SetColumnData( FilmItem::ProducerColumn, RegExpTools::ParseList( str, reProducerList, reName, 10 ) );  // 10 first producers

              // Composer
            QRegExp reComposerList( "Music by(.*)Film Editing by" );
            film.SetColumnData( FilmItem::ComposerColumn, RegExpTools::ParseList( str, reComposerList, reName ) );
        }
        else
        {
              // Starring
            QRegExp reStarringList( "Cast</h2>(.*)</table>" );
            film.SetColumnData( FilmItem::StarringColumn, RegExpTools::ParseList( str, reStarringList, reName ) );

              // Director
            QRegExp reDirectorList( "Director.*</h4>(.*)</div>" );
            QRegExp reName( "itemprop=\"name\">(.*)</span>" );
            film.SetColumnData( FilmItem::DirectorColumn, RegExpTools::ParseList( str, reDirectorList, reName ) );

              // Screenwriter
            QRegExp reScreenwriterList( "Writer.*</h4>(.*)</div>" );
            film.SetColumnData( FilmItem::ScreenwriterColumn, RegExpTools::ParseList( str, reScreenwriterList, reName ) );
        }

          // Poster

        if( AlexandraSettings::GetInstance()->GetParsersLoadBigPoster() )
        {
            QRegExp rePoster( "div class=\"poster\"><a href=\"(.*)\"" );
            QString s = QString( request.runSync( QUrl( "http://www.imdb.com" + RegExpTools::ParseItem( str, rePoster ) ) ) );

            RegExpTools::SimplifyText( s );
            DebugPrint( QString( "Simpified to: %1 bytes" ).arg( s.size() ) );

            rePoster = QRegExp( "id=\"primary-img\".*src=\"(.*)\"" );
            posterUrl = RegExpTools::ParseItem( s, rePoster );
        }

        if( posterUrl.isEmpty() ) // Small poster
        {
            QRegExp rePoster( "div class=\"poster\"><.*><img.*src=\"(.*)\"" );
            posterUrl = RegExpTools::ParseItem( str, rePoster );
        }

        DebugPrint( "Text parsed!" );
        emit Loaded( film, posterUrl );
    }
    else
    {
        emit Error( "Movie not found!" );
    }

    return( posterUrl );
}