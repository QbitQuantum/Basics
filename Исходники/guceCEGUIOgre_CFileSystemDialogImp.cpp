CEGUI::Window*
CFileSystemDialogImp::GetWindowImp( void )
{GUCE_TRACE;

    return static_cast< CEGUI::Window* >( GetWindow()->GetImplementationPtr() );
}