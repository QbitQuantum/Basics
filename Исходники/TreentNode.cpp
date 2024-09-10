bool TreentNode::deepMouseUp( ci::app::MouseEvent &event )
{
  bool captured = false;
  auto gui_component = component<GuiComponent>();
  if( gui_component )
    captured = gui_component->mouseUp( event, getWorldTransform() );

  for( TreentNodeRef &child : mChildren )
  { // stop evaluation if event was captured by self or a child
    if( captured )
      break;

    captured = child->deepMouseUp( event );
  }
  return captured;
}