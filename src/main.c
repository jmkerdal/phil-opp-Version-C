#include "vga.h"
#include "tools.h"
#include "clavier.h"

int ligne;
int colonne;

void avance_curseur() {
    colonne += 2;
    if (colonne == LARGEUR_ECRAN) {
        colonne = 0;
        ligne++;
    }
}

void kernel_start(unsigned long magic, unsigned long addr) {
    
    vga_init();
    
    vga_efface(vga_couleur(COULEUR_BLANC, COULEUR_BLEU));
    
    //vga_disable_cursor();
    //vga_enable_cursor();
    
    vga_string(vga_couleur(COULEUR_MAGENTA, COULEUR_NOIR), (unsigned char *)"Tauri, demarre!", 0, 0);
    //vga_update_cursor(5, 1);
    
    //asm( "hlt" );

    kb_init();
    ligne = 2;
    colonne = 0;
    int seq_souris = 0;
    
    unsigned char touche;
    unsigned char status;
    unsigned char mouse_byte[3];
    unsigned char echap = 0;
    
    souris_init(); // Active clavier, souris?
    
    do {
        
        // Attend une modification clavier
        //while (!(inb(0x64) & 1));
        do {
            status = inb(0x64);
            vga_string(vga_couleur(COULEUR_ROUGE_CLAIR, COULEUR_NOIR), HEX(status), 1, 10);
        } while (!(status & 1));
        vga_string(vga_couleur(COULEUR_ROUGE, COULEUR_NOIR), HEX(status), 1, 13);
        
        touche = inb(0x60); // Lecture entrée clavier
        
        if (status == 0x1D || status == 0x15) { // Touche clavier
            vga_string(vga_couleur(COULEUR_GRIS_CLAIR, COULEUR_NOIR), HEX(touche), 1, 2);
            if (touche < 128) {
                kb_memo[touche] = 1;
                vga_string(vga_couleur(COULEUR_BLANC, COULEUR_NOIR), HEX(touche), ligne, colonne);
                avance_curseur();
                vga_char(vga_couleur(COULEUR_GRIS_CLAIR, COULEUR_NOIR), caractere(touche), 1, 5);
                echap = 0;
            }
            else {
                //vga_string(vga_couleur(COULEUR_BLEU_CLAIR, COULEUR_NOIR), HEX(touche), 1, 7);
                if (touche == 0xE0) {
                    vga_string(vga_couleur(COULEUR_NOIR, COULEUR_CYAN), HEX(touche), ligne, colonne); // Code sequence
                    avance_curseur();
                    echap = 1;
                }
                else {
                    kb_memo[touche & 0x7F] = 0;
                    vga_string(vga_couleur(COULEUR_NOIR, COULEUR_GRIS_CLAIR), HEX(touche & 0x7F), ligne, colonne); // Touche relachée
                    avance_curseur();
                    echap = 0;
                }
            }
        }
        else { // Souris
            vga_string(vga_couleur(COULEUR_GRIS_CLAIR, COULEUR_NOIR), HEX(touche), 1, 16);
            vga_string(vga_couleur(COULEUR_BLANC, COULEUR_NOIR), HEX(touche), 1, 19 + 2 * seq_souris);
            mouse_byte[seq_souris] = touche;
            if (seq_souris == 2) seq_souris = 0; else seq_souris++;
        }
    } while(1);
}
