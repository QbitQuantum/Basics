 Matriz<4,1> projeta(Matriz<4,1> t)
 {
    Matriz<4,1> res;
    res.setZero();
    if(tipo_de_projecao == 0){ //ortrográfica
       res = apllyOrto(_M*t);
    }
    else { //perspectiva
       res = applyPersp(_M*t);
    }
    return res;
 }