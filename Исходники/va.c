// error: formal x is shadowed by local x, hence can't be seen by va_start
void f(int x, ...) {
  { int x,y;
    va_list p;
    va_start(p,x);
    vscanf("FOO %d %d",p);
  }
}