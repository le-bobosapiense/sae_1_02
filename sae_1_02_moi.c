#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition d'une structure pour représenter un arbre
struct Arbre {
    char Identifiant[20];  // identifiant unique de l'arbre ex: AR042
    char Espece[20];       // espece de l'arbre ex: Chene, Erable
    int Age;               // âge en années
    float Hauteur;         // hauteur en mètres
    float Diametre;        // diamètre en cm
    float Volume;          // volume en m3
    int Sante;             // état de santé sur 10
};

// Fonction pour charger les données du CSV en mémoire
// Elle prend en paramètre un tableau de struct Arbre et retourne le nombre d'arbres lus
int ram(struct Arbre arbres[]) {
    FILE *f = fopen("foret_arbres_50_V1.csv", "r"); // ouvrir le fichier CSV en lecture
    if (!f) {                                      // vérifier si l'ouverture a échoué
        perror("Erreur ouverture fichier");        // afficher le message d'erreur
        return 0;                                  // retourner 0 si le fichier n'a pas pu être ouvert
    }

    char line[256];         // capacité de lecture de caractère par ligne ici 256
    int nb_arbres = 0;      // compteur du nombre d'arbres chargés
    int ligne_num = 0;      // compteur pour savoir si on est sur la première ligne (en-têtes)

    
    while (fgets(line, sizeof(line), f)) {      // Boucle pour lire le fichier ligne par ligne
        line[strcspn(line, "\n")] = '\0';  // retirer le caractère '\n' à la fin de la ligne
        if (ligne_num == 0) {              // si c'est la première ligne en-tête
            ligne_num++;                        // on l'incrémente
            continue;                       // on passe à la ligne suivante
        }

        char *token = strtok(line, ";");    // découper la ligne en tokens (séparés par ';')
        struct Arbre a;                     // créer une variable temporaire pour stocker l'arbre
        int colonne = 0;                     // compteur de colonne pour savoir quel champ on lit

        // Boucle pour lire tous les tokens de la ligne
        while (token != NULL) {
            // Selon la colonne, remplir le bon champ de la structure
            for (char *p = token; *p; p++) if (*p == ',') *p = '.'; // remplacer ',' par '.' pour qu'il détect les valeur float
            if (colonne == 0) strcpy(a.Identifiant, token); // colonne 0 Identifiant
            else if (colonne == 1) strcpy(a.Espece, token); // colonne 1 Espece
            else if (colonne == 2) a.Age = atoi(token);     // colonne 2 Age (conversion string → int)
            else if (colonne == 3) a.Hauteur = atof(token); // colonne 3 Hauteur (string → float)
            else if (colonne == 4) a.Diametre = atof(token); // colonne 4 Diametre
            else if (colonne == 5) a.Volume = atof(token);   // colonne 5 Volume
            else if (colonne == 6) a.Sante = atoi(token);    // colonne 6 Sante

            colonne++;                           // passer à la colonne suivante
            token = strtok(NULL, ";");           // passer au token suivant
        }

        arbres[nb_arbres] = a; // stocker l'arbre dans le tableau
        nb_arbres++;           // incrémenter le nombre d'arbres stockés
        ligne_num++;           // passer à la ligne suivante
    }

    fclose(f);                  // fermer le fichier
    return nb_arbres;           // retourner le nombre d'arbres chargés
}

// Fonction pour afficher les arbres déjà chargés en RAM
void afficher_RAM(struct Arbre arbres[], int nb_arbres) {
    for (int i = 0; i < nb_arbres; i++) {    // boucle sur tous les arbres
        printf("| %-12s | %-12s | %3d | %6.2f | %6.2f | %6.2f | %2d |\n",
               arbres[i].Identifiant,          // afficher l'identifiant
               arbres[i].Espece,               // afficher l'espèce
               arbres[i].Age,                  // afficher l'âge
               arbres[i].Hauteur,              // afficher la hauteur
               arbres[i].Diametre,             // afficher le diamètre
               arbres[i].Volume,               // afficher le volume
               arbres[i].Sante);               // afficher l'état de santé
    }
    // afficher une ligne pour séparer le tableau
    printf("-------------------------------------------------------------------------------\n");
}






int aficher(){
    FILE *f = fopen("foret_arbres_50_V1.csv", "r");      // ouverture du fichier css situer dans le même dossier que l'exécutable
    if (!f) {
        perror("Erreur ouverture fichier");     //si on arrive pas a ouvrire le fichier
        return 1;
    }
    char line[256];                             // capacité de lecture de caractère par ligne
    while (fgets(line, sizeof(line), f)) {      // lie le fichier f ligne par ligne; 
        line[strcspn(line, "\n")] = '\0';       //permet de suprimer le retour a la ligne automatique a la fin du dernier token de chaque ligne

        char *token = strtok(line, ";");      // découpe la ligne par token avec comme séparateur ;
        
        while (token != NULL) {
            printf("| %-12s ", token);          // affiche le fichier f ligne par ligne
            token = strtok(NULL, ";"); // passer au token suivant
        }
        printf("|\n");
        printf("------------------------------------------------------------------------------------------------------\n");       // pour séparer les ligne

    }
}

int rechercher(void) {
    FILE *f = fopen("foret_arbres_50_V1.csv", "r");      // ouverture du fichier css situer dans le même dossier que l'exécutable
    if (!f) {
        perror("Erreur ouverture fichier");     //si on arrive pas a ouvrire le fichier
        return 1;
    }

    char line[256];         // capacité de lecture de caractère par ligne
    char copy_line[256];    // copi de line pour avoir la ligne intacte

    int colonne_espece = -1;  // position de la colonne Espece
    int ligne_num = 0;        // compteur de lignes

    while (fgets(line, sizeof(line), f)) {  // lie le fichier f ligne par ligne; 
        //boucle : fgets lit une ligne entière du fichier f dans la mémoire line, elle lit jusqu’au prochain saut de ligne (\n) ou jusqu’à 
        //ce que line soit pleine (ici 256 caractères max). La boucle while continue tant qu’il y a des lignes à lire. 
        
        line[strcspn(line, "\n")] = '\0';   //permet de suprimer le retour a la ligne automatique a la fin du dernier token de chaque ligne
        int colonne = 0;                  // compteur pour les colonnes de cette ligne
        strcpy (copy_line, line);         // on créer une copy de line car il vas être fragmentée 
        char *token = strtok(line, ";");      // découpe la ligne par token avec comme séparateur ;

        while (token != NULL) {
            if (ligne_num == 0) { // première ligne = en-têtes
                if (strcmp(token, "Espece") == 0) {     //regarde ci le token et égal a Espece en considérent les majuscule
                    colonne_espece = colonne; // mémoriser la position
                }
            } else { // autres lignes = données
                if (colonne == colonne_espece) {
                    if (strcmp(token, "Chene") == 0){
                        printf("%s",copy_line);             // copie la ligne si on a dans la colone Espece, Chene
                    }
                }
            }
            colonne++;                  // on ajoute 1 a notre compteur de colone
            token = strtok(NULL, ";"); // passer au token suivant
        }
        ligne_num++; // passer à la ligne suivante
    }

    fclose(f);
    return 0;
}

int main() {
    struct Arbre arbres[60];
    int nb_arbres = ram(arbres);
    afficher_RAM(arbres, nb_arbres);
    return 0;
}