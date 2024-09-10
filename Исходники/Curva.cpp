float Curva::Yn(int n){
    if (n >= cantidadDePuntos)
        return Yn(n-cantidadDePuntos);
	if (n < 0)
        return Yn(n+cantidadDePuntos);
    return this->puntos[n]->Y();
}