    bool checkForCollision( const vec4uint32 & dim ) const {
#ifdef QUADDEBUG
        log() << indent_ << boundary_ << " checking for collision with " << dim << std::endl;
#endif
        if( level_ == 0 || boundary_.intersects( dim ) ) {
            if( leftBottomNode_.get() != nullptr ) {
#ifdef QUADDEBUG
                log() << indent_ << "Using the boundary tests" << std::endl;
#endif
                return ( leftBottomNode_->checkForCollision( dim )
                         ||
                         rightBottomNode_->checkForCollision( dim )
                         ||
                         leftTopNode_->checkForCollision( dim )
                         ||
                         rightTopNode_->checkForCollision( dim ) );
            }
            else if( nodeContent_.size() > 0 ) {
#ifdef QUADDEBUG
                log() << indent_ << "Node " << boundary_ << " doing rooms collision check: " << dim << std::endl;
#endif
                for( const Content * c : nodeContent_ ) {
#ifdef QUADDEBUG
                    log() << indent_ << "-- checking if room " << c << " intersects with " << dim << std::endl;
#endif
                    if( intersects( *c, dim ) ) {
#ifdef QUADDEBUG
                        log() << indent_ << "-- room collision between new room " << dim << " and existing room " << *dcr << std::endl;
#endif
                        return true;
                    }
                }
            }
        }

#ifdef QUADDEBUG
        log() << indent_ << "No collision" << std::endl;
#endif
        return false;
    }