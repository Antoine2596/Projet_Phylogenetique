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

    // on détermine la position (colonne ou ligne peut importe car il s'agit d'un matrice symétrique) du caractère.
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


    // On détermine la x et y de la case qui à pour ligne la position1 et colonne la position2.
    int position1 = get_val_base(ch1);
    int position2 = get_val_base(ch2);
    // On renvoie la valeur de la case à cette position.
    return similarity_matrix[position1][position2];


}

/*
Input : Deux chaînes de caracteres s
Output : Un entier
Main : Fonction qui prend en entier 2 chaînes de caracteres et qui retourne 
       le score d'alignement entre les deux chaînes
*/
int score_alignement(char* alignement1, char* alignement2) {
    // On détermine via strlen la longueur ds chaînes de caracètres
    int length1 = strlen(alignement1);
    // La somme est définit à 0 au début.
    int somme = 0;
    for (size_t i = 0; i < length1; i++)
    {
        // A chaque itération, on prend le caracètre de chaque séquence à la position i
        char chr1 = alignement1[i];
        char chr2 = alignement2[i];
        // et on ajoute le score de similarité de ces deux caractère à la somme.
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
 // On initialise toutes les cases de la matrice à 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            M[i][j] = 0;
        }
    }

    // Et on remplit la première ligne et la première colonne avec les valeurs décroissantes
    for (int i = 0; i < m; i++) {
        M[0][i] = -5 * i;
    }
    for (int i = 0; i < n; i++) {
        M[i][0] = -5 * i;
    }

   
}


/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice T
*/
void initialise_T(int n, int m, char T[][m]) {
    // La case en 0,0 prend la valeur 'o'
    T[0][0] = 'o';

    // On réalise une double boucle pour remplir toute les cases avec des '.' (soucis de lecture du tableau pour ensuite vérifier la matrice)
    for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
            T[i][j] = '.';
        }
    }

    // Les cases de la premières lignes sont remplis de 'l'
    for (int i = 1; i < m; i++)
    {
        
        T[0][i] = 'l';
        
    }

    // Les cases de la première colonne sont remplit de 'u'
    for (int i = 1; i < n; i++)
    {
        
        T[i][0] = 'u';
        
    }

    




}

/*
Input : un entier
Output : un caractere
Main : Fonction qui retourne le caractere correspondant au maximum index de la formule Mij
*/
char symbole(int entier) {
    // On a mit demande la valeur de l'index, qui nous communique de quel équation a eu la valeur maximal
    // Selon la valeur de l'index, on choisit de prendre d, l ou u
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
    // On détermine EQ1, EQ2 et EQ3, les trois équations qui vont être réaliser pour chaques cases

    int EQ1, EQ2, EQ3;
    // On définit deux pointeurs qui vont pointer vers les deux séquences
    char* alignement1 = s1->seq;
    char* alignement2 = s2->seq;

    // On réalise les équations, EQ1 fait la somme entre la valeur de la case en haut à gauche de la case étudié, avec le score d'alignement des nucléotides présentent à cette case.
    EQ1 = M[i-1][j-1] + similarity_score(alignement1[i-1], alignement2[j-1]);
    EQ2 = M[i][j-1]- 5;
    EQ3 = M[i-1][j] -5;
    
    // On initialise max et index à la première condition
    *max = EQ1;
    *index = 0; // Nous supposons au départ que EQ1 à la valeur maximal et index vaut 0, si ce n'est pas le cas les deux conditions suivants changeront max et index.

    if (EQ2 > *max) {
        *max = EQ2;
        *index = 1; // Supposons 1 pour le mouvement à gauche
    } else if (EQ3 > *max) {
        *max = EQ3;
        *index = 2; // Supposons 2 pour le mouvement vers le haut
    }




    // J'ai mis ici en commentaire un script me permettant d'afficher les valeurs à chaque itération afin de comprendre une erreur que j'avai eu

    // printf("%c - %c\n", s1->seq[i-1], s2->seq[j-1]);
    // printf("M[i-1][j-1] : %d | M[i][j-1] : %d | M[i-1][j] : %d\n", M[i-1][j-1],M[i][j-1],M[i-1][j]);
    // printf("Score : %d\n", similarity_score(alignement1[i-1], alignement2[j-1]));
    // printf("EQ1 : %d | i : %d j :%d \n", EQ1, i, j);
    // printf("EQ2 : %d | i : %d j :%d \n", EQ2, i, j);
    // printf("EQ3 : %d | i : %d j :%d \n", EQ3, i, j);
    // printf("max %d\n", *max);
   
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
    // On prend les dimenssion de la matrice (+1 puisque ont ajoute la valeurs des gaps)
    int n = strlen(seq1.seq)+1;
    int m = strlen(seq2.seq)+1;

    // On créer la matrice M et T de dimension m,n.
    int M[n][m];
    char T[n][m];
    initialise_M(n,m,M);
    initialise_T(n,m,T);

    // On définit index prenant pour valeur 1,2,3 pour communiqué s'il s'agit d'un left, upper, ou diag.
    int index;

    // On réalise une double boucle afin de remplir la matrice M et T.
        for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            // On définit la variable max, qui va être remplacé par le résultat maximal dans la fonction fonction_Mij
            int max = 0; 
            fonction_Mij(&seq1, &seq2, i, j, n, m, M, &max, &index);
            M[i][j] = max;
            T[i][j] = symbole(index);            
        }   
    }

    // Les variable qui vont prendre les chaînes de caractères predront la dimension de la séquence la plus grande.
    int lengthAB;
    if (m > n)
    {
        lengthAB = m;
    }
    else{
        lengthAB = n;
    }
    
    // On définit les tableau seqA et seqB qui vont être deux tableaux qui prendront les séquences A et B respectivement via la matrice T.
    char seqA[lengthAB];
    char seqB[lengthAB];    

    // On définit les positions d'où on lit le tableau T, on commence à la fin. la position vaut n-1 ou m-1 puisque au début nous avons fait +1 pour prendre en compte la colonnes et lignes des gaps.
    int positionN = n-1;
    int positionM = m-1;
    // IndexA et indexB sont les valeurs opposé à position N et M. Où dans la matrice T on lit de la fin vers le début, on ajoute les nucléotides ou les gaps dans le sens début -> dans nos séquences seqA et seqB.
    int indexA = 0;
    int indexB = 0;

    // Remplir seqA et seqB à l'endroit
    while (positionN > 0 || positionM > 0) {
        // On lit la matrice T, et on prend la décision si la case faut d (pour diagonale), u (pour upper) ou l (pour left)
        if (T[positionN][positionM] == 'd') {
            // Si la case lut vaut 'd', alors il n'y a pas de gap. SeqA et SeqB prennent pour leur position index actuelle la valeur de leur séquences respective.
            // 
            seqA[indexA++] = seq1.seq[--positionN];
            seqB[indexB++] = seq2.seq[--positionM];
        } else if (T[positionN][positionM] == 'u') {
            seqA[indexA++] = seq1.seq[--positionN];
            seqB[indexB++] = '-';
        } else if (T[positionN][positionM] == 'l') {
            seqA[indexA++] = '-';
            seqB[indexB++] = seq2.seq[--positionM];
        }
    }

    // Pour terminer les chaînes avec le caractère nul
    seqA[indexA] = '\0';
    seqB[indexB] = '\0';


    
    //On copie les chaînes dans alignement1 et alignement2
    strcpy(alignement1, seqA);
    strcpy(alignement2, seqB);

    // Nous n'arrivons pas à utiliser la fonction reverse_string, cependant cela ne change pas les résultat du score d'alignement.
    // reverse_string(alignement1);
    // reverse_string(alignement2);

    


  


    


}






