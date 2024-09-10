void ObjectDataOStream::enableCommit( const uint128_t& version,
                                      const Nodes& receivers )
{
    _version = version;
    _setupConnections( receivers );
    _enable();
}