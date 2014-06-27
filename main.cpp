#include <cstdio>
#include "miosix.h"
#include <unistd.h>
#include <cstring>
#include <map>
#include "Proprieta.h"
#include "UserInterface.h"
#include <string>
#include "miosix.h"
#include "light_aware.h"
#include <fft.h>
#include <goertzel_algorithm.h>
#include <complex.h>
#include <miosix/_examples/context_aware/adc.h>
#include "subscribe_light_aware.h"

using namespace std;
using namespace miosix;

UserInterface userInterface;

FFTAlgorithm algorithm;
subscribe_light_aware sub;

light_aware light_awareness(algorithm, ADCInit::NO_TIMER, sub);

/*questa funzione controlla che la stringa inserita in input dall'utente corrisponda
 * ad un modulo del progetto, che deve essere un numero che va da 1 a 8; sfrutto
 * quindi il codice ASCII per controllare il range dei valori numerici considerati
 * validi.
 */
short controllaModulo(std::string stringa) {
    char msgModuloErrato[50] = "ERRORE: il modulo inserito non è valido.";
    if (stringa.size() != 1) {
        printf("%s \n", msgModuloErrato);
        scanf("%*[^\n]");
        return -1;
    } else {
        /* controllo che la stringa non abbia valori non numerici
         * e che non siano tra i moduli previsti dal progetto,
         * cioè che non siano numeri compresi tra 1 a 8
         */
        if (stringa[0] < 49 or stringa[0] > 56) {
            printf("%s \n", msgModuloErrato);
            scanf("%*[^\n]");
            return -1;
        } else {
            return atoi(stringa.c_str());
        }
    }
}

/* questa funzione controlla che la stringa che l'utente ha immesso in input, che corrisponde
 * in questo caso ad un nome di una nuova proprieta, non superi di dimensione la massima
 * dimensione consentita per le proprieta, la quale maxDimensione è stata definita all'interno
 * del file Proprieta.cpp.
 */
bool controllaDimensioneProprieta(std::string stringa) {
    char msgDimProprieta[70] = "ERRORE: la proprieta inserita supera i 30 caratteri di lunghezza!";
    if (stringa.size() > Proprieta::maxDimProprieta) {
        printf("%s \n", msgDimProprieta);
        return true;
    }
    return false;
}

/* questa funzione controlla che l'input dell'utente corrisponda ad un valore numerico
 * valido da poter essere utilizzato nella gestione delle proprieta; si sfrutta anche qui
 * il codice ASCII per verificare il range numerico attendibile, con aggiunta del
 * carattere separatore del punto necessario per i double.
 */
double controllaValore(std::string stringa) {
    char msgValoreErrato[50] = "ERRORE: il valore inserito non è valido.";

    int i = 0;
    bool error = false;
    while (!error and stringa[i] != '\0') {
        if ((stringa[i] < 48 or stringa[i] > 57) and stringa[i] != '.')
            error = true;
        else
            i++;
    }
    if (error == false)
        return atof(stringa.c_str());
    else {
        printf("%s \n", msgValoreErrato);
        scanf("%*[^\n]");
        return -1;
    }
}

/* questa funzione è usata come esempio al posto di usarne una già definita in un altro file 
 * che dovrebbe essere fornita dagli altri moduli; viene chiamata ogni volta che viene 
 * trovata una sottoscrizione con una callback function il cui valore è diverso da NULL.
 */
void funzioneDiCallback() {

    printf("light level: %g\n", light_awareness.getMeasure());

    if (light_awareness.isOutdoor()) {
        printf("Outside\n");
    } else {
        printf("Inside\n");
    }

}

int main() {

    std::vector<Proprieta::CheckResult> risultatoCheck;
    std::vector<Proprieta::CallbackFn> vectorfn;
    char primaStringa[UserInterface::maxDimComando];
    char secondaStringa[Proprieta::maxDimProprieta];
    char terzaStringa[Proprieta::maxDimProprieta];
    double valore;
    short modulo;
    unsigned int i;
    char vuoiCallbackfn;
    char msgProprietaInesistente[50] = "ERRORE: la proprieta inserita non esiste.";

    userInterface.help();

    for (;;) {
        scanf("%s", primaStringa);
        if (!userInterface.esisteComando(primaStringa)) {
            printf("ERRORE: il comando inserito non esiste. \n");
            scanf("%*[^\n]");
        } else {
            if (strcmp(primaStringa, "help") == 0) {
                userInterface.help();
                scanf("%*[^\n]"); //elimina eventuali parole dopo un comando errato
            }
            if (strcmp(primaStringa, "read") == 0) {
                scanf("%s%*[^\n]", secondaStringa);
                if (userInterface.esisteProprieta(secondaStringa)) {
                    printf("%s = %f \n", secondaStringa, userInterface.read(secondaStringa));
                } else {
                    printf("%s \n", msgProprietaInesistente);
                    scanf("%*[^\n]");
                }
            }
            if (strcmp(primaStringa, "update") == 0) {
                scanf("%s", secondaStringa);
                if (userInterface.esisteProprieta(secondaStringa)) {
                    scanf("%s%*[^\n]", terzaStringa);
                    if ((valore = controllaValore(terzaStringa)) != -1) {
                        vectorfn = userInterface.update(secondaStringa, valore);
                        printf("INFO: proprieta %s aggiornata con successo!! \n", secondaStringa);
                        if (vectorfn.size() != 0)
                            for (i = 0; i < vectorfn.size(); i++)
                                vectorfn[i]();
                    }
                } else {
                    printf("%s \n", msgProprietaInesistente);
                    scanf("%*[^\n]");
                }
            }
            if (strcmp(primaStringa, "subscribe") == 0) {
                scanf("%s", secondaStringa);
                if (userInterface.esisteProprieta(secondaStringa)) {
                    scanf("%s", terzaStringa);
                    if ((modulo = controllaModulo(terzaStringa)) != -1) {
                        /* lo spazio prima del %c è voluto per una corretta lettura del carattere */
                        scanf(" %c%*[^\n]", &vuoiCallbackfn);
                        if (vuoiCallbackfn != 'y' && vuoiCallbackfn != 'n')
                            printf("ERRORE: devi immettere o y (per yes) oppure n (per no)! \n");
                        else {
                            if (vuoiCallbackfn == 'y') {
                                /* per aggiungere una reale implementazione di una funzione di callback, basterà sostituire
                                 * il parametro vuoiCallbackfn con il puntatore di una funzione reale, controllando
                                 * ovviamente che questo sia diverso da NULL.
                                 */
                                userInterface.subscribePlusCallback(secondaStringa, modulo, &funzioneDiCallback);

                                printf("INFO: il modulo %hd è stato correttamente sottoscritto alla proprietà %s unitamente alla funzione di callback passata!! \n",
                                        modulo, secondaStringa);
                            } else {
                                userInterface.subscribe(secondaStringa, modulo);
                                printf("INFO: il modulo %d è stato correttamente sottoscritto alla proprietà %s! (senza funzione di callback) \n",
                                        modulo, secondaStringa);
                            }
                        }
                    }
                } else {
                    printf("%s \n", msgProprietaInesistente);
                    scanf("%*[^\n]");
                }
            }
            if (strcmp(primaStringa, "check") == 0) {
                scanf("%s%*[^\n]", secondaStringa);

                if ((modulo = controllaModulo(secondaStringa)) != -1) {

                    if (!userInterface.verificaSottoscrizioni(modulo))
                        printf("INFO: il modulo %d non è sottoscritto a nessuna proprieta; utilizzare il comando subscribe per aggiungere"
                            " una sottoscrizione. \n", modulo);
                    else {
                        printf("INFO: Elenco delle proprieta a cui il modulo %d è sottoscritto : \n", modulo);
                        risultatoCheck = userInterface.check(modulo);
                        for (i = 0; i < risultatoCheck.size(); i++) {
                            printf("%s = %f \n", risultatoCheck[i].proprieta.c_str(), risultatoCheck[i].valore);
                        }
                    }
                }
            }
            if (strcmp(primaStringa, "store") == 0) {
                scanf("%s%*[^\n]", secondaStringa);
                if (!controllaDimensioneProprieta(secondaStringa)) {
                    userInterface.storeParam(secondaStringa);
                    printf("INFO: Proprieta' aggiunta correttamente.\n");
                }
            }
            if (strcmp(primaStringa, "delete") == 0) {
                scanf("%s%*[^\n]", secondaStringa);
                if (userInterface.esisteProprieta(secondaStringa)) {
                    userInterface.deleteParam(secondaStringa);
                    printf("INFO: Proprieta' eliminata con successo.\n");
                } else {
                    printf("%s \n", msgProprietaInesistente);
                    scanf("%*[^\n]");
                }
            }

        }
    }
}

/* CODICE ASCII :
 * 0 = 48       1 = 49      ...         9 = 57
 * a = 97       b = 98          ...     z = 122
 * A = 65       B = 66          ...     Z = 90
 */
