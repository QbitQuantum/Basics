/*
******* echoLightPosition()
**
** sets "pos" to xyz position for current sample of given light
*/
void
echoLightPosition(echoPos_t pos[3], echoObject *light,
                  echoThreadState *tstate) {
  char me[]="echoLightPos";
  echoPos_t x, y;
  echoRectangle *rectLight;
  
  x = tstate->jitt[0 + 2*echoJittableLight] + 0.5;
  y = tstate->jitt[1 + 2*echoJittableLight] + 0.5;
  switch(light->type) {
  case echoTypeRectangle:
    rectLight = RECTANGLE(light);
    ELL_3V_SCALE_ADD3(pos, 1, rectLight->origin,
                     x, rectLight->edge0,
                     y, rectLight->edge1);
    break;
  default:
    fprintf(stderr, "%s: currently only support echoTypeRectangle lights", me);
    break;
  }
  return;
}