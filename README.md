# tp-rio-error-detection

## Distance de Hamming
ici pour calculer la distance de hamming sur un mots de 8 bits avec le dernier 
bits un bit de control de parité. Donc pour trouver la distance de hamming 
il faut calculer la distance du mot 00000000 avec tout les mots de 8 bits
(en sachant que le dernier bit est un bit de parité donc il est fixer
par les 7 autres bits)

## Code polynomiaux
Ont part d'un polynome (le degrés definit le nombre de bits de redondance)
ici ont part sur un mot de taille de 8 donc un polynome de degrés 8
donc sur un mot de 16 bits => il ya 8 bits qui contient le mot (les bits de poids
fort) et les 8 autres ce sont 

> dans un premier temps nous allons faire un exemple avec un bit de parité

> ici nous allons prendre un mot un 8 bits avec un polynome de degrés 8
> donc le mots finale sera de 16 bits


### Question 1
> Pour simplifier votre travail, 
> sa lecture, et le debuggage, commencez par écrire 
> quatre fonctions utilitaires : 
> set_nth_bit, read_nth_bit, print_word et chg_nth_bit.
> Pour implémenter ces fonctions, vous veillerez à n’utiliser que des 
> opérateurs logiques bit à bit et/ou des shifts. L’utilisation de if ou 
> autre structure de contrôle n’est pas autorisée 
> (à l’exception de for pour la fonction print_word).

### Question 2
> Implémentez le calcul du cardinal des bits à 1 dans un mot de votre code.
