//Luca Fantin

#include "../include/Computer.h"


// Funzione ausiliaria che esprime il 25% di probabilita'
int choice() {
    int n = rand() % 4; // Genera un numero casuale da 0 a 3
    if (n==3) {
        return 1;
    } else { // In qualsiasi altro caso (0, 1, 2) restituisce falso
        return 0;
    }
}

// Funzione che restituisce il numero dato dal lancio del dado
int Computer::rollDice() const {
    int n = rand() % 11 + 2; // Genera un numero casuale tra 2 e 12
    return n;
}

// Funzione virtuale pura che restitusce 1 se il giocatore decide di comprare una proprietà, 0 altrimenti, 2 se il giocatore vuole visualizzare
int Computer::buyLand(Land *t) const {
    return choice();
}

// Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire una casa, 0 altrimenti, 2 se il giocatore vuole visualizzare
int Computer::buildHouse(Land *t) const {
    return choice();
}

// Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire un albergo, 0 altrimenti, 2 se il giocatore vuole visualizzare
int Computer::buildHotel(Land *t) const {
    return choice();
}

