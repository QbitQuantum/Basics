QStringList AudioCdRecord::arguments() const
{
    QStringList args;

/*! --------------------- Normal Arguments --------------------!*/
    args << "-v";

    if( publicRead()           )        args << "-r";
    if( dummy()                )        args << "-dummy";
    if( force()                )        args << "-force";
    if( sessionAtOnce()        )        args << "-sao";
    if( trackAtOnce()          )        args << "-tao";
    if( swab()                 )        args << "-swab";
    if( multiSession()         )        args << "-multi";
    if( pad()                  )        args << "-pad";
    if( pad() && padSize() > 0 )        args << QString::number( padSize() );
    if( eject()                )        args << "-eject";

    if( ringBuffer() > 0       )        args << "fs="     + QString::number( ringBuffer() );
    if( minimumBuffer() > 0    )        args << "minbuf=" + QString::number( minimumBuffer() );
    if( speed() > 0            )        args << "speed="  + QString::number( speed() );

    args << "dev=" + currentDevice().toQString();
    args << "-audio";
    args << files();
    /*! -----------------------------------------------------------!*/

    return args;
}