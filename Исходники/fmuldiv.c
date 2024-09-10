  { if(la&1) { q += qn;
               r += rn;
               if(r>=lc) { q++; r -= lc; }
            }
    la  >>= 1;
/*    la = la & 0x7FFFFFFF;*/
    qn <<= 1;
    rn <<= 1;
    if(rn>=lc) {qn++; rn -= lc; }
  }
  result2 = rneg ? -r : r;
  return qneg ? -q : q;
}

void try(INT32 a, INT32 b, INT32 c)
{ INT32 x = muldiv(a, b, c), y = muldiva(a, b, c);
  printf("muldiv (%8x, %8x, %8x) = %8x,  remainder %8x\n",
          a, b, c, x, result2);
  printf("muldiva(%8x, %8x, %8x) = %8x,  remainder %8x\n\n",
          a, b, c, y, result2a);
}

int main()
{ int i,j,k;
  INT32 w = 0x80000000;

  try(4,5,6);
  try(-5,6,7);
  try(-5,-6,7);
  try(-5,6,-7);
  try(5,-6,7);