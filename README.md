# Calcul de polynôme sur F2 de degré < 64



## Introduction

Il est possible de représenter un polynôme sur F2 en C avec un entier. En effet, en écrivant un nombre N en base 2, nous sommes capable de représenter n’importe quel polynôme sur F2 avec pour limite de degrée la taille du type de la variable choisie.
Exemple : le polynôme de l’AES : X^8 + X^4 + X^3 + X + 1 est représenté par l’entier 283 qui a pour valeur binaire : b = 100011011. On lit b de droite (les coefficients du polynômes de bas degrée) vers la gauche : jusqu’au degrée du polynôme.
Le polynôme de l’AES peut être stockée dans une variable de type unsigned short int. Le plus grand polynôme stockable dans ce type est representée par 65535 = 215 −1 qui n’est autre que X^14 +X^13 +X^12 +X^11 +X^10 +X^9 +X^8 + X^7 +X^6 +X^5 +X^4 +X^3 +X^2 +X^1 +X +1.
Pour notre bibliothèque nous utilisons le type f2 poly t = unsigned int64.

## Installation

```
make all
```

8 programmes seront générés :
- ./arithm_test : des tests des fonctions arithmétiques implémentées
- ./enumerate_irreductible N : afficher dans le terminal (stdout) tous les polynômes irréductibles de degré N sur F2.
- ./enumerate_primitive N : affiche dans le terminal (stdout) tous les polynômes primitifs de degré N sur F2.
-  ./count_irreductible : Compter le nombre de polynômes irréductibles par énumération du degré 1 à 63.
- ./count_primitive : Compter le nombre de polynômes primitifs par énumération du degré 1 à 63.
- ./f2 poly test : Procéder à des tests des fonctions implémentées et donne le nombre de polynômes irréductibles de degré de 1 à 63 et le nombre de polynômes primitifs de 1 à 63.
- ./f2 poly interface (P) : traitement rapide d’un polynôme en argument (P) ou via l’interface
- ./f2 poly random (N): analyser des polynômes aléatoires de degré N en argument ou via l’interface
