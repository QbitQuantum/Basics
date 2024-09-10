bool CAutoNuclear::EventProcess(const Event &event)
{
    CObject*    fret;
    Math::Matrix*   mat;
    Math::Vector    pos, goal, speed;
    Math::Point     dim, rot;
    float       angle;
    int         i, max;

    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;
    if ( event.type != EVENT_FRAME )  return true;

    m_progress += event.rTime*m_speed;
    m_timeVirus -= event.rTime;

    if ( m_object->GetVirusMode() )  // contaminated by a virus?
    {
        if ( m_timeVirus <= 0.0f )
        {
            m_timeVirus = 0.1f+Math::Rand()*0.3f;
        }
        return true;
    }

    EventProgress(event.rTime);

    if ( m_phase == ANUP_WAIT )
    {
        if ( m_progress >= 1.0f )
        {
            fret = SearchUranium();  // transform uranium?
            if ( fret == 0 || SearchVehicle() )
            {
                m_phase    = ANUP_WAIT;  // still waiting ...
                m_progress = 0.0f;
                m_speed    = 1.0f/2.0f;
            }
            else
            {
                fret->SetLock(true);  // usable uranium

                SetBusy(true);
                InitProgressTotal(1.5f+NUCLEAR_DELAY+1.5f);
                UpdateInterface();

                m_sound->Play(SOUND_OPEN, m_object->GetPosition(0), 1.0f, 1.4f);

                m_phase    = ANUP_CLOSE;
                m_progress = 0.0f;
                m_speed    = 1.0f/1.5f;
            }
        }
    }

    if ( m_phase == ANUP_CLOSE )
    {
        if ( m_progress < 1.0f )
        {
            angle = (1.0f-m_progress)*(135.0f*Math::PI/180.0f);
            m_object->SetAngleZ(1, angle);
        }
        else
        {
            m_object->SetAngleZ(1, 0.0f);

            mat = m_object->GetWorldMatrix(0);
            max = static_cast< int >(10.0f*m_engine->GetParticleDensity());
            for ( i=0 ; i<max ; i++ )
            {
                pos.x = 27.0f;
                pos.y =  0.0f;
                pos.z = (Math::Rand()-0.5f)*8.0f;
                pos = Transform(*mat, pos);
                speed.y = 0.0f;
                speed.x = 0.0f;
                speed.z = 0.0f;
                dim.x = Math::Rand()*1.0f+1.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTICRASH);
            }

            m_sound->Play(SOUND_CLOSE, m_object->GetPosition(0), 1.0f, 1.0f);

            m_channelSound = m_sound->Play(SOUND_NUCLEAR, m_object->GetPosition(0), 1.0f, 0.1f, true);
            m_sound->AddEnvelope(m_channelSound, 1.0f, 1.0f, NUCLEAR_DELAY-1.0f, SOPER_CONTINUE);
            m_sound->AddEnvelope(m_channelSound, 0.0f, 1.0f, 2.0f, SOPER_STOP);

            m_phase    = ANUP_GENERATE;
            m_progress = 0.0f;
            m_speed    = 1.0f/NUCLEAR_DELAY;
        }
    }

    if ( m_phase == ANUP_GENERATE )
    {
        if ( m_progress < 1.0f )
        {
            if ( m_lastParticle+m_engine->ParticleAdapt(0.10f) <= m_time )
            {
                m_lastParticle = m_time;

                pos = m_object->GetPosition(0);
                pos.y += 30.0f;
                pos.x += (Math::Rand()-0.5f)*6.0f;
                pos.z += (Math::Rand()-0.5f)*6.0f;
                speed.y = Math::Rand()*15.0f+15.0f;
                speed.x = 0.0f;
                speed.z = 0.0f;
                dim.x = Math::Rand()*8.0f+8.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTICRASH);

                pos = m_pos;
                speed.x = (Math::Rand()-0.5f)*20.0f;
                speed.y = (Math::Rand()-0.5f)*20.0f;
                speed.z = (Math::Rand()-0.5f)*20.0f;
                dim.x = 2.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIBLITZ, 1.0f, 0.0f, 0.0f);
            }
        }
        else
        {
            fret = SearchUranium();
            if ( fret != 0 )
            {
                fret->DeleteObject();  // destroyed uranium
                delete fret;
                m_object->SetPower(0);
            }

            CreatePower();  // creates the atomic cell

            max = static_cast< int >(20.0f*m_engine->GetParticleDensity());
            for ( i=0 ; i<max ; i++ )
            {
                pos = m_pos;
                pos.x += (Math::Rand()-0.5f)*3.0f;
                pos.y += (Math::Rand()-0.5f)*3.0f;
                pos.z += (Math::Rand()-0.5f)*3.0f;
                speed.y = 0.0f;
                speed.x = 0.0f;
                speed.z = 0.0f;
                dim.x = Math::Rand()*2.0f+2.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIBLUE, Math::Rand()*5.0f+5.0f, 0.0f, 0.0f);
            }

            m_sound->Play(SOUND_OPEN, m_object->GetPosition(0), 1.0f, 1.4f);

            m_phase    = ANUP_OPEN;
            m_progress = 0.0f;
            m_speed    = 1.0f/1.5f;
        }
    }

    if ( m_phase == ANUP_OPEN )
    {
        if ( m_progress < 1.0f )
        {
            angle = m_progress*(135.0f*Math::PI/180.0f);
            m_object->SetAngleZ(1, angle);
        }
        else
        {
            m_object->SetAngleZ(1, 135.0f*Math::PI/180.0f);

            SetBusy(false);
            UpdateInterface();

            m_main->DisplayError(INFO_NUCLEAR, m_object);

            m_phase    = ANUP_WAIT;
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    return true;
}