/* 
 * File:   UserInterface.cpp
 * Author: Liscio-Cazzetta
 * 
 * la classe UserInterface.cpp gestisce i comandi presenti nel vector comandi, quindi
 * in base all'input dell'utente restituisce un valore di una proprieta passata
 * per input oppure valori booleani per il controllo di correttezza di input
 */

#include <cstdio>
#include "miosix.h"
#include <unistd.h>
#include <cstring>
#include <map>
#include "Proprieta.h"
#include "UserInterface.h"
#include <string>

using namespace std;

Proprieta proprieta;

UserInterface::UserInterface(){
    comandi[0].comando = "help";
    comandi[1].comando = "read";
    comandi[2].comando = "update";
    comandi[3].comando = "subscribe";
    comandi[4].comando = "check";
    comandi[5].comando = "store";
    comandi[6].comando = "delete";
    
}


bool UserInterface::esisteComando(std::string stringa){
    for(int i=0; i<numComandi; i++)
        if (comandi[i].comando.compare(stringa) == 0)
            return true;
    return false;
}

void UserInterface::help(){
        printf("########################################################################################## \n");
        printf("##                      elenco con sintassi dei comandi :                               ## \n");
        printf("##                                                                                      ## \n");
        printf("##                         help                                                         ## \n");
        printf("##                         read          proprieta                                      ## \n");
        printf("##                         update        proprieta     valore                           ## \n");
        printf("##                         subscribe     proprieta     modulo        callbackfn         ## \n");
        printf("##                         check         modulo                                         ## \n");
        printf("##                         store         proprieta                                      ## \n");
        printf("##                         delete        proprieta                                      ## \n");
        printf("##                                                                                      ## \n");
        printf("########################################################################################## \n");
}

double UserInterface::read(std::string nomeProprieta){
        return proprieta.getValoreProprieta(nomeProprieta);
}

std::vector<Proprieta::CallbackFn> UserInterface::update(std::string nomeProprieta, int valore){
    return proprieta.updateProprieta(nomeProprieta,valore);
}

void UserInterface::subscribe(std::string nomeProprieta, short numeroModulo){
    proprieta.subscribeModulo(nomeProprieta, numeroModulo);
}

void UserInterface::subscribePlusCallback(std::string nomeProprieta, short numeroModulo, Proprieta::CallbackFn funzioneDiCallback){
    proprieta.subscribeModuloConCallback(nomeProprieta, numeroModulo, funzioneDiCallback);
}

bool UserInterface::verificaSottoscrizioni(short numeroModulo){
    return proprieta.verificaSottoscrizioniModulo(numeroModulo);
}
std::vector<Proprieta::CheckResult> UserInterface::check(short numeroModulo){
        return proprieta.checkModulo(numeroModulo);
}
void UserInterface::storeParam (std::string nomeProprieta){
    proprieta.storeParameter(nomeProprieta);
}
void UserInterface::deleteParam (std::string nomeProprieta){
    proprieta.deleteParameter(nomeProprieta);
}
bool UserInterface::esisteProprieta(std::string stringa){
    return proprieta.esisteProprieta(stringa);
}

