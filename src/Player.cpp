//Luca Fantin
#include <iostream>
#include "../include/Player.h"
#include <ctime>



// Costruttore che inizializza il numero id e usa come budget 100 fiorini
Player::Player(int id) {
    srand(time(NULL)); // Permette di avere numeri casuali ad ogni esecuzione
    this->id = id;
    this->budget = 100;
    this->position = 0; // Il giocatore parte dal via
}

// Costruttore che inizializza il numero id e il budget
Player::Player(int id, int fiorini) {
    srand(time(NULL)); // Permette di avere numeri casuali ad ogni esecuzione
    this->id = id;
    this->budget = fiorini;
    this->position = 0; // Il giocatore parte dal via
}

// Funzione che muove il giocatore di un certo numero di caselle
std::string Player::move(int n) {
    this->position = (this->position + n) % 28; // Aggiorna il campo position sommando n e facendo il modulo 28 (può passare dal via)
    if (this->position < n) { // Se il giocatore è passato dal via
        this->passGo(); // Chiama la funzione passGo
        return "Giocatore " + std::to_string(this->id+1) + " e' passato dal via e ha ricevuto 20 fiorini\n";
    }
    return "";

}

// Funzione che aggiunge la proprieta' alla lista di quelle possedute
void Player::addLand(Land* t) {
    this->properties.push_back(t); // Aggiunge il puntatore t al vettore properties
    t->setOwner(this->id); // Imposta il giocatore come proprietario del terreno
}

// Funzione che rimuove una proprieta' dalla lista di quelle possedute dal giocatore
void Player::removeLand(Land* t) {
    for (int i = 0; i < this->properties.size(); i++) { // Scorre il vettore properties
        if (this->properties[i] == t) { // Se trova il puntatore t
            this->properties.erase(this->properties.begin() + i); // Rimuove il puntatore dal vettore
            t->setOwner(-1); // Imposta il proprietario del terreno a null
            break;
        }
    }
}

// Funzione che paga un certo numero di fiorini ad un altro giocatore, se li possiede
void Player::pay(Player* g, int amount) {
    if(amount <= this->budget) { // Se il giocatore ha ancora soldi
        this->budget -= amount; // Sottrae amount al campo budget
        g->budget += amount; // Aggiunge amount al campo budget dell'altro giocatore
        }
    else{
        g->budget += this->budget;
        this->budget = 0;

    }
}

// Funzione che paga un certo numero di fiorini alla banca
void Player::pay(int amount) {
    if(amount <= this->budget) { // Se il giocatore ha ancora soldi
        this->budget -= amount; // Sottrae amount al campo budget
    }
    else{
        this->budget = 0;
    }
}

// Funzione che incrementa il budget di 20 fiorini: il giocatore e' passato dal via
void Player::passGo() {
    this->budget = this->budget+20; // Aggiunge 20 al campo budget
}

// Funzione che restituisce un vettore che contiene la lista delle proprieta' possedute dal giocatore
std::vector<Land*>& Player::getLands() {
    return this->properties; // Restituisce il campo properties
}

// Funzione che restituisce vero se il giocatore e' eliminato, falso altrimenti
bool Player::isEliminated() {
    return this->budget == 0; // Restituisce vero se il campo budget è minore o uguale a zero, falso altrimenti
}
