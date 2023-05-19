#include <stdio.h>
#include <stdint.h>

#define WORD_SIZE 8
#define POLYNOMIAL 0xD5
#define MULTIPLE_ERROR 500

uint16_t chg_nth_bit(int n, uint16_t m) {
    uint16_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
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

void print_binary_8bit(uint8_t value) {
    for (int i = 7; i >= 0; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            printf("1");
        } else {  // Si le i-ème bit est 0
            printf("0");
        }
    }
}

void print_binary_16bit(uint16_t value) {
    for (int i = 15; i >= 0; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            printf("1");
        } else {  // Si le i-ème bit est 0
            printf("0");
        }
    }
}

void print_word(int k, uint8_t value) {
    for (int i = 15; i >= 16 - k; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            printf("1");
        } else {  // Si le i-ème bit est 0
            printf("0");
        }
    }
}

int cardinal_bit(uint16_t value) {
    int cpt = 0;
    for (int i = 15; i >= 0; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
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

    for (int i = 0; i < WORD_SIZE; i++){
        if ((crc ^ m) & 0x80){
            crc = (crc << 1) ^ POLYNOMIAL;
        }else{
            crc <<= 1;
        }
        m <<= 1;
    }

    return crc;
}

uint8_t crcVerif(uint16_t m) {
    uint8_t message = (m >> 8) & 0xFF;    // Extraire les 8 bits de message
    uint8_t error = m & 0xFF;             // Extraire les 8 bits de code d'erreur

    uint8_t new_crc = crcGeneration(message);
    if (new_crc == error) {
        return 0;
    } else {
        return new_crc;
    }
}

int crc_error_amount(uint16_t m){
    for (int i = 8; i < 16; ++i) {
        m = chg_nth_bit(i, m);

        if (crcVerif(m) == 0){
            return i-8;
        }

        m = chg_nth_bit(i, m);
    }

    return MULTIPLE_ERROR;
}

uint16_t concat(uint8_t m, uint8_t crc) {
    uint16_t message = m;
    message <<= 8;
    message |= crc;
    return message;
}

/**
 * @brief calcule la distance de hamming pour un message donné
 */
int hamming_distance(uint16_t m){
    int min = 999;
    for (int i = 1; i < 256; ++i) {
        uint8_t crc = crcGeneration(i);
        uint16_t message = concat(i, crc);
        int distance = cardinal_bit(message);
        if (distance < min){
            min = distance;
        }
    }
    return min;
}

int main(int argc, char const *argv[]) {
    uint8_t m = 0;
    printf("Entrez un nombre (8 bits): ");

    scanf("%hhu", &m);  // Lire un entier non signé sur 8 bits

    printf("Le nombre binaire est : %d\n", m);
    print_binary_8bit(m);  // Afficher la représentation binaire de m
    uint8_t crc = crcGeneration(m);
    printf("\nLe CRC est : %d\n", crc);
    print_binary_8bit(crc);


    uint16_t message = concat(m, crc);

    printf("\nLe message concaténé est : %d\n", message);
    print_binary_16bit(message);

    message = chg_nth_bit(10, message);
    message = chg_nth_bit(14, message);
    printf("\nLe message modif est : %d\n", message);
    print_binary_16bit(message);

    uint8_t error = crcVerif(message);
    if (error == 0){
        printf("\nLe message est valide\n");
    }else{
        printf("\nLe message est invalide\n");
        int error_index = crc_error_amount(message);
        if (error_index == MULTIPLE_ERROR){
            printf("Il y a plusieurs erreurs\n");
        }else{
            printf("L'erreur est à la position %d\n", error_index);
        }
    }


    return 0;
}
