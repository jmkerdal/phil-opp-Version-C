unsigned char* memB;
unsigned short* memW;
unsigned long* memL;

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);
unsigned char* HEX(unsigned char valeur);

void pokeB(unsigned long adresse, unsigned char valeur);
unsigned char peekB(unsigned long adresse);
void pokeW(unsigned long adresse, unsigned short valeur);
unsigned short peekW(unsigned long adresse);
