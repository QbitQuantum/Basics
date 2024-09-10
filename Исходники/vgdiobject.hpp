    /** Function to set the internal object handle. This function will
    delete any previous GDI object held in this class. This can be used to
    re-use VGDIObject classes that wrap different logical GDI objects. In a
    pure OOP world, this would not be considered good behaviour. But in
    reality, this offers a great deal of functionality to objects that
    expose internal GDI objects that can be manipulated. If we did not
    allow this to occur, the end result would be many dynamically allocated
    objects used to similuate this behaviour. For instance, if class A
    allows customization of a VBrush object, without this ability that
    brush would have to be deleted and reallocated with the new settings.
    This adds an obvious problem when dealing with GDI objects in that it
    makes it more prone to allocation and deallocation errors, and forces
    the use of pointers when references would be preferred.*/
    VBOOL			SetHandle(HGDIOBJ hGDIObject)
    {
        /* Delete and current object wrapped by this class.*/
        Delete();

        /* hGDIObject should be valid.*/
        VBOOL bValidObject =
            (hGDIObject && GetObjectType(hGDIObject) != 0) ? VTRUE : VFALSE;
        VASSERT(bValidObject)

        /* Save handle.*/
        m_hGDIObject = (bValidObject) ? hGDIObject : NULL;

        return (m_hGDIObject) ? VTRUE : VFALSE;
    }