 //Metodo para invertir las notas en la estructura de lista enlazada.
  void invertirListaEnlazada(){
      Nota temp;
      for(int i=0;i<listaEnlazada.length();i++){
          temp=listaEnlazada.remove(i);
          pila.push(temp);
      }
      while(pila.length()!=0){
          listaEnlazada.append(pila.pop() );
      }
  }