//Luca Fantin
#include "../include/Human.h"

// Funzione ausilaria (restituisce 0 se la risposta e' no, 1 se si, 2 se il giocatore vuole visualizzare)
int valueAnswer() {
    std::string answer;
    std::cin >> answer; // Legge la risposta
    while(answer != "s" && answer != "S" && answer != "n" && answer != "N" && answer != "show" && answer != "SHOW"){
        std::cout << "Non ho capito, riprova" << std::endl;
        std::cin >> answer;
    }
    if (answer == "n" || answer == "N") { //Accetta sia la N maiuscola sia quella minuscola
        return 0; 
    } else if (answer == "s" || answer == "S"){ 
        return 1; 
    } 
    else if(answer == "show" || answer == "SHOW") return 2;
}


// Funzione che restituisce il numero dato dal lancio del dado oppure 1 se l'utente vuole visualizzare il tabellone, la lista delle proprieta e la lista dei budget'
int Human::rollDice() const{
    int n; 
    std::cout << "Premi un tasto per lanciare i dadi" << std::endl; 
    std::string s;
    std::cin >> s; // Aspetta che l'utente prema un tasto
    if(s == "show" || s == "SHOW"){
        return 1;
    }
    n = rand() % 11 + 2; // Genera un numero casuale tra 2 e 12
    return n; 
}

// Funzione virtuale pura che restitusce 1 se il giocatore decide di comprare una proprietà, 0 altrimenti, 2 se il giocatore vuole visualizzare
int Human::buyLand(Land* t) const {
    std::cout << "Vuoi comprare il terreno al prezzo di " << t->landCost() << " fiorini? (s/n/show)" << std::endl; 
    return valueAnswer();
}

// Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire una casa, 0 altrimenti, 2 se il giocatore vuole visualizzare
int Human::buildHouse(Land* t) const {
    std::cout << "Vuoi costruire una casa sul terreno al costo di " << t->upgradeCost() << " fiorini? (s/n/show)" << std::endl; 
    return valueAnswer();
}

// Funzione virtuale pura che restitusce 1 se il giocatore decide di costruire un albergo, 0 altrimenti, 2 se il giocatore vuole visualizzare
int Human::buildHotel(Land* t) const {
    std::cout << "Vuoi costruire un albergo sul terreno al costo di " << t->upgradeCost() << " fiorini? (s/n/show)" << std::endl; 
    return valueAnswer();
}

