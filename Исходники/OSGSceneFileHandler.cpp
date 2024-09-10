/*! Retrieves the option \a name from the SceneFileType that handles files
    with the given \a suffix and stores its value in \a value.
    Returns \c true if successful, \c false otherwise in which case \a value has
    an undefined value.
    
    \param[in] suffix File extension to choose the scene file type
                      this option applies to.
    \param[in] name Name of the option.
    \param[out] value Value the option.
    \return Whether the option is present for the given SceneFileType.
 */
bool
    SceneFileHandlerBase::getOption(
        const std::string &suffix,
        const std::string &name,
              std::string &value  )
{
    bool           retVal = false;
    SceneFileType *type   = getFileType(suffix.c_str());
    
    if(type != NULL)
    {
        retVal = type->getOption(name, value);
    }
    
    return retVal;
}