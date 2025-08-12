-Problema riscontrato:

Le partite non terminano mai poiché i fiorini che vongono aggiunti quando si
 passa per la casella di partenza (20) e la probabilità di acquisto di un 
 terreno/casa/albergo per i computer (25%) è troppo bassa.

Suggeriamo di modificare il bonus della casella di partenza da 20 a 5 fiorini
 e la probabilità dei Computer di acquisto a 50%; in questo modo abbiamo
 notato che le partite terminano in media prima di 500 turni.

-note sullo sviluppo:

1.Il progetto Monopoly è stato pensato come un unico programma e non come
 insieme di Librerie, questo ha permesso di semplificare il codice creando
 classi e funzioni membro strettamente necessarie al corretto funzionamento
 del programma e non è quindi utilizzabile come libreria.
2.Abbiamo deciso di non implementare i costruttori di copia poiché non vengono
 utilizzati ed in certe classi come Match l'implementazione di un tale
 construttore non sarebbe ragionevole perché Match, essendo una classe
 abbastanza complessa che contiene a sua volta altre classi, dovrebbe clonare
 anche i singoli giocatori, con tutti i loro dati membro. 
Questo ha portato a non implementare i costruttori di copia e di spostamento
 in Match (anche se utilizza l'allocazione dinamica della memoria).
3.Land non utilizza l'ereditarietà o polimorfismo, anche se apparentemente
 potrebbe sembrare utile utilizzarla, perché ci sembrava eccessivo creare due
 classi separate per gestire le caselle di tipo laterale ed angolare. Siccome
 entrambi i tipi di caselle devono possedere una categoria (standard, economy,
 lusso per le laterali, e vuota o partenza per angolari) tutte le varie
 tipologie si possono rappresenare mediante l'uso di solo due dati membro:
 type e category.
4.Le funzioni virtuali pure buyLand,buildHouse e buildHotel hanno tipo di
 ritorno int e non bool perché in ogni momento della partita il giocatore
 umano può decidere con il comando 'show' di visualizzare il tabellone, le
 proprietà ed il budget; questo viene gestito appunto tramite valori int
 (0=no, 1=sì, 2=show).


Autori: Boscardin Tommaso, Celant Filippo, Fantin Luca.

