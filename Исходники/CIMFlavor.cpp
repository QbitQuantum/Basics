String CIMFlavor::toString () const
{
    String tmp;

    if (this->hasFlavor (CIMFlavor::OVERRIDABLE))
        tmp.append("OVERRIDABLE ");

    if (this->hasFlavor (CIMFlavor::TOSUBCLASS))
        tmp.append("TOSUBCLASS ");

    if (this->hasFlavor (CIMFlavor::TOINSTANCE))
        tmp.append("TOINSTANCE ");

    if (this->hasFlavor (CIMFlavor::TRANSLATABLE))
        tmp.append("TRANSLATABLE ");

    if (this->hasFlavor (CIMFlavor::DISABLEOVERRIDE))
        tmp.append("DISABLEOVERRIDE ");

    if (this->hasFlavor (CIMFlavor::RESTRICTED))
        tmp.append("RESTRICTED ");

    if (tmp.size ())
        tmp.remove (tmp.size () - 1);

    return tmp;
}