//Luca Fantin
#ifndef PLAYER_H
#define PLAYER_H
#include "Land.h"

#include <iostream>
#include <vector>


class Player {
    protected:
        int id;
        int budget;
        int position; // posizione nel tabellone
        std::vector<Land*> properties; // lista delle proprietà possedute
        //Costruttore che inizializza il numero id e usa come budget 100 fiorini
        Player(int id);

        //Costruttore che inizializza il numero id e il budget
        Player(int id, int fiorini);
    public:



        // Funzione virtuale pura che restituisce il numero dato dal lancio del dado:
        //l'umano potra' infatti lanciarlo da input (vedi README)
        virtual int rollDice() const = 0;

        // Funzione virtuale pura che restitusce 1 se il giocatore decide di comprare una proprietà, 0 altrimenti, 2 se il giocatore vuole visualizzare
        virtual int buyLand(Land* t) const = 0;

        // Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire una casa, 0 altrimenti, 2 se il giocatore vuole visualizzare
        virtual int buildHouse(Land* t) const = 0;

        // Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire un albergo, 0 altrimenti, 2 se il giocatore vuole visualizzare
        virtual int buildHotel(Land* t) const = 0;

        // Funzione che muove il giocatore di un certo numero di caselle
        std::string move(int n);

        // Funzione che aggiunge la proprieta' alla lista di quelle possedute
        void addLand(Land* t);

        // Funzione che rimuove una proprieta' dalla lista di quelle possedute dal giocatore
        void removeLand(Land* t);

        // Funzione che paga un certo numero di fiorini ad un altro giocatore, se li possiede
        void pay(Player* g, int amount);

        // Funzione che paga un certo numero di fiorini alla banca
        void pay(int amount);

        // Funzione che incrementa il budget di 20 fiorini: il giocatore e' passato dal via
        void passGo();

        // Funzione che ritorna l'id del giocatore
        int getId() {return id;}

        // Funzione che restituisce il numero di fiorini a disposizione del giocatore
        int getBudget() {return budget;}

        // Funzione che restituisce la posizione del giocatore nel tabellone (da 0 a 23)
        int getPosition() {return position;}

        // Funzione che restituisce un vettore che contiene la lista delle proprieta' possedute dal giocatore
        std::vector<Land*>& getLands();

        // Funzione che restituisce vero se il giocatore e' eliminato, falso altrimenti
        bool isEliminated();

        // Disattivo costruttore di copia e operator= per evitare problemi di slicing
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
};

#endif //PLAYER_H
