void set_user(object new_user) {
  if (!SYSTEM() && !COMMON() && !GAME()) {
    error("Tylko autoryzowany kod może zmieniać użytkownika!");
  }

  user = new_user;
}