// pack reverse complement read
void packRevComp(char *sym, uint8_t *pck, uint8_t len)
{
  memset(pck, 0, CEIL(len, 4)*sizeof(uint8_t));      
  
  for (uint32_t i = 0; i < len; i++) {
    switch (sym[i]) {
    case 'A': setVal(pck, i, 3); break;
    case 'C': setVal(pck, i, 2); break;
    case 'G': setVal(pck, i, 1); break;
    case 'T': setVal(pck, i, 0); break;
    default : setVal(pck, i, 0);
    }
  }
}