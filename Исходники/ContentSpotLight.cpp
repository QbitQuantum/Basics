void SpotLight::EnumerateClass( Reflect::Compositor<SpotLight>& comp )
{
  comp.AddField( &SpotLight::m_InnerRadius,                 "m_InnerRadius" );
  comp.AddField( &SpotLight::m_OuterRadius,                 "m_OuterRadius" );
  comp.AddField( &SpotLight::m_InnerConeAngle,              "m_InnerConeAngle" );
  comp.AddField( &SpotLight::m_OuterConeAngle,              "m_OuterConeAngle" );
  comp.AddField( &SpotLight::m_ShadowMapHiRes,              "m_ShadowMapHiRes" );
  comp.AddField( &SpotLight::m_GodRayEnabled,               "m_GodRayEnabled" );
  comp.AddField( &SpotLight::m_GodRayOpacity,               "m_GodRayOpacity" );
  comp.AddField( &SpotLight::m_GodRayDensity,               "m_GodRayDensity" );
  comp.AddField( &SpotLight::m_GodRayQuality,               "m_GodRayQuality" ); 
  comp.AddField( &SpotLight::m_GodRayFadeNear,              "m_GodRayFadeNear" );
  comp.AddField( &SpotLight::m_GodRayFadeFar,               "m_GodRayFadeFar" );
  comp.AddField( &SpotLight::m_GodRayClipPlanePhiOffset,    "m_GodRayClipPlanePhiOffset" ); 
  comp.AddField( &SpotLight::m_GodRayClipPlaneOffset,       "m_GodRayClipPlaneOffset" );
  comp.AddField( &SpotLight::m_OffsetFactor,                "m_OffsetFactor" );
  comp.AddField( &SpotLight::m_OffsetUnits,                 "m_OffsetUnits" );
}