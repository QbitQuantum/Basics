void KRFBDecoder::sendCutEvent( const QString &unicode )
{
  //
  // Warning: There is a bug in the RFB protocol because there is no way to find
  // out the codepage in use on the remote machine. This could be fixed by requiring
  // the remote server to use utf8 etc. but for now we have to assume they're the
  // same. I've reported this problem to the ORL guys, but they apparantly have no
  // immediate plans to fix the issue. :-( (rich)
  //

  CARD8 padding[3];
  QCString text = unicode.local8Bit();
  CARD32 length = text.length();
  length = Swap32IfLE( length );

  con->write( &ClientCutTextId, 1 );
  con->write( &padding, 3 );
  con->write( &length, 4 );
  con->write( text.data(), length );
}