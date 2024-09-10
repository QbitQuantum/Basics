/*! Creates a new expression struct with the given type
    @param type     the type of data to be stored in the expression
    @return         the new expression struct
*/
inline expression* newExpressionOfType (datatype type) {
	exprvals ev;
	switch(type) {
		case TYPE_NIL:
			break;
		case TYPE_EXP:
			ev.expval = NULL;
			break;
		case TYPE_LAZ:
			ev.lazval = newLazyExpression();
			break;
		case TYPE_INT:
			ev.intval = 0;
			break;
		case TYPE_FLO:
			ev.floval = 0;
			break;
		case TYPE_STR:
			ev.strval = newString(strDup(""));
			break;
		case TYPE_ARR:
			ev.arrval = newArray(0);
			break;
		case TYPE_DAT:
			ev.datval = time(NULL);
			break;
		case TYPE_OBJ:
			// TODO
			break;
		case TYPE_FUN:
			ev.funval = newTapFunction(NULL, 0, 0, newExpressionNil());
			break;
		case TYPE_TYP:
			ev.intval = TYPE_UNK;
			break;
	}
    return newExpressionAll(type, &ev, NULL, 0); // set the value to null until a real value is given and set the next expression to null
}