#include "vga.h"
#include "tools.h"

void souris_info(unsigned char commande) {
    outb(0x64, 0xD4); //Informe la souris d'un envoie une commande
    outb(0x60, commande); //Commande
}

void souris_init() {
    unsigned char retour;

    //Enable the auxiliary mouse device
    outb(0x64, 0xA8);

    //Enable the interrupts
    outb(0x64, 0x20);
    retour = (inb(0x60) | 2);
    outb(0x64, 0x60);
    outb(0x60, retour);

    //Tell the mouse to use default settings
    souris_info(0xF6);
    retour = inb(0x60);//Acknowledge
    
    //Enable the mouse
    souris_info(0xF4);
    retour = inb(0x60);//Acknowledge

    //Setup the mouse handler
    //irq_install_handler(12, mouse_handler);
}

//void mouse_handler(struct regs *r)
//{
//    static unsigned char cycle = 0;
//    static char mouse_bytes[3];
//    mouse_bytes[cycle++] = inportb(0x60);

//    if (cycle == 3) { // if we have all the 3 bytes...
//        cycle = 0; // reset the counter
//        // do what you wish with the bytes, this is just a sample
//        if ((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40))
//            return; // the mouse only sends information about overflowing, do not care about it and return
//        if (!(mouse_bytes[0] & 0x20))
//            y |= 0xFFFFFF00; //delta-y is a negative value
//        if (!(mouse_bytes[0] & 0x10))
//            x |= 0xFFFFFF00; //delta-x is a negative value
//        if (mouse_bytes[0] & 0x4)
//            puts("Middle button is pressed!n");
//        if (mouse_bytes[0] & 0x2)
//            puts("Right button is pressed!n");
//        if (mouse_bytes[0] & 0x1)
//        puts("Left button is pressed!n");
//        // do what you want here, just replace the puts's to execute an action for each button
//        // to use the coordinate data, use mouse_bytes[1] for delta-x, and mouse_bytes[2] for delta-y
//    }
//}

void vga_init() {
    vga = (char *) 0xb8000;
}

void vga_disable_cursor() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void vga_enable_cursor() { //unsigned char cursor_start, unsigned char cursor_end)
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);
    
    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3E0) & 0xE0) | 15);

    //cursor_enabled = true;
    //outb(0x3D4, 0x0A);
    //outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
    //outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);
    //outb(0x3D5, 0xC0 | cursor_start);
    //outb(0x3D5, 0);
    
    //outb(0x3D4, 0x0B);
    //outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
    //outb(0x3D5, (inb(0x3E0) & 0xE0) | 0);
    //outb(0x3D5, 0xE0 | cursor_end);
    //outb(0x3D5, 0);
}

void vga_update_cursor(unsigned char x, unsigned char y) {
    char pos = y * LARGEUR_ECRAN + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char) (pos & 0xFF));
    
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
}

unsigned char vga_couleur(unsigned char couleur, unsigned char fond) {
    return couleur | fond << 4;
}

void vga_efface(unsigned char couleur) {
    //unsigned long adr = 0xb8000;
    
    for (int i = 0; i < LARGEUR_ECRAN * HAUTEUR_ECRAN; i++) {
        vga[i * 2] = 0x20;
        vga[i * 2 + 1] = couleur;
        
        //pokeB(adr++, 0x20);
        //pokeB(adr++, couleur);
        
        //pokeW(adr, 0x20 | couleur << 8);
        //adr += 2;
    }
}

void vga_string(unsigned char couleur, const unsigned char *string, int ligne, int colonne) {
    int i = ligne * LARGEUR_ECRAN + colonne;
    while( *string != 0) {
        vga[i * 2] = *string++;
        vga[i * 2 + 1] = couleur;
        i++;
    }
}

void vga_char(unsigned char couleur, unsigned char c, int ligne, int colonne) {
    int i = ligne * LARGEUR_ECRAN + colonne;
    vga[i * 2] = c;
    vga[i * 2 + 1] = couleur;
}
