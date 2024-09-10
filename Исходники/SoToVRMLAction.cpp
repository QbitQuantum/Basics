SoCallbackAction::Response
SoToVRMLActionP::unsupported_cb(void * closure, SoCallbackAction * COIN_UNUSED_ARG(action), const SoNode * node)
{
  SoInfo * info = NEW_NODE(SoInfo, node);
  SbString str;
  str.sprintf("Unsupported node: %s",
              node->getTypeId().getName().getString());
  info->string = str;
  THISP(closure)->get_current_tail()->addChild(info);
  return SoCallbackAction::CONTINUE;
}