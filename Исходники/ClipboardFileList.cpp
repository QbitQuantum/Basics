void ClipboardFileList::EnumerateClass( Reflect::Compositor<ClipboardFileList>& comp )
{
    Reflect::Field* fieldFiles = comp.AddField( &ClipboardFileList::m_Files, "m_Files" );
    Reflect::Field* fieldIsDirty = comp.AddField( &ClipboardFileList::m_IsDirty, "m_IsDirty", Reflect::FieldFlags::Discard );
}