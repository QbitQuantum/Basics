void WandEmulationService::generateEvent(Event::Type type)
{
    Event* newEvent = writeHead();
    newEvent->reset(type, Service::Wand, 0);
    newEvent->setPosition(myWandPosition);
    newEvent->setOrientation(myWandOrientation);
    newEvent->setFlags(myEventFlags);

    // Add axis data.
    newEvent->setExtraDataType(Event::ExtraDataFloatArray);
    newEvent->setExtraDataFloat(0, myXAxis);
    newEvent->setExtraDataFloat(1, myYAxis);
}