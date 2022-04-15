#include "tools.h"

void outb(unsigned short port, unsigned char data) { // Sort un octet sur le port
    asm("mov dx, %0" : : "dN" (port));
    asm("mov al, %0" : : "a" (data));
    asm("out dx, al");
}

unsigned char inb(unsigned short port) { // Lecture octet sur un port
    unsigned char data;
    
    asm("mov dx, %0" : : "dN" (port));
    asm("in %0, dx" : "=a" (data));
    
    return data;
}

unsigned char* HEX(unsigned char valeur) { // Convertie un octet en chaine HEXA
    static unsigned char retour[3];
    int val = valeur >> 4;
    retour[0] = val < 10 ? (char)(val + 48) : (char)(val + 55);
    val = valeur & 0xF;
    retour[1] = val < 10 ? (char)(val + 48) : (char)(val + 55);
    retour[2] = 0; // Fin de chaine
    return retour;
}

void pokeB(unsigned long adresse, unsigned char valeur) {
    memB = (unsigned char *) adresse;
    *memB = valeur;
}

unsigned char peekB(unsigned long adresse) {
    memB = (unsigned char *) adresse;
    return *memB;
}

void pokeW(unsigned long adresse, unsigned short valeur) {
    memW = (unsigned short *) adresse;
    *memW = valeur;
}

unsigned short peekW(unsigned long adresse) {
    memW = (unsigned short *) adresse;
    return *memW;
}
