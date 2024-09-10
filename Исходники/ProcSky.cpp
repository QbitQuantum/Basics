float ProcSky::SetDayTime(float time)
{
    if (!initialized_)
        Initialize();

    sunAngle_ = (time+0.5f) * M_PI;

    int degrees = int(sunAngle_ * M_RADTODEG);

    degrees %= 360;

    timeOfDay_ = ((degrees + 90) % 360) / 15.0f;

    if (degrees >= 150 || degrees <= 15)
    {
        // fade out
        if (shadowFade_ < 0.0f || shadowFade_ != 1.0f)
        {
            shadowFade_ += .05f;

            if (shadowFade_ > 1.0f)
                shadowFade_ = 1.0f;

            sunlight_->SetShadowIntensity(shadowFade_);

            if (!sunlight_->GetCastShadows())
                sunlight_->SetCastShadows(true);

        }
        else
        {
            if (sunlight_->GetCastShadows())
                sunlight_->SetCastShadows(false);
        }

    }
    else
    {
        // fade in
        if (shadowFade_ < 0.0f || shadowFade_ != 0.0f)
        {
            shadowFade_ -= .05f;

            if (shadowFade_ < 0.0f)
                shadowFade_ = 0.0f;

            sunlight_->SetShadowIntensity(shadowFade_);

            if (!sunlight_->GetCastShadows())
                sunlight_->SetCastShadows(true);

        }
        else
        {
            if (!sunlight_->GetCastShadows())
                sunlight_->SetCastShadows(true);
        }
    }

    Quaternion rot(degrees, Vector3::RIGHT);

    node_->SetRotation(rot);


    float daylight = cosf( time * M_PI ) * 0.8f + 0.4f;

    if( daylight > 1.0f )
        daylight = 1.0f;

    if( daylight < 0.0f )
        daylight = 0.0f;

    daylight = sqrtf( daylight );

    float dawnGlow = sinf( time * M_PI * 1.0f );
    int glowX = dawnGlow > 0.0f ? 0 : 7;
    dawnGlow = Atomic::Max( 0.0f, fabs( dawnGlow * dawnGlow * dawnGlow ) * 1.1f - 0.1f );

    Color top = Color(0,0,0,1).Lerp(topColor_, daylight);
    Color horiz = Color(.1,.1,.1,1).Lerp(horizColor_, daylight);

    uint8_t skytex[32 * 8 * 4 ];
    uint8_t* p;

    // bottom row is black
    p = &skytex[31*8*4];

    for( uint32_t x = 0; x < 8; x++ )
    {
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 255;
    }

    p = skytex;
    for( uint32_t z = 0; z < 31; z++ )
    {
        for( uint32_t x = 0; x < 8; x++ )
        {
            float xGlow = Atomic::Max( 0, -abs((int)x-glowX) + 5 ) / 5.0f;
            float hGlow = z/31.0f;
            float glow = (dawnGlow * hGlow * hGlow * sqrtf( xGlow ));

            Color baseColor = top.Lerp(horiz, Atomic::Min( 1.0f, float (z*11) / 255.0f));
            baseColor = baseColor.Lerp(lerpColor_, glow );

            // pic a color from the mid - horizon (this is cheesy!)
            if (z == 28 && x == 4)
            {
                fogColor_ = baseColor;
                zone_->SetFogColor(fogColor_);
                Color sunColor (.3f, .2f, .1f);
                sunColor += fogColor_;

                sunlight_->SetColor(sunColor);

                Color ambient = sunColor * .75f;

                if (ambient.r_ < .25f)
                    ambient.r_ = .25f;
                if (ambient.g_ < .25f)
                    ambient.g_ = .25f;
                if (ambient.b_ < .25f)
                    ambient.b_ = .25f;

                zone_->SetAmbientColor(ambient);

            }

            unsigned r = Clamp(((int)(baseColor.r_ * 255.0f)), 0, 255);
            unsigned g = Clamp(((int)(baseColor.g_ * 255.0f)), 0, 255);
            unsigned b = Clamp(((int)(baseColor.b_ * 255.0f)), 0, 255);

            *p++ = (uint8_t) r;
            *p++ = (uint8_t) g;
            *p++ = (uint8_t) b;
            *p++ = 255;
        }
    }

    //if (fabs(lastDayTimeUpdate_ - dayTime_) > .005f)
    {
        skyTexture_->SetData(0,0,0,8,32,skytex);
        lastDayTimeUpdate_ = dayTime_;
    }



    return Atomic::Max( 4.0f/15.0f, daylight );
}