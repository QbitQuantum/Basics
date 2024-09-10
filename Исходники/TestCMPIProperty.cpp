void _getInstance(CIMClient & client)
{
    try
    {
        instance = client.getInstance(SOURCE_NAMESPACE, objectNames[0]);
        if (verbose)
        {
            XmlWriter::printInstanceElement(instance, PEGASUS_STD(cout));
            PEGASUS_STD (cout) << "+++++ getInstance completed successfully"
                               << PEGASUS_STD (endl);
        }
    }
    catch (Exception & e)
    {
        PEGASUS_STD (cerr) << "getInstance failed: " << e.getMessage ()
                           << PEGASUS_STD (endl);
        exit (-1);
    }
}