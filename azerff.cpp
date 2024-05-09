#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USERNAME "utilisateur"
#define PASSWORD "motdepasse"

typedef struct {
    int id;
    char nom[50];
    char marque[50]; 
    int quantite;
    float prix;
    struct fournisseur {
        char nom[50];
        char contact[50];
    } fournisseur;
} produit;

produit *prod = NULL; 
int n = 0;

void affmenu() {
    printf("\n\t\t\t\t===============================================================================\n");
    printf("                       \t\t\t\t      GESTION DES PRODUITS\n");
    printf("\n\t\t\t\t===============================================================================\n");
    printf("                      \t\t\t\t1. Ajouter un produit\n");
    printf("                     \t\t\t\t -----------------------\n");
    printf("                     \t\t\t\t 2. Afficher tous les produits\n");
    printf("                      \t\t\t\t-----------------------------\n");
    printf("                     \t\t\t\t 3. Modifier un produit\n");
    printf("                      \t\t\t\t----------------------------\n");
    printf("                     \t\t\t\t 4. Supprimer un produit par son id\n");
    printf("                      \t\t\t\t---------------------------\n");
    printf("                     \t\t\t\t 5. Supprimer les produits ayant la meme marque\n");
    printf("                      \t\t\t\t----------------------------------------------\n");
    printf("                      \t\t\t\t6. Supprimer les produits ayant le meme nom\n");
    printf("                      \t\t\t\t-------------------------------------------\n");
    printf("                      \t\t\t\t7. Supprimer les produits ayant le meme fournisseur\n");
    printf("                      \t\t\t\t----------------------------------------------------\n");
    printf("                     \t\t\t\t 8. Afficher les produits d'une marque\n");
    printf("                      \t\t\t\t---------------------------------------\n");
    printf("                      \t\t\t\t9. Afficher les produits d'un fournisseur\n");
    printf("                     \t\t\t\t -------------------------------------------\n");
    printf("                      \t\t\t\t10. Afficher les produits d'un nom\n");
    printf("                      \t\t\t\t-----------------------------------\n");
    printf("                      \t\t\t\t11. Trier les produits par nom\n");
    printf("                     \t\t\t\t ----------------------------------\n");
    printf("                      \t\t\t\t12. Trier les produits par prix\n");
    printf("                     \t\t\t\t-----------------------------------\n");
    printf("                     \t\t\t\t 13. Afficher le fournisseur le plus actif\n");
     printf("                     \t\t\t\t -------------------------------------------\n");
    printf("                     \t\t\t\t 14. Quitter\n");
    printf("\t\t\t\t===============================================================================\n");
    printf("                                 \t\t\t\t Votre choix : ");
}



void ajtprod() {
    FILE *ajt;
    ajt = fopen("produit.csv", "a");
    int i;
    int nouveaun;
    printf("entrez le nombre de produits : ");
    scanf("%d", &nouveaun);
    prod = (produit *)realloc(prod, (n + nouveaun) * sizeof(produit));
    for (i = n; i < n + nouveaun; i++) {
        printf("\nentrez l'id du produit : ");
        scanf("%d", &(prod + i)->id);
        printf("entrez le nom du produit : ");
        scanf("%s", (prod + i)->nom);
        printf("entrez la marque du produit : "); 
        scanf("%s", (prod + i)->marque); 
        printf("entrez la quantite du produit : ");
        scanf("%d", &(prod + i)->quantite);
        printf("entrez le prix du produit : ");
        scanf("%f", &(prod + i)->prix);
        printf("entrez le nom du fournisseur : ");
        scanf("%s", (prod + i)->fournisseur.nom);
        printf("entrez le contact du fournisseur : ");
        scanf("%s", (prod + i)->fournisseur.contact);
        printf("le produit a ete ajoute avec succes.\n");
        fprintf(ajt,"%d;%s;%s;%d;%.2f;%s;%s",(prod + i)->id,(prod + i)->nom,(prod + i)->marque,(prod + i)->quantite,(prod + i)->prix,(prod + i)->fournisseur.nom,(prod + i)->fournisseur.contact);
    }
    fclose(ajt) ;
	    n += nouveaun; 
}

void affprod() {
    printf("\nliste des produits :\n");
    printf("id\t|nom\t\t|marque\t\t|quantite\t|prix\t\t|fournisseur\t|contact\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t|%s\t\t|%s\t|%d\t\t|%.2f\t|%s\t\t|%s\n", (prod + i)->id, (prod + i)->nom, (prod + i)->marque, (prod + i)->quantite, (prod + i)->prix, (prod + i)->fournisseur.nom, (prod + i)->fournisseur.contact);
    }
}

void modifproduit() {
    int id;
    printf("\nEntrez l'ID du produit à modifier : ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if ((prod + i)->id == id) {
            printf("\nNouvelles informations pour le produit :\n");
            printf("Nouveau nom : ");
            scanf("%s", (prod + i)->nom);
            printf("Nouvelle marque : ");
            scanf("%s", (prod + i)->marque);
            printf("Nouvelle quantite : ");
            scanf("%d", &(prod + i)->quantite);
            printf("Nouveau prix : ");
            scanf("%f", &(prod + i)->prix);
            printf("Nouveau fournisseur : ");
            scanf("%s", (prod + i)->fournisseur.nom);
            printf("Nouveau contact fournisseur : ");
            scanf("%s", (prod + i)->fournisseur.contact);
            printf("Produit modifié avec succès.\n");
            return;
        }
    }

    printf("Produit non trouvé.\n");
}


void supprimerproduit() {
    int id;
    printf("\nentrez l'id du produit a supprimer : ");
    scanf("%d", &id);
    for (int i = 0; i < n; i++) {
        if ((prod + i)->id == id) {
            for (int j = i; j < n - 1; j++) {
                *(prod + j) = *(prod + j + 1);
            }
            n--;
            printf("le produit a ete supprime avec succes.\n");
            return;
        }
    }
    printf("produit non trouve.\n");
}

void supprimermarque(char marque[]) {
    int i, j;
    for (i = 0; i < n; i++) {
        if (strcmp((prod + i)->marque, marque) == 0) {
            for (j = i; j < n - 1; j++) {
                *(prod + j) = *(prod + j + 1);
            }
            n--;
            i--; 
        }
    }
    printf("les produits de la marque %s ont ete supprimes avec succes.\n", marque);
}

void supprimernom(char nom[]) {
    int i, j;
    for (i = 0; i < n; i++) {
        if (strcmp((prod + i)->nom, nom) == 0) {
            for (j = i; j < n - 1; j++) {
                *(prod + j) = *(prod + j + 1);
            }
            n--;
            i--; 
        }
    }
    printf("les produits avec le nom %s ont ete supprimes avec succes.\n", nom);
}

void supprimerfournisseur(char nomfournisseur[]) {
    int i, j;
    for (i = 0; i < n; i++) {
        if (strcmp((prod + i)->fournisseur.nom, nomfournisseur) == 0) {
            for (j = i; j < n - 1; j++) {
                *(prod + j) = *(prod + j + 1);
            }
            n--;
            i--; 
        }
    }
    printf("les produits du fournisseur %s ont ete supprimes avec succes.\n", nomfournisseur);
}
void affichermarque(char marque[]) {
    printf("\nProduits de la marque %s :\n", marque);
    printf("id\t|nom\t\t|marque\t\t|quantite\t|prix\t\t|fournisseur\t|contact\n");
    for (int i = 0; i < n; i++) {
        if (strcmp((prod + i)->marque, marque) == 0) {
            printf("%d\t|%s\t\t|%s\t|%d\t\t|%.2f\t|%s\t\t|%s\n", (prod + i)->id, (prod + i)->nom, (prod + i)->marque, (prod + i)->quantite, (prod + i)->prix, (prod + i)->fournisseur.nom, (prod + i)->fournisseur.contact);
        }
    }
}

void afficherfournisseur(char nomfournisseur[]) {
    printf("\nProduits du fournisseur %s :\n", nomfournisseur);
    printf("id\t|nom\t\t|marque\t\t|quantite\t|prix\t\t|fournisseur\t|contact\n");
    for (int i = 0; i < n; i++) {
        if (strcmp((prod + i)->fournisseur.nom, nomfournisseur) == 0) {
            printf("%d\t|%s\t\t|%s\t|%d\t\t|%.2f\t|%s\t\t|%s\n", (prod + i)->id, (prod + i)->nom, (prod + i)->marque, (prod + i)->quantite, (prod + i)->prix, (prod + i)->fournisseur.nom, (prod + i)->fournisseur.contact);
        }
    }
}

void affichernom(char nom[]) {
    printf("\nProduits avec le nom %s :\n", nom);
    printf("id\t|nom\t\t|marque\t\t|quantite\t|prix\t\t|fournisseur\t|contact\n");
    for (int i = 0; i < n; i++) {
        if (strcmp((prod + i)->nom, nom) == 0) {
            printf("%d\t|%s\t\t|%s\t|%d\t\t|%.2f\t|%s\t\t|%s\n", (prod + i)->id, (prod + i)->nom, (prod + i)->marque, (prod + i)->quantite, (prod + i)->prix, (prod + i)->fournisseur.nom, (prod + i)->fournisseur.contact);
        }
    }
}

int verifierConnexion(const char* id, const char* motDePasse) {
    char identifiant[] = "yassine";
    char mdp[] = "123456";

    int resultatComparaisonId = strcmp(id, identifiant);
    int resultatComparaisonMdp = strcmp(motDePasse, mdp);

    if (resultatComparaisonId == 0 && resultatComparaisonMdp == 0) {
        return 1; 
    } else {
        return 0; 
    }
}void trierparnom() {
    produit temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp((prod + j)->nom, (prod + j + 1)->nom) > 0) {
                temp = *(prod + j);
                *(prod + j) = *(prod + j + 1);
                *(prod + j + 1) = temp;
            }
        }
    }
    printf("Produits tries par nom :\n");
    affprod();
}

void trierparprix() {
    produit temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((prod + j)->prix > (prod + j + 1)->prix) {
                temp = *(prod + j);
                *(prod + j) = *(prod + j + 1);
                *(prod + j + 1) = temp;
            }
        }
    }
    printf("Produits tries par prix croissant :\n");
    affprod();
}
void fournisseurleplusactif() {
    
    char fournisseuractif[50] = "";
    int maxnombreproduits = 0;

    for (int i = 0; i < n; i++) {
     
        int nombreproduitsfournisseuractuel = 0;

        for (int j = 0; j < n; j++) {
            if (strcmp((prod + i)->fournisseur.nom, (prod + j)->fournisseur.nom) == 0) {
                nombreproduitsfournisseuractuel++;
            }
        }

        // Mettre à jour le fournisseur le plus actif si nécessaire
        if (nombreproduitsfournisseuractuel > maxnombreproduits) {
            maxnombreproduits = nombreproduitsfournisseuractuel;
            strcpy(fournisseuractif, (prod + i)->fournisseur.nom);
        }
    }

    if (maxnombreproduits > 0) {
        printf("\nLe fournisseur le plus actif est : %s avec %d produit(s).\n", fournisseuractif, maxnombreproduits);
    } else {
        printf("\nAucun produit n'a été trouvé.\n");
    }
}




int main() {
	char id[20], mdp[20];
    int tentatives = 0;

    do {
        printf("Identifiant : ");
        scanf("%s", id);
        printf("Mot de passe : ");
        scanf("%s", mdp);

        if (verifierConnexion(id, mdp)) {
            printf("Connexion reussie !");
            break; 
        } else {
            tentatives++;
            printf("Identifiant ou mot de passe incorrect.\n");
            if (tentatives >= 3) {
                printf("Nombre maximal de tentatives atteint. Le programme va se fermer.\n");
                return 1; 
            } else {
                printf("Il vous reste %d tentative(s).\n", 3 - tentatives);
            }
        }
    } while (tentatives < 3);

    int choix;
    do {
        affmenu();
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                ajtprod();
                break;
            case 2:
                affprod();
                break;
            case 3:
                modifproduit();
                break;
            case 4:
                supprimerproduit();
                break;
            case 5: {
                char marque[50];
                printf("entrez la marque des produits a supprimer : ");
                scanf("%s", marque);
                supprimermarque(marque);
                break;
            }
            case 6: {
                char nom[50];
                printf("entrez le nom des produits a supprimer : ");
                scanf("%s", nom);
                supprimernom(nom);
                break;
            }
            case 7: {
                char nomfournisseur[50];
                printf("entrez le nom du fournisseur des produits a supprimer : ");
                scanf("%s", nomfournisseur);
                supprimerfournisseur(nomfournisseur);
                break;
            }
            case 8: {
                 char marque[50];
                 printf("Entrez la marque des produits a afficher : ");
                 scanf("%s", marque);
                 affichermarque(marque);
                 break;
            }
            case 9: {
                 char nomfournisseur[50];
                 printf("Entrez le fournisseur des produits a afficher : ");
                 scanf("%s", nomfournisseur);
                 afficherfournisseur(nomfournisseur);
                 break;
            }
            case 10: {
                 char nom[50];
                 printf("Entrez le nom des produits a afficher : ");
                 scanf("%s", nom);
                affichernom(nom);
                 break;
            }
            case 11:
            trierparnom();
                 break;
            case 12:
                 trierparprix();
                 break;

            case 13:
                 fournisseurleplusactif();
                break;
            case 14:
                printf("au revoir !\n");
                break;
            default:
                printf("choix invalide. veuillez reessayer.\n");
        }
    } while (choix != 14);

    free(prod);
    return 0;
}
