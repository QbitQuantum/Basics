QStatus AllJoynBusObjectManager::UnregisterAndDestroyBusObject(_Inout_ alljoyn_busattachment busAttachment, _In_ const PCSTR objectPath)
{
    if (AllJoynBusObjectManager::BusObjectExists(busAttachment, objectPath))
    {
        std::tuple<alljoyn_busobject, bool, int>& busObjectEntry = (*AllJoynBusObjectManager::BusAttachmentMap[busAttachment])[objectPath];

        // Unregister and destroy the specified BusObject, then remove its entry from the containing map.
        alljoyn_busattachment_unregisterbusobject(busAttachment, std::get<0>(busObjectEntry));
        alljoyn_busobject_destroy(std::get<0>(busObjectEntry));
        (*AllJoynBusObjectManager::BusAttachmentMap[busAttachment]).erase(objectPath);

        // If the associated BusAttachment contains no more BusObjects, also remove the BusAttachment from BusAttachmentMap.
        if (AllJoynBusObjectManager::BusAttachmentMap[busAttachment]->size() == 0)
        {
            AllJoynBusObjectManager::BusAttachmentMap.erase(busAttachment);
        }
    }
    return ER_OK;
}