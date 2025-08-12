//Tommaso Boscardin
#include "../include/Land.h"


Land::Land(int id, char t){
    setType(t);
    this->id=id;
}
Land::Land(int id, char t, char c){
    setType(t);
    setCategory(c);
    this->id=id;
}

void Land::setType(char t){// funzione membro che imposta il tipo di una casella "A" angolare, "L" laterale
    if(t=='A' || t=='L'){
        type=t;
    }else{
        throw InvalidType("Il tipo non è valido.");
    }
}
void Land::setCategory(char c){// funzione membro che imposta la categoria di una casella

    if(type=='L'){//se e' di tipo L le categorie possibili sono standard, economy e lusso
        if(c=='S' || c=='E' || c=='L'){
            category=c;
        }else{
            throw InvalidCategory("Categoria non valida");
        }

    }
    else if(type=='A'){//se e' di tipo A le categorie possibili sono " " per angolo vuoto, o "P" per la partenza
        if(c=='P' || c==' '){
            category=c;
        }else{
            throw InvalidCategory("Categoria non valida");
        }
    }else{
        throw InvalidType(" Categoria non valido. ");
    }
}
int Land::landCost()const{//funzione membro che restituisce il prezzo di una casella in base alla categoria
    if(category=='E')
        return ECONOMY_LAND_COST;
    if(category=='S')
        return STANDARD_LAND_COST;
    if(category=='L')
        return LUXURY_LAND_COST;
    return -1;// se Land ha categoty Angular non e' in vendita
}
void Land::upgradeBuildingType(){//funzione membro che aumenta il tipo di costruzione presente nella casella.
    if(building<2){
        building++;             //se vuota 0, con casa 1 e con albergo 2
    }
}
int Land::upgradeCost()const{//funzione membro che restituisce il costo per effettuare un miglioramento della casella in base alla categoria e alla costruzione già presente
    switch(building){
    case 0:
        if(type=='E')
            return ECONOMY_HOUSE_COST;
        if(type=='S')
            return STANDARD_HOUSE_COST;
        if(type=='L')
            return LUXURY_HOUSE_COST;
    case 1:
        if(type=='E')
            return ECONOMY_HOTEL_COST;
        if(type=='S')
            return STANDARD_HOTEL_COST;
        if(type=='L')
            return LUXURY_HOTEL_COST;
    case 2:
        throw NoUpgradeAvailable("Nessun Upgrade disponibile");
    }
}
int Land::fee()const{//funzione membro che restituisce il prezzo da pagare per un giocatore che pernotta in una casella di un altro giocatore
    switch(building){
    case 0:
        return 0;
    case 1:
        if(type=='E')
            return ECONOMY_HOUSE_FEE;
        if(type=='S')
            return STANDARD_HOUSE_FEE;
        if(type=='L')
            return LUXURY_HOUSE_FEE;
    case 2:
        if(type=='E')
            return ECONOMY_HOTEL_FEE;
        if(type=='S')
            return STANDARD_HOTEL_FEE;
        if(type=='L')
            return LUXURY_HOTEL_FEE;
    }
}
void Land::reset(){//funzione membro che rende disponibile il terreno di un giocatore quando viene eliminato
    building=0;//il terreno torna vuoto
    owner=-1;//il proprietario non e' nessuno
}
