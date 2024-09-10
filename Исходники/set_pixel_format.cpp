void SetPixelFormat::setFormat(PixelFormat format)
{
    Sprite* sprite = this->sprite();

    sprite->setPixelFormat(format);
    sprite->incrementVersion();

    // Regenerate extras
    static_cast<app::Document*>(sprite->document())
    ->setExtraCel(ExtraCelRef(nullptr));

    // Generate notification
    DocumentEvent ev(sprite->document());
    ev.sprite(sprite);
    sprite->document()->notifyObservers<DocumentEvent&>(&DocumentObserver::onPixelFormatChanged, ev);
}