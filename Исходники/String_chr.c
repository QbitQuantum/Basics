// ----- predicate

defmethod(OBJ, gisAlnum, Char)
  retmethod(isalnum(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisAlpha, Char)
  retmethod(isalpha(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisBlank, Char)
  retmethod(isblank(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisCntrl, Char)
  retmethod(iscntrl(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisDigit, Char)
  retmethod(isdigit(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisGraph, Char)
  retmethod(isgraph(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisLower, Char)
  retmethod(islower(self->Int.value) ? True : False);
endmethod

defmethod(OBJ, gisPrint, Char)