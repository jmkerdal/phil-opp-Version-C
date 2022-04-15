// Mapping clavier
unsigned char kb_memo[128];

void kb_init();
unsigned char caractere(unsigned char touche);

unsigned char _touche[3];
void touche_traite(unsigned char touche);
void touche_ajoute(unsigned char touche);
unsigned char touche_retire();
