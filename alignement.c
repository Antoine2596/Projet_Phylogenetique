/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"

const int similarity_matrix[NB_BASE][NB_BASE] = {{10, -1, -3, -4, -5},
                                                 {-1,  7, -5, -3, -5},
                                                 {-3, -5,  9,  0, -5},
                                                 {-4, -3,  0,  8, -5},
                                                 {-5, -5, -5, -5,  0}};


/*----------------------------------------------------------------------------------
Fonctions permettant de calculer le score d'alignement entre 2 chaînes de caracteres
------------------------------------------------------------------------------------*/

/*
Input : Un caractere
Output : Un entier
Main : Fonction qui prend un caractere et retourne l'index correspondant (voir l'enum Base_Azotee)
*/
int get_val_base(char a) {

    // On lui donne un caractère, et il me donne la position de la ligne ou de la colonne où il se situe
    // Cependant, comment avec juste un caractère, on peut lui dire si c'est la colonne ou la ligne?
    // Ducoup imaginons qu'on a chr1 = C et chr2 = G
    // On se base uniquement sur la position de la colonne, chr1 va renvoyer -1 et chr2 va renvoyer -3
    // Pour le second caractère, il est en deuxième colonne, vu qu'il correcpond à -1.
    // Ensuite pour le second caractère, on va déterminer dans quel position de colonne il est (dans lequel il y a -3), ici la 3ème colonne.
    //Parfait pour déterminer le score, on cherche le score pour à la position du tableau[position chr1][position chr2]

    // Sauf qu'on sait que -1 et -3 sont des scores pour la première ligne, si de base chr2 est A, mais on s'en fou je pense, pourquoi ?
    // Parce on se sert uniqueemnt se ce score pour avoir la position de chr1, ensuite si chr2 vaut -3 alors on c'est qu'il est à la 3ème position.
    int position;
    switch (a)
    {
    case 'A':
        position = 0;
        break;
    case 'C':
        position = 1;
        break;
    case 'G':
        position = 2;
        break;
    case 'T':
        position = 3;
        break;
    case '-':
        position = 4;
        break;
    default:
        break;
    }
    return position;
    
}

/*
Input : Deux caracteres 
Output : Un entier
Main : Fonction qui prend en entier 2 caracteres et qui retourne 
       le score entre les 2 caracteres suivant la matrice de similarite
*/
int similarity_score(char ch1, char ch2) {


    // Mon hypothèse : avec une lettre on peut pas directement savoir où dans le tableau elle se situe (dans quelle colonne/ligne)
    // ON va donc utiliter la fonction get_val_base pour déterminer la colonne ou la ligne dans lequel sont positionné les deux caractères
    // Ensuite, vu qu'on connait la colonne et la ligne, on pourra avoir le score qui se situe à cette position.
    //printf("%c",ch2);
    //Déterminer la position de chr1

    int position1 = get_val_base(ch1);
    int position2 = get_val_base(ch2);
    return similarity_matrix[position1][position2];


}

/*
Input : Deux chaînes de caracteres s
Output : Un entier
Main : Fonction qui prend en entier 2 chaînes de caracteres et qui retourne 
       le score d'alignement entre les deux chaînes
*/
int score_alignement(char* alignement1, char* alignement2) {
    int length1 = strlen(alignement1);
    int somme = 0;
    for (size_t i = 0; i < length1; i++)
    {
        char chr1 = alignement1[i];
        char chr2 = alignement2[i];
        
        somme += similarity_score(alignement1[i],alignement2[i]);
    }
    
    
    return somme;
    
}

/*
Input : Deux chaînes de caracteres et un score
Output : None
Main : Procedure qui prend en entier 2 chaînes de caracteres et un score
       Et qui fait un bel affichage montrant l'alignement et le score
*/
void print_quality_alignement(char* ali1, char* ali2, int score) {

    printf("Le score d'alignement : %d\n", score);
    printf("	%s\n", ali1);
    printf("	%s\n", ali2);
    printf("\n");

}

/*----------------------------
Algorithme de Needleman-Wunsch
------------------------------*/

/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice M
*/
void initialise_M(int n, int m, int M[][m]) {
    int gapscore = 0;
    for (int i = 1; i < n+1; i++)
    {
        
        M[i][2] = gapscore;
        gapscore -= 5;
        
    }
    gapscore = 0;
    for (int i = 1; i < n+1; i++)
    {
        
        M[2][i] = gapscore;
        gapscore -= 5;
        
    }

            for (int i = 1; i < n+1; i++)
    {
        for (int j = 1; j < m+1; j++)
        {
            printf("%c\t", M[i][j]);
        }
        printf("\n");
        
    }



    
    
}

/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice T
*/
void initialise_T(int n, int m, char T[][m]) {
    T[1][1] = 'o';
    for (int i = 2; i < m+1; i++)
    {
        
        T[i][2] = 'l';
        
    }
    for (int i = 2; i < n+1; i++)
    {
        
        T[2][i] = 'u';
        
    }

}

/*
Input : un entier
Output : un caractere
Main : Fonction qui retourne le caractere correspondant au maximum index de la formule Mij
*/
char symbole(int entier) {
    if (entier == 0) {
        return 'd';
    }
    else if (entier == 1) {
        return 'l';
    }
    return 'u';
}

/*
Input : une chaîne de caracteres
Output : None
Main : Procedure qui inverse une chaîne de caracteres
*/
void reverse_string(char* str) {
    char* reverse_string;
    char length = strlen(str);
    for (int i = 0; i < length; i++)
    {
        reverse_string[i] = str[length-i];
    }
    return reverse_string;
}

/*
Input : - 2 Sequences
        - 2 index
        - 2 tailles
        - une matrice de taille n*m
        - Deux pointeurs sur des entiers
Output : None
Main : Procedure qui applique la formule Mij et qui sauvegarde 
       la plus grande valeur dans le premier pointeur et l'index
       correspondant (0, 1 ou 2) dans le deuxieme.
*/
void fonction_Mij(Sequence* s1, Sequence* s2, int i, int j, int n, int m, int M[][m], int* max, int* index) {
    //TODO

    int EQ1, EQ2, EQ3;
    EQ1 = M[i-1][j-1] + similarity_score(s1->seq[i], s2->seq[j]);
    EQ2 = M[i-1][j] -5;
    EQ2 = M[i-1][j] -5;

    if (EQ1 > EQ2 && EQ1 > EQ3);
    {
        max = EQ1;
        index = 0;
    }
    if (EQ2 > EQ1 && EQ2 > EQ3);
    {
        max = EQ2;
        index = 1;

    }
    if (EQ3 > EQ1 && EQ3 > EQ2);
    {
        max = EQ3;
        index = 2;
    }
    

    
}

/*
Input : - 2 Sequences
        - Deux chaînes de caracteres
Output : None
Main : Procedure qui applique l'algorithme Needleman-Wunsch
       sur les 2 sequences et qui sauvegarde les alignements
       dans les 2 pointeurs
*/
void needleman_wunsch(Sequence seq1, Sequence seq2, char* alignement1, char* alignement2) {
    //TODO

    int n = strlen(seq1.seq);
    int m = strlen(seq2.seq);

    int M[n][m];
    char T[n][m];
    initialise_M(n,m,M);
    initialise_T(n,m,T);


    
    int max = 0;
    char index;

        for (int i = 2; i < n+1; i++)
    {
        for (int j = 2; j < m+1; j++)
        {

            fonction_Mij(seq1.seq, seq2.seq, i, j, n, m, M, max, index);
            M[i][j] = max;
            T[i][j] = symbole(index);            
        }   
    }

    int lengthAB;
    if (m > n)
    {
        lengthAB = m;
    }
    else{
        lengthAB = n;
    }
    
    char seqA[lengthAB];
    char seqB[lengthAB];
   

    
    // // Faire l'alignement final
    // while (T[n][m] != 'o')
    // {
    //     printf("n : %d,  m : %d, %c", n, m, T[n][m]);
    //     if (T[n][m] == 'd')
    //     {
    //         seqA[n] = seq1.seq[n];
    //         seqB[m] = seq1.seq[m];
    //         m = m-1;
    //         n = n-1; 
    //         printf("\n1");
    //     }
    //     if (T[n][m] == 'u')
    //     {
    //         seqA[n] = seq1.seq[n];
    //         seqB[m] = '-';
    //         n = n-1;
    //         printf("\n2");
    //     }
    //     if (T[n][m] =='l')
    //     {
    //         seqB[m] = seq2.seq;
    //         seqA[n] = '-';
    //         m = m-1;
    //         printf("\n3");
    //     if (T[n][m] == 'o')
    //     {
    //         break;
    //     }
        

    //     }
        
    //     alignement1 = seqA;
    //     alignement2 = seqB;

        

            
    // }
    
    

}







