void FileGrabForeground::draw(DrawActionBase *action, Viewport *port)
{
    if(getActive() == false)
        return;
    
    if(getName().empty())
    {
        FWARNING(("FileGrabForeground::draw: no name ?!?\n"));
        return;
    }
    
    Image::PixelFormat pixelFormat = (Image::PixelFormat)getPixelFormat();
    pixelFormat = (pixelFormat == 0) ? Image::OSG_RGB_PF : pixelFormat;
    
    // do we have an image yet? If not, create one.
    if(getImage() == NullFC)
    {
        beginEditCP(this->getPtr(), FileGrabForeground::ImageFieldMask);
        {
			ImagePtr iPtr = Image::create();
			
			iPtr->set(pixelFormat, 1);
			
            setImage(iPtr);
        }
        endEditCP  (this->getPtr(), FileGrabForeground::ImageFieldMask);
    }
    else if(getImage()->getPixelFormat() != pixelFormat)
    {
        ImagePtr iPtr = getImage();
        
        beginEditCP(iPtr, Image::PixelFormatFieldMask);
        {
            iPtr->reformat(pixelFormat);
        }
        endEditCP  (iPtr, Image::PixelFormatFieldMask);
    }
    
    // read pixels
    Inherited::draw(action,port);
    
    Char8 *name = new Char8 [ getName().size() + 32 ]; // this is really 
                                                       // arbitrary... :(

    sprintf(name, getName().c_str(), getFrame());
    
    ImagePtr i = getImage();

    i->write(name);
    
    delete [] name;
    
    if(getIncrement() != false)
    {
        beginEditCP(this->getPtr(), FileGrabForeground::FrameFieldMask);
        {
            setFrame(getFrame() + 1);
        }
        endEditCP  (this->getPtr(), FileGrabForeground::FrameFieldMask);
    }   
}