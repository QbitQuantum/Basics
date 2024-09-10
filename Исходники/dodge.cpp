 void Dodge::onLeave()
 {
     State::onLeave();
     unsigned int shieldVal = static_cast<unsigned int>(trunc(_entity->_shieldMaxValue/5));
     _entity->_shieldValue = _entity->_shieldValue < shieldVal ? 0 : _entity->_shieldValue - shieldVal;
 }