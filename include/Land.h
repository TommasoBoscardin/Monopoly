//Tommaso Boscardin
#ifndef LAND_H
#define LAND_H
#include <iostream>
#include <stdexcept>



class Land{
    static constexpr int ECONOMY_LAND_COST=6;
    static constexpr int STANDARD_LAND_COST=10;
    static constexpr int LUXURY_LAND_COST=20;
    static constexpr int ECONOMY_HOUSE_COST=3;
    static constexpr int STANDARD_HOUSE_COST=5;
    static constexpr int LUXURY_HOUSE_COST=10;
    static constexpr int ECONOMY_HOTEL_COST=3;
    static constexpr int STANDARD_HOTEL_COST=5;
    static constexpr int LUXURY_HOTEL_COST=10;
    static constexpr int ECONOMY_HOUSE_FEE=2;
    static constexpr int STANDARD_HOUSE_FEE=4;
    static constexpr int LUXURY_HOUSE_FEE=7;
    static constexpr int ECONOMY_HOTEL_FEE=4;
    static constexpr int STANDARD_HOTEL_FEE=8;
    static constexpr int LUXURY_HOTEL_FEE=14;
    char type=' ';          // A se angolare, L se laterale
    char category=' ';      // E se economy, S se standard, L se luxury, P se start
    int building=0;         // 0 se vuoto, 1 se casa, 2 se albergo
    int owner = -1;         //-1 se non e' di nessuno
    int id=0;
public:
    Land(){}					// costruttore di default, necessario per Table che utilizza un'array di Land
    Land(int, char);            // costruttore per inizializzare un Land con id e il tipo
    Land(int, char, char);      // costruttore per inizializzare un Land con id, il tipo e la categoria
    char getType()const{return type;}
    char getCategory()const{return category;}
    int getOwner()const{return owner;}
    int getBuildingType()const{return building;}
    int getId()const{return id;}
    void setType(char);
    void setCategory(char);
    void setOwner(int id){owner=id;}//permette di associare un terreno ad un giocatore (quando viene acquistato)
    int landCost()const;            // restituisce il prezzo del terreno; -1 se non in vendita
    void upgradeBuildingType();     // migliora da niente->a casa, o da casa-> ad albergo
    int upgradeCost()const;         //restituisce il prezzo se si vuole migliorare il terreno
    int fee()const;                 //restituisce il prezzo da pagare se un giocatore non proprietario soggiorna
    bool hasHouse()const{return building==1 ? true:false;}
    bool hasHotel()const{return building==2 ? true:false;}
    void reset();                   //funzione membro che viene chiamata quando un giocatore viene eliminato
};
//eccezioni che posso essere lanciate
class InvalidType: public std::exception{
    public:
        InvalidType(const char* m) : message(m) {}
        const char* what() const noexcept override {
            return message.c_str();
        }
        private:
        std::string message;
};

    class InvalidCategory: public std::exception{
    public:
        InvalidCategory(const char* m) : message(m) {}
        const char* what() const noexcept override {
        return message.c_str();
        }
        private:
        std::string message;
    };

    class NoUpgradeAvailable: public std::exception{
    public:
        NoUpgradeAvailable(const char* m) : message(m) {}
        const char* what() const noexcept override {
        return message.c_str();
        }
        private:
        std::string message;
    };

#endif // LAND_H
