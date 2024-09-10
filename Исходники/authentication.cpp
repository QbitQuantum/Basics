void Authentication_GetKeyHash( char *_sourceKey, char *_destKey, int _hashToken )
{
    HashData( _sourceKey, _hashToken, _destKey );
}