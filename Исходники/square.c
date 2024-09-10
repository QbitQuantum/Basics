int integer_square(integer_t target, integer_t source) {
  bool aliased;
  integer_t result;
  
  if(integer_is_zero(source)) { return integer_set_unsigned_value(target, 0); }
  
  aliased = (result == source);
  result = aliased ? integer_create(0) : target;

  VERIFY(GROW(result, 2 * LENGTH(source)));
  SET_SIGNED_LENGTH(result, 2 * LENGTH(source));

  VERIFY(digits_square(DIGITS(result), DIGITS(source), LENGTH(source)));
  NORMALIZE(result);

  // TODO: call a karatsuba routine here...

  if(aliased) {
    EXCHANGE(target, result);
    integer_destroy(result);
  }

  return 0;  
}