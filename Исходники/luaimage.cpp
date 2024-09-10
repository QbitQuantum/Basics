CLuaImage::CLuaImage(const char *file) : CBaseLuaWidget(""), m_iImageW(0), m_iImageH(0)
{
    Fl_Shared_Image *img = Fl_Shared_Image::get(file);
    
    if (img)
    {
        if ((img->w() > MaxImageW()) || (img->h() > MaxImageH()))
        {
            int neww, newh;
            GetScaledImageSize(img->w(), img->h(), MaxImageW(), MaxImageH(), neww, newh);
            Fl_Image *temp = img->copy(neww, newh);
            img->release();
            img = (Fl_Shared_Image *)temp;
        }

        Fl_Box *imgbox = new Fl_Box(0, 0, img->w(), img->h());
        imgbox->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        imgbox->image(img);
        GetGroup()->add(imgbox);
        
        m_iImageW = img->w();
        m_iImageH = img->h();
    }
    else
        GetGroup()->hide();
}