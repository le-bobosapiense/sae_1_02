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
int ram(struct Arbre arbres[]) {                    //struct Arbre: c'est le type et arbres c'est le tableau qui enregistre chaque ligne 
    FILE *f = fopen("foret_arbres_50_V1.csv", "r"); // ouvrir le fichier CSV en lecture
    if (!f) {                                      // vérifier si l'ouverture a échoué
        perror("Erreur ouverture fichier");        // afficher le message d'erreur
        return 0;                                  // retourner 0 si le fichier n'a pas pu être ouvert
    }

    char line[256];         // capacité de lecture de caractère par ligne ici 256
    int nb_arbres = 0;      // compteur du nombre d'arbres chargés
    
    while (fgets(line, sizeof(line), f)) {      // Boucle pour lire le fichier ligne par ligne, fgets lit une ligne du fichier csv, sizeof retourne la taille en mémoire
        line[strcspn(line, "\n")] = '\0';  // retirer le caractère '\n' à la fin de la ligne

        if (nb_arbres == 0) {   // première ligne = en-têtes
            nb_arbres++;
            continue;           // on ignore cette ligne pour les calculs
        }
        char *token = strtok(line, ";");    // découper la ligne en tokens (séparés par ';')
        struct Arbre a;                     // créer une variable temporaire pour stocker l'arbre
        int colonne = 0;                     // compteur de colonne pour savoir quel champ on lit

        // Boucle pour lire tous les tokens de la ligne
        while (token != NULL) {
            // Selon la colonne, remplir le bon champ de la structure
            for (char *p = token; *p; p++) if (*p == ',') *p = '.'; // remplacer ',' par '.' pour qu'il détect les valeur float
            if (colonne == 0) strcpy(a.Identifiant, token); // colonne 0 Identifiant, strcpy permet de copier notre chaine de caractère dans a.identifiant
            else if (colonne == 1) strcpy(a.Espece, token); // colonne 1 Espece 
            else if (colonne == 2) a.Age = atoi(token);     // colonne 2 Age (conversion string  int), atoi convertie caine de caractère en entier
            else if (colonne == 3) a.Hauteur = atof(token); // colonne 3 Hauteur (string  float), atof convertie une chaine de caractère en flotant
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

void afficher_entete() {
    printf("| %-12s | %-12s | %-3s | %-10s | %-12s | %-11s | %-10s |\n",   // les nombre son les espace de caractère dédier pour l'espace entre les valeur dans le tableau
           "Identifiant", "Espece", "Age",
           "Hauteur(m)", "Diametre(cm)", "Volume(m3)", "Sante(/10)");
}



// Fonction pour afficher les arbres déjà chargés en RAM
void afficher_RAM(struct Arbre arbres[], int nb_arbres) {
    for (int i = 1; i < nb_arbres; i++) {    // boucle sur tous les arbres
        printf("| %-12s | %-12s | %3d | %-10.2f | %-12.2f | %-11.2f | %-10d |\n",       //format d'afichate %x et la position l'écartement entre deux token que on print, 
        //et .2 signifi que on print 2 caractère après la virgule
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


void rechercher_RAM(struct Arbre arbres[], int nb_arbres) {     // Fonction pour rechercher un arbre dans la RAM selon l'espèce
    char arbre_cherche[20];  // variable pour stocker l'espèce recherchée
    printf("Choisir la categorie d'arbre que vous voulez rechercher : ");
    scanf("%19s", arbre_cherche);  // lit une chaîne (max 19 caractères) entrée par l'utilisateur

    int trouve = 0; // flag pour savoir si au moins un arbre a été trouvé
    afficher_entete();
    
    for (int i = 1; i < nb_arbres; i++) {           // boucle sur tous les arbres en mémoire
        if (strcmp(arbres[i].Espece, arbre_cherche) == 0) {      // comparer l'espèce de l'arbre courant avec celle recherchée
            printf("| %-12s | %-12s | %3d | %-10.2f | %-12.2f | %-11.2f | %-10d |\n",            
                   arbres[i].Identifiant,
                   arbres[i].Espece,
                   arbres[i].Age,
                   arbres[i].Hauteur,
                   arbres[i].Diametre,
                   arbres[i].Volume,
                   arbres[i].Sante);
            trouve = 1; // on marque que l'on a trouvé au moins un arbre
        }
    }

    
    if (!trouve) {          // si aucun arbre n'a été trouvé, afficher un message
        printf("Aucun arbre de l'espèce '%s' trouve.\n", arbre_cherche);
    }

    // ligne séparatrice pour l'affichage
    printf("-------------------------------------------------------------------------------\n");
}

void tri_bulle_age(struct Arbre arbres[], int nb_arbres) {      // Tri à bulle par âge (méthode 1)

    for (int i = 1; i < nb_arbres - 1; i++) {    // boucle principale : chaque passage met l'arbre le plus âgé à la fin

        for (int j = 1; j < nb_arbres - i - 1; j++) {
            if (arbres[j].Age > arbres[j+1].Age) {            // comparer l'âge de l'arbre j et j+1
                struct Arbre temp = arbres[j];                // échanger les deux arbres si l'ordre n'est pas correct
                arbres[j] = arbres[j+1];
                arbres[j+1] = temp;
            }
        }
    }
}

void tri_selection_sante(struct Arbre arbres[], int nb_arbres) {        // Tri par sélection par santé (méthode 2)
    for (int i = 1; i < nb_arbres - 1; i++) {    // pour chaque position i, on cherche le minimum dans le reste du tableau
        int min_idx = i; // indice du minimum trouvé
        for (int j = i + 1; j < nb_arbres; j++) {
            if (arbres[j].Sante < arbres[min_idx].Sante) {
                min_idx = j; // mise à jour du minimum
            }
        }
        struct Arbre temp = arbres[i];        // échanger l'arbre à i avec le minimum trouvé
        arbres[i] = arbres[min_idx];
        arbres[min_idx] = temp;
    }
}

int menu() {
    int choix;                                  //fonction qui nous permet de faire le choix de ce que l'on veut exécuté
    printf("\n========= MENU =========\n");
    printf("1 - Rechercher par espece\n");
    printf("2 - Trier par age\n");
    printf("3 - Trier par sante\n");
    printf("0 - Quitter\n");
    printf("========================\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    return choix;
}


int main() {

    struct Arbre arbres[61];            // tableau pour stocker les arbres
    int nb_arbres = ram(arbres);        // charger les arbres depuis le CSV

    // affichage initial des données
    printf("=== Donne=ees initiales ===\n");
    afficher_entete();
    afficher_RAM(arbres, nb_arbres);

    int choix;


    do {
        choix = menu();

        switch (choix) {

        case 1:
        // affichage de notre recherche
            printf("\n=== Recherche d'espece ===\n");
            rechercher_RAM(arbres, nb_arbres);
            break;

        case 2:
        // tri par âge et affichage
            printf("\n=== Tri par age (Bubble Sort) ===\n");
            tri_bulle_age(arbres, nb_arbres);
            afficher_entete();
            afficher_RAM(arbres, nb_arbres);
            break;

        case 3:
        // tri par santé et affichage
            printf("\n=== Tri par sante (Selection Sort) ===\n");
            tri_selection_sante(arbres, nb_arbres);
            afficher_entete();
            afficher_RAM(arbres, nb_arbres);
            break;

        case 0:
            printf("Fin du programme.\n");
            break;

        default:
            printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}




