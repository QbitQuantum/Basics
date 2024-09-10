int qore_number_private::formatNumberString(QoreString& num, const QoreString& fmt, ExceptionSink* xsink) {
   assert(!num.empty());
   assert(num.getEncoding() == fmt.getEncoding());
   // get the length of the format string in characters (not bytes)
   qore_size_t fl = fmt.length();
   if (fmt.empty() || fl == 2) {
      printd(5, "qore_number_private::formatNumberString() invalid format string: '%s' for number: '%s'\n", fmt.getBuffer(), num.getBuffer());
      return 0;
   }

   // get thousands separator character
   QoreString tsep;
   if (tsep.concat(fmt, 0, 1, xsink))
      return -1;

   // decimal separator
   QoreString dsep;
   // number of digits after the decimal separator
   unsigned prec = 0;
   if (fl > 1) {
      if (dsep.concat(fmt, 1, 1, xsink))
         return -1;
      // get byte offset of start of decimal precision number
      qore_offset_t i = fmt.getByteOffset(2, xsink);
      if (*xsink)
         return -1;
      assert(i >= 2);
      prec = atoi(fmt.getBuffer() + i);
      if (!prec)
         dsep.clear();
   }

   //printd(5, "qore_number_private::formatNumberString() tsep: '%s' dsep: '%s' prec: %d '%s'\n", tsep.getBuffer(), dsep.getBuffer(), prec, num.getBuffer());

   // find decimal point
   qore_offset_t dp = num.find('.');
   if (dp != -1) {
      // how many digits do we have now after the decimal point
      qore_size_t d = num.strlen() - dp - 1;
      assert(d);
      if (d < prec)
         num.addch('0', prec - d);
      else if (d > prec) {
         if ((num[dp + prec + 1] > '4') && (roundUp(num, dp + prec)))
            ++dp;
         num.terminate(dp + prec + 1);
      }
      // now substitute decimal point if necessary
      if (dsep.strlen() != 1 || dsep[0] != '.')
         num.replace(dp, 1, dsep.getBuffer());
   }
   else {
      dp = num.size();
      if (prec) {
         // add decimal point
         num.concat(&dsep, xsink);
         assert(!*xsink);
         // add zeros for significant digits
         num.addch('0', prec);
      }
   }

   // now insert thousands separator
   // start of digits before the decimal point
   qore_offset_t ds = num[0] == '-' ? 1 : 0;

   // work backwards from the decimal point
   qore_offset_t i = dp - 3;
   while (i > ds) {
      num.replace(i, 0, tsep.getBuffer());
      i -= 3;
   }

   //printd(0, "qore_number_private::formatNumberString() ok '%s'\n", num.getBuffer());

   //assert(false); xxx
   return 0;
}