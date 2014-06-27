/*
 * File:   Proprieta.cpp
 * Author: Liscio-Cazzetta
 *
 * la classe Proprieta gestisce le proprietà memorizzate nella board
 * permettendo, tramite terminale, una facile localizzazione
 * e quindi, utilizzando la classe Comando.cpp, una facile gestione
 * per eventuali read, update eccetera.
 */
 
#include <cstdio>
#include "miosix.h"
#include <unistd.h>
#include <cstring>
#include "Proprieta.h"
#include <map>
#include <string>
 
using namespace std;
using namespace miosix;
 
short i=0;
 
Proprieta::Proprieta() {
     
    /* inizializzo la map delle proprieta con i nomi delle proprieta ed i rispettivi
     * valori
     */
    mapProprieta.insert(Map::value_type("passi",1000));
    mapProprieta.insert(Map::value_type("peso",80));
    mapProprieta.insert(Map::value_type("eta",40));
    mapProprieta.insert(Map::value_type("frequenza",1));
    mapProprieta.insert(Map::value_type("altezza",190));
    
    /* inizializzo la tabella delle sottoscrizioni con le callback functions */
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioniConCallback["passi"][i] = NULL;
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioniConCallback["peso"][i] = NULL;
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioniConCallback["eta"][i] = NULL;
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioniConCallback["frequenza"][i] = NULL;
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioniConCallback["altezza"][i] = NULL;
    
    /* inizializzo la tabella delle sottoscrizioni */
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioni["passi"][i] = 'f';
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioni["peso"][i] = 'f';
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioni["eta"][i] = 'f';
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioni["frequenza"][i] = 'f';
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioni["altezza"][i] = 'f';
}

bool Proprieta::esisteProprieta(std::string stringa){
    if(mapProprieta.find(stringa)!=mapProprieta.end())
        return true;
    return false;
}

double Proprieta::getValoreProprieta(std::string nome) {
    return mapProprieta[nome];
}

std::vector<Proprieta::CallbackFn> Proprieta::updateProprieta(std::string nome, double valore){
    mapProprieta[nome]=valore;
    std::vector<CallbackFn> vectorfn;
    CallbackFn funzioneCallback;
    for (i=1; i<=numModuli; i++)
        if((funzioneCallback = tabSottoscrizioniConCallback[nome][i])!=NULL)
            vectorfn.push_back(funzioneCallback);
    return vectorfn;
}

void Proprieta::subscribeModuloConCallback(std::string nomeProprieta, short modulo, CallbackFn funzioneDiCallback){
     tabSottoscrizioniConCallback[nomeProprieta][modulo] = funzioneDiCallback;
}

void Proprieta::subscribeModulo(std::string nomeProprieta, short numeroModulo){
    tabSottoscrizioni[nomeProprieta][numeroModulo] = 't'; 
    MapProprietaModuli::iterator itEsterno;
}
    
bool Proprieta::verificaSottoscrizioniModulo(short modulo){
    for (Proprieta::MapProprietaModuli::iterator it = tabSottoscrizioni.begin(); it != tabSottoscrizioni.end(); it++){
        if ( it->second[modulo] != 'f' )
              return true;
    }
    return false;
}
 
std::vector<Proprieta::CheckResult> Proprieta::checkModulo(short modulo){   
    std::vector<CheckResult> checkVector;
    CheckResult check;
    MapProprietaModuli::iterator itEsterno;
    map<short, char>::iterator itInterno;
    for (itEsterno = tabSottoscrizioni.begin(); itEsterno != tabSottoscrizioni.end(); itEsterno++){
        for(itInterno = itEsterno->second.begin(); itInterno != itEsterno->second.end(); itInterno++){
            if ( itInterno->second == 't' && itInterno->first == modulo){
                    check.proprieta = itEsterno->first;
                    check.valore = mapProprieta[itEsterno->first];
                    checkVector.push_back(check);
                }
        }
    }
    return checkVector;
}

/* funziona */
void Proprieta::storeParameter (std::string nomeProprieta){
    mapProprieta.insert(Map::value_type(nomeProprieta,0));
    
    /* inizializzo la riga corrispondente alla nuova proprietà nella tabella delle sottoscrizioni senza callback functions*/
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioni[nomeProprieta][i] = 'f';

    /* inizializzo la riga corrispondente alla nuova proprietà nella tabella delle sottoscrizioni con callback functions*/
    for(i=1; i<=numModuli; i++)
        tabSottoscrizioniConCallback[nomeProprieta][i] = NULL; 
}
void Proprieta::deleteParameter (std::string nomeProprieta){
    mapProprieta.erase(nomeProprieta);
    /*elimino la proprietà anche dalle tabelle delle subscriptions*/
    tabSottoscrizioni.erase(nomeProprieta);
    tabSottoscrizioniConCallback.erase(nomeProprieta); 
}
