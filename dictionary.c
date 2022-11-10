#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct NodoParola {
    char chiave;
    int occorrenzaCarattere;
    struct NodoParola *prossimo;
} NodoParola_t;
typedef NodoParola_t *List;

typedef struct Nodo {
    char *parola;
    struct Nodo *prossimo;
} Nodo_t;
typedef Nodo_t *Stack;

typedef struct listaInteri {
    int n;
    struct listaInteri *prossimo;
} listaInteri_t;
typedef listaInteri_t *ListaInteri;

typedef struct letters {
    char c;
    ListaInteri listaInteri;
    struct letters *prossimo;
} letters_t;
typedef letters_t *Lettere;

typedef struct notletters {
    char c;
    struct notletters *prossimo;
} notletters_t;
typedef notletters_t *NotLetters;

typedef struct nodoDizionario {
    char c;
    Stack listaParole;
} nodoDizionario_t;

void inserisciInDizionario(nodoDizionario_t *dizionario, char *parola, int dim);

int funzioneHash(char c);

int parolaUguale(char *parola1, char *parola2, int dim);

void stringaGioco(char *parolaDaConfrontare, int dim, nodoDizionario_t *dizionario, char *parolaRif, int *numeroDiTentativi,
                  NotLetters *k, List *maxLetters, List *minLetters,
                  Lettere *wrongPositionLetters, char *stringaGiocoCheConosco, nodoDizionario_t *filtrate);

void copiaStringa(char *stringaDaCopiare, char *stringaInCuiCopiare, int dim);

void nuovaOccorrenzaCarattere(List *listaDiCaratteri, char c);

void riduciOccorrenze(List listaCaratteriParola, char c);

int cercaChiave(List listaCaratteriParola, char c);

int cercaCarattere(char *stringa, char c, int dim);

int calcolaOccorrenzeCarattere(char *stringa, int dim, char c);

int parolaMinore(char *parolaDaConfrontare, char *parola2, int dim);

void ordinaLista(nodoDizionario_t *dizionario, int dim, nodoDizionario_t *filt);

void pulisciListaCartteri(List *listaCaratteri);

void stampaLista(Stack filtrate, int dim);

void cercaMezzo(Stack list, Stack *curr, Stack *prec);

Stack ordinaMergiati(Stack a, Stack b, int dim);

void ordinamentoLista(Stack *list, int dim);

void inserisciDizionarioFiltrato(nodoDizionario_t *dizionario, char *parola, int dim, Lettere wrongPositionLetters,
                                 List maxLetters, List minLetters, NotLetters notLetters, char *stringaGiocoCheConosco,
                                 nodoDizionario_t *filtrate);

void pulisciListaInteri(ListaInteri *listaInteri);

void aggiungiInListaInteri(ListaInteri *listaInteri, int r);

void aggiungiInLetters(Lettere *lettere, char t, int r);

void aggiungiInNotLetters(NotLetters *l, char t);

void aggiungiMinLetters(List *l, char c, int min);

void aggiungiMaxLetters(List *l, char c, int max);

void pulisciNotLetters(NotLetters *l);

void pulisciLetters(Lettere *lettere);

int filtraParola(char *parola, Lettere wrongPositionLetters, List maxLetters, List minLetters,
                 NotLetters notLetters, int dim, char *stringaGiocoCheConosco);

void setStringaGiocoCheConosco(char *stringa, int dim);

void attachDictAndFiltrate(nodoDizionario_t *filt, nodoDizionario_t *dizionario);


int main() {
    nodoDizionario_t dizionario[64];
    nodoDizionario_t filtrate[64];
    Lettere wrongPositionLetters = NULL;
    NotLetters notLetters = NULL;
    List maxLetters = NULL;
    List minLetters = NULL;
    int dim, valoreScanf;
    int numerodiTentativi;
    valoreScanf = scanf("%d", &dim);
    if (valoreScanf == -1) {
        return 0;
    }
    char parolaRiferimento[MAX];
    char parolaDaInserire[MAX];
    char stringaGiocoCheConosco[dim];
    for (int i = 0; i < 64; i++) {
        dizionario[i].listaParole = NULL;
        filtrate[i].listaParole = NULL;
    }
    int counter = 0;
    dizionario[counter].c = '-';
    filtrate[counter].c = '-';
    counter++;
    for(char c = '0'; c <= '9'; c++){
        dizionario[counter].c = c;
        filtrate[counter].c = c;
        counter++;
    }
    for(char c = 'A'; c <= 'Z'; c++){
        dizionario[counter].c = c;
        filtrate[counter].c = c;
        counter++;
    }
    dizionario[counter].c = '_';
    filtrate[counter].c = '_';
    counter++;
    for(char c = 'a'; c <= 'z'; c++){
        dizionario[counter].c = c;
        filtrate[counter].c = c;
        counter++;
    }
    do {
        valoreScanf = scanf("%s", parolaDaInserire);
        if (valoreScanf == -1) {
            return 0;
        }
        
        if (strcmp(parolaDaInserire, "+nuova_partita") == 0) {
            break;
        } else if(parolaDaInserire[0] != '+') {
            parolaDaInserire[dim] = '\0';
            inserisciInDizionario(dizionario, parolaDaInserire, dim);
        }
    } while (EOF);
    while (EOF) {
        valoreScanf = scanf("%s", parolaRiferimento);
        if (valoreScanf == -1) {
            return 0;
        }
        parolaRiferimento[dim] = '\0';
        setStringaGiocoCheConosco(stringaGiocoCheConosco, dim);
        valoreScanf = scanf("%d", &numerodiTentativi);
        if (valoreScanf == -1) {
            return 0;
        }
        while (numerodiTentativi > 0) {
            int paroleAggiunte = 0;
            valoreScanf = scanf("%s", parolaDaInserire);
            if (valoreScanf == -1) {
                return 0;
            }

            if (parolaDaInserire[0] == '+' && parolaDaInserire[1] == 'i') {
                while (EOF) {
                    valoreScanf = scanf("%s", parolaDaInserire);
                    if (valoreScanf == -1) {
                        return 0;
                    }
                    if (strcmp(parolaDaInserire, "+inserisci_fine") == 0) {
                        paroleAggiunte = 1;
                        break;
                    } else if(parolaDaInserire[0] != '+') {
                        parolaDaInserire[dim] = '\0';
                        inserisciDizionarioFiltrato(dizionario, parolaDaInserire, dim, wrongPositionLetters,
                                                    maxLetters, minLetters, notLetters, stringaGiocoCheConosco,
                                                    filtrate);
                    }
                }
            }
            
            if (paroleAggiunte == 1) {
                continue;
            }
            if (parolaDaInserire[0] == '+' && parolaDaInserire[1] == 's') {
                ordinaLista(dizionario, dim, filtrate);
                continue;
            }
            
            parolaDaInserire[dim] = '\0';
            if (parolaUguale(parolaDaInserire, parolaRiferimento, dim) == 1) {
                printf("ok");
                printf("\n");
                break;
            }
            stringaGioco(parolaDaInserire, dim, dizionario, parolaRiferimento, &numerodiTentativi, &notLetters,
                         &maxLetters, &minLetters, &wrongPositionLetters, stringaGiocoCheConosco,
                         filtrate);
        }
        if (numerodiTentativi == 0) {
            printf("ko");
            printf("\n");
        }
        while (EOF) {
            valoreScanf = scanf("%s", parolaDaInserire);
            if (valoreScanf == -1) {
                return 0;
            }
            
            if (parolaDaInserire[0] == '+') {
                if (parolaDaInserire[1] == 'n') {
                    attachDictAndFiltrate(filtrate, dizionario);
                    pulisciLetters(&wrongPositionLetters);
                    pulisciNotLetters(&notLetters);
                    pulisciListaCartteri(&maxLetters);
                    pulisciListaCartteri(&minLetters);
                    break;
                } else if (parolaDaInserire[1] == 'i') {
                    while (EOF) {
                        valoreScanf = scanf("%s", parolaDaInserire);
                        if (valoreScanf == -1) {
                            return 0;
                        }

                        if (strcmp(parolaDaInserire, "+inserisci_fine") == 0) {
                            break;
                        } else if(parolaDaInserire[0] != '+') {
                            parolaDaInserire[dim] = '\0';
                            inserisciInDizionario(dizionario, parolaDaInserire, dim);
                        }
                    }
                }
            }
        }
    }
}

void inserisciInDizionario(nodoDizionario_t *dizionario, char *parola, int dim) {
    Stack nuovaParola = malloc(sizeof(Nodo_t));
    if (nuovaParola) {
        nuovaParola->parola = malloc(sizeof(char) * (dim + 1));
        copiaStringa(parola, nuovaParola->parola, dim);
        nuovaParola->prossimo = dizionario[funzioneHash(parola[0])].listaParole;
        dizionario[funzioneHash(parola[0])].listaParole = nuovaParola;
        return;
    }
}

int parolaUguale(char *parola1, char *parola2, int dim) {
    for (int i = 0; i < dim; i++) {
        if (parola1[i] != parola2[i]) {
            return 0;
        }
    }
    return 1;
}

void stringaGioco(char *parolaDaConfrontare, int dim, nodoDizionario_t *dizionario, char *parolaRif, int *numeroDiTentativi,
                  NotLetters *k, List *maxLetters, List *minLetters,
                  Lettere *wrongPositionLetters, char *stringaGiocoCheConosco, nodoDizionario_t *filtrate) {
    char stringaGioco[dim];
    int presenteNelDizionario = 0;
    Stack currDict = dizionario[funzioneHash(parolaDaConfrontare[0])].listaParole;
    Stack currFilt = filtrate[funzioneHash(parolaDaConfrontare[0])].listaParole;
    while(currDict){
        if(parolaUguale(currDict -> parola,parolaDaConfrontare,dim) == 1){
            presenteNelDizionario = 1;
            break;
        }
        currDict = currDict -> prossimo;
    }
    while(currFilt){
        if(parolaUguale(currFilt -> parola,parolaDaConfrontare,dim) == 1){
            presenteNelDizionario = 1;
            break;
        }
        currFilt = currFilt -> prossimo;
    }
    if (presenteNelDizionario == 0) {
        printf("not_exists");
        printf("\n");
        return;
    }
    for(int i = 0; i < dim; i++){
        stringaGioco[i] = '*';
    }
    for(int i = 0; i < dim; i++){
        if(parolaDaConfrontare[i] == parolaRif[i]){
            stringaGioco[i] = '+';
        }
    }
    for(int i = 0; i < dim; i++){
        if(stringaGioco[i] == '*'){
            int occorrenzeRif = calcolaOccorrenzeCarattere(parolaRif,dim,parolaDaConfrontare[i]);
            int occorrenzeConf = calcolaOccorrenzeCarattere(parolaDaConfrontare,dim,parolaDaConfrontare[i]);
            if(occorrenzeRif < occorrenzeConf){
                int counter = occorrenzeConf - occorrenzeRif;
                for(int j = dim - 1; j >= 0; j--){
                    if(stringaGioco[j] != '+' && parolaDaConfrontare[j] == parolaDaConfrontare[i]){
                        stringaGioco[j] = '/';
                        counter--;
                        if(counter == 0){
                            break;
                        }
                        else{
                            continue;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < dim; i++){
        if(stringaGioco[i] == '*'){
            stringaGioco[i] = '|';
        }
    }
    //Adesso devo aggiornare Filtrate
    for (int i = 0; i < dim; i++) {
        if (stringaGioco[i] == '/') {
            if (cercaCarattere(parolaRif, parolaDaConfrontare[i], dim) == 1) {
                aggiungiInLetters(wrongPositionLetters, parolaDaConfrontare[i], i);
                int occorrenzeMax = calcolaOccorrenzeCarattere(parolaRif, dim, parolaDaConfrontare[i]);
                aggiungiMaxLetters(maxLetters, parolaDaConfrontare[i], occorrenzeMax);
            } else {
                aggiungiInNotLetters(k, parolaDaConfrontare[i]);
            }
        }
        if (stringaGioco[i] == '|') {
            aggiungiInLetters(wrongPositionLetters, parolaDaConfrontare[i], i);
            int occorrenzeRif = calcolaOccorrenzeCarattere(parolaRif, dim, parolaDaConfrontare[i]);
            int occorrenze = calcolaOccorrenzeCarattere(parolaDaConfrontare, dim, parolaDaConfrontare[i]);
            if (occorrenze <= occorrenzeRif) {
                aggiungiMinLetters(minLetters, parolaDaConfrontare[i], occorrenze);
            }
        }
        if (stringaGioco[i] == '+') {
            stringaGiocoCheConosco[i] = parolaRif[i];
            int occorrenzeRif = calcolaOccorrenzeCarattere(parolaRif, dim, parolaDaConfrontare[i]);
            int occorrenze = calcolaOccorrenzeCarattere(parolaDaConfrontare, dim, parolaDaConfrontare[i]);
            if (occorrenze <= occorrenzeRif) {
                aggiungiMinLetters(minLetters, parolaDaConfrontare[i], occorrenze);
            }
        }
    }
    int size = 0;
    if(stringaGiocoCheConosco[0] != '*'){
        for(int i = 0; i < 64; i++){
            if(stringaGiocoCheConosco[0] != dizionario[i].c){
                Stack tmp = dizionario[i].listaParole;
                while(tmp){
                    dizionario[i].listaParole = tmp -> prossimo;
                    inserisciInDizionario(filtrate,tmp ->parola,dim);
                    free(tmp -> parola);
                    free(tmp);
                    tmp = dizionario[i].listaParole;
                }
                dizionario[i].listaParole = NULL;
            }
        }
    }
    for(int i = 0; i < 64; i++){
        if(dizionario[i].listaParole){
            Stack curr = dizionario[i].listaParole;
            Stack prec = NULL;
            while(curr){
                if(prec){
                    if(filtraParola(curr -> parola,*wrongPositionLetters,*maxLetters,*minLetters,*k,dim,stringaGiocoCheConosco) == 1){
                        prec -> prossimo = curr -> prossimo;
                        inserisciInDizionario(filtrate,curr -> parola,dim);
                        free(curr -> parola);
                        free(curr);
                        curr = prec -> prossimo;
                        continue;
                    }
                    else{
                        size++;
                    }
                }
                else{
                    if(filtraParola(curr -> parola,*wrongPositionLetters,*maxLetters,*minLetters,*k,dim,stringaGiocoCheConosco) == 1){
                        inserisciInDizionario(filtrate,curr -> parola,dim);
                        dizionario[i].listaParole = curr -> prossimo;
                        free(curr -> parola);
                        free(curr);
                        curr = dizionario[i].listaParole;
                        continue;
                    }
                    else{
                        size++;
                    }
                }
                prec = curr;
                curr = curr -> prossimo;
            }
        }
    }
    for (int i = 0; i < dim; i++) {
        printf("%c", stringaGioco[i]);
    }
    printf("\n");
    printf("%d", size);

    printf("\n");
    *numeroDiTentativi = *numeroDiTentativi - 1;
}

void copiaStringa(char *stringaDaCopiare, char *stringaInCuiCopiare, int dim) {
    for (int i = 0; i < dim; i++) {
        stringaInCuiCopiare[i] = stringaDaCopiare[i];
    }
}

void nuovaOccorrenzaCarattere(List *listaDiCaratteri, char c) {
    List tmp = *listaDiCaratteri;
    while (tmp) {
        if (tmp->chiave == c) {
            tmp->occorrenzaCarattere = tmp->occorrenzaCarattere + 1;
            return;
        }
        tmp = tmp->prossimo;
    }
    List nuovoCarattere = malloc(sizeof(NodoParola_t));
    if (nuovoCarattere) {
        nuovoCarattere->chiave = c;
        nuovoCarattere->occorrenzaCarattere = 1;
        nuovoCarattere->prossimo = *listaDiCaratteri;
        *listaDiCaratteri = nuovoCarattere;
    }
}

void riduciOccorrenze(List listaCaratteriParola, char c) {
    List tmp = listaCaratteriParola;
    while (tmp) {
        if (tmp->chiave == c) {
            tmp->occorrenzaCarattere = tmp->occorrenzaCarattere - 1;
            return;
        }
        tmp = tmp->prossimo;
    }
}

int cercaChiave(List listaCaratteriParola, char c) {
    List tmp = listaCaratteriParola;
    while (tmp) {
        if (tmp->chiave == c) {
            return tmp->occorrenzaCarattere;
        }
        tmp = tmp->prossimo;
    }
    return 0;
}

int cercaCarattere(char *stringa, char c, int dim) {
    for (int i = 0; i < dim; i++) {
        if (c == stringa[i]) {
            return 1;
        }
    }
    return 0;
}

int calcolaOccorrenzeCarattere(char *stringa, int dim, char c) {
    int counter = 0;
    for (int i = 0; i < dim; i++) {
        if (stringa[i] == c) {
            counter++;
        }
    }
    return counter;
}


void ordinaLista(nodoDizionario_t *dizionario, int dim, nodoDizionario_t *filt) {
    for(int i = 0; i < 64; i++){
        ordinamentoLista(&dizionario[i].listaParole,dim);
        stampaLista(dizionario[i].listaParole,dim);
    }
}

int parolaMinore(char *parolaDaConfrontare, char *parola2, int dim) {
    int counter = 0;
    while (1) {
        if (parolaDaConfrontare[counter] < parola2[counter]) {
            return 1;
        }
        if (parolaDaConfrontare[counter] > parola2[counter]) {
            return 0;
        }
        if (parolaDaConfrontare[counter] == parola2[counter]) {
            counter++;
        }
        if (counter == dim) {
            return 1;
        }
    }
}

void pulisciListaCartteri(List *listaCaratteri) {
    List tmp = *listaCaratteri;
    List c;
    while (tmp) {
        c = tmp->prossimo;
        free(tmp);
        tmp = c;
    }
    *listaCaratteri = NULL;
}

void stampaLista(Stack filtrate, int dim) {
    Stack curr;
    for (curr = filtrate; curr; curr = curr->prossimo) {
        for (int i = 0; i < dim; i++) {
            printf("%c", (curr->parola)[i]);
        }
        printf("\n");
    }
}

void ordinamentoLista(Stack *list, int dim) {
    Stack tmp = *list;
    Stack sottolista1;
    Stack sottolista2;
    if ((tmp == NULL) || (tmp->prossimo == NULL)) {
        return;
    }
    cercaMezzo(tmp, &sottolista1, &sottolista2);
    ordinamentoLista(&sottolista1, dim);
    ordinamentoLista(&sottolista2, dim);
    *list = ordinaMergiati(sottolista1, sottolista2, dim);
}

Stack ordinaMergiati(Stack a, Stack b, int dim) {
    Stack tmp = NULL;
    if (a == NULL){
        return (b);
    }
    if (b == NULL){
        return (a);
    }
    if (parolaMinore(a->parola, b->parola, dim)) {
        tmp = a;
        tmp ->prossimo = ordinaMergiati(a->prossimo, b, dim);
    } else {
        tmp = b;
        tmp -> prossimo = ordinaMergiati(a, b->prossimo, dim);
    }
    return (tmp);
}

void cercaMezzo(Stack list,
                Stack *curr, Stack *prec) {
    Stack tmp1 = list->prossimo;;
    Stack tmp2 = list;
    while (tmp1) {
        tmp1 = tmp1->prossimo;
        if (tmp1) {
            tmp2 = tmp2->prossimo;
            tmp1 = tmp1->prossimo;
        }
    }
    *curr = list;
    *prec = tmp2->prossimo;
    tmp2->prossimo = NULL;
}

void inserisciDizionarioFiltrato(nodoDizionario_t *dizionario, char *parola, int dim, Lettere wrongPositionLetters,
                                 List maxLetters, List minLetters, NotLetters notLetters,
                                 char *stringaGiocoCheConosco, nodoDizionario_t *filt) {
    Stack nuovaParola = malloc(sizeof(Nodo_t));
    if (nuovaParola) {
        nuovaParola->parola = malloc(sizeof(char) * (dim + 1));
        copiaStringa(parola, nuovaParola->parola, dim);
        if (filtraParola(parola, wrongPositionLetters, maxLetters, minLetters, notLetters, dim,
                         stringaGiocoCheConosco) == 1) {
            nuovaParola->prossimo = filt[funzioneHash(parola[0])].listaParole;
            filt[funzioneHash(parola[0])].listaParole = nuovaParola;
        } else {
            nuovaParola->prossimo = dizionario[funzioneHash(parola[0])].listaParole;
            dizionario[funzioneHash(parola[0])].listaParole = nuovaParola;
        }
        return;

    }
}

void aggiungiInLetters(Lettere *lettere, char t, int r) {
    Lettere h = *lettere;
    while (h) {
        if (h->c == t) {
            ListaInteri curr = h->listaInteri;
            while (curr) {
                if (curr->n == r) {
                    return;
                }
                curr = curr->prossimo;
            }
            aggiungiInListaInteri(&(h->listaInteri), r);
            return;
        }
        h = h->prossimo;
    }
    Lettere tmp = malloc(sizeof(letters_t));
    if (tmp) {
        tmp->c = t;
        tmp->listaInteri = NULL;
        aggiungiInListaInteri(&(tmp->listaInteri), r);
        tmp->prossimo = *lettere;
        *lettere = tmp;
    }
}

void pulisciLetters(Lettere *lettere) {
    Lettere tmp = *lettere;
    Lettere t;
    while (tmp) {
        t = tmp->prossimo;
        pulisciListaInteri(&(tmp->listaInteri));
        free(tmp);
        tmp = t;
    }
    *lettere = NULL;
}

void pulisciListaInteri(ListaInteri *listaInteri) {
    ListaInteri tmp = *listaInteri;
    ListaInteri t;
    while (tmp) {
        t = tmp->prossimo;
        free(tmp);
        tmp = t;
    }
    *listaInteri = NULL;
}

void aggiungiInListaInteri(ListaInteri *listaInteri, int r) {
    ListaInteri tmp = malloc(sizeof(listaInteri_t));
    if (tmp) {
        tmp->n = r;
        tmp->prossimo = *listaInteri;
        *listaInteri = tmp;
    }
}

void aggiungiInNotLetters(NotLetters *l, char t) {
    NotLetters r = *l;
    while (r) {
        if (r->c == t) {
            return;
        }
        r = r->prossimo;
    }
    NotLetters tmp = malloc(sizeof(notletters_t));
    if (tmp) {
        tmp->c = t;
        tmp->prossimo = *l;
        *l = tmp;
    }
}

void pulisciNotLetters(NotLetters *l) {
    NotLetters tmp = *l;
    NotLetters t;
    while (tmp) {
        t = tmp->prossimo;
        free(tmp);
        tmp = t;
    }
    *l = NULL;
}

void aggiungiMaxLetters(List *l, char c, int max) {
    List tmp = *l;
    while (tmp) {
        if (tmp->chiave == c) {
            return;
        }
        tmp = tmp->prossimo;
    }
    List r = malloc(sizeof(NodoParola_t));
    if (r) {
        r->chiave = c;
        r->occorrenzaCarattere = max;
        r->prossimo = *l;
        *l = r;
    }
}

void aggiungiMinLetters(List *l, char c, int min) {
    List tmp = *l;
    while (tmp) {
        if (tmp->chiave == c) {
            if (tmp->occorrenzaCarattere >= min) {
                return;
            } else {
                tmp->occorrenzaCarattere = min;
                return;
            }
        }
        tmp = tmp->prossimo;
    }
    List r = malloc(sizeof(NodoParola_t));
    if (r) {
        r->chiave = c;
        r->occorrenzaCarattere = min;
        r->prossimo = *l;
        *l = r;
    }
}

int filtraParola(char *parola, Lettere wrongPositionLetters, List maxLetters, List minLetters,
                 NotLetters notLetters, int dim, char *stringaGiocoCheConosco) {
    for (int i = 0; i < dim; i++) {
        if (stringaGiocoCheConosco[i] != '*') {
            if (stringaGiocoCheConosco[i] != parola[i]) {
                return 1;
            }
        }
    }
    Lettere tmp2 = wrongPositionLetters;
    while (tmp2) {
        if (cercaCarattere(parola, tmp2->c, dim) == 0) {
            return 1;
        }
        ListaInteri curr = tmp2->listaInteri;
        while (curr) {
            if (parola[curr->n] == tmp2->c) {
                return 1;
            }
            curr = curr->prossimo;
        }
        tmp2 = tmp2->prossimo;
    }
    List tmp3 = maxLetters;
    while (tmp3) {
        int occorrenzeCarattereParola = calcolaOccorrenzeCarattere(parola, dim, tmp3->chiave);
        if (occorrenzeCarattereParola != tmp3->occorrenzaCarattere) {
            return 1;
        }
        tmp3 = tmp3->prossimo;
    }
    List tmp4 = minLetters;
    while (tmp4) {
        int occorrenzeCarattereParola = calcolaOccorrenzeCarattere(parola, dim, tmp4->chiave);
        if (occorrenzeCarattereParola < tmp4->occorrenzaCarattere) {
            return 1;
        }
        tmp4 = tmp4->prossimo;
    }
    NotLetters tmp0 = notLetters;
    while (tmp0) {
        if (cercaCarattere(parola, tmp0->c, dim) == 1) {
            return 1;
        }
        tmp0 = tmp0->prossimo;
    }
    return 0;
}

void setStringaGiocoCheConosco(char *stringa, int dim) {
    for (int i = 0; i < dim; i++) {
        stringa[i] = '*';
    }
}

void attachDictAndFiltrate(nodoDizionario_t  *filt, nodoDizionario_t *dizionario) {
    for(int i = 0; i < 64; i++){
        Stack tmp = dizionario[i].listaParole;
        if(tmp){
            while (tmp->prossimo) {
                tmp = tmp->prossimo;
            }
            tmp->prossimo = filt[i].listaParole;
            filt[i].listaParole = NULL;
        }
        else{
            dizionario[i].listaParole = filt[i].listaParole;
            filt[i].listaParole = NULL;
        }
    }
}

int booleanOrdinata(Stack list, int dim) {
    Stack curr = list;
    Stack prec = NULL;
    while (curr) {
        if (prec) {
            if (parolaMinore(prec->parola, curr->parola, dim) == 0) {
                return 0;
            }
        }
        prec = curr;
        curr = curr->prossimo;
    }
    return 1;
}

int funzioneHash(char c) {
    if (c == '-') {
        return 0;
    }
    if (c == '0') {
        return 1;
    }
    if (c == '1') {
        return 2;
    }
    if (c == '2') {
        return 3;
    }
    if (c == '3') {
        return 4;
    }
    if (c == '4') {
        return 5;
    }
    if (c == '5') {
        return 6;
    }
    if (c == '6') {
        return 7;
    }
    if (c == '7') {
        return 8;
    }
    if (c == '8') {
        return 9;
    }
    if (c == '9') {
        return 10;
    }
    if (c == 'A') {
        return 11;
    }
    if (c == 'B') {
        return 12;
    }
    if (c == 'C') {
        return 13;
    }
    if (c == 'D') {
        return 14;
    }
    if (c == 'E') {
        return 15;
    }
    if (c == 'F') {
        return 16;
    }
    if (c == 'G') {
        return 17;
    }
    if (c == 'H') {
        return 18;
    }
    if (c == 'I') {
        return 19;
    }
    if (c == 'J') {
        return 20;
    }
    if (c == 'K') {
        return 21;
    }
    if (c == 'L') {
        return 22;
    }
    if (c == 'M') {
        return 23;
    }
    if (c == 'N') {
        return 24;
    }
    if (c == 'O') {
        return 25;
    }
    if (c == 'P') {
        return 26;
    }
    if (c == 'Q') {
        return 27;
    }
    if (c == 'R') {
        return 28;
    }
    if (c == 'S') {
        return 29;
    }
    if (c == 'T') {
        return 30;
    }
    if (c == 'U') {
        return 31;
    }
    if (c == 'V') {
        return 32;
    }
    if (c == 'W') {
        return 33;
    }
    if (c == 'X') {
        return 34;
    }
    if (c == 'Y') {
        return 35;
    }
    if (c == 'Z') {
        return 36;
    }
    if (c == '_') {
        return 37;
    }
    if (c == 'a') {
        return 38;
    }
    if (c == 'b') {
        return 39;
    }
    if (c == 'c') {
        return 40;
    }
    if (c == 'd') {
        return 41;
    }
    if (c == 'e') {
        return 42;
    }
    if (c == 'f') {
        return 43;
    }
    if (c == 'g') {
        return 44;
    }
    if (c == 'h') {
        return 45;
    }
    if (c == 'i') {
        return 46;
    }
    if (c == 'j') {
        return 47;
    }
    if (c == 'k') {
        return 48;
    }
    if (c == 'l') {
        return 49;
    }
    if (c == 'm') {
        return 50;
    }
    if (c == 'n') {
        return 51;
    }
    if (c == 'o') {
        return 52;
    }
    if (c == 'p') {
        return 53;
    }
    if (c == 'q') {
        return 54;
    }
    if (c == 'r') {
        return 55;
    }
    if (c == 's') {
        return 56;
    }
    if (c == 't') {
        return 57;
    }
    if (c == 'u') {
        return 58;
    }
    if (c == 'v') {
        return 59;
    }
    if (c == 'w') {
        return 60;
    }
    if (c == 'x') {
        return 61;
    }
    if (c == 'y') {
        return 62;
    }
    if (c == 'z') {
        return 63;
    }
    return 64;
}

