//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
Object* Polyline::Factory (Stream& rkStream)
{
    Polyline* pkObject = new Polyline;
    Stream::Link* pkLink = new Stream::Link(pkObject);
    pkObject->Load(rkStream,pkLink);
    return pkObject;
}