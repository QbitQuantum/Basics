void FlattenLayersCommand::onExecute(Context* context)
{
  ContextWriter writer(context);
  Document* document = writer.document();
  Sprite* sprite = writer.sprite();
  int bgcolor = color_utils::color_for_image(ColorBar::instance()->getBgColor(),
                                             sprite->getPixelFormat());
  {
    UndoTransaction undoTransaction(writer.context(), "Flatten Layers");
    document->getApi().flattenLayers(sprite, bgcolor);
    undoTransaction.commit();
  }
  update_screen_for_document(writer.document());
}