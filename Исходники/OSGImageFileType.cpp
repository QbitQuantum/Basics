/*!
Tries to store the raster data to the given mem block.
Will include a ImageFileType::Head description for the derived
concreate mimeType.
*/
UInt64 ImageFileType::store(const ImagePtr &image,
                            UChar8 *buffer, Int32 memSize)
{
    Head            *head;
    unsigned long   dataSize = 0, headSize = sizeof(Head);
    unsigned long   attachmentSize;
    UChar8          *dest;
    const UChar8    *src = image->getData();
    std::map<std::string, std::string>::const_iterator aI;
    std::string     value;

    attachmentSize = 0;

    // get attachment size
    /*
    ImageGenericAttPtr att=ImageGenericAttPtr::dcast(
        const_cast<Image*>(image.getCPtr())->findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));
    if(att != NullFC)
    {
        for(i = 0; i < (att->getType().getNumFieldDescs()-1); ++i)
        {
            FieldDescription *fieldDesc=att->getType().getFieldDescription(i);
            Field *field=att->getField(i);
            if (fieldDesc && field) 
            {
                field->getValueByStr(value);
                attachmentSize += strlen( fieldDesc->getName().str() ) + 1;
                attachmentSize += value.length() + 1;
              
                std::cout << fieldDesc->getName().str() << std::endl; 
                std::cout << value << std::endl; 
            }
            else 
            {
                FFATAL (("Invalid Attachment in ImageFileType::store()\n"));
            }
        }
    }
    */

    if (buffer) 
    {
        head = reinterpret_cast<Head *>(buffer);

        head->pixelFormat    = image->getPixelFormat();
        head->width          = image->getWidth();
        head->height         = image->getHeight();
        head->depth          = image->getDepth();
        head->mipmapCount    = image->getMipMapCount();
        head->frameCount     = image->getFrameCount();
        head->frameDelay     = short(image->getFrameDelay() * 1000.0);
        head->sideCount      = image->getSideCount();
        head->dataType       = image->getDataType();
        head->attachmentSize = static_cast<unsigned short>(attachmentSize);
        head->hostToNet();
      
        strcpy(head->suffix, _suffixList.front().str());
      
        dest = static_cast<UChar8 *>(buffer + headSize);

        if (src) 
            dataSize = static_cast<unsigned long>(
                storeData(image, dest, memSize - headSize));

        dest = static_cast<UChar8 *>(buffer + headSize + dataSize);

        /*
        if(att != NullFC)
        {
            for(i = 0; i < (att->getType().getNumFieldDescs()-1); ++i)
            {
                FieldDescription *fieldDesc=att->getType().getFieldDescription(i);
                Field *field=att->getField(i);
                if (field && fieldDesc) 
                {
                    field->getValueByStr(value);

                    l = strlen( fieldDesc->getName().str() );
                    for (i = 0; i < l; i++)
                      *dest++ = fieldDesc->getName().str()[i];
                    *dest++ = 0;
                    l = value.length();
                    for (i = 0; i < l; i++)
                      *dest++ = value[i];
                    *dest++ = 0;
                }
                else
                {
                    FFATAL (("Invalid Attachment in ImageFileType::store()\n"));
                }
            }
        }
        */

        FDEBUG (( "Store image data: %lu (%lu/%lu/%lu)\n",
                  headSize + dataSize + attachmentSize, headSize, dataSize, 
                  attachmentSize ));
    }
    else {
        FFATAL (("Invalid buffer in ImageFileType::store()\n"));
    }
  
    return (headSize + dataSize + attachmentSize);

}