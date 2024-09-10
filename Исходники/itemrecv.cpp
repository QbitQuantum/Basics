void ItemRecv::processItemDropped(Net::MessageIn &msg)
{
    const BeingId id = msg.readBeingId("id");
    const int itemId = msg.readInt16("item id");
    ItemTypeT itemType = ItemType::Unknown;
    if (msg.getVersion() >= 20130000)
        itemType = static_cast<ItemTypeT>(msg.readInt16("type"));
    const Identified identified = fromInt(
        msg.readUInt8("identify"), Identified);
    const int x = msg.readInt16("x");
    const int y = msg.readInt16("y");
    const int subX = CAST_S32(msg.readInt8("subx"));
    const int subY = CAST_S32(msg.readInt8("suby"));
    const int amount = msg.readInt16("count");

    if (actorManager)
    {
        actorManager->createItem(id,
            itemId,
            x, y,
            itemType,
            amount,
            0,
            ItemColor_one,
            identified,
            Damaged_false,
            subX, subY,
            nullptr);
    }
}