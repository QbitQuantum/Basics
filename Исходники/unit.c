int is_unit_present(char *label, char *unit){
  if(strlen(label)!=strlen(unit)||STRCMP(label,unit)!=0)return 0;
  return 1;
}