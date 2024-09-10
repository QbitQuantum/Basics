namespace Demi
{
    const ArrayFloat MathlibSSE2::HALF       = _mm_set_ps1( 0.5f );
    const ArrayFloat MathlibSSE2::ONE        = _mm_set_ps1( 1.0f );
    const ArrayFloat MathlibSSE2::THREE      = _mm_set_ps1( 3.0f );
    const ArrayFloat MathlibSSE2::NEG_ONE    = _mm_set_ps1( -1.0f );
    const ArrayFloat MathlibSSE2::fEpsilon   = _mm_set_ps1( 1e-6f );
    const ArrayFloat MathlibSSE2::fSqEpsilon = _mm_set_ps1( 1e-12f );
    const ArrayFloat MathlibSSE2::OneMinusEpsilon= _mm_set_ps1( 1.0f - 1e-6f );
    const ArrayFloat MathlibSSE2::FLOAT_MIN  = _mm_set_ps1( std::numeric_limits<float>::min() );
    const ArrayFloat MathlibSSE2::SIGN_MASK  = _mm_set_ps1( -0.0f );
    const ArrayFloat MathlibSSE2::INFINITEA  = _mm_set_ps1( std::numeric_limits<float>::infinity() );
    const ArrayFloat MathlibSSE2::MAX_NEG    = _mm_set_ps1( -std::numeric_limits<float>::max() );
    const ArrayFloat MathlibSSE2::MAX_POS    = _mm_set_ps1( std::numeric_limits<float>::max() );
    const ArrayFloat MathlibSSE2::LAST_AFFINE_COLUMN = _mm_setr_ps( 0, 0, 0, 1 );

    static const float _PI = float( 4.0 * atan( 1.0 ) );
    //We can't use Math::fDeg2Rad & Math::fRad2Deg directly because
    //it's not guaranteed to have been initialized first
    const ArrayFloat MathlibSSE2::PI         = _mm_set_ps1( _PI );
    const ArrayFloat MathlibSSE2::TWO_PI     = _mm_set_ps1( 2.0f * _PI );
    const ArrayFloat MathlibSSE2::fDeg2Rad   = _mm_set_ps1( _PI / 180.0f );
    const ArrayFloat MathlibSSE2::fRad2Deg   = _mm_set_ps1( 180.0f / _PI );

    const ArrayFloat MathlibSSE2::ONE_DIV_2PI= _mm_set_ps1( 1.0f / (2.0f * _PI) );

    
    ArrayFloat MathlibSSE2::Sin4( ArrayFloat x )
    {
        // Map arbitrary angle x to the range [-pi; +pi] without using division.
        // Code taken from MSDN's HLSL trick. Architectures with fused mad (i.e. NEON)
        // can replace the add, the sub, & the two muls for two mad
        ArrayFloat integralPart;
        x = _mm_add_ps( _mm_mul_ps( x, ONE_DIV_2PI ), HALF );
        x = Modf4( x, integralPart );
        x = _mm_sub_ps( _mm_mul_ps( x, TWO_PI ), PI );

        return sin_ps( x );
    }
    
    ArrayFloat MathlibSSE2::Cos4( ArrayFloat x )
    {
        // Map arbitrary angle x to the range [-pi; +pi] without using division.
        // Code taken from MSDN's HLSL trick. Architectures with fused mad (i.e. NEON)
        // can replace the add, the sub, & the two muls for two mad
        ArrayFloat integralPart;
        x = _mm_add_ps( _mm_mul_ps( x, ONE_DIV_2PI ), HALF );
        x = Modf4( x, integralPart );
        x = _mm_sub_ps( _mm_mul_ps( x, TWO_PI ), PI );

        return cos_ps( x );
    }
    
    void MathlibSSE2::SinCos4( ArrayFloat x, ArrayFloat &outSin, ArrayFloat &outCos )
    {
        // TODO: Improve accuracy by mapping to the range [-pi/4, pi/4] and swap
        // between cos & sin depending on which quadrant it fell:
        // Quadrant | sin     |  cos
        // n = 0 ->  sin( x ),  cos( x )
        // n = 1 ->  cos( x ), -sin( x )
        // n = 2 -> -sin( x ), -cos( x )
        // n = 3 -> -sin( x ),  sin( x )
        // See ARGUMENT REDUCTION FOR HUGE ARGUMENTS:
        // Good to the Last Bit
        // K. C. Ng and themembers of the FP group of SunPro
        // http://www.derekroconnor.net/Software/Ng--ArgReduction.pdf

        // -- Perhaps we can leave this to GSoC students? --

        // Map arbitrary angle x to the range [-pi; +pi] without using division.
        // Code taken from MSDN's HLSL trick. Architectures with fused mad (i.e. NEON)
        // can replace the add, the sub, & the two muls for two mad
        ArrayFloat integralPart;
        x = _mm_add_ps( _mm_mul_ps( x, ONE_DIV_2PI ), HALF );
        x = Modf4( x, integralPart );
        x = _mm_sub_ps( _mm_mul_ps( x, TWO_PI ), PI );

        sincos_ps( x, &outSin, &outCos );
    }

    const ArrayFloat BooleanMask4::mMasks[NUM_MASKS] =
    {
        _mm_castsi128_ps(_mm_set_epi32( 0x00000000, 0x00000000, 0x00000000, 0x00000000 )),//MASK_NONE
        _mm_castsi128_ps(_mm_set_epi32( 0x00000000, 0x00000000, 0x00000000, 0xffffffff )),//MASK_X
        _mm_castsi128_ps(_mm_set_epi32( 0x00000000, 0x00000000, 0xffffffff, 0x00000000 )),//MASK_Y
        _mm_castsi128_ps(_mm_set_epi32( 0x00000000, 0x00000000, 0xffffffff, 0xffffffff )),//MASK_XY
        _mm_castsi128_ps(_mm_set_epi32( 0x00000000, 0xffffffff, 0x00000000, 0x00000000 )),//MASK_Z
        _mm_castsi128_ps(_mm_set_epi32( 0x00000000, 0xffffffff, 0x00000000, 0xffffffff )),//MASK_XZ
        _mm_castsi128_ps(_mm_set_epi32( 0x00000000, 0xffffffff, 0xffffffff, 0x00000000 )),//MASK_YZ
        _mm_castsi128_ps(_mm_set_epi32( 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff )),//MASK_XYZ
        _mm_castsi128_ps(_mm_set_epi32( 0xffffffff, 0x00000000, 0x00000000, 0x00000000 )),//MASK_W
        _mm_castsi128_ps(_mm_set_epi32( 0xffffffff, 0x00000000, 0x00000000, 0xffffffff )),//MASK_XW
        _mm_castsi128_ps(_mm_set_epi32( 0xffffffff, 0x00000000, 0xffffffff, 0x00000000 )),//MASK_YW
        _mm_castsi128_ps(_mm_set_epi32( 0xffffffff, 0x00000000, 0xffffffff, 0xffffffff )),//MASK_XYW
        _mm_castsi128_ps(_mm_set_epi32( 0xffffffff, 0xffffffff, 0x00000000, 0x00000000 )),//MASK_ZW
        _mm_castsi128_ps(_mm_set_epi32( 0xffffffff, 0xffffffff, 0x00000000, 0xffffffff )),//MASK_XZW
        _mm_castsi128_ps(_mm_set_epi32( 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000 )),//MASK_YZW
        _mm_castsi128_ps(_mm_set_epi32( 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff )) //MASK_XYZW
    };
}