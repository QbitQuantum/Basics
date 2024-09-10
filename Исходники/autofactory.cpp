bool CAutoFactory::EventProcess(const Event &event)
{
    ObjectType  type;
    CObject*    fret;
    CObject*    vehicle;
    Math::Matrix*   mat;
    CPhysics*   physics;
    Math::Vector    pos, speed;
    Math::Point     dim;
    float       zoom, angle, prog;
    int         i;

    CAuto::EventProcess(event);

    if ( m_engine->GetPause() )  return true;

    if ( m_object->GetSelect() )  // factory selected?
    {
        if ( event.type == EVENT_UPDINTERFACE )
        {
            CreateInterface(true);
        }

        type = OBJECT_NULL;
        if ( event.type == EVENT_OBJECT_FACTORYwa )  type = OBJECT_MOBILEwa;
        if ( event.type == EVENT_OBJECT_FACTORYta )  type = OBJECT_MOBILEta;
        if ( event.type == EVENT_OBJECT_FACTORYfa )  type = OBJECT_MOBILEfa;
        if ( event.type == EVENT_OBJECT_FACTORYia )  type = OBJECT_MOBILEia;
        if ( event.type == EVENT_OBJECT_FACTORYws )  type = OBJECT_MOBILEws;
        if ( event.type == EVENT_OBJECT_FACTORYts )  type = OBJECT_MOBILEts;
        if ( event.type == EVENT_OBJECT_FACTORYfs )  type = OBJECT_MOBILEfs;
        if ( event.type == EVENT_OBJECT_FACTORYis )  type = OBJECT_MOBILEis;
        if ( event.type == EVENT_OBJECT_FACTORYwc )  type = OBJECT_MOBILEwc;
        if ( event.type == EVENT_OBJECT_FACTORYtc )  type = OBJECT_MOBILEtc;
        if ( event.type == EVENT_OBJECT_FACTORYfc )  type = OBJECT_MOBILEfc;
        if ( event.type == EVENT_OBJECT_FACTORYic )  type = OBJECT_MOBILEic;
        if ( event.type == EVENT_OBJECT_FACTORYwi )  type = OBJECT_MOBILEwi;
        if ( event.type == EVENT_OBJECT_FACTORYti )  type = OBJECT_MOBILEti;
        if ( event.type == EVENT_OBJECT_FACTORYfi )  type = OBJECT_MOBILEfi;
        if ( event.type == EVENT_OBJECT_FACTORYii )  type = OBJECT_MOBILEii;
        if ( event.type == EVENT_OBJECT_FACTORYrt )  type = OBJECT_MOBILErt;
        if ( event.type == EVENT_OBJECT_FACTORYrc )  type = OBJECT_MOBILErc;
        if ( event.type == EVENT_OBJECT_FACTORYrr )  type = OBJECT_MOBILErr;
        if ( event.type == EVENT_OBJECT_FACTORYrs )  type = OBJECT_MOBILErs;
        if ( event.type == EVENT_OBJECT_FACTORYsa )  type = OBJECT_MOBILEsa;

        Error err = StartAction(type);
        if( err != ERR_OK && err != ERR_GENERIC )
            m_displayText->DisplayError(err, m_object);

        if( err != ERR_GENERIC )
            return false;
    }

    if ( event.type != EVENT_FRAME )  return true;

    m_progress += event.rTime*m_speed;
    EventProgress(event.rTime);

    if ( m_phase == AFP_WAIT )
    {
        if ( m_progress >= 1.0f )
        {
            m_phase    = AFP_WAIT;  // still waiting ...
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    if ( m_phase == AFP_CLOSE_S )
    {
        if ( m_progress < 1.0f )
        {
            for ( i=0 ; i<9 ; i++ )
            {
                zoom = 0.30f+(m_progress-0.5f+i/16.0f)*2.0f*0.70f;
                if ( zoom < 0.30f )  zoom = 0.30f;
                if ( zoom > 1.00f )  zoom = 1.00f;
                m_object->SetZoomZ( 1+i, zoom);
                m_object->SetZoomZ(10+i, zoom);
            }
        }
        else
        {
            for ( i=0 ; i<9 ; i++ )
            {
                m_object->SetZoomZ( 1+i, 1.0f);
                m_object->SetZoomZ(10+i, 1.0f);
            }

            SoundManip(2.0f, 1.0f, 1.2f);

            m_phase    = AFP_CLOSE_T;
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    if ( m_phase == AFP_CLOSE_T )
    {
        if ( m_progress < 1.0f )
        {
            for ( i=0 ; i<9 ; i++ )
            {
                angle = -m_progress*(Math::PI/2.0f)+Math::PI/2.0f;
                m_object->SetAngleZ( 1+i,  angle);
                m_object->SetAngleZ(10+i, -angle);
            }
        }
        else
        {
            for ( i=0 ; i<9 ; i++ )
            {
                m_object->SetAngleZ( 1+i, 0.0f);
                m_object->SetAngleZ(10+i, 0.0f);
            }

            m_channelSound = m_sound->Play(SOUND_FACTORY, m_object->GetPosition(0), 0.0f, 1.0f, true);
            m_sound->AddEnvelope(m_channelSound, 1.0f, 1.0f,  2.0f, SOPER_CONTINUE);
            m_sound->AddEnvelope(m_channelSound, 1.0f, 1.0f, 11.0f, SOPER_CONTINUE);
            m_sound->AddEnvelope(m_channelSound, 0.0f, 1.0f,  2.0f, SOPER_STOP);

            m_phase    = AFP_BUILD;
            m_progress = 0.0f;
            m_speed    = 1.0f/15.0f;
        }
    }

    if ( m_phase == AFP_BUILD )
    {
        if ( m_progress == 0.0f )
        {
            if ( !CreateVehicle() )
            {
                fret = SearchFret();  // transform metal?
                if ( fret != 0 )
                {
                    fret->SetLock(false);  // metal usable again
                }

                if ( m_channelSound != -1 )
                {
                    m_sound->FlushEnvelope(m_channelSound);
                    m_sound->AddEnvelope(m_channelSound, 0.0f, 1.0f, 1.0f, SOPER_STOP);
                    m_channelSound = -1;
                }

                m_phase    = AFP_OPEN_T;
                m_progress = 0.0f;
                m_speed    = 1.0f/2.0f;
                return true;
            }
        }

        if ( m_progress < 1.0f )
        {
            if ( m_type == OBJECT_MOBILErt ||
                 m_type == OBJECT_MOBILErc ||
                 m_type == OBJECT_MOBILErr ||
                 m_type == OBJECT_MOBILErs )
            {
                prog = 1.0f-m_progress*1.5f;
                if ( prog < 0.0f )  prog = 0.0f;
            }
            else
            {
                prog = 1.0f-m_progress;
            }
            angle = powf(prog*10.0f, 2.0f)+m_object->GetAngleY(0);

            vehicle = SearchVehicle();
            if ( vehicle != 0 )
            {
                vehicle->SetAngleY(0, angle+Math::PI);
                vehicle->SetZoom(0, m_progress);
            }

            fret = SearchFret();  // transform metal?
            if ( fret != 0 )
            {
                fret->SetZoom(0, 1.0f-m_progress);
            }

            if ( m_lastParticle+m_engine->ParticleAdapt(0.05f) <= m_time )
            {
                m_lastParticle = m_time;

#if 0
                pos = m_fretPos;
                pos.x += (Math::Rand()-0.5f)*20.0f;
                pos.z += (Math::Rand()-0.5f)*20.0f;
                pos.y += 1.0f;
                speed.x = (Math::Rand()-0.5f)*12.0f;
                speed.z = (Math::Rand()-0.5f)*12.0f;
                speed.y = Math::Rand()*12.0f;
                dim.x = Math::Rand()*12.0f+10.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, PARTIBLUE, 1.0f, 0.0f, 0.0f);
#else
                mat = m_object->GetWorldMatrix(0);
                pos = Math::Vector(-12.0f, 20.0f, -4.0f);  // position of chimney
                pos = Math::Transform(*mat, pos);
                pos.y += 2.0f;
                pos.x += (Math::Rand()-0.5f)*2.0f;
                pos.z += (Math::Rand()-0.5f)*2.0f;
                speed.x = 0.0f;
                speed.z = 0.0f;
                speed.y = 6.0f+Math::Rand()*6.0f;
                dim.x = Math::Rand()*1.5f+1.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTISMOKE3, 4.0f);
#endif
            }
        }
        else
        {
            m_displayText->DisplayError(INFO_FACTORY, m_object);
            SoundManip(2.0f, 1.0f, 1.2f);

            fret = SearchFret();  // transform metal?
            if ( fret != 0 )
            {
                fret->DeleteObject();  // removes the metal
                delete fret;
            }

            m_vehicle = vehicle = SearchVehicle();
            if ( vehicle != 0 )
            {
                physics = vehicle->GetPhysics();
                if ( physics != 0 )
                {
                    physics->SetFreeze(false);  // can move
                }

                vehicle->SetLock(false);  // vehicle useable
//?             vehicle->GetPhysics()->GetBrain()->StartTaskAdvance(16.0f);
                vehicle->SetAngleY(0, m_object->GetAngleY(0)+Math::PI);
                vehicle->SetZoom(0, 1.0f);
            }

            m_main->CreateShortcuts();

            m_phase    = AFP_OPEN_T;
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    if ( m_phase == AFP_OPEN_T )
    {
        if ( m_progress < 1.0f )
        {
            for ( i=0 ; i<9 ; i++ )
            {
                angle = -(1.0f-m_progress)*(Math::PI/2.0f)+Math::PI/2.0f;
                m_object->SetAngleZ( 1+i,  angle);
                m_object->SetAngleZ(10+i, -angle);
            }

            if ( m_lastParticle+m_engine->ParticleAdapt(0.1f) <= m_time )
            {
                m_lastParticle = m_time;

                pos = m_fretPos;
                pos.x += (Math::Rand()-0.5f)*10.0f;
                pos.z += (Math::Rand()-0.5f)*10.0f;
                pos.y += Math::Rand()*10.0f;
                speed = Math::Vector(0.0f, 0.0f, 0.0f);
                dim.x = 2.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIGLINT, 2.0f, 0.0f, 0.0f);
            }
        }
        else
        {
            for ( i=0 ; i<9 ; i++ )
            {
                m_object->SetAngleZ( 1+i,  Math::PI/2.0f);
                m_object->SetAngleZ(10+i, -Math::PI/2.0f);
            }

            SoundManip(3.0f, 1.0f, 0.5f);

            m_phase    = AFP_OPEN_S;
            m_progress = 0.0f;
            m_speed    = 1.0f/3.0f;
        }
    }

    if ( m_phase == AFP_OPEN_S )
    {
        if ( m_progress < 1.0f )
        {
            for ( i=0 ; i<9 ; i++ )
            {
                zoom = 0.30f+((1.0f-m_progress)-0.5f+i/16.0f)*2.0f*0.70f;
                if ( zoom < 0.30f )  zoom = 0.30f;
                if ( zoom > 1.00f )  zoom = 1.00f;
                m_object->SetZoomZ( 1+i, zoom);
                m_object->SetZoomZ(10+i, zoom);
            }

            if ( m_lastParticle+m_engine->ParticleAdapt(0.1f) <= m_time )
            {
                m_lastParticle = m_time;

                pos = m_fretPos;
                pos.x += (Math::Rand()-0.5f)*10.0f;
                pos.z += (Math::Rand()-0.5f)*10.0f;
                pos.y += Math::Rand()*10.0f;
                speed = Math::Vector(0.0f, 0.0f, 0.0f);
                dim.x = 2.0f;
                dim.y = dim.x;
                m_particle->CreateParticle(pos, speed, dim, Gfx::PARTIGLINT, 2.0f, 0.0f, 0.0f);
            }
        }
        else
        {
            for ( i=0 ; i<9 ; i++ )
            {
                m_object->SetZoomZ( 1+i, 0.30f);
                m_object->SetZoomZ(10+i, 0.30f);
            }

            if ( m_program != nullptr )
            {
                CBrain* brain = m_vehicle->GetBrain();
                if ( brain != nullptr )
                {
                    brain->SendProgram(0, const_cast<const char*>(m_program));
                    brain->SetScriptRun(0);
                    brain->RunProgram(0);
                }
            }

            SetBusy(false);
            UpdateInterface();

            m_phase    = AFP_WAIT;
            m_progress = 0.0f;
            m_speed    = 1.0f/2.0f;
        }
    }

    return true;
}