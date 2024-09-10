/*-----------------------------------------------------------------*/
void
allocLocal (symbol * sym)
{
  /* generate an unique name */
  SNPRINTF (sym->rname, sizeof(sym->rname),
            "%s%s_%s_%d_%d",
            port->fun_prefix,
            currFunc->name, sym->name, sym->level, sym->block);

  sym->islocal = 1;
  sym->localof = currFunc;

  /* if this is a static variable */
  if (IS_STATIC (sym->etype))
    {
      allocGlobal (sym);
      sym->allocreq = 1;
      return;
    }

  /* if volatile then */
  if (IS_VOLATILE (sym->etype))
    sym->allocreq = 1;

  /* this is automatic           */

  /* if it's to be placed on the stack */
  if (options.stackAuto || reentrant) {
    sym->onStack = 1;
    if (options.useXstack) {
      /* PENDING: stack direction for xstack */
      SPEC_OCLS (sym->etype) = xstack;
      SPEC_STAK (sym->etype) = sym->stack = (xstackPtr + 1);
      xstackPtr += getSize (sym->type);
    } else {
      SPEC_OCLS (sym->etype) = istack;
      if (port->stack.direction > 0) {
        SPEC_STAK (sym->etype) = sym->stack = (stackPtr + 1);
        stackPtr += getSize (sym->type);
      } else {
        stackPtr -= getSize (sym->type);
        SPEC_STAK (sym->etype) = sym->stack = stackPtr;
      }
    }
    allocIntoSeg (sym);
    return;
  }

  /* else depending on the storage class specified */

  /* if this is a function then assign code space    */
  if (IS_FUNC (sym->type))
    {
      SPEC_OCLS (sym->etype) = code;
      return;
    }

  /* if this is a bit variable and no storage class */
  if (IS_SPEC(sym->type) && SPEC_NOUN (sym->type) == V_BIT)
    {
      SPEC_SCLS (sym->type) = S_BIT;
      SPEC_OCLS (sym->type) = bit;
      allocIntoSeg (sym);
      return;
    }

  if ((SPEC_SCLS (sym->etype) == S_DATA) || (SPEC_SCLS (sym->etype) == S_REGISTER))
    {
      SPEC_OCLS (sym->etype) = (options.noOverlay ? data : overlay);
      allocIntoSeg (sym);
      return;
    }

  if (allocDefault (sym))
    {
      return;
    }

  /* again note that we have put it into the overlay segment
     will remove and put into the 'data' segment if required after
     overlay  analysis has been done */
  if (options.model == MODEL_SMALL) {
      SPEC_OCLS (sym->etype) =
        (options.noOverlay ? port->mem.default_local_map : overlay);
  } else {
      SPEC_OCLS (sym->etype) = port->mem.default_local_map;
  }
  allocIntoSeg (sym);
}