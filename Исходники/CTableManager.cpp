///////////////////////////////////////////////////////////////////////////////
/// Provides a shared read lock to the table with the given identifier.
/// @pre None.
/// @post Return a lock interface to the stored device table.
/// @param identifier The name of the device table to obtain a lock on.
/// @return Shared pointer to a read lock over the specified table.
/// @limitations None.
///////////////////////////////////////////////////////////////////////////////
CTableManager::TReader CTableManager::AsReader( std::string identifier )
{
    Logger.Trace << __PRETTY_FUNCTION__ << std::endl;
    return TReader( new TReadLock(GetInstance(identifier)) );
}