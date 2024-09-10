bool IVDFileHandler::init( const file_args_t& file_params )
{
    struct stat sb;
    _fileD = ::open( file_params[0].c_str(), O_RDONLY );
    if( _fileD == -1 )
    {
        ::perror("open");
        return false;
    }

    if( ::fstat( _fileD, &sb ) == -1 )
    {
        ::perror("fstat");
        return false;
    }
    _lengthFile = sb.st_size;

    _startFile = (char*) ::mmap(NULL, _lengthFile, PROT_READ, MAP_PRIVATE, _fileD, 0);
    if( _startFile == MAP_FAILED )
    {
        ::perror("mmap");
        return false;
    }

    char * data = _startFile;
    _nLevels = *( (level_t*) data );
    data += sizeof( level_t );
    _level   = *( (level_t*) data );
    data += sizeof( level_t );
    _cubeInc = *( (int32_t*) data );
    data += sizeof( int32_t);
    const int32_t xdim = *( (int32_t*) data );
    data += sizeof( int32_t );
    const int32_t ydim = *( (int32_t*) data );
    data += sizeof( int32_t );
    const int32_t zdim = *( (int32_t*) data );
    data += sizeof( int32_t );
    _realDimension.set( xdim, ydim, zdim );
    _xGrid = (float*) data;
    data += xdim * sizeof( float );
    _yGrid = (float*) data;
    data += ydim * sizeof( float );
    _zGrid = (float*) data;
    data += zdim * sizeof( float );
    _idStart  = 1 << 3 * _level;
    _idFinish = ( 2 << 3 * _level ) - 1;
    _numCubes = _idFinish - _idStart + 1;
    _offsets = (int32_t*) data;
    data += _numCubes * sizeof( int32_t );
    _cubes = (float*) data;

    const uint32_t dim = exp2f( _nLevels - _level );
    _cubeSize = powf( dim + 2 * _cubeInc, 3 );

    return true;
}