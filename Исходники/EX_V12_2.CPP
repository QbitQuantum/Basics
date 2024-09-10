void Hotell::slett(int nr)  {   //  Oppgave 2C - Sletter/fjerner en gjest:
  Gjest* gjest = (Gjest*) gjester->remove(nr);  //  Pr�ver � ta ut gjesten.
  if (gjest)  {                                 //  Gjesten ble funnet:
     if (*gjest == City)  ant_C--;              //  Teller ned #City-fans.
     else if (*gjest == United)  ant_U--;       //  Teller ned #United-fans.
     delete gjest;                              //  Sletter/fjerner gjesten.
  } else
    cout << "\n\tIngen gjest p� hotellet med dette nummeret!\n";
}