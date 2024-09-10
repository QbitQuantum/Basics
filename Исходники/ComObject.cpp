ComObject::~ComObject ()
{
    if (m_registeredActiveObject) {
        // TODO: This call may return an error but I don't want to throw an
        // exception from a destructor.
        RevokeActiveObject(m_activeObjectHandle, 0);
    }

    m_iidToAdapterMap.forEach(Delete());
    delete m_pDispatch;

    // Execute destructor Tcl command if defined.
    int length;
    Tcl_GetStringFromObj(m_destructor, &length);
    if (length > 0) {
        TclObject script(m_destructor);
        script.lappend(m_servant);
        eval(script);
    }

    ComModule::instance().unlock();
//    Tcl_Release(reinterpret_cast<ClientData>(m_interp));
}