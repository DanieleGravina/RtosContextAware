/*
 * File:   Proprieta.cpp
 * Author: Liscio-Cazzetta
 *
 * la classe Proprieta gestisce le proprietà memorizzate nella board
 * permettendo, tramite terminale, una facile localizzazione
 * e quindi, utilizzando la classe Comando.cpp, una facile gestione
 * per eventuali read, update eccetera.
 */
 
#ifndef PROPRIETA_H
#define PROPRIETA_H
 
#include <cstdio>
#include "miosix.h"
#include <unistd.h>
#include <cstring>
#include <map>
#include <string>
 
class Proprieta {
public:
         
    /* costanti del progetto su cui si basa tutto il codice */
    const static unsigned short numModuli = 8;
    const static unsigned short maxDimProprieta = 30;
     
    /* char * : tipo della chiave primaria(stringa);
     * double: il tipo del valore assegnato alle proprieta;
     * str_cmp: comparatore che ordina gli elementi della mappa.
     */
    typedef std::map<std::string, double> Map;
    
    /* la mapProprieta contiene tutte le proprieta disponibili all'assegnazione di valori
     * ed il loro relativo valore.
     */
    Map mapProprieta;
        
    /* definisce il tipo della callback function che sarà usata dai moduli quando
     * verranno aggiornate delle proprietà ai quali si sono sottoscritti, ovviamente
     * solo se in fase di sottoscrizione hanno passato anche il parametro che definisce
     * la callback function
     */
    typedef void (*CallbackFn)(void);
    
    /* tabella che ha per righe le proprieta e per colonne i moduli;
     * viene usata per la proprieta subscribe; ad esempio se il modulo 1 che corrisponde
     * al pedometer sceglie di sottoscriversi alla proprieta "passi", allora nella
     * casella corrispondente si trova il char t che sta per true, altrimenti di default
     * sono tutte a f cioè false.
     */
    typedef std::map<std::string, std::map<short, char> > MapProprietaModuli;

    MapProprietaModuli tabSottoscrizioni;
    
    /* tabella che ha per righe le proprieta e per colonne i moduli;
     * viene usata per la proprieta subscribe; ad esempio se il modulo 1 che corrisponde
     * al pedometer sceglie di sottoscriversi alla proprieta "passi", allora nella
     * casella corrispondente si trova la callback function passata come parametro, altrimenti di default
     * sono tutte a NULL.
     */
    typedef std::map<std::string, std::map<short, CallbackFn> > MapProprietaModuliCallbackfn;

    MapProprietaModuliCallbackfn tabSottoscrizioniConCallback;

    /* questa struct è utilizzata per il ritorno dei risultati del comando check, il quale
     * restituisce un puntatore ad un oggetto contenente i nomi delle proprieta ed i
     * rispettivi valori.
     */
    struct CheckResult{
        std::string proprieta;
        double valore;
    };
    
    /* il costruttore inizializza la lista delle proprieta effettivamente
     * utlizzate dalla board e dagli utenti e la tabella delle sottoscrizioni.
     */
    Proprieta();
     
    /*restituisce true se il nome del parametro equivale ad un nome di proprieta
     * memorizzato nella Map
     */
    bool esisteProprieta(std::string stringa);
     
    /* restituisce il valore della proprietà corrispondente al parametro passato
     */
    double getValoreProprieta(std::string nome);
     
    /*aggiorna il valore della proprietà richiesta e ritorna true in caso di corretto
     * update, altrimenti false
     */
    std::vector<CallbackFn> updateProprieta(std::string nome, double valore);
     
    /* sottoscrive il modulo alla proprieta richiesta, definendo anche
     * la callbackFunction associata.
     * Se un modulo non è sottoscritto ad una proprietà, il valore di default è NULL.
     */
    void subscribeModuloConCallback(std::string nome, short modulo, CallbackFn funzioneDiCallback);
    
    /* sottoscrive il modulo alla proprieta richiesta; tramite funzione di check quindi
     * potrà controllare l'elenco delle proprietà a cui è iscritto ed il loro relativo valore.
     * Se un modulo non è sottoscritto ad una proprietà, il valore di default è 0.
     */
    void subscribeModulo(std::string nomeProprieta, short numeroModulo);
     
    /* controlla se il modulo è sottoscritto a qualche proprieta; se sì, ritorna true
     * altrimenti false.
     */
    bool verificaSottoscrizioniModulo(short modulo);
     
    /* questa funzione controlla tutte le sottoscrizioni del modulo passato come
     * parametro, ritornando il nome delle proprieta a cui è sottoscritto con i relativi valori
     * associati; ritorna quindi un puntatore ad un array di struct.
     */
    std::vector<CheckResult> checkModulo(short modulo);
    
    /* la funzione permette all'utente o ai moduli di definire una proprietà nuova
     * e di salvarla in memoria, la quale proprietà sarà poi accessibile esattamente
     * come le altre proprietà già presenti sfruttando i comandi esistenti.
     */
    void storeParameter (std::string nomeProprieta);
    
    void deleteParameter (std::string nomeProprieta);
private:
 
};
 
#endif  /* PROPRIETA_H */


