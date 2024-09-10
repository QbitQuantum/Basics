void EC_MeshmoonWater::OnUpdate(float elapsedTime)
{
#ifdef MESHMOON_TRITON
    if (!visible.Get() || !ParentScene() || !state_.environment || !state_.ocean)
        return;

    PROFILE(EC_MeshmoonWater_Update);

    if (!windConditionsComp_.expired())
    {
        if (windConditionsComp_.lock().get()->TypeId() == EC_MeshmoonSky::TypeIdStatic())
        {
            EC_MeshmoonSky *meshmoonSky = dynamic_cast<EC_MeshmoonSky*>(windConditionsComp_.lock().get());
            if (meshmoonSky)
            {
                float windDirFloored = Floor(fmod(meshmoonSky->windDirection.Get() + 180.0f, 360.0f));
                float windSpeedFloored = Floor(meshmoonSky->windSpeed.Get());
                if (windSpeedFloored != state_.windSpeedPerSec || windDirFloored != Floor(state_.windDirDegrees))
                {
                    state_.windDirDegrees = windDirFloored;
                    state_.windSpeedPerSec = windSpeedFloored;
                    UpdateWeatherConditions();
                }
            }
        }
        else if (windConditionsComp_.lock().get()->TypeId() == EC_SkyX::TypeIdStatic())
        {
            EC_SkyX *skyx = dynamic_cast<EC_SkyX*>(windConditionsComp_.lock().get());
            if (skyx)
            {
                /// SkyX-To-Triton wind direction needs a small adjustment for them to align properly.
                /// (-skyxDir + 90 deg) and we round the float + modulo with 360 degrees to get [0,359] range.
                float tritonWindDir = fmod(Floor(-skyx->windDirection.Get() + 90.0f), 360.0f);
                if (skyx->windSpeed.Get() != state_.windSpeedPerSec || tritonWindDir != Floor(state_.windDirDegrees))
                {
                    state_.windDirDegrees = tritonWindDir;
                    state_.windSpeedPerSec = skyx->windSpeed.Get();
                    UpdateWeatherConditions();
                }
            }
        }
    }
#endif
}