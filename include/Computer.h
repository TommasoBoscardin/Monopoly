//Luca Fantin
#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"
#include <time.h>



class Computer : public Player{
    public:

        //Costruttore che inizializza il numero id e usa come budget 100 fiorini
        Computer(int id) : Player(id){srand(time(NULL));}

        // Costruttore che inizializza il numero id e il budget
        Computer(int id, int fiorini) : Player(id, fiorini){srand(time(NULL));}

        // Funzione che restituisce il numero dato dal lancio del dado
        int rollDice() const override;

        // Funzione virtuale pura che restitusce 1 se il giocatore decide di comprare una proprietà, 0 altrimenti, 2 se il giocatore vuole visualizzare
        int buyLand(Land* t) const override;

        // Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire una casa, 0 altrimenti, 2 se il giocatore vuole visualizzare
        int buildHouse(Land* t) const override;

    // Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire un albergo, 0 altrimenti, 2 se il giocatore vuole visualizzare
        int buildHotel(Land* t) const override;

};


#endif //COMPUTER_H
