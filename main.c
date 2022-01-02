#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct strom {

    char string[8193];
    struct strom *vlavo, *doprava;

} BDD;

void uvolni(BDD *root){

    if(root == NULL){
        return;
    }

    uvolni(root->vlavo);
    uvolni(root->doprava);

    free(root);

}

BDD *BDD_create(char pole[]){

    char string1[strlen(pole) / 2 + 1], string2[strlen(pole) / 2 + 1];

    BDD *koren = (BDD *) malloc(sizeof(BDD));

    strcpy(koren ->string, pole);
    //printf("%s\n", koren ->string);

    if(strlen(pole) == 1){
        koren ->doprava = NULL;
        koren ->vlavo = NULL;
       // printf("%s\n", koren->string);
    }

    if(strlen(pole) == 1){
        return koren;
    }

        string1[strlen(pole) / 2] = '\0';
        string2[strlen(pole) / 2] = '\0';

        strncpy(string1, pole, strlen(pole)/2);
        strcpy(string2, pole + strlen(pole)/2);

        koren ->vlavo = BDD_create(string1);
        koren ->doprava = BDD_create(string2);

    return koren;

}

char BDD_use(BDD *root, char *vstupy){

    char znak = '6';
    int i = 0;

    if(strlen(vstupy) != 13){
        return 'k';
    }

    while (znak != '\0'){

        znak = vstupy[i++];

        if(znak == '0'){
            if(root->vlavo == NULL){
                return 'k';
            }
            root = root->vlavo;
        }

        if(znak == '1'){
            if(root->doprava == NULL){
                return 'k';
            }
            root = root->doprava;
        }


    }

    znak = root->string[0];

    return znak;

}

int main() {

    BDD *zaciatok;

    char pole[8193] ={'\0'};
    char testPole[14];
    char znak;
    int cislo, uspesne = 0, neuspesne = 0, kontrolaU = 0, kontrolaN = 0;
    unsigned pocet = 0;

    clock_t t;
    t = clock();

    srand(time(0));

    for (int k = 0; k < 2000; k++) {

        for (int i = 0; i < 8192; i++) {

            cislo = rand() % (2);

            if(cislo == 1){
                pole[i] = '1';
            }

            if(cislo == 0){
                pole[i] = '0';
            }

        }

        zaciatok = BDD_create(pole);

        strcpy(testPole,"0000000000000");

        for(int i = 0; i < 8192; i++){

            znak = BDD_use(zaciatok, testPole);
            pocet++;

            testPole[12]++;

            for(int j = 12; j >= 0; j--){

                if(testPole[j] == '2'){
                    testPole[j] = '0';
                    testPole[j-1]++;
                }
            }

            if(znak == pole[i]){
                uspesne++;
            }

            if(znak == 'k'){
                neuspesne++;
            }

        }

        if(uspesne == 8192){
            kontrolaU++;
            uspesne = 0;
        }

        else{
            kontrolaN++;
            uspesne = neuspesne = 0;
        }

        uvolni(zaciatok);

    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("Cas: %.2f\n", time_taken);
    printf("Uspesne: %d\n", kontrolaU);
    printf("Neuspesne: %d\n", kontrolaN);
    printf("Pocet: %d", pocet);

    return 0;
}
