/*! Removes the option \a name from the ImageFileType that handles files
    with the given \a suffix. If the option is not present \c false is
    returned, \c true otherwise.

    \param[in] suffix File extension to choose the image file type
                      this option applies to.
    \param[in] name Name of the option.
    \return Whether the option was successfully removed.
 */
bool
    ImageFileHandlerBase::unsetOption(
        const std::string &suffix,
        const std::string &name   )
{
    bool           retVal = false;
    ImageFileType *type   = getFileType(suffix.c_str());
    
    if(type != NULL)
    {
        retVal = type->unsetOption(name);
    }
    
    return retVal;
}