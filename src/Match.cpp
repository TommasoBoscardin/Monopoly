//Filippo Celant
#include "../include/Match.h"
#include "../include/Computer.h"
#include "../include/Human.h"

#include <algorithm>



Match::Match(int t, int max_t){
    if(t==0){//computers
        players[0]=new Computer(0);
        players[1]=new Computer(1);
        players[2]=new Computer(2);
        players[3]=new Computer(3);
    }else if(t==1){// 1 Human
        players[0]=new Human(0);
        players[1]=new Computer(1);
        players[2]=new Computer(2);
        players[3]=new Computer(3);
    }
    max_turns=max_t;
    table=new Table(players[0],players[1],players[2],players[3]);
}

//metodo che inizializza il file di log testuale
void Match::setLogFile(const std::string& fileName){
    file_log.open(fileName);
    if (!file_log.is_open()) {
        std::cerr << "Errore nell'apertura del file di log testuale: " << fileName << std::endl;
    }
}

//metodo che fa iniziare la partita
void Match::startMatch(){
    struct id_dice{
        int id;
        int n;
    };
    id_dice start_dice[4];
    for(int i=0;i<4;i++){// tutti i giocatori lanciano i dadi
        id_dice k;
        k.id=players[i]->getId();
        k.n=players[i]->rollDice();
        bool new_roll=false;
        for(int j=0;j<i;j++){// controlla che non ci siano duplicati
            if(k.n==start_dice[j].n){
                new_roll=true;
                i--;
                break;
            }
        }
        if(new_roll){
            continue;
        }
        start_dice[i]=k;
    }
    std::sort(start_dice,start_dice+4,[](const id_dice& n1,const id_dice& n2){return n1.n>n2.n;});//ordina id_dice in ordine crescente
    for(int i=0;i<4;i++){
        turn_order[i]=start_dice[i].id;
    }
    std::cout<<"Ordine di gioco: ";
    for(int i=0;i<4;i++){
        std::cout<<turn_order[i]+1<<" ";
    }
    std::cout<<std::endl;
}

//metodo che esegue il turno di un giocatore
void Match::playTurn(){
    std::cout<<"Turno: "<<turn+1<<std::endl;
    std::string msg="";
    while(turn_order[current_turn]==-1){// l'id è -1 quando un giocatore viene eliminato
        current_turn=(current_turn+1)%4;//avanzo l'indice del turno
    }
    Player* p=players[turn_order[current_turn]];//identifico il giocatore che deve tirare i dadi in base al suo id memorizzato in turn_order
    int n;
    do{
        n=p->rollDice();//lancio i dadi
        if (n==1) table->show();
    } while(n==1);//se viene chiamato il comando show devo richiedere se lanciare i dadi
    msg="Giocatore "+ std::to_string(p->getId()+1) + " ha tirato i dadi ottenendo un valore di " + std::to_string(n) +"\n";
    eventLog(msg);

    std::string s = p->move(n); //se passa dal via stampo (vedi Player.cpp)
    if(s!=""){
        msg = s;
        eventLog(msg);
    }
    msg="Giocatore "+ std::to_string(p->getId()+1)+" e' arrivato alla casella "+ table->getLabel(p->getPosition())+"\n";
    eventLog(msg);

    Land& l=table->getLand(p->getPosition());// Land in cui si trova player dopo aver tirato i dadi
    if(l.getType()=='A'){// se di tipo angolare
        //non succede nulla
    }else{// è di tipo laterale
        int ans=2;
        if(l.getOwner()==-1 && p->getBudget()>l.landCost()){// se non è di nessuno e il giocatore ha i soldi chiedo se comprare
            do {//chiedi fino a quando l'utente non smette di chiedere lo show
                ans = p->buyLand(&l);
                if(ans==2) table->show();
            }while(ans==2);
            if (ans==1){//se accetta di comprare una proprieta
                p->pay(l.landCost());
                p->addLand(&l);
                l.setOwner(p->getId());
                msg="Giocatore "+std::to_string(p->getId()+1)+" ha acquistato il terreno "+table->getLabel(p->getPosition())+"\n";
                eventLog(msg);
            }

        }else if(l.getOwner()==p->getId()){// se il proprietario è il giocatore stesso
            int build_t=l.getBuildingType();
            switch(build_t){
            case 0:// terreno vuoto
                if(p->getBudget()>l.upgradeCost()){// se ha abbastanza soldi
                    do {//chiedi fino a quando l'utente non smette di chiedere lo show
                        ans = p->buildHouse(&l);
                        if(ans==2) table->show();
                    }while(ans==2);
                    if(ans==1){//se vuole costruire una casa
                        p->pay(l.upgradeCost());
                        l.upgradeBuildingType();
                        msg="Giocatore "+std::to_string(p->getId()+1)+" ha costruito una casa sul terreno "+table->getLabel(p->getPosition())+"\n";
                        eventLog(msg);
                    }
                }
                break;
            case 1:// terreno ha già la casa
                if(p->getBudget()>l.upgradeCost()){// se ha abbastanza soldi
                    do {//chiedi fino a quando l'utente non smette di chiedere lo show
                        ans = p->buildHotel(&l);
                        if(ans==2) table->show();
                    }while(ans==2);
                    if(ans==1){//se vuole costruire un albergo
                        p->pay(l.upgradeCost());
                        l.upgradeBuildingType();
                        msg="Giocatore "+std::to_string(p->getId()+1)+" ha migliorato una casa in un albergo sul terreno "+table->getLabel(p->getPosition())+"\n";
                        eventLog(msg);
                    }
                }
                break;
            }
        }else if(l.getBuildingType()!=0){// è di un altro giocatore e il giocatore ha costruito una casa o albergo
            int f_pay=0;//numero effettivo di fiorini pagati
            if(p->getBudget()<l.fee()){// se non riesco a pagare interamente (è un controllo ridondante in quanto già presente in Player::pay() ma necessario per conoscere il valore di f_pay)
                f_pay=p->getBudget();
                p->pay(players[l.getOwner()],p->getBudget());//paga quello che puoi, poi verrà eliminato
            }else{// se ho i soldi necessari
                f_pay=l.fee();
                p->pay(players[l.getOwner()],l.fee());
            }
            msg="Giocatore "+std::to_string(p->getId()+1)+" ha pagato "+std::to_string(f_pay)+" fiorini a giocatore "+std::to_string(l.getOwner()+1)+" per pernottamento nella casella "+table->getLabel(p->getPosition())+"\n";
            eventLog(msg);
        }
    }
    current_turn=(current_turn+1)%4;//avanzo l'indice del turno
    turn++;
    msg="Giocatore "+std::to_string(p->getId()+1)+" ha finito il turno\n";
    eventLog(msg);
    eliminatePlayer();
    std::cout<<std::endl;
}

//metodo che elimina un giocatore
void Match::eliminatePlayer(){
    int eliminated_player = -1; //inizializzato a -1 per non trovare nessun giocatore
    for (int i=0; i<4; i++) {
        if(players[i] != nullptr && players[i]->isEliminated()) {
            eliminated_player = i;
            break; //il ciclo si interrompe quando un giocatore ha budget=0
        }
    }

    if (eliminated_player != -1) {
        int* turn_index=std::find(std::begin(turn_order),std::end(turn_order),eliminated_player);
        *turn_index=-1;//rimuovo il giocatore dalla lista dei turni
        std::vector<Land*> l=players[eliminated_player]->getLands();//devo rimuovere le case e gli alberghi dai terreni del giocatore eliminato
        for(int i=0;i<l.size();i++){
            l[i]->reset();// libero i terreni
        }
        std::string msg="";
        msg="Il giocatore " + std::to_string(players[eliminated_player]->getId()+1) + " e' stato eliminato\n";
        eventLog(msg); //stampa dell'evento sul log
        table->removePlayer(players[eliminated_player]);
        delete players[eliminated_player];
        players[eliminated_player]=nullptr;
    }

}

//metodo che controlla se la partita e' finita
bool Match::hasMatchEnded(){
    int alive_players = 0;
    int last_player = -1;

    for (int i = 0; i < 4; i++) {
        if (players[i] != nullptr) {
            alive_players++;
            last_player = i;
        }
    }

    if (alive_players == 1) { // Se c'è un solo giocatore rimasto, la partita finisce
        std::string msg="";
        msg="Giocatore " + std::to_string(players[last_player]->getId()+1) + " ha vinto la partita\n";
        eventLog(msg);
        return true;
    }

    if (turn >= max_turns) { // Se il numero massimo di turni è stato raggiunto, determina il vincitore in base al budget
        std::cout<<"La partita e' terminata perche' e' stato raggiunto il numero massimo di turni ("+std::to_string(max_turns)+")\n";
        int higher_budget = -1;
        std::string msg;
        std::vector<int> winning_players; // vettore che contiene i vincitori


        for (int i = 0; i < 4; i++) { // Trova il giocatore con il budget massimo
            if (players[i] != nullptr) {
                if(players[i]->getBudget() > higher_budget){// se il giocatore ha il badget più alto
                    higher_budget = players[i]->getBudget();//aggiorno il budget più alto
                    winning_players.erase(winning_players.begin(),winning_players.end());//allora svuoto il vettore dei giocatori
                    winning_players.push_back(players[i]->getId());//aggiungo al vettore dei vincitori
                }else if(players[i]->getBudget() == higher_budget){//se il budget è uguale
                    winning_players.push_back(players[i]->getId());//aggiungo al vettore dei vincitori
                }
            }
        }

        switch(winning_players.size()){
            case 1:
                msg = "Giocatore " + std::to_string(winning_players[0]+1) + " ha vinto la partita\n";
                eventLog(msg);
                return true;
            case 2:
                msg = "I giocatori " + std::to_string(winning_players[0]+1) + " e " + std::to_string(winning_players[1]+1) + " hanno vinto la partita ex aequo\n";
                eventLog(msg);
                return true;
            case 3:
                msg = "I giocatori " + std::to_string(winning_players[0]+1) + ", " + std::to_string(winning_players[1]+1) + "e " + std::to_string(winning_players[2]+1) + " hanno vinto la partita ex aequo\n";
                eventLog(msg);
                return true;
            case 4:
                msg = "la partita si e' conclusa con un pareggio tra tutti i giocatori\n";
                eventLog(msg);
                return true;
        }
    }

    // Se nessuna delle condizioni precedenti è verificata, la partita continua
    return false;
}

//metodo per registrare gli eventi nel file di log testuale
void Match::eventLog(const std::string& event) {
    if(file_log.is_open()) {
        std::cout << event;
        file_log << event << std::endl;
    } else {
        std::cerr << "File di log testuale non aperto correttamente";
    }
}

Match::~Match(){
    file_log.close();//chiudo il file di log
    delete table;
    for(int i=0;i<4;i++){
        if(players[i]!=nullptr){
            delete players[i];
            players[i]=nullptr;
        }

    }
}
