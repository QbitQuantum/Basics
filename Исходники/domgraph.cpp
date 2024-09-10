//------------------------------EVAL-------------------------------------------
Tarjan *Tarjan::EVAL() {
  if( !_ancestor ) return _label;
  COMPRESS();
  return (_ancestor->_label->_semi >= _label->_semi) ? _label : _ancestor->_label;
}