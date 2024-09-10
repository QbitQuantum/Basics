            Openni2Helper()
            {
                openni::OpenNI::initialize();
                openni::OpenNI::enumerateDevices( &_deviceInfos );

                _camInfos.resize( _deviceInfos.getSize() );
                for( size_t i = 0; i < _deviceInfos.getSize(); ++i ){
                    CameraInfo& c = _camInfos[ i ];
                    const openni::DeviceInfo& devInfo = _deviceInfos[ i ];
                    c.setName(  devInfo.getName() );
                    c.setIndex( i );
                    c.setType( CAMERATYPE_OPENNI2 );
                    String id;
                    id.sprintf( "%s_%s", devInfo.getVendor(), devInfo.getUri() );
                    c.setIdentifier( id );

                    // add the supported modes
                    openni::Device d;
                    d.open( devInfo.getUri() );
                    const openni::SensorInfo* sinfo = d.getSensorInfo( openni::SENSOR_COLOR );
                    const openni::Array<openni::VideoMode>& vmodes = sinfo->getSupportedVideoModes();
                    for( size_t i = 0; i < vmodes.getSize(); ++i ){
                        const openni::VideoMode& vm = vmodes[ i ];
                        try {
                            c.addMode( CameraMode( vm.getResolutionX(), vm.getResolutionY(), vm.getFps(), toIFormat( vm.getPixelFormat() ) ) );
                        } catch( const cvt::Exception& e ){}
                    }
                    d.close();
                }
            }