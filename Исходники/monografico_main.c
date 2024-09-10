int main(void){
config(); // Lamamos a la rutina de configuración/inicialización

while(1) {
	SMCR|=(1<<SE); // Nos vamos a dormir
	_SLEEP();
	SMCR&=~(1<<SE);
}
}