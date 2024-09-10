// pequeña prueba
int main()
{
  HWND hwnd = FindWindow( 0, "Solitaire" ) ;
  assert( hwnd ) ;
  DWORD procid = 0 ;
  GetWindowThreadProcessId( hwnd, &procid ) ;
  assert( procid ) ;
  
  //Una manera de tener mas presicion al abrir el proceso. 
  //Practicamente se suman los flags
  DWORD amask = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ ;
  
  HANDLE hproc = OpenProcess( amask, 0, procid ) ;
  assert( hproc ) ;
  
  wchar_t* env = GetEnvironmentStringsW( hproc ) ;

  wchar_t* pwstr = env  ;
  do
  {
    std::cout << pwstr << '\n' ;
    pwstr += wcslen(pwstr) + 1 ; //strlen
  }while( *pwstr ) ;

  delete[] env  ;
}