/*
 * File:   UserInterface.cpp
 * Author: Liscio-Cazzetta
 *
 * la classe UserInterface.cpp gestisce i comandi presenti nel vector comandi, quindi
 * in base all'input dell'utente restituisce un valore di una proprieta passata
 * per input oppure valori booleani per il controllo di correttezza di input
 */
 
#ifndef USERINTERFACE_H
#define USERINTERFACE_H
 
#include <cstdio>
#include "miosix.h"
#include <unistd.h>
#include <cstring>
#include <map>
#include "Proprieta.h"
#include <string>
 
using namespace std;
 
class UserInterface
{
public:
        /* costanti del progetto su cui si basa tutto il codice */
        const static short numComandi = 7;
        const static short maxDimComando = 10;
        
        struct tipo_Comandi {
            std::string comando;
        };
        tipo_Comandi comandi[numComandi];
         
        /* inizializza la lista dei comandi
         */
    UserInterface();
 
        /* data una stringa, verifica che questa corrisponda a qualche comando
         * presente nella lista dei comandi; se si, ritorna true, altrimenti false
         */
        bool esisteComando(std::string stringa);
        
        /* stampa a terminale la sintassi dei comandi disponibili.
         */
        void help();
         
        double read(std::string nomeProprieta);
         
        std::vector<Proprieta::CallbackFn> update(std::string nomeProprieta, int valore);
         
        /* un modulo può iscriversi ad una certa proprieta per ricevere una notifica
         * ogni qualvolta tale proprieta si aggiorna tramite richiamo della funzione di
         * callback passata come parametro.
         */
        void subscribePlusCallback(std::string nomeProprieta, short numeroModulo, Proprieta::CallbackFn funzioneDiCallback);
        
        /* un modulo puo iscriversi ad una certa proprieta per controllare, tramite
         * comando check, i valori delle proprieta a cui si è sottoscritto in ottica
         * di futuri cambiamenti delle proprieta.
         */
        void subscribe(std::string nomeProprieta, short numeroModulo);
         
        /* questa funzione controlla che il modulo sia effettivamente sottoscritto
         * a qualche proprieta
         */
        bool verificaSottoscrizioni(short numeroModulo);
         
        /* questo metodo restituisce un vettore di struct di tipo CheckResult con 
         * le proprieta a cui si è sottoscritto il modulo ed i relativi valori.
         */
        std::vector<Proprieta::CheckResult> check(short numeroModulo);
         
        /*funzione che inserisce una nuova proprieta nella map delle proprieta presenti
         * assegnandogli come nome il parametro passato.
         */
        void storeParam(std::string nomeProprieta);
        
        void deleteParam(std::string nomeProprieta);
        
        /*funzione che controlla se la proprietà inserita esiste*/
        bool esisteProprieta(std::string stringa);
};
 
#endif //USERINTERFACE_H

