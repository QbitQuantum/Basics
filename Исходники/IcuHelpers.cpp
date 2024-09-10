void
registerIcuHelpers( Parser & parser )
{

  parser.registerHelper(
    "camelize", [] (
      const RenderingContext & c,
      const helper_params & p,
      const helper_options & ) -> QVariant
    {
      auto _text( p.value( 0 ));
      //
      static Transliterator *t = nullptr;
      if( t == nullptr ) {
        UErrorCode status = U_ZERO_ERROR;
        t = Transliterator::createInstance(
          "Latin; Latin-ASCII; Title; [^[:Letter:][:Number:]] Remove",
          UTRANS_FORWARD, status );
        if( U_FAILURE( status )) {
          c.error( QString( "ICU Helper: camelize: Error %1 (%2)" ) .arg( status ) .arg( u_errorName( status )));
          return _text;
        }
      }
      //
      UnicodeString text = UnicodeString::fromUTF8( StringPiece( _text.toByteArray() ));
      t->transliterate( text );
      //
      QByteArray out;
      text.toUTF8String( out );
      //
      if( out.isEmpty() || ! std::isalpha( out.at( 0 )) )
        out.prepend( '_' );
      //
      return out;
    } );

  parser.registerHelper(
    "icu_transform", [] (
      const RenderingContext & c,
      const helper_params & p,
      const helper_options & )
    {
      return icuTransform(
        p.value( 0 ).toByteArray(),
        p.value( 1 ).toByteArray(),
        c );
    } );

    //"NFD; [:Nonspacing Mark:] Remove; NFC", UTRANS_FORWARD, status);
    // Any-Latin; Latin-ASCII

  parser.registerBlockHelper(
    "icu_transform_b", [] (
      RenderingContext & context,
      const helper_params & params,
      const helper_options &,
      const NodeList & truthy,
      const NodeList &
      )
    {
      QString text;
      QTextStream stream( & text, QIODevice::WriteOnly );
      context.render( truthy, & stream );
      //
      context.output( icuTransform(
          params.value( 0 ).toByteArray(),
          text.toUtf8(),
          context ));
    } );

}