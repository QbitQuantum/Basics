void ScreenController::update(
    kvs::ni::DepthGenerator& depth,
    kvs::ni::UserGenerator& user )
{
    if ( !m_ref_screen )
    {
        kvsMessageError( "kvs::ScreenBase* is not attached." );
        return;
    }

    if ( kvs::Math::IsZero( m_p2r ) )
    {
        const unsigned long zpd = depth.zeroPlaneDistance();
        const float zpps = depth.zeroPlanePixelSize();
        m_p2r = zpps * ( 1280.0f / m_width ) / static_cast<float>( zpd );
    }

    kvs::ValueArray<unsigned int> users = user.users();
    const float hand_level = 0.35f;
    for ( size_t i = 0; i < users.size(); i++ )
    {
        HandList::iterator itr = m_list.begin();
        kvs::tdw::HandPosition* user_hand = NULL;
        while ( itr != m_list.end() )
        {
            if ( (*itr).user() == users[i] )
            {
                user_hand = &(*itr);
                break;
            }
            itr++;
        }

        if ( !user_hand )
        {
            kvs::tdw::HandPosition hand( users[i] );
            m_list.push_back( hand );
            user_hand = &(m_list.back());
        }

        if ( user.skeleton().isTracking( users[i] ) )
        {
            const kvs::Vector3f neck = this->vertex_of_joint(
                users[i], kvs::ni::Skeleton::Neck, depth, user );
            const kvs::Vector3f left_hand = this->vertex_of_joint(
                users[i], kvs::ni::Skeleton::LeftHand, depth, user );
            const kvs::Vector3f right_hand = this->vertex_of_joint(
                users[i], kvs::ni::Skeleton::RightHand, depth, user );

            kvs::Vector3f prev_left_hand;
            kvs::Vector3f prev_right_hand;
            bool is_prev_left_active = false;
            bool is_prev_right_active = false;
            if ( !user_hand->isActive( 0 ) )
            {
                if ( left_hand.z() - neck.z() > hand_level )
                {
                    user_hand->setIsActive( 0, true );
                    user_hand->setPosition( 0, left_hand );
                }
            }
            else
            {
                prev_left_hand = user_hand->position( 0 );
                if ( left_hand.z() - neck.z() > hand_level )
                {
                    is_prev_left_active = true;
                    user_hand->setPosition( 0, left_hand );
                }
                else
                {
                    user_hand->setIsActive( 0, false );
                }
            }

            if ( !user_hand->isActive( 1 ) )
            {
                if ( right_hand.z() - neck.z() > hand_level )
                {
                    user_hand->setIsActive( 1, true );
                    user_hand->setPosition( 1, right_hand );
                }
            }
            else
            {
                prev_right_hand = user_hand->position( 1 );
                if ( right_hand.z() - neck.z() > hand_level )
                {
                    is_prev_right_active = true;
                    user_hand->setPosition( 1, right_hand );
                }
                else
                {
                    user_hand->setIsActive( 1, false );
                }
            }

            if ( user_hand->isActive( 0 ) && !user_hand->isActive( 1 ) &&
                 is_prev_left_active )
            {
                // Translation with left hand.
                this->translate( prev_left_hand, user_hand->position( 0 ) );
            }
            else if ( !user_hand->isActive( 0 ) && user_hand->isActive( 1 ) &&
                      is_prev_right_active )
            {
                // Rotation with right hand.
                this->rotate( prev_right_hand, user_hand->position( 1 ), neck );
            }
            else if ( user_hand->isActive( 0 ) && user_hand->isActive( 1 ) &&
                      is_prev_left_active && is_prev_right_active )
            {
                // Scaling with two hand.
                this->scale( prev_left_hand, prev_right_hand,
                    user_hand->position( 0 ), user_hand->position( 1 ) );
            }
            else if ( !user_hand->isActive( 0 ) && !user_hand->isActive( 1 ) &&
                      itr != m_list.end() )
            {
                // Delete from list.
                m_list.erase( itr );
            }
        }
        if ( this->is_cross_pose( users[i], depth, user ) )
        {
            m_ref_screen->reset();
            kvs::KeyEvent event;
            event.setKey( kvs::Key::Home );
            m_ref_sender->sendKeyEvent( &event );
        }
    }

}