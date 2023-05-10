#include <stdio.h>
#include <stdint.h>

uint16_t chg_nth_bit(int n, uint16_t m) {
    uint16_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
    return m ^ mask;  // Appliquer le masque avec l'opérateur "ou exclusif" binaire pour inverser le n-ième bit
}

uint16_t set_nth_bit(int n, uint16_t m) {
    uint16_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
    return m | mask;  // Appliquer le masque avec l'opérateur "ou" binaire pour mettre le n-ième bit à 1
}

uint16_t get_nth_bit(int n, uint16_t m) {
    uint16_t mask = 1 << n;  // Créer un masque pour le n-ième bit (en partant de 0)
    return (m & mask) >> n;  // Appliquer le masque avec l'opérateur "et" binaire pour récupérer le n-ième bit
}

void print_binary(uint16_t value) {
    for (int i = 15; i >= 0; i--) {  // Parcours les bits du poids fort au poids faible
        if ((value >> i) & 1) {  // Si le i-ème bit est 1
            printf("1");
        } else {  // Si le i-ème bit est 0
            printf("0");
        }
    }
}

void print_word(int k, uint16_t value) {
    for (int i = 15; i >= 15 - k + 1; i--) {  // Parcours les bits du poids fort au poids faible
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

int main(int argc, char const *argv[]) {
    uint16_t m = 0;
    printf("Entrez un nombre entre 0 et 65 535 (16 bits): ");
    scanf("%hu", &m);  // Utiliser le format de conversion %hu pour lire un uint16_t
    printf("Le nombre binaire est : ");
    print_binary(m);  // Afficher la représentation binaire de m
    printf("\n");
    printf("cardinal bit 1 : %d\n"), cardinal_bit(m);
    return 0;
}
