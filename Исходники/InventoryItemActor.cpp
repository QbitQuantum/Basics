const ActorEvent InventoryItemActor::onHover( Player& player )
{
    if ( !pickedUp ) {
        player.setCursor( CursorStyle::CURSOR_SELECT );
    }

    return BaseActor::onHover( player );
}