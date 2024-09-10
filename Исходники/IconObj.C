void IconObj::StateIconFile(char *stateIconName)
{
   delete _stateIconName;
   _stateIconName = STRDUP(stateIconName);
   SetStateIconFile(IconView());
}