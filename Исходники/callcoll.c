void 
backAndForth(UCollationElements *iter)
{
    /* Run through the iterator forwards and stick it into an array */
    int32_t idx, o;
    UErrorCode status = U_ZERO_ERROR;
    int32_t orderLength = 0;
    OrderAndOffset *orders = getOrders(iter, &orderLength);


    /* Now go through it backwards and make sure we get the same values */
    idx = orderLength;
    ucol_reset(iter);

    /* synwee : changed */
    while ((o = ucol_previous(iter, &status)) != UCOL_NULLORDER) {
#if TEST_OFFSETS
      int32_t offset = 
#endif
        ucol_getOffset(iter);

      idx -= 1;
      if (o != orders[idx].order) {
        if (o == 0)
          idx ++;
        else {
          while (idx > 0 && orders[-- idx].order == 0) {
            /* nothing... */
          }

          if (o != orders[idx].order) {
              log_err("Mismatched order at index %d: 0x%8.8X vs. 0x%8.8X\n", idx,
                orders[idx].order, o);
            goto bail;
          }
        }
      }

#if TEST_OFFSETS
      if (offset != orders[idx].offset) {
        log_err("Mismatched offset at index %d: %d vs. %d\n", idx,
            orders[idx].offset, offset);
        goto bail;
      }
#endif

    }

    while (idx != 0 && orders[idx - 1].order == 0) {
      idx -= 1;
    }

    if (idx != 0) {
        log_err("Didn't get back to beginning - index is %d\n", idx);

        ucol_reset(iter);
        log_err("\nnext: ");

        if ((o = ucol_next(iter, &status)) != UCOL_NULLORDER) {
            log_err("Error at %x\n", o);
        }

        log_err("\nprev: ");

        if ((o = ucol_previous(iter, &status)) != UCOL_NULLORDER) {
            log_err("Error at %x\n", o);
        }

        log_verbose("\n");
    }

bail:
    free(orders);
}