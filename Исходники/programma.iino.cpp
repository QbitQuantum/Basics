void loop() {

   statoPulsante = digitalRead(6);
   if(statoPulsante != precedenteStatoPulsante)
      if (statoPulsante == LOW) {
         risposta = random(8);

         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("La Palla dice:");
         lcd.setCursor(0,1);

       switch(risposta) {
          case 0: lcd.print("Si"); break;
          case 1: lcd.print("Molto probabilmente"); break;
          case 2: lcd.print("Certamemte"); break;
          case 3: lcd.print("Sembra di si"); break;
          case 4: lcd.print("Insicuro"); break;
          case 5: lcd.print("Domanda ancora"); break;
          case 6: lcd.print("Molto dubbio"); break;
          case 7: lcd.print("NO"); break;
          };
    };
   precedenteStatoPulsante = statoPulsante;   
}