//Load the asset from the specified file
bool GMAsset_Sprite::Load(const QFileInfo &file)
{
    this->GMAsset::Load(file);
    QFile spriteFile(file.absoluteFilePath());
    if (!spriteFile.exists()) return false; //File does not exist
    if (!spriteFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return false; //Failed to open the file
    QXmlQuery query;
    QXmlResultItems  result;
    QXmlItem item;
    query.setFocus(&spriteFile);

    //Type of sprite
    query.setQuery("sprite/type/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
        SetType(item.toAtomicValue().toInt());
    }

    QPoint origin;
    //X Origin
    query.setQuery("sprite/xorig/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
        origin.setX(item.toAtomicValue().toInt());
    }

    //Y Origin
    query.setQuery("sprite/yorigin/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
        origin.setY(item.toAtomicValue().toInt());
    }
    SetOrigin(origin);

    //Collision Kind
    query.setQuery("sprite/colkind/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
        SetCollisionKind((CollisionKind)item.toAtomicValue().toInt());
    }

    //Color Tolerance
    query.setQuery("sprite/coltolerance/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
        SetColTolerance(item.toAtomicValue().toInt());
    }

    //Seprate Masks?
    query.setQuery("sprite/sepmasks/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
        SetSepMasks(item.toAtomicValue().toBool());
    }

    //Bounding Box Mode
    query.setQuery("sprite/bboxmode/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
        SetBboxMode((BoundingBoxMode)item.toAtomicValue().toInt());
    }

    QRect bbox; //Bounding box
    //Bounding Box Left
    query.setQuery("sprite/bbox_left/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
       bbox.setLeft(item.toAtomicValue().toInt());
    }

    //Bounding Box Right
    query.setQuery("sprite/bbox_right/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
       bbox.setRight(item.toAtomicValue().toInt());
    }

    //Bounding Box Top
    query.setQuery("sprite/bbox_top/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
       bbox.setTop(item.toAtomicValue().toInt());
    }

    //Bounding Box Bottom
    query.setQuery("sprite/bbox_bottom/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
       bbox.setBottom(item.toAtomicValue().toInt());
    }

    SetBbox(bbox); //Set the bounding box

    //Horizontal Tile?
    query.setQuery("sprite/HTile/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
       SetHTile(item.toAtomicValue().toBool());
    }

    //Vertical Tile?
    query.setQuery("sprite/VTile/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
       SetVTile(item.toAtomicValue().toBool());
    }

    //For 3D?
    query.setQuery("sprite/For3D/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
       SetFor3D(item.toAtomicValue().toBool());
    }


    QSize size;
    //Width of sprite
    query.setQuery("sprite/width/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
       size.setWidth(item.toAtomicValue().toInt());
    }

    //Height of Sprite
    query.setQuery("sprite/height/string()");
    query.evaluateTo(&result);
    item = result.next();
    if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
       size.setHeight(item.toAtomicValue().toInt());
    }

    SetSize(size); //Set the size of the sprite


    //We will now get all of the frames for the sprite (NOTE: This ignores the index attribute and just adds them in order)
    query.setQuery("sprite/frames/frame/string()");
    query.evaluateTo(&result);
    item = result.next();
    while (!item.isNull()) {
        if (item.isAtomicValue()) { //Make sure the item is an atomic value (ie, the node string was returned)
            QString frameFilePath = GetFileInfo().absolutePath().append("/").append(item.toAtomicValue().toString());
            frames.push_back(QFileInfo(frameFilePath));
        }
        item = result.next();
    }

    spriteFile.close(); //Close the XML File
    return true;
}