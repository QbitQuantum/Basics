QueueItem::QueueItem( const QueueItem& rhs )
    : DataOStream()
    , _impl( new detail::QueueItem( *rhs._impl ))
{
    enableSave();
    _enable();
}