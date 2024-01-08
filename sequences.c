/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"

/*------------------------------------------------
Fonctions de manipulation de chaînes de caracteres
--------------------------------------------------*/

/*
Input : une chaîne de caracteres et un caractere
Output : None
Main : Ajoute le caractere à la fin de la chaîne de caracteres
*/
void appendString(char* str, char c) {
    int length = strlen(str);
    str[length] = c;
    str[length + 1] = '\0';
}

/*
Input : une chaîne de caracteres
Output : None
Main : Initialise la chaîne de caracteres comme une chaîne vide
*/
void set_empty_string(char* str) {
    str[0] = '\0';
}



/*------------------------------------
Fonctions de manipulation de sequences
--------------------------------------*/

/*
Input : une sequence et une chaîne de caracteres
Output : None
Main : Initialise la chaîne de caracteres en tant qu'ID pour la sequence
*/
void set_id(Sequence* sequence, char* ID) {
    int length = strlen(ID);
    for (int i = 0; i < length; i++) {
        sequence->ID[i] = ID[i];
    }
    sequence->ID[length] = '\0';
}

/*
Input : une sequence et une chaîne de caracteres
Output : None
Main : Initialise la chaîne de caracteres en tant que sequence pour l'objet sequence
*/
void set_seq(Sequence* sequence, char* seq) {
    int length = strlen(seq);
    for (int i = 0; i < length; i++) {
        sequence->seq[i] = seq[i];
    }
    sequence->seq[length] = '\0';
}

/*
Input : une sequence et un entier
Output : Un caractere
Main : Retourne le nucleotide correspondant à l'index
*/
char get_nucleotide(Sequence* sequence, int i) { // Je n'ai toujours pas compris dans quel cas je dois utiliser cette fonction
    return sequence->seq[i];
} 

/*
Input : une sequence et deux chaînes de caracteres
Output : None
Main : Initialise l'ID et la sequence pour l'objet sequence
*/
void set_sequence(Sequence* sequence, char* ID, char* seq) {
    set_id(sequence, ID); // On initialise l'ID
    set_seq(sequence, seq); // On initialise la sequence
}

/*
Input : une sequence
Output : None
Main : Effectue l'affichage de la sequence
*/
void affiche_sequence(Sequence* sequence) {

    
    // On fait deux printf, l'un pour l'ID, l'autre pour la séquence
    printf("     * ID : %s\n", sequence->ID);
    printf("     * Sequence : %s\n", sequence->seq);

}


/*-------------------------------
Fonctions de manipulation de fichiers
---------------------------------*/

/*
Input : Adresse d'un fichier
Output : Nombre de sequences dans le fichier
Main : Compte le nombre de sequences presentes dans le fichier
*/
//https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/
int get_number_entries(char* address) {
    int num = 0;
    FILE* ptr;
    char ch;
    ptr = fopen(address, "r");
    if (NULL == ptr) {
        printf("Le fichier ne peut pas être ouvert\n");
    }
    do {
        ch = fgetc(ptr);
        if (ch == '>') {
            num += 1;
        }
    } while (ch != EOF);
    fclose(ptr);
    return num;
}

/*
Input : Adresse d'un fichier
Output : Une chaîne de caracteres
Main : Fonction qui lit un fichier et retourne la chaîne de caracteres
*/
//https://stackoverflow.com/a/15713419
char* readFile(char* fileName) { // Permet de lire le fichier
    FILE* file = fopen(fileName, "r");
    char* code;
    size_t n = 0;
    int c;

    if (file == NULL) return NULL; // Impossible d'ouvrir le fichier
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);

    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }
    code[n] = '\0';
    return code;
}

/*
Input : - une chaîne de caracteres correspondant au code
        - un entier correspondant à la position start, à partir de laquelle on va commencer à chercher
        - Une sequence qu'on va set à partir de l'information trouvee dans le code
Output : - un entier correspondant à la position où on a fini de "lire"
Main : Fonction qui prend le code ainsi qu'une position start, elle va chercher la prochaine sequence 
       definie apres le start et set l'objet sequence avec cette information.
       Elle retourne ensuite la derniere position qui est lu. Pour le cas de la derniere
       sequence elle retourne -1 
*/
int extract_next_sequence(char* code, int start, Sequence* sequence) {

  
    int n = 0; // n va être la position de l'objet ID de la structure séquence.
    int i = start; // Position du '>' actuelle du tableau IDTab[] à la position

    if (code[i] == '>') { // On décale au caractère suivant pour ne pas prendre le '>'
        i++;
    } 

    while (code[i] != '\n' && code[i] != '\0' && n<ID_MAX_LENGTH) // Boucle qui va enregister chaque caractère de l'ID du fichier code, et le mettre dans la structure sequence->ID
    {                                                             // La boucle s'arrête le caractère à la position i est un saut de ligne ou un caractère nulle (marquant la fin de la chaîne de caractère), signifiant la fin du chaîne de caractère de l'ID.
            sequence->ID[n] = code[i];
            n++;
            i++;
    }
    sequence->ID[n] = '\0'; // On marque la fin de la chaîne de caractère
    i++; // On passe au caractère suivant, qui est le 1er caractère de la séquence associé à l'ID qu'on a récupéré
    
    
    n = 0; // On redefinit n à 0, pour commencer au début de sequence->seq.


    // On extrait la séquence, si on lit à la position i un '>' ou un '\0', alors on ne lit plus la séquence, on arrête la boucle.
    while(code[i] != '>' && code[i] != '\0')  

    {
        if (code[i] != '\n') {
            sequence->seq[n] = code[i];
            n++;
        }
        i++;
     
    }
    // On marque la fin de la chaîne de caractère
    sequence->seq[n] = '\0';
    
    // Si le caractère de finale à la position i marque la fin de la chaîne de caractère du fichier, alors c'est que le fichier est terminée, nous avons lu la dernière séquence. Nous renvoyons donc -1
    if (code[i] == '\0')
    {
        return -1; // Si on a lu la dernière séquence
    }  else {
        return 0; // Si on n'a pas lu la dernière séquence
    }

    
    
    
    
    
    
    /*readFile(char* fileName) permet d'avoir accès directement au contenu texte du fichier*/
}

/*
Input : Adresse d'un fichier et une liste de sequences
Output : None
Main : Fonction qui lit un fichier, remplit la liste avec les sequences trouvees dans le fichier
*/
void parse_file(char* address, Sequence tab_sequences[]) {

    // Lire le fichier avec la fonction readFile()
    char* code = readFile(address);
    
    // On définit l'entier n, qui est simplement la position dans le tableau IDTableau ci-dessous.
    int n = 0;

    // On crée le tableau IDTab, qui contiendra toute les position des '>'
    int IDTab[ID_MAX_LENGTH];


    // Cours Structure https://www.youtube.com/watch?v=1Kmq-9knIUY&list=PLrSOXFDHBtfEh6PCE39HERGgbbaIHhy4j&index=14
    // En premier temps on va faire un tableau qui contient la position de tous les ">"
    for (int i = 0; code[i] != '\0' && n < ID_MAX_LENGTH; i++) // la n-ième position du tableau ne peux pas être supérieur à la taille définit du tableau IDTab. 
    {
        // On lit caractère par caractère dans l'objet 'code' qui est notre fichier.
        // Si le caractère actuellement lu est un '>', alors on note ça position dans le tableau IDTab.
        if (code[i] == '>')
        {
            IDTab[n] = i;
            n++;
        }
    }
    // Ainsi on a un tableau qui contient l'ensemble des début de position des ID



    // } Afficher la position de tous les '>'
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d ", IDTab[i]);
    //     printf("\n");
    // }



    // A présent qu'on a la position des début des ID, on va pouvoir extraire les ID et les séquences qui les suivent.


    int position = 0; // Position peut être considéré comme un booléen, il prend par défaut 0, si la séquence extrait de la fonction extract_next_sequence() est la dernière séquence, alors position prendra la valeur de -1, brisant la boucle.
    int i = 0;
    // On réalise une boucle lisant chaque i dans le tableau IDTab.
    while (position != -1 && i < n)
    {
        //La fonction extract_next_sequence va permettre de prendre l'ensemble de la chaîne de caractère de l'ID et la sequence et les renter dans la structure sequence.ID et sequence.seq
        position = extract_next_sequence(code, IDTab[i], &tab_sequences[i]);
        i++;
    }
    


    

    
    
     
    



}

/*
Input : Adresse d'un fichier
Output : None
Main : Parse le fichier, sauvegarde les sequences dans une liste. 
       Puis affiche une sequence une par une.
       Parser ça veut dire : analyser un fichier et entrer les données dans le programme.
*/
void show_sequences_file(char* file){
    int nb_entries = get_number_entries(file);
    printf("Nombre d'entrees : %d\n", nb_entries);
    printf("\n");
    Sequence tab_sequences[nb_entries];
    parse_file(file, tab_sequences);

    for (int i = 0; i < nb_entries; i++) {
        affiche_sequence(&tab_sequences[i]);
        printf("\n");
    }
}
