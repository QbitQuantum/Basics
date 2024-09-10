bool IMCursorManager::createCursor( const CursorType type, const sf::Texture* texture, const sf::Rect<int> offsetAndSize )
{
    return createCursor( type, texture, offsetAndSize.left, offsetAndSize.top, offsetAndSize.width, offsetAndSize.height );
}