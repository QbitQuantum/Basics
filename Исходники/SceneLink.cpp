const ActorEvent SceneLink::onHover( Player& player )
{
    player.setCursor( cursorStyle );

    return BaseActor::onHover( player );
}