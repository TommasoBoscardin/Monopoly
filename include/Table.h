//Tommaso Boscardin
#ifndef TABLE_H
#define TABLE_H
#include "Land.h"
#include "Player.h"




class Table{
    Land sq[28];                        // array che memorizza le caselle
    Player* p[4]={nullptr,nullptr,nullptr,nullptr};
    void initTable();                   //riempie l'array sq in modo casuale seguendo le regole
    void drawCell(char, int) const;
    void printBudgets() const;          //visualizza il budget rimanente dei giocatori
    void printOwners()const;            //visualizza i proprietari di ogni proprietà
    void printTable()const;             //visualizza il tabellone
public:
    Table();
    Table(Player*, Player*, Player*, Player*);
    void addPlayer(Player*);            //aggiunge un giocatore al tabellone
    void removePlayer(Player*);         //rimuove i giocatori eliminati
    Land& getLand(int);                 //restituisce il terreno in una certa posizione
    std::string getLabel(int ) const;   //restituisce il nome del terreno
    void show() const;                  //stampa a video il tabellone, la lista dei budget e delle proprieta'

};
//eccezioni che possono essere lanciate da Table
class MaxNumberPlayer: public std::exception{
public:
    MaxNumberPlayer(const char* m) : message(m) {}
    const char* what() const noexcept override {
    return message.c_str();
    }
    private:
    std::string message;
};

class InvalidPosition: public std::exception{
public:
    InvalidPosition(const char* m) : message(m) {}
    const char* what() const noexcept override {
    return message.c_str();
    }
    private:
    std::string message;
};
#endif // TABLE_H
