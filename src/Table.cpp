//Tommaso Boscardin
#include "../include/Table.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void Table::initTable(){//funzione membro che inizializza il tabellone riempiendolo di caselle, seguendo le regole del gioco

    srand(time(NULL));
    sq[0]=Land(0,'A','P');  //prima casella e' la partenza

    sq[7]=Land(7,'A');      //casella angolare vuota

    sq[14]=Land(14,'A');    //casella angolare vuota

    sq[21]=Land(21,'A');    //casella angolare vuota

    //contatori che contano il numero di caselle da creare per tipo
    int economy=8;
    int standard=10;
    int luxury=6;
    for(int i=1; i<28; i++){
        if(i==7 || i==14 || i==21) continue;// salta le caselle angolari che sono gia' state create

        switch(std::rand()%3){//scelgo a caso
        case 0:{//economy
            if(economy>0){//se ci sono caselle economiche da creare
                sq[i]=Land(i,'L','E');
                economy--;//decremento il contatore
            }else{
                i--;//altrimenti decremento il contatore del ciclo for per riprovare
            }
            break;}
        case 1:{//standard

            if(standard>0){//se ci sono caselle standard da creare
                sq[i]=Land(i,'L','S');
                standard--;//decremento il contatore
            }else{
                i--;//altrimenti decremento il contatore del ciclo for per riprovare
            }
            break;}
        case 2:{//luxury

            if(luxury>0){//se ci sono caselle lusso da creare
                sq[i]=Land(i,'L','L');
                luxury--;//decremento il contatore
            }else{
                i--;//altrimenti decremento il contatore del ciclo for per riprovare
            }
            break;
        }
        }
    }
}

Table::Table(){//iniziaizzo la tabella senza i gicatori
    initTable();
}

Table::Table(Player* p1, Player* p2, Player* p3, Player* p4){//iniziaizzo la tabella con i 4 giocatori i gicatori
    p[0]=p1;
    p[1]=p2;
    p[2]=p3;
    p[3]=p4;
    initTable();
}

void Table::addPlayer(Player* pl){//funzione membro che aggiunge i giocatori
    if(p[0]==nullptr){//se non c'e' un giocatore assegnato lo assegno
        p[0]=pl;
    }else if(p[1]==nullptr){
        p[1]=pl;
    }else if(p[2]==nullptr){
        p[2]=pl;
    }else if(p[3]==nullptr){
        p[3]=pl;
    }else{//se tutti e 4 i giocatori sono stati aggiunti lancio eccezione
        throw MaxNumberPlayer("Numero massimo: 4");
    }
}

Land& Table::getLand(int pos){//funzione membro che restituisce una casella sapendo la posizione nel tabellone
    if(pos>=0 && pos<28){//controlla che la posizione sia valida
        return sq[pos];
    }
    throw InvalidPosition("Posizione non valida");
}

//funzione membro che permette di disegnare una casella rappresentando la categoria della casella, il tipo di costruzione e i giocatori sopra ad essa.
//aiuta printTable a disegnare il tabellone
void Table::drawCell(char t,int j) const{ // il carattere rappresenta il tipo, il numero l'indice
    constexpr int MAX_CELL=8; // |E^1234| e' da dimensione massima che puo' avere una casella
    int tot=0;// conta quanti caratteri devono starci dentro la casella
    if(t==' '){// se il tipo e' vuoto allora non e' una casella ma uno spazio interno al tabellone
        for(int k=0;k<MAX_CELL+1;k++)//nelle caselle all'interno del tabellone non c'e' nulla quindi stampo spazi
            std::cout<<" ";
        return;
    }
    if(t!='A'){// se non e' angolare
        tot=1;// perche' c'e' anche il tipo
    }
    for(int k=0;k<4;k++){// conto i giocatori su quella casella
        if(p[k]!=nullptr){
            if(p[k]->getPosition()==j){
                tot++;//incremento di uno per ogni giocatore che trovo sulla casella
            }
        }
    }

    if(sq[j].hasHouse()||sq[j].hasHotel()){// conto se c'e' una costruzione
        tot++;
    }
    int space=MAX_CELL-tot-2;   //lo spazio totale che mi rimane all'interno della casella
    int l_space=space/2;        //spazio che sta a sinistra
    int r_space=space-l_space;  //spazio che sta a destra
    std::cout<<"|";
    for(int g=0;g<l_space;g++){// stampa spazi iniziali (sinistra)
        std::cout<<" ";
    }

    if(t!='A'){// stampa il tipo
        std::cout<<t;
    }

    if(sq[j].hasHouse()){//stampo il tipo di costruzione se c'e'
        std::cout<<"*";
    }else if(sq[j].hasHotel()){
        std::cout<<"^";
    }
    for(int k=0;k<4;k++){// stampo i giocatori su quella casella
        if(p[k]!=nullptr){
            if(p[k]->getPosition()==j){
                std::cout<<k+1;
            }
        }
    }

    for(int g=0;g<r_space;g++){// stampo gli spazi finali (destra)
        std::cout<<" ";
    }
    std::cout<<"|";

}
void Table::printTable() const{//funzione membro che disegna il tabellone con tutte le caselle
    std::cout<<std::endl;
    char row='A';//carattere di riga
    std::cout<<"     1        2        3        4        5        6        7        8\n";
    std::cout<<row<<" ";
    row++;//incremento la riga
    for(int i=0;i<8;i++){//se una riga e'
        if(i==0){//prima riga
            for(int j=0;j<=7;j++){//scorro la prima riga
                if(sq[j].getType()=='A'){ //se angolare
                    if(sq[j].getCategory()=='P'){ // se partenza
                        drawCell('P', j); //stampa la cella partenza
                    }
                    else{
                        drawCell('A',j); // altrimenti e' semplicemente l'angolo in alto a destra
                    }
                }
                else{
                    drawCell(sq[j].getCategory(),j); //altrimenti stampa quelle centrali
                }
                std::cout<<" ";
            }
            std::cout<<std::endl;
        }
        else if(i==7){//lato inferiore del tabellone
            std::cout<<row<<" ";
            for(int j=21;j>=14;j--){//scorro l'array da 21 a14
                if(sq[j].getType()=='A'){ //se angolare
                    drawCell('A',j);
                }
                else{
                    drawCell(sq[j].getCategory(),j); //altrimenti stampa quelle centrali
                }
                std::cout<<" ";
            }
            std::cout<<std::endl;
            continue;//passo alla riga successiva
        }
        else{//lato sinistro e destro
            std::cout<<row<<" ";
            row++;//incremento la riga
            drawCell(sq[28-i].getCategory(), 28-i);//casella di sinistra
            std::cout<<" ";
            for(int k=0;k<6;k++){//spazi vuoti in mezzo al tabellone
                drawCell(' ',0);
            }
            drawCell(sq[i+7].getCategory(),i+7);//casella di destra
            std::cout<<std::endl;
            continue;//passo alla riga successiva
        }
    }
    std::cout<<std::endl;
}
//funzione membro che associa un nome (label) ad una casella secondo la sua posizione nel tabellone
std::string Table::getLabel(int i) const{// i e' la posizione nell'array
    char lett='A';
    int pos_x;
    char pos_y;
    if(i<8){// lato superiore
        pos_x=i+1;
        pos_y=lett;
    }else if(i<=14 && i>=8){// lato destro
        pos_x=8;
        pos_y=lett+(i%8)+1;
    }else if(i<=21 && i>14){//lato inferiore
        pos_x=7-(i%15);
        pos_y='H';
    }else{//lato sinistro
        pos_x=1;
        pos_y=lett+7-(i%21);
    }
    std::string label=pos_y+std::to_string(pos_x);
    return label;
}

void Table::printOwners()const{//funzione membro che scrive le proprieta' possedute da ogni giocatore
    std::cout<<"\nProprieta' dei giocatori: \n\n";
    for(int i=0;i<4;i++){//per ogni giocatore
        if(p[i]!=nullptr){
            std::cout<<"Giocatore "<<i+1<<": ";
            int counter=0;
            for(int k=0;k<p[i]->getLands().size();k++){//utilizzo il vettore contenuto in Player per sapere quali sono i suoi terreni
                    if(counter!=0){//scrivo la virgola tranne prima del primo
                        std::cout<<", ";
                    }
                    counter++;
                std::cout<<getLabel(p[i]->getLands().at(k)->getId());//stampo utilizzando getLabel
            }
            std::cout<<std::endl;
        }

    }
}

void Table::printBudgets() const{//funzione membro che scrive il budget rimanente di ogni giocatore
    std::cout<<"\nBudget rimanente:\n\n";
    for(int i=0; i<4; i++){//per ogni giocatore
        if(p[i]!=nullptr){
            std::cout<<"Giocatore "<<i+1<<": "<<p[i]->getBudget()<<std::endl;//chiedo a Player il suo budget e scrivo
        }
    }
}

void Table::show() const{//funzione membro che chiama printTable, printOwners e printBudgets quando viene invocato il comando show
    printTable();
    printOwners();
    printBudgets();

}
void Table::removePlayer(Player* pl){//funzione membro che rimuove un giocatore quando viene liminato
    for(int i=0;i<4;i++){//cerco il giocatore da eliminare
        if(p[i]!=nullptr){
            if(pl->getId()==p[i]->getId()){
                p[i]=nullptr;//lo elimino mettendo il puntatore a nullptr
            }
        }

    }
}
