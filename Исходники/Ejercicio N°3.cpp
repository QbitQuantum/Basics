void cargarUnCliente(Cliente &regi)
{
  int tipoDePoliza = -1;   
     
  printf("\n------------- ");
  printf("\nNuevo Cliente ");
  printf("\nDNI: ");
  _flushall();
  scanf("%d", &regi.dni);

  printf("\nApellido: ");
  _flushall();
  gets(regi.apellido);


  printf("\nNombre: ");
  _flushall();
  gets(regi.nombre);


  do 
  {
      printf("\nPoliza (0 a 4): ");
      _flushall();
      scanf("%d", &tipoDePoliza);
  }
  while ( ( tipoDePoliza < 0 ) || ( tipoDePoliza > 4) );

  regi.poliza = tipoDePoliza; 

  printf("\nMonto: ");
  _flushall();
  scanf("%f", &regi.montoAsegurado);


  printf("\nCiudad: ");
  _flushall();
  gets(regi.ciudad);
  
  printf("\n------------- ");
     
}