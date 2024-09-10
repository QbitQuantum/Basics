/*
    Format a variant value as a string representation of time.
    This method was written to convert a QVariant of type ??? (the type used to represent times in CA),
    but should cope with a variant of any type.
*/
void QEStringFormatting::formatFromTime( const QVariant &value ) {
    bool okay;
    double seconds;
    double time;
    QString sign;
    int days;
    int hours;
    int mins;
    int secs;
    int nanoSecs;
    QString image;
    int effectivePrecision;
    QString fraction;


    if( value.type() == QVariant::String )
        stream << value.toString();
    else {
        seconds = value.toDouble( &okay );
        if (okay) {
           if (seconds >= 0.0) {
              time = seconds;
              sign= "";
           } else {
              time = -seconds;
              sign= "-";
           }

           #define EXTRACT(item, spi) { item = int (floor (time / spi)); time = time - (spi * item); }

           EXTRACT (days, 86400.0);
           EXTRACT (hours, 3600.0);
           EXTRACT (mins, 60.0);
           EXTRACT (secs, 1.0);
           EXTRACT (nanoSecs, 1.0E-9);

           #undef EXTRACT

           // Include days field if rquired or if requested.
           //
           if ((days > 0) || leadingZero) {
              image.sprintf ("%d %02d:%02d:%02d", days, hours, mins, secs);
           } else {
              image.sprintf ("%02d:%02d:%02d", hours, mins, secs);
           }

           // Select data base or user precision as appropriate.
           //
           effectivePrecision = useDbPrecision ? dbPrecision : precision;
           if (effectivePrecision > 9) effectivePrecision = 9;

           if (effectivePrecision > 0) {
              fraction.sprintf (".%09d", nanoSecs);
              fraction.truncate( effectivePrecision + 1 );
           } else {
              fraction = "";
           }

           stream << sign << image << fraction;

        } else {
            stream << QString( "not a valid numeric" );
        }
    }
}