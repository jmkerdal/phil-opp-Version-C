#define COULEUR_NOIR            0x00
#define COULEUR_BLEU            0x01
#define COULEUR_VERT            0x02
#define COULEUR_CYAN            0x03
#define COULEUR_ROUGE           0x04
#define COULEUR_MAGENTA         0x05
#define COULEUR_MARRON          0x06
#define COULEUR_GRIS_CLAIR      0x07
#define COULEUR_GRIS            0x08
#define COULEUR_BLEU_CLAIR      0x09
#define COULEUR_VERT_CLAIR      0x0A
#define COULEUR_CYAN_CLAIR      0x0B
#define COULEUR_ROUGE_CLAIR     0x0C
#define COULEUR_MAGENTA_CLAIR   0x0D
#define COULEUR_MARRON_CLAIR    0x0E
#define COULEUR_BLANC           0x0F

#define LARGEUR_ECRAN 80
#define HAUTEUR_ECRAN 25

char *vga;

void souris_info(unsigned char commande);
void souris_init();
void vga_init();
void vga_disable_cursor();
void vga_enable_cursor();
void vga_update_cursor(unsigned char x, unsigned char y);
unsigned char vga_couleur(unsigned char couleur, unsigned char fond);
void vga_efface(unsigned char couleur);
void vga_string(unsigned char couleur, const unsigned char *string, int ligne, int colonne);
void vga_char(unsigned char couleur, unsigned char c, int ligne, int colonne);
