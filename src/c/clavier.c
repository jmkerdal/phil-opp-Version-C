#include "clavier.h"
// Mapping clavier

//unsigned char kb_us[128] = {
//    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
//    '\t' , 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
//    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 0x97, 0xFD,
//    0, '*', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
//    0, 0, ' ', 0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,'<',
//};

unsigned char kb_fr[128] = {
    0, 27, '&', 0x82, '"', '\'', '(', '-', 0x8A, '_', 0x87, 0x85, ')', '=', '\b',
    '\t' , 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n',
    0, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 0x97, 0xFD,
    0, '*', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!', 0,
    0, 0, ' ', 0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,'<',
};

unsigned char kb_fr_shift[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0xF8, '+', '\b',
    '\t' , 'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0xFA, 0x9C, '\n', // 0xFA ou ¨ £ \n
    0, 'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', '%', 0xFD,
    0, 0xE6, 'W', 'X', 'C', 'V', 'B', 'N', '?', '.', 0x2F, 0xA7, 0,
    0, 0, ' ', 0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,'>',
};

unsigned char kb_fr_AltGr[128] = {
    0, 27, '&', '#', '{', '[', '|', '`', 0x5C, '^', 0x85, '@', ']', '}', '\b',
    '\t' , 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', 0x1F, '\n',
    0, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 0x97, 0xFD,
    0, '*', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!', 0,
    0, 0, ' ', 0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,'<',
};

void kb_init() {
    for (unsigned char i = 0; i < 128; i++) kb_memo[i] = 0;
    for (unsigned char i = 0; i < 3; i++) _touche[i] = 0;
}

unsigned char caractere(unsigned char touche) {
    if (kb_memo[0x2A] | kb_memo[0x36]) {
        if (kb_fr_shift[touche]) return kb_fr_shift[touche]; else return kb_fr[touche];
    }
    else {
        return kb_fr[touche];
    }
//    if (kb_memo[0x2A] | kb_memo[0x36]) {
//        if (kb_fr_shift[touche]) return kb_fr_shift[touche]; else return kbdus[touche];
//    }
//    else {
//        return kbdus[touche];
//    }
}

void touche_traite(unsigned char touche) {
    if (touche == 0xE0) {
        _touche[0] = touche;
    } else {
        if (_touche[0] == 0xE0) {
        } else {
        }
    }
}

void touche_ajoute(unsigned char touche) { // Ajoute une touche pour composer un caractère
    
}

unsigned char touche_retire() { // Lit un caractère
    return 0;
}
