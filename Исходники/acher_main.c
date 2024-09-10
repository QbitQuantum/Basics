int main(void){
config();

while(1) {
  SMCR|=(1<<SE);
  _SLEEP();
  SMCR&=~(1<<SE);
}
}