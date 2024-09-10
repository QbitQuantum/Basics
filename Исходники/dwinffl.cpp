void
INFwfile::putShort(short n)
{
  if (n == 0) {
    putChar('0');
    return;
  }

  if (n < 0) {
    putChar('-');
    n = -n;
  }

  if (n >= 10000) {
    putChar((n / 10000) + '0');
    n %= 10000;
    putChar((n / 1000) + '0');
    n %= 1000;
    putChar((n / 100) + '0');
    n %= 100;
    putChar((n / 10) + '0');
    n %= 10;
  }
  else if (n >= 1000) {
    putChar((n / 1000) + '0');
    n %= 1000;
    putChar((n / 100) + '0');
    n %= 100;
    putChar((n / 10) + '0');
    n %= 10;
  }
  else if (n >= 100) {
    putChar((n / 100) + '0');
    n %= 100;
    putChar((n / 10) + '0');
    n %= 10;
  }
  else if (n >= 10) {
    putChar((n / 10) + '0');
    n %= 10;
  }

  putChar(n + '0');
}