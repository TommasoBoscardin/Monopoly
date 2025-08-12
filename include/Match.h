//Filippo Celant
#ifndef MATCH_H
#define MATCH_H


#include "Table.h"

#include <iostream>
#include <string>
#include <fstream> //aggiunto per la gestione del file di log



class Match {
    private:
        Table* table; //tabellone del gioco
        Player* players[4]; //array che contiene i giocatori
        int turn=0; //turno corrente del gioco
        int max_turns; //numero massimo di turni in una partita
        int match_type; //tipo di partita 0 se 4 computer, 1 se 1 umano
        std::ofstream file_log; //file di log degli eventi del gioco
        int turn_order[4]; //contiene in ordine di turno gli id dei giocatori
        int current_turn=0;

    public:

        //costruttore che inizializza il gioco con il tipo di partita e il numero massimo di turni
        Match(int t, int max_t);

        //metodo che inizializza il file di log testuale
        void setLogFile(const std::string& fileName);

        //metodo che fa iniziare la partita
        void startMatch();

        //metodo che esegue il turno di un giocatore
        void playTurn();

        //metodo che elimina un giocatore
        void eliminatePlayer();

        //metodo che controlla se la partita è finita
        bool hasMatchEnded();

        //metodo per registrare gli eventi nel file di log testuale
        void eventLog(const std::string& event);

        //distruttore
        ~Match();

};


#endif //MATCH_H
