compl compl_create(const real rl,const real img){
    /* DESC: Constructor del tipo */

    compl c; 
    c.mod = sqrtl(rl*rl + img*img);
    if (rl > 0){
      c.ang = (atanl(img/rl));
    }else if ((rl < 0) && (img >= 0)) {
            c.ang = atanl((img/rl)+ PI);
    }else if ((rl < 0) && (img < 0)) {
      c.ang = (atanl (img/rl)) - PI;
    }else if ((rl == 0) &&(img > 0)){
      c.ang = PI / 2;
    }else if ((rl == 0) && (img < 0)){
      c.ang = -PI/2;
    }else if ((rl == 0) && (img == 0)){
      c.ang = 0;
    }              
                    
    return c;
}