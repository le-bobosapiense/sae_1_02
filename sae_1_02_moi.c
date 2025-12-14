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
    
    while (fgets(line, sizeof(line), f)) {      // Boucle pour lire le fichier ligne par ligne
        line[strcspn(line, "\n")] = '\0';  // retirer le caractère '\n' à la fin de la ligne


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


void rechercher_RAM(struct Arbre arbres[], int nb_arbres) {
    char arbre_cherche[20];
    printf("Choisir la catégorie d'arbre que vous voulez rechercher : ");
    scanf("%19s", arbre_cherche);

    int trouve = 0; // pour savoir si on a trouvé au moins un arbre

    for (int i = 0; i < nb_arbres; i++) {
        if (strcmp(arbres[i].Espece, arbre_cherche) == 0) {
            printf("| %-12s | %-12s | %3d | %6.2f | %6.2f | %6.2f | %2d |\n",
                   arbres[i].Identifiant,
                   arbres[i].Espece,
                   arbres[i].Age,
                   arbres[i].Hauteur,
                   arbres[i].Diametre,
                   arbres[i].Volume,
                   arbres[i].Sante);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun arbre de l'espèce '%s' trouvé.\n", arbre_cherche);
    }

    printf("-------------------------------------------------------------------------------\n");
}


int main() {
    struct Arbre arbres[61];
    int nb_arbres = ram(arbres);
    afficher_RAM(arbres, nb_arbres);
    rechercher_RAM(arbres, nb_arbres);
    return 0;
}
