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
//TODO
float distance(Sequence seq1, Sequence seq2) {
    
    int lengthseq1 = strlen(seq1.seq); //longueur première sequence 
    int lengthseq2 = strlen(seq2.seq); //longueur deuxième sequence
    int diff = 0;                      // compteur du nombre de differences(substitutions) entre les deux sequences
    int length = 0;                    // Compteur du nombre de nucleotides compares
    for (int i=0; i < lengthseq1 && i < lengthseq2; i++){

        if (seq1.seq[i] != seq2.seq[i] && seq1.seq[i] != '-' && seq2.seq[i] != '-')
        {

            diff++;
        }

        if (seq1.seq[i] == '-' || seq2.seq[i] == '-')
        {
            length--;
        }

        length++;
    }
    float distanceseq1seq2 = (float)diff / (float)length;
    printf(" len : %d   diff : %d   dist : %f \n", length, diff, distanceseq1seq2);
    return distanceseq1seq2;
    
}

/*
Input : Float
Output : Float
Main : Fonction qui applique la correction de Jukes-Cantor
*/
//TODO
#include <math.h> //necessaire pour la fonction log
float jukes_cantor(float x) {

    float ln = logf(1.0 - (4.0 / 3.0) * x);

    float realdistanceseq1seq2 = (-3.0 / 4.0) * ln ;
    return realdistanceseq1seq2; //distance reelle après correction

}

/*-------------------------------------------------
Fonctions de manipulation de la matrice de distance
---------------------------------------------------*/

/*
Input : un entier et Une matrice de float
Output : None
Main : Procedure qui initialise une matrice à une matrice nulle
*/
void initialise_matrice(int entries, float matrice_distance[][entries]) {
    
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
void print_matrix_float(int n, int m, float matrix[][m])
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i > 0 && j < i) // Permet de n'écrire que la matrice diagonale inférieure
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][j] = -matrix[i][j];
                    printf("%f ", matrix[i][j]);  // Permet d'éviter m'écriture de -0.0000, ce qui perturbe l'affichage
                }
                else
                {
                    printf("%f ", matrix[i][j]);
                }
            }
            else
            {
                printf(".        ");
            }
        }
        printf("\n"); // pour créer un saut de ligne après chaque ligne de la matrice
    }
}

/*
Input : entier, matrice de float et une liste de sequence
Output : None
Main : Procedure qui remplit la matrice avec la distance entre les sequences
*/
void fill_distance_matrix(int entries, float matrice_distance[][entries], Sequence sequences[]) {
    
    // Les fonctions précédentes sont nécessaire pour celui-ci 
    for (int i = 1 ; i<entries ;i++){
        for (int j = 0;j <i;j++){
            matrice_distance[i][j] = jukes_cantor(distance(sequences[i], sequences[j]));
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
