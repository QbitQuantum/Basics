void ObjectFactory::handleDatabaseJobComplete(void* ref,DatabaseResult* result)
{
    OFAsyncContainer* asyncContainer = reinterpret_cast<OFAsyncContainer*>(ref);

    switch(asyncContainer->query)
    {
    case OFQuery_House:
    {
        PlayerObject* player = dynamic_cast<PlayerObject*>(gWorldManager->getObjectById(asyncContainer->PlayerId));
        if(!result->getRowCount())
        {
        	LOG(ERROR) << "create house failed : no result";
            break;
        }

        uint64 requestId = 0;
        DataBinding* binding = mDatabase->createDataBinding(1);
        binding->addField(DFT_uint64,0,8);
        result->getNextRow(binding,&requestId);
        mDatabase->destroyDataBinding(binding);

        if(!requestId)
        {
            LOG(ERROR) << "Create house failed : result is 0";
        }
        mHouseFactory->requestObject(asyncContainer->ofCallback,requestId,0,0,asyncContainer->client);

        //now we need to update the Owners Lots
        //cave he might have logged out already - even if thats *very* unlikely (heck of a query that would have been)
        if(player)
        {
            gStructureManager->UpdateCharacterLots(asyncContainer->PlayerId);
            Deed* deed = dynamic_cast<Deed*>(gWorldManager->getObjectById(asyncContainer->DeedId));

            ObjectContainer* tO = dynamic_cast<ObjectContainer*>(gWorldManager->getObjectById(deed->getParentId()));
            //destroy it in the client
            gMessageLib->sendDestroyObject(asyncContainer->DeedId,player);

            //delete it out of the inventory
            tO->deleteObject(deed);

            Datapad* datapad			= player->getDataPad();
            datapad->requestNewWaypoint("Player House",asyncContainer->coords,gWorldManager->getPlanetIdByName(gWorldManager->getPlanetNameThis()),1);

        }

        // now we need to link the deed to the factory in the db and remove it out of the inventory in the db
        int8 sql[250];
        sprintf(sql,"UPDATE items SET parent_id = %"PRIu64" WHERE id = %"PRIu64"",requestId, asyncContainer->DeedId);
        mDatabase->executeSqlAsync(NULL,NULL,sql);

    }
    break;

    case OFQuery_Factory:
    {
        PlayerObject* player = dynamic_cast<PlayerObject*>(gWorldManager->getObjectById(asyncContainer->PlayerId));
        if(!result->getRowCount())
        {
        	LOG(ERROR) << "Create factory failed : no result";
            break;
        }

        uint64 requestId = 0;
        DataBinding* binding = mDatabase->createDataBinding(1);
        binding->addField(DFT_uint64,0,8);
        result->getNextRow(binding,&requestId);
        mDatabase->destroyDataBinding(binding);

        if(!requestId)
        {
        	LOG(ERROR) << "Create factor failed : result is 0";
        }
        mFactoryFactory->requestObject(asyncContainer->ofCallback,requestId,0,0,asyncContainer->client);

        //now we need to update the Owners Lots

        //cave he might have logged out already - even if thats *very* unlikely (heck of a query that would have been)
        if(player)
        {
            gStructureManager->UpdateCharacterLots(asyncContainer->PlayerId);
            Deed* deed = dynamic_cast<Deed*>(gWorldManager->getObjectById(asyncContainer->DeedId));

            //destroy it in the client
            gMessageLib->sendDestroyObject(asyncContainer->DeedId,player);

            //delete it out of the container
            ObjectContainer* tO = dynamic_cast<ObjectContainer*>(gWorldManager->getObjectById(deed->getParentId()));
            tO->deleteObject(deed);

            Datapad* datapad			= player->getDataPad();
            datapad->requestNewWaypoint("Player Factory",asyncContainer->coords,gWorldManager->getPlanetIdByName(gWorldManager->getPlanetNameThis()),1);
        }

        // now we need to link the deed to the factory in the db and remove it out of the inventory in the db
        int8 sql[250];
        sprintf(sql,"UPDATE items SET parent_id = %"PRIu64" WHERE id = %"PRIu64"",requestId, asyncContainer->DeedId);
        mDatabase->executeSqlAsync(NULL,NULL,sql);
        

    }
    break;

    case OFQuery_Harvester:
    {
        if(!result->getRowCount())
        {
        	LOG(ERROR) << "Create harvester failed : no result";
            break;
        }

        uint64 requestId = 0;
        DataBinding* binding = mDatabase->createDataBinding(1);
        binding->addField(DFT_uint64,0,8);
        result->getNextRow(binding,&requestId);
        mDatabase->destroyDataBinding(binding);

        if(requestId)
        {
            mHarvesterFactory->requestObject(asyncContainer->ofCallback,requestId,0,0,asyncContainer->client);

            //now we need to update the Owners Lots
            PlayerObject* player = dynamic_cast<PlayerObject*>(gWorldManager->getObjectById(asyncContainer->PlayerId));

            //cave he might have logged out already - even if thats *very* unlikely (heck of a query that would have been)
            if(player)
            {
                gStructureManager->UpdateCharacterLots(asyncContainer->PlayerId);

                Deed* deed = dynamic_cast<Deed*>(gWorldManager->getObjectById(asyncContainer->DeedId));

                //destroy it in the client
                gMessageLib->sendDestroyObject(asyncContainer->DeedId,player);

                //delete it out of the inventory
                ObjectContainer* tO = dynamic_cast<ObjectContainer*>(gWorldManager->getObjectById(deed->getParentId()));
                tO->deleteObject(deed);

                Datapad* datapad			= player->getDataPad();
                datapad->requestNewWaypoint("Harvester",asyncContainer->coords,gWorldManager->getPlanetIdByName(gWorldManager->getPlanetNameThis()),1);

            }

            // now we need to link the deed to the harvester in the db and remove it out of the inventory
            int8 sql[250];
            sprintf(sql,"UPDATE items SET parent_id = %"PRIu64" WHERE id = %"PRIu64"",requestId, asyncContainer->DeedId);
            mDatabase->executeSqlAsync(NULL,NULL,sql);
         
        }
        else
        	LOG(ERROR) << "Create harvester failed";
    }
    break;

    case OFQuery_WaypointCreate:
    {
        uint64 requestId = 0;
        DataBinding* binding = mDatabase->createDataBinding(1);
        binding->addField(DFT_uint64,0,8);
        result->getNextRow(binding,&requestId);
        mDatabase->destroyDataBinding(binding);

        if(requestId)
            mWaypointFactory->requestObject(asyncContainer->ofCallback,requestId,0,0,asyncContainer->client);
        else
        	LOG(ERROR) << "Create waypoint failed";
    }
    break;
    case QFQuery_WaypointUpdate:
    {
        // we're looking for a value of the waypoint that was updated
        uint32 returnId = 0;
        DataBinding* binding = mDatabase->createDataBinding(1);
        binding->addField(DFT_uint32,0,4);
        result->getNextRow(binding,&returnId);
        mDatabase->destroyDataBinding(binding);
        switch (returnId)
        {
        case 0:
        case 3:
            mWaypointFactory->requestObject(asyncContainer->ofCallback,asyncContainer->Id,0,0,asyncContainer->client);
            break;
        default:
        	LOG(ERROR) << "Update waypoint failed";
        }
    }
    break;
    case OFQuery_Item:
    {
        uint64 requestId = 0;
        DataBinding* binding = mDatabase->createDataBinding(1);
        binding->addField(DFT_uint64,0,8);
        result->getNextRow(binding,&requestId);
        mDatabase->destroyDataBinding(binding);

        if(requestId)
            mTangibleFactory->requestObject(asyncContainer->ofCallback,requestId,TanGroup_Item,0,asyncContainer->client);
        else
        	LOG(ERROR) << "Create item failed";
    }
    break;

    case OFQuery_ResourceContainerCreate:
    {
        uint64 requestId = 0;
        DataBinding* binding = mDatabase->createDataBinding(1);
        binding->addField(DFT_uint64,0,8);
        result->getNextRow(binding,&requestId);
        mDatabase->destroyDataBinding(binding);

        if(requestId)
            mTangibleFactory->requestObject(asyncContainer->ofCallback,requestId,TanGroup_ResourceContainer,0,asyncContainer->client);
        else
        	LOG(ERROR) << "Create resource container failed";
    }
    break;

    default:
    {
        mTangibleFactory->requestObject(asyncContainer->ofCallback,asyncContainer->Id,asyncContainer->Group,0,asyncContainer->client);
    }
    break;
    }

    mDbAsyncPool.free(asyncContainer);
}