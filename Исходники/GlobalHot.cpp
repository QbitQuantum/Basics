bool GlobalHotImpl::unregister_hot(const QKeySequence &keys) {
  if (keys.isEmpty()) return false;
  Qt::KeyboardModifiers allMods = Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier;
  quint32 code = native_keycode(Qt::Key((keys[0] ^ allMods) & keys[0]));
  quint32 mods = native_modifiers(Qt::KeyboardModifiers(keys[0] & allMods));
  unregister_hot(code, mods);
  m_shortcuts.remove(qMakePair(code, mods));
  return true;
}