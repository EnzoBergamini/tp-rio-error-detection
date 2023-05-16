#include <stdio.h>
#include <stdint.h>

#define WORD_SIZE 8
#define POLYNOMIAL 0x07

uint8_t chg_nth_bit(int n, uint8_t m) {
    uint8_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
    return m ^ mask;  // Appliquer le masque avec l'opérateur "ou exclusif" binaire pour inverser le n-ième bit
}

uint8_t set_nth_bit(int n, uint8_t m) {
    uint8_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
    return m | mask;  // Appliquer le masque avec l'opérateur "ou" binaire pour mettre le n-ième bit à 1
}

uint8_t get_nth_bit(int n, uint8_t m) {
    uint8_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
    return (m & mask) >> n;  // Appliquer le masque avec l'opérateur "et" binaire pour récupérer le n-ième bit
}

void print_binary(uint8_t value) {
    for (int i = WORD_SIZE - 1; i >= 0; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            printf("1");
        } else {  // Si le i-ème bit est 0
            printf("0");
        }
    }
}

void print_word(int k, uint8_t value) {
    for (int i = WORD_SIZE - 1; i >= WORD_SIZE - 1 - k + 1; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            printf("1");
        } else {  // Si le i-ème bit est 0
            printf("0");
        }
    }
}

int cardinal_bit(uint8_t value) {
    int cpt = 0;
    for (int i = 15; i >= 0; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            cpt++;
        }
    }
    return cpt;
}

int hamming_distance(uint8_t m){
    int cpt = 0;
    for (int i = 0; i < 2; i--) {  // Parcours les bits du poids fort au poids faible
        if ((m >> i) & 1) {  // Si le i-ème bit est 1
            cpt++;
        }
    }
    return cpt;
}

uint8_t parity_bit(uint8_t m){
    int cpt = 0;
    for (int i = 0; i < 2; i--) {  // Parcours les bits du poids fort au poids faible
        if ((m >> i) & 1) {  // Si le i-ème bit est 1
            cpt++;
        }
    }
    if (cpt % 2 == 0){
        return 0;
    }
    else{
        return 1;
    }
}

uint8_t crcGeneration(uint8_t m){
    uint8_t crc = 0;

    for (int i = 0; i < 8; i++){
        if ((crc ^ m) & 0x80){
            crc = (crc << 1) ^ POLYNOMIAL;
        }else{
            crc <<= 1;
        }
        m <<= 1;
    }

    return crc;
}

int main(int argc, char const *argv[]) {
    uint8_t m = 0;
    printf("Entrez un nombre (8 bits): ");

    scanf("%hhu", &m);  // Lire un entier non signé sur 8 bits

    printf("Le nombre binaire est : %d\n", m);
    print_binary(m);  // Afficher la représentation binaire de m
    uint8_t crc = crcGeneration(m);
    printf("\nLe CRC est : %d\n", crc);
    return 0;
}
