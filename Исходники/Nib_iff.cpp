//------------------------------------------------------------------------------
// IffManager() -- (Output support) IFF manager
//------------------------------------------------------------------------------
bool Nib::IffManager(const double curExecTime)
{
   NetIO* disIO = static_cast<NetIO*>(getNetIO());
   const base::Pair* pair = getPlayer()->getRadioByType(typeid(models::Iff));

   // OK if the player has an IFF transponder and we're the correct version.
   bool ok = (disIO->getVersion() >= NetIO::VERSION_1278_1A) && (pair != nullptr);

   if (ok) {
      const models::Iff* iffSystem = static_cast<const models::Iff*>(pair->object());

      if (isIffUpdateRequired(curExecTime, iffSystem)) {


         // Standard header stuff
         IffAtcNavaidsPDU pdu;
         pdu.header.protocolVersion = disIO->getVersion();
         pdu.header.exerciseIdentifier = disIO->getExerciseID();
         pdu.header.PDUType = NetIO::PDU_IFF_ATC_NAVAIDS;
         pdu.header.protocolFamily = NetIO::PDU_FAMILY_DIS_EMISSION_REG;
         pdu.header.timeStamp = disIO->timeStamp();
         pdu.header.length = sizeof(IffAtcNavaidsPDU);

         // Entity ID
         pdu.emittingEntityID.simulationID.siteIdentification = getSiteID();
         pdu.emittingEntityID.simulationID.applicationIdentification = getApplicationID();
         pdu.emittingEntityID.ID = getPlayerID();

         // Location (default is center of parent entity)
         pdu.location.component[0] = 0;
         pdu.location.component[1] = 0;
         pdu.location.component[2] = 0;

         // System ID (for now just use a standard Mark X11; upgrade to type from IFF later)
         pdu.systemID.systemType = 1;        // Mark X11
         pdu.systemID.systemName = 2;        // Mark X11
         pdu.systemID.systemMode = 0;        // Other
         pdu.systemID.options = iffOptions;  // Option bits

         // Functional operational data
         pdu.operationalData.systemStatus = iffFunOpData->systemStatus;
         pdu.operationalData.alternateParam4 = iffFunOpData->alternateParam4;
         pdu.operationalData.informationLayers = iffFunOpData->informationLayers;
         pdu.operationalData.modifier = iffFunOpData->modifier;
         pdu.operationalData.param1 = iffFunOpData->param1;
         pdu.operationalData.param2 = iffFunOpData->param2;
         pdu.operationalData.param3 = iffFunOpData->param3;
         pdu.operationalData.param4 = iffFunOpData->param4;
         pdu.operationalData.param5 = iffFunOpData->param5;
         pdu.operationalData.param6 = iffFunOpData->param6;

         // Event ID
         pdu.eventID.simulationID.siteIdentification = disIO->getSiteID();
         pdu.eventID.simulationID.applicationIdentification = disIO->getApplicationID();
         pdu.eventID.eventNumber = disIO->getNewIffEventID();

         //pdu.dumpData();
         if (base::NetHandler::isNotNetworkByteOrder()) pdu.swapBytes();
         ok = disIO->sendData(reinterpret_cast<char*>(&pdu), sizeof(pdu));

         iffLastExecTime = curExecTime;

      }

   }

   return ok;
}