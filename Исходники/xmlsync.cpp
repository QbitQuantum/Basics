void XmlSync::saveXml(QString path)
{
    QFile outFile(path);

    if( !outFile.open(QIODevice::WriteOnly))
    {
        fatalExit("Cannot open output file!");
    }

    QTextStream xmlOutStream(&outFile);
    xmlData_out.save(xmlOutStream, 2);
    xmlOutStream.flush();

    outFile.close();
}