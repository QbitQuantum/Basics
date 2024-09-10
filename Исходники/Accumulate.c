Binding MakeAnAccuBinding 
   (Environment sc, Binding attr, DefTableKey context, CoordPtr co) {

  Binding res = BindIdn (sc, IdnOf(attr));
#ifdef ACCUTEST
  printf ("MakeAnAccuBinding line %d\n", LineOf (*co));
#endif
  ResetAttribute (KeyOf (res), KeyOf (attr));
  ResetContext (KeyOf (res), context);
  ResetCoord (KeyOf (res), co);
  ResetIsAccu (KeyOf (res), 1);
  return res;
}/* MakeAnAccuBinding */