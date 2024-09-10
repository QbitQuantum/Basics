//------------------------------------------------------------------------------
// entityStateManager() --  (Output support)
//    -- Update the entity object for this NIB(Player)
//------------------------------------------------------------------------------
bool Nib::entityStateManager(const LCreal curExecTime)
{
   bool ok = false;

   // Get the player pointer
   const Simulation::Player* player = getPlayer();
   if (player == nullptr) return ok;

   // Dummy weapon?
   const Simulation::Weapon* ww = dynamic_cast<const Simulation::Weapon*>( player );
   if (ww != nullptr) {
      if (ww->isDummy()) return ok;
   }

   if (isPlayerStateUpdateRequired(curExecTime)) {

      //
      // Send an entity state PDU
      //   1) create buffer
      //   2) set state information
      //   3) send data
      //

      // Get our NetIO and the main simulation
      NetIO* disIO = static_cast<NetIO*>(getNetIO());
      Simulation::Simulation* sim = disIO->getSimulation();

      // Capture the player data, reset the dead reckoning and
      // mark the current time.
      playerState2Nib();

      // ---
      // Create buffer and cast it as an entity state PDU
      // ---
      char pduBuffer[NetIO::MAX_PDU_SIZE];
      EntityStatePDU* pdu = (EntityStatePDU*) &pduBuffer[0];

      //
      // Entity state PDU structure
      // =========================================================
      // PDUHeader            header;
      // EntityIdentifierDIS  entityID;
      // uint8_t              forceID;
      // uint8_t              numberOfArticulationParameters;
      // EntityType           entityType;
      // EntityType           alternativeType;
      // VectorDIS            entityLinearVelocity;
      // WorldCoordinates     entityLocation;
      // EulerAngles          entityOrientation;
      // uint32_t             appearance;
      // uint8_t              deadReckoningAlgorithm;
      // uint8_t              otherParameters[15];
      // VectorDIS            DRentityLinearAcceleration;
      // AngularVelocityVectorDIS DRentityAngularVelocity;
      // EntityMarking        entityMarking;
      // uint32_t             capabilities;
      // =========================================================
      //

      // ---
      // Standard header (PDUHeader)
      // ---
      pdu->header.protocolVersion = disIO->getVersion();
      pdu->header.exerciseIdentifier = disIO->getExerciseID();
      pdu->header.PDUType = NetIO::PDU_ENTITY_STATE;
      pdu->header.protocolFamily = NetIO::PDU_FAMILY_ENTITY_INFO;
      //
      if (disIO->getTimeline() == Simulation::NetIO::UTC)
         pdu->header.timeStamp = disIO->makeTimeStamp( getTimeUtc(), true );
      else
         pdu->header.timeStamp = disIO->makeTimeStamp( getTimeExec(), false );
      //
      pdu->header.status = 0;
      pdu->header.padding = 0;

      // ---
      // Entity ID (EntityIdentifierID)
      // ---
      pdu->entityID.simulationID.siteIdentification = getSiteID();
      pdu->entityID.simulationID.applicationIdentification = getApplicationID();
      pdu->entityID.ID = getPlayerID();

      // ---
      // Force ID: When mapping Player side to force IDs ...
      // ---
      if (getSide() == Simulation::Player::BLUE) {
         // blue's are friendly, ...
         pdu->forceID = NetIO::FRIENDLY_FORCE;
      }
      else if (getSide() == Simulation::Player::RED) {
         // red's are not, ...
         pdu->forceID = NetIO::OPPOSING_FORCE;
      }
      else if (getSide() == Simulation::Player::WHITE) {
         // white is neutral, ...
         pdu->forceID = NetIO::NEUTRAL_FORCE;
      }
      else {
         // and everyone else is type OTHER.
         pdu->forceID = NetIO::OTHER_FORCE;
      }

      // ---
      // Entity type (EntityType)
      // ---
      pdu->entityType.kind                 = getEntityKind();
      pdu->entityType.domain               = getEntityDomain();
      pdu->entityType.country              = getEntityCountry();
      pdu->entityType.category             = getEntityCategory();
      pdu->entityType.subcategory          = getEntitySubcategory();
      pdu->entityType.specific             = getEntitySpecific();
      pdu->entityType.extra                = getEntityExtra();
      // ---
      // Alternative type (EntityType)
      // ---
      pdu->alternativeType.kind            = getEntityKind();
      pdu->alternativeType.domain          = getEntityDomain();
      pdu->alternativeType.country         = getEntityCountry();
      pdu->alternativeType.category        = getEntityCategory();
      pdu->alternativeType.subcategory     = getEntitySubcategory();
      pdu->alternativeType.specific        = getEntitySpecific();
      pdu->alternativeType.extra           = getEntityExtra();

      // ---
      // Player position and orientation state data data
      // 1) All data is geocentric (ECEF)
      // 2) The playerState2Nib() function, which was called above, captures
      //    the state data and passed the state data to the dead reckoning
      //    system, and we're using this DR captured data.
      // ---
      {
         // ---
         // Entity linear velocity (VectorDIS)
         // ---
         osg::Vec3d geocVel = getDrVelocity();
         pdu->entityLinearVelocity.component[0] = static_cast<float>(geocVel[0]);
         pdu->entityLinearVelocity.component[1] = static_cast<float>(geocVel[1]);
         pdu->entityLinearVelocity.component[2] = static_cast<float>(geocVel[2]);

         // ---
         // Entity location (WorldCoordinates)
         // ---
         osg::Vec3d geocPos = getDrPosition();
         pdu->entityLocation.X_coord = geocPos[Basic::Nav::IX];
         pdu->entityLocation.Y_coord = geocPos[Basic::Nav::IY];
         pdu->entityLocation.Z_coord = geocPos[Basic::Nav::IZ];

         // ---
         // Entity orientation (EulerAngles)
         // ---
         osg::Vec3d geocAngles = getDrEulerAngles();
         pdu->entityOrientation.phi   = static_cast<float>(geocAngles[Basic::Nav::IPHI]);
         pdu->entityOrientation.theta = static_cast<float>(geocAngles[Basic::Nav::ITHETA]);
         pdu->entityOrientation.psi   = static_cast<float>(geocAngles[Basic::Nav::IPSI]);
      }

      // ---
      // Appearance bits generic to all domains (except munitions)
      // ---
      {
         pdu->appearance = 0x0;

         // ---
         // Frozen?
         // ---
         if ( isFrozen() || sim->isFrozen() ) {
            pdu->appearance |= FROZEN_BIT;
         }

         // Deactive this entity?
         {
            if (isMode(Simulation::Player::DELETE_REQUEST) || player->isDead() )
               pdu->appearance |= DEACTIVATE_BIT;
         }


         // Damage or health?  (Bits 3-4)
         {
            unsigned int bits = 0;
            if (getDamage() > 0.9f) bits = 3;       // Destroyed or Fatality
            else if (getDamage() > 0.5) bits = 2;   // Moderate
            else if (getDamage() > 0.0) bits = 1;   // Slight
            else bits = 0;                          // None
            pdu->appearance |= (bits << 3);
         }


         // Camouflage type
         // Note: air platform appearance bits 17 and 18 are not used, but we're using them the same as land platforms
         {
            unsigned int bits = getCamouflageType();
            if (bits > 0 && bits <= 4) {
               pdu->appearance |= CAMOUFLAGE_BIT;

               // Land based camouflage bits
               if (player->isMajorType(Simulation::Player::GROUND_VEHICLE)) {
                  // Subtract one to match DIS camouflage bits.
                  // Our camouflage type for DIS is the camouflage appearance bits
                  // plus one because our camouflage type of zero is no camouflage.
                  bits--;
                  pdu->appearance |= (bits << 17);
               }
            }
         }

         // Life forms appearance bits
         if (player->isMajorType(Simulation::Player::LIFE_FORM)) {
            const Simulation::LifeForm* lf = dynamic_cast<const Simulation::LifeForm*>(player);
            if (lf != nullptr) {
               // Health (aka damaged for other domains) same bits (3-4) - this is from the NIB, because it IS
               // updated
               // bits 5-8 compliance (not implemented)
               // bits 9 - 11 unused
               // bit 12 flashlight (not implemented)
               // bits 13-15 unused
               // bits 16 - 19 life form state
               // data is from the player, because NIB doesn't have actions associated with it
               {
                  unsigned int bits = 1;      // upright, standing still
                  if (lf->getActionState() == Simulation::LifeForm::UPRIGHT_STANDING) bits = 1;       // standing
                  else if (lf->getActionState() == Simulation::LifeForm::UPRIGHT_WALKING) bits = 2;   // walking
                  else if (lf->getActionState() == Simulation::LifeForm::UPRIGHT_RUNNING) bits = 3;   // running
                  else if (lf->getActionState() == Simulation::LifeForm::KNEELING) bits = 4;          // kneeling
                  else if (lf->getActionState() == Simulation::LifeForm::PRONE) bits = 5;             // prone
                  else if (lf->getActionState() == Simulation::LifeForm::CRAWLING) bits = 6;          // crawling
                  else if (lf->getActionState() == Simulation::LifeForm::SWIMMING) bits = 7;          // swimming
                  else if (lf->getActionState() == Simulation::LifeForm::PARACHUTING) bits = 8;       // parachuting
                  else if (lf->getActionState() == Simulation::LifeForm::JUMPING) bits = 9;           // jumping
                  else if (lf->getActionState() == Simulation::LifeForm::SITTING) bits = 10;          // sitting
                  else if (lf->getActionState() == Simulation::LifeForm::SQUATTING) bits = 11;        // squatting
                  else if (lf->getActionState() == Simulation::LifeForm::CROUCHING) bits = 12;        // crouching
                  else if (lf->getActionState() == Simulation::LifeForm::WADING) bits = 13;           // wading
                  else if (lf->getActionState() == Simulation::LifeForm::SURRENDER) bits = 14;        // surrender
                  else if (lf->getActionState() == Simulation::LifeForm::DETAINED) bits = 15;         // detained
                  else bits = 1;
                  pdu->appearance |= (bits << 16);
               }
               // bit 20 unused
               // bit 21 frozen status (taken care of above)
               // bits 24 - 25 weapon 1 (not implemented)
               // bits 26-27 weapon 2 (N/I)
               // bits 28-29
            }
         }

         // Common Non-life form appearance bits
         else {

            // Smoking?  (Bits 5-6) Standard (IST-CF-03-01, May 5, 2003)
            {
               unsigned int bits = 0;
               if (getSmoke() > 0.9f) bits = 3;
               else if (getSmoke() > 0.5) bits = 2;
               else if (getSmoke() > 0.0) bits = 1;
               else bits = 0;
               pdu->appearance |= (bits << 5);
            }

            // Flames? (Bit 15) Standard (IST-CF-03-01, May 5, 2003)
            {
               if (getFlames() > 0.5f)
                  pdu->appearance |= FLAMES_BIT;
            }

            // Power plant status bit (just leave ON for now)
            pdu->appearance |= POWER_PLANT_BIT;
         }


      }

      // ---
      // Dead reckoning algorithm
      // ---
      pdu->deadReckoningAlgorithm = static_cast<unsigned char>(getDeadReckoning());

      // ---
      // Other parameters
      // ---
      for (unsigned int i=0; i<15; i++) {
          pdu->otherParameters[i] = 0;
      }

      // ---
      // Dead reckoning information
      // ---
      {
         // ---
         // Dead reckoning linear acceleration (VectorDIS)
         // ---
         osg::Vec3d geocAcc = getDrAcceleration();
         pdu->DRentityLinearAcceleration.component[0] = static_cast<float>(geocAcc[0]);
         pdu->DRentityLinearAcceleration.component[1] = static_cast<float>(geocAcc[1]);
         pdu->DRentityLinearAcceleration.component[2] = static_cast<float>(geocAcc[2]);

         // ---
         // Dead reckoning angular velocity (AngularVelocityVectorDIS)
         // ---
         osg::Vec3d geocAngVel = getDrAngularVelocities();
         pdu->DRentityAngularVelocity.x_axis = static_cast<float>(geocAngVel[Basic::Nav::IX]);
         pdu->DRentityAngularVelocity.y_axis = static_cast<float>(geocAngVel[Basic::Nav::IY]);
         pdu->DRentityAngularVelocity.z_axis = static_cast<float>(geocAngVel[Basic::Nav::IZ]);
      }

      // ---
      // Entity marking (EntityMarking)
      // ---
      {
         const char* const pName = getPlayerName();
         size_t nameLen = std::strlen(pName);
         for (unsigned int i = 0; i < EntityMarking::BUFF_SIZE; i++) {
            if (i < nameLen) {
               pdu->entityMarking.marking[i] = pName[i];
            }
            else {
               pdu->entityMarking.marking[i] = '\0';
            }
         }
         pdu->entityMarking.characterSet = 1;
      }

      // ---
      // Capabilities
      // ---
      pdu->capabilites = 0x0;

      // ---
      // Articulation parameters
      // ---
      pdu->numberOfArticulationParameters = manageArticulationParameters(pdu);

      // Size of the PDU package
      unsigned short length = sizeof(EntityStatePDU) + (pdu->numberOfArticulationParameters * sizeof(VpArticulatedPart));
      pdu->header.length = length;

      if (Basic::NetHandler::isNotNetworkByteOrder()) pdu->swapBytes();
      ok = disIO->sendData( reinterpret_cast<char*>(pdu), length );
   }
   return ok;
}