//Luca Fantin
#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"
#include<iostream>




class Human : public Player {
    public:

        //Costruttore che inizializza il numero id e usa come budget 100 fiorini
        Human(int id) : Player(id){}

        // Costruttore che inizializza il numero id e il budget
        Human(int id, int fiorini) : Player(id, fiorini){}

        // Funzione che restituisce il numero dato dal lancio del dado
        int rollDice() const override;

        // Funzione virtuale pura che restitusce 1 se il giocatore decide di comprare una proprietà, 0 altrimenti, 2 se il giocatore vuole visualizzare
        int buyLand(Land* t) const override;

        // Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire una casa, 0 altrimenti, 2 se il giocatore vuole visualizzare
        int buildHouse(Land* t) const override;

        // Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire un albergo, 0 altrimenti, 2 se il giocatore vuole visualizzare
        int buildHotel(Land* t) const override;

};


#endif //HUMAN_H