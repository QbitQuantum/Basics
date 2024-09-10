__declspec ( naked ) void nseel_asm_floor(void)
{
  FUNC1_ENTER

  *__nextBlock = __floor(*parm_a);

  FUNC_LEAVE
}