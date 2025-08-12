//Luca Fantin
#include <iostream>
#include <cstring> // Per la funzione std::strcmp
#include "../include/Match.h"
#include "../include/Computer.h"
#include "../include/Human.h"


int main(int argc, char* argv[]){
    if(argc==2 && std::strcmp(argv[1], "human") == 0){

        std::cout << "Benvenuto. Questo e' Monopoly. Iniziamo." << std::endl;
        std::cout << "Per visualizzare il tabellone in qualsiasi momento, tranne ad inizio partita, scrivi 'show' quando tiri i dadi o quando ti viene fatta una richiesta"<<std::endl;

        std::cout <<"Quanti turni vuoi giocare al massimo? Giocati quei turni, la partita finisce e vince il giocatore con piu' fiorini" << std::endl;
        std::cout <<"Sono disponibili tre modalita' di gioco:" << std::endl;
        std::cout <<"A: 100 turni" << std::endl;
        std::cout <<"B: 250 turni" << std::endl;
        std::cout <<"C: 500 turni" << std::endl;
        std::cout << std::endl;
        std::string turn_mode;
        do{
            std::cout <<"Digita A/B/C per scegliere la modalita' di gioco:" << std::endl;
            std::cin >> turn_mode;
        } while(turn_mode != "A" && turn_mode != "a" && turn_mode != "B" && turn_mode != "b" && turn_mode != "C" && turn_mode != "c");
        int turns;
        if(turn_mode == "A" || turn_mode == "a") turns = 100;
        else if (turn_mode == "B" || turn_mode == "b") turns = 250;
        else turns = 500;
        std::cout << "Tu sei il giocatore 1, buona fortuna!" << std::endl;
        Match m(1, turns);
        m.setLogFile("log_human.txt");
        m.startMatch();
        while(!m.hasMatchEnded()){
            m.playTurn();
        }

    }
    else if(argc==2 && std::strcmp(argv[1], "computer") == 0){
        Match m(0, 500);
        m.setLogFile("log_computer.txt");
        m.startMatch();
        while(!m.hasMatchEnded()){
            m.playTurn();
        }
    }else{
        std::cout<<"Modalita' disponibili: human o computer";
    }
    return 0;
}
