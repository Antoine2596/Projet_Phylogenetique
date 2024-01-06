/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"

/*
Input : Deux Sequences
Output : Float
Main : Fonction qui retourne la distance entre deux sequences 
*/
float distance(Sequence seq1, Sequence seq2) {
    //TODO
    int lengthseq1 = strlen(seq1->seq); //longueur première sequence 
    int lengthseq2 = strlen(seq2->seq); //longueur deuxième sequence
    int lengthtot = lengthseq1 + lengthseq2; //longueur totale des sequences
    int diff = 0; //compteur du nombre de differences(substitutions) entre les deux sequences
    for (int i=0; i < lengthseq1 && i < lengthseq2; i++){
        if (seq1->seq[i] != seq2->seq[i]){
            diff++;
        }
    }
    float distanceseq1seq2 = (float)diff/lengthtot;
    return distanceseq1seq2;
}

/*
Input : Float
Output : Float
Main : Fonction qui applique la correction de Jukes-Cantor
*/
#include <math.h> //necessaire pour la fonction log
float jukes_cantor(float x) {
    //TODO
    float realdistanceseq1seq2 = (-3.0/4.0)*log(1-(3.0/4.0)*x); //3/4 donne 0 sur C car c'est des entiers or on veut un float donc j'ajoute ".0"
    return realdistanceseq1seq2; //distance reelle après correction de jukes

}

/*-------------------------------------------------
Fonctions de manipulation de la matrice de distance
---------------------------------------------------*/

/*
Input : un entier et Une matrice de float
Output : None
Main : Procedure qui initialise une matrice à une matrice nulle
*/
void initialise_matrice(int entries, float matrice_distance[][entries]) { //apparemment, nous sommes en présence d'une matrice carrée
    //TODO
    for (int i = 0; i < entries; i++){
        for (int j = 0; j < entries; j++){
            matrice_distance[i][j] = 0;
        }
    }
}

/*
Input : Deux entiers et Une matrice de float
Output : None
Main : Procedure qui print une matrice
*/
void print_matrix_float(int n, int m, float matrix[][m]) {
    //TODO
    for (int i = 0;i<n;i++){
        for (int j = 0;j<m;j++){
            printf("%f\t",matrix[i][j]); //le \t est la tabulation et apparemment ça permet d'éviter que les éléments de la matrice soient collés les uns aux autres
        }
        printf("\n"); //pour créer un saut de ligne après chaque ligne de la matrice 
    }
}

/*
Input : entier, matrice de float et une liste de sequence
Output : None
Main : Procedure qui remplit la matrice avec la distance entre les sequences
*/
void fill_distance_matrix(int entries, float matrice_distance[][entries], Sequence sequences[]) {
    //TODO
    // je pense qu'il faut utiliser les fonctions précédentes pour celui-ci 
    for (int i = 0; i<entries;i++){
        for (int j = 0;j<entries;j++){
            float distancepaire = distance(sequences[i],sequences[j]);
            float distancecorrigee = jukes_cantor(distancepaire);
            matrice_distance[i][j] = distancecorrigee;
        }
    }
}

/*
Input : Un fichier
Output : None
Main : Fonction qui prend une adresse en entree et qui calcule et affiche la matrice de distance correspondant aux sequences
*/
void show_distance_matrix(char* file_aligne){
    int nb_entries = get_number_entries(file_aligne);
    Sequence tab_sequences_aligne[nb_entries];
    parse_file(file_aligne, tab_sequences_aligne);

    float matrice_distance[nb_entries][nb_entries];
    initialise_matrice(nb_entries, matrice_distance);
    fill_distance_matrix(nb_entries, matrice_distance, tab_sequences_aligne);
    printf("La matrice de distance calculee pour le fichier '%s' :\n", file_aligne);
    print_matrix_float(nb_entries, nb_entries, matrice_distance);
    printf("\n");
}
