    static int main( const std::vector<CL_String> &args ) {
	 _mm_setcsr( _mm_getcsr() | _MM_FLUSH_ZERO_ON);
//      plane p( plane::dir_zx_p, vec3f( 0.5, 0.5, 0.5 ));

//      return 0;
        try {
            
     
            ortho o;
            o.start();
        } catch( gl_error_exception x ) {
            std::cerr << x.what() << std::endl;
            std::cerr << "bailing out\n";
        }

        return 0;
    }