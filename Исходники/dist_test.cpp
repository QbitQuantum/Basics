int start()
{
    X3DWriter* writer[2];
    writer[0] = new X3DWriterXML();
    writer[1] = new X3DWriterFI();

    for(int i = 0; i< 2; i++)
    {
        X3DWriter* w = writer[i];
        if (i == 0)
            w->openFile("iotest.x3d");
        else
            w->openFile("iotest.x3db");
        w->startX3DDocument();

        w->startNode(ID::Shape);
        w->startNode(ID::Appearance);
        w->startNode(ID::Material);
        w->setSFVec3f(ID::diffuseColor, 1.0f, 0.0f, 0.0f);
        w->setSFFloat(ID::transparency, 0.1f);
        w->endNode();
        w->endNode(); // Appearance
        w->startNode(ID::Box);
        w->setSFVec3f(ID::size, 0.5f, 0.5f, 0.5f);
        w->endNode(); // Box
        w->endNode();//Shape
        w->endX3DDocument();
        w->closeFile();

        delete w;
    }


    for(int i = 0; i< 2; i++)
    {
        X3DLoader loader;
        MyNodeHandler handler;
        loader.setNodeHandler(&handler);
        try {
            if (i == 0)
                loader.load("iotest.x3d");
            else
                loader.load("iotest.x3db");
        } catch (X3DParseException& e)
        {
            cerr << "Error while parsing file:" << endl;
            cerr << e.getMessage() << " (Line: " << e.getLineNumber() << ", Column: " << e.getColumnNumber() << ")" << endl;
            return 1;
        }
    }
    return 0;
}