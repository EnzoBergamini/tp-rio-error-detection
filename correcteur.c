#include <stdio.h>
#include <stdint.h>

#define WORD_SIZE 8
#define POLYNOMIAL 0xD5
#define MULTIPLE_ERROR 500

/**
 * @brief permet de changer le n-ième bit d'un mot de 8 bits
 *
 * @param n index du bit à changer
 * @param m le mot de 16 bits
 * @return uint16_t le mot de 16 bits avec le n-ième bit inversé
 */
uint16_t chg_nth_bit(int n, uint16_t m) {
    uint16_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
    return m ^ mask;  // Appliquer le masque avec l'opérateur "ou exclusif" binaire pour inverser le n-ième bit
}

/**
 * @brief permet de mettre à 1 le n-ième bit d'un mot de 16 bits
 *
 * @param n index du bit à mettre à 1
 * @param m le mot de 16 bits
 * @return uint16_t le mot de 16 bits avec le n-ième bit à 1
 */
uint16_t set_nth_bit(int n, uint16_t m) {
    uint16_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
    return m | mask;  // Appliquer le masque avec l'opérateur "ou" binaire pour mettre le n-ième bit à 1
}

/**
 * @brief permet de récupérer le n-ième bit d'un mot de 8 bits
 *
 * @param n index du bit à récupérer
 * @param m le mot de 8 bits
 * @return uint8_t le n-ième bit
 */
uint8_t get_nth_bit(int n, uint8_t m) {
    uint8_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
    return (m & mask) >> n;  // Appliquer le masque avec l'opérateur "et" binaire pour récupérer le n-ième bit
}

/**
 * @brief permet d'afficher en binaire un mot de 8 bits
 *
 * @param value le mot de 8 bits
 */
void print_binary_8bit(uint8_t value) {
    for (int i = 7; i >= 0; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            printf("1");
        } else {  // Si le i-ème bit est 0
            printf("0");
        }
    }
}

/**
 * @brief permet d'afficher en binaire un mot de 16 bits
 *
 * @param value le mot de 16 bits
 */
void print_binary_16bit(uint16_t value) {
    for (int i = 15; i >= 0; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            printf("1");
        } else {  // Si le i-ème bit est 0
            printf("0");
        }
    }
}

/**
 * @brief permet d'afficher un mot de k bits
 *
 * @param k nombre de bits à afficher
 * @param value le message de 16 bits
 */
void print_word(int k, uint16_t value) {
    for (int i = 15; i >= 16 - k; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            printf("1");
        } else {  // Si le i-ème bit est 0
            printf("0");
        }
    }
}

/**
 * @brief permet de calculer le cardinal d'un message (le nombre de bit à 1)
 *
 * @param value le message de 16 bits
 * @return int le nombre de bit à 1
 */
int cardinal_bit(uint16_t value) {
    int cpt = 0;
    for (int i = 15; i >= 0; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            cpt++;
        }
    }
    return cpt;
}

/**
 * @brief permet le bit de parité
 *
 * @param m le message de 8 bits
 * @return int 1 si le message est impair, 0 si il est pair
 */
int parity_bit(uint8_t m){
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

/**
 * @brief permet de generer le crc d'un message
 *
 * @param m le message de 8 bits
 * @return uint8_t le crc sur 8 bits correspondant au message
 */
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

/**
 * @brief permet de verifier si le message contient une erreur
 *
 * @param m message de 16 bits
 * @return uint8_t le code d'erreur le syndorme et 0 si il n'y a pas d'erreur
 */
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

/**
 * @brief permet de savoir si le message contient une erreur ou plus
 *
 * si le message contient une erreur, on renvoie l'index du bit qui est erroné
 *
 * @param m le message de 16 bits
 * @return int l'index du bit erroné ou si il y a plus d'une erreur, -1
 */
int crc_error_amount(uint16_t m){
    for (int i = 8; i < 16; ++i) {
        m = chg_nth_bit(i, m);

        if (crcVerif(m) == 0){
            return i-8;
        }

        m = chg_nth_bit(i, m);
    }

    return -1;
}

/**
 * @brief concatene le message et le crc
 *
 * @param m le message de 8 bits
 * @param crc le crc de 8 bits
 * @return uint16_t le message concaténé
 */
uint16_t concat(uint8_t m, uint8_t crc) {
    uint16_t message = m;
    message <<= 8;
    message |= crc;
    return message;
}

/**
 * @brief calcule le minimum des distances de Hamming entre les messages de 8 bits et le message null
 *
 * cela definit la capacité de detection d'erreur du code
 *
 * @param m le message de 8 bits
 * @return int la capacité de detection d'erreur du code
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

    message = chg_nth_bit(14, message);
    printf("\nLe message modif est : %d\n", message);
    print_binary_16bit(message);

    uint8_t error = crcVerif(message);
    if (error == 0){
        printf("\nLe message est valide\n");
    }else{
        printf("\nLe message est invalide\n");
        int error_index = crc_error_amount(message);
        if (error_index == -1){
            printf("Il y a plusieurs erreurs\n");
        }else{
            printf("L'erreur est à la position %d\n", error_index);
            message = chg_nth_bit(error_index+8, message);

            printf("Le message corrigé est : %d\n", message);
            print_binary_16bit(message);
        }
    }


    return 0;
}
