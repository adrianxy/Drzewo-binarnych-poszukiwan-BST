#include <iostream>

using namespace std;

struct wezel {
    int value;
    wezel *right;
    wezel *left;
};

void BST_insert(wezel* &r, int x){  //wprowadzanie wezla
    if (r == NULL){                 //dla pierwszego wezla
        wezel *nowy = new wezel;
        nowy->value = x;
        nowy->right = NULL;
        nowy->left = NULL;
        r = nowy;
    }
    else if (x == r->value);                    //jesli taka wartosc juz istnieje nie tworz wezla
    else if (x > r->value) BST_insert(r->right,x);    //jesli wprowadzono wieksza zapisz po prawej
    else BST_insert(r->left,x);                        //jesli wprowadzono mniejsza zapisz po lewej
}

wezel* BST_search(wezel *r, int x){     //wyszukuje wezel w ktorym znajduje sie szukana liczba
    if ((r == NULL) or (r->value == x)) //jezeli nie ma to zwraca NULL, jesli jest zwraca wezel
        return r;
    else if (x < r->value)
        return BST_search(r->left,x);      //szuka po lewej
    else
        return BST_search(r->right,x);     //szuka po prawej
}

wezel* BST_delete(wezel* r, int x)
{
  if(r == NULL) return r;
  else if(x < r->value) r->left  = BST_delete(r->left, x);          //jezeli stad wyjde znaczy ze r=x
  else if(x > r->value) r->right = BST_delete(r->right, x);         //

  else{
    if(r->left == NULL && r->right == NULL){ //usuwany wezel nie ma dzieci
      r = NULL;
    }
    else if(r->left == NULL){       //usuwany wezel ma dziecko po prawej
       wezel* nowa = r;
       r= r->right;
    }
    else if(r->right == NULL){      //usuwany wezel ma dziecko po lewej
       wezel* nowa = r;
       r = r->left;
    }
    else{                                 // usuwany wezel ma dziecko po lewej i prawej
       wezel* nowa = r->right;

       while(nowa->left != NULL) nowa = nowa->left;     //@ szukamy wezla najmniejszego sposrod prawego potomka wezla usuwanego

       r->value = nowa->value;                          //usuwany wezel przyjmuje wartosc z @
       r->right = BST_delete(r->right, nowa->value);    //usuwamy @
    }
  }
  return r;
}

void wysokosc(wezel* r, int &m, int &wys, int wystab[]){
    if(r == NULL) wys=0;
    if(r->right != NULL){               //idz w prawo i inkrementuj wysokosc
        wys++;
        wysokosc(r->right, m, wys, wystab);
    }
    if(r->left != NULL){                //idz w lewo i inkrementuj wysokosc
        wys++;
        wysokosc(r->left, m, wys, wystab);
    }
    if(m==0) wystab[0]=wys;             //doszedles pierwszego do liscia, zapisz wysokosc
    if(m>0){                            //doszedles do kolejnego liscia, zapisz wysokosc
        wystab[1]=wys;
        if(wystab[0]<wystab[1]) wystab[0]=wystab[1];    //porowaj nowa wysokosc z dotychczas najwieksza, <wystab[0]- wartosc najwieksza>
    }
    m=1;
    wys--;              //cofasz sie, wiec dekrementuj wysokosc
}

void BT_postorder(wezel *r, int tab[], int &i){
    if (r != NULL) {
        BT_postorder(r->left, tab, i);
        BT_postorder(r->right, tab, i);
        tab[i]= r->value;
        i++;
    }
}

void rysowanie(int tab[], int i){
    int i_zap=i;
    int wieksze[100];
    int z[100];
    int id_najm;
    int positioning[100];

    positioning[i-1]=0;         //odleglosc od lewej krawedzi konsoli

    cout << tab[i-1];
    while(i>=2){
        if(tab[i-1]<tab[i-2] && i>=2)
        while(tab[i-1]<tab[i-2] && i>=2){       //rysowanie wiekszych potomkow
            cout << "-----" << tab[i-2];
            positioning[i-2]=positioning[i-1]+1;
            i--;
        }
        int k=0;

        cout << endl;
        if(tab[i-1]>tab[i-2] && i>=2){                  //rysowanie mniejszego potomka
            for(int j=i_zap-1; j>i-2; j--){     //wyszukuje liczby wieksze od biezacej liczby
                if(tab[i-2]<tab[j]){
                    wieksze[k]=tab[j];
                    z[k]=j;                     //zapisuje ich indeks w tablicy
                    k++;
                }
            }
            int min_wieksza;
            id_najm=z[0];
            if(k>0){
                min_wieksza=tab[z[0]];
                for(int j=1; j<k; j++){
                    if(tab[z[j]]<min_wieksza) {         //wybiera najmniejsza sposrod wiekszych
                        min_wieksza=tab[z[j]];          //
                        id_najm=z[j];                   //zapisuje jej indeks
                    }
                }
            }
            else if(k=0) min_wieksza=wieksze[0];

            positioning[i-2]=positioning[id_najm];      //odleglosc od krawedzi wezla jest rowna odleglosci jego rodzica

            for(int j=0; j<positioning[i-2]; j++) cout << "       ";    //na bazie positioningu tworzymy odleglosc
            cout << tab[i-2];
            i--;
        }
    };

}
/*void print(struct wezel *tmp,unsigned h,unsigned long long M){
        unsigned int i;
   if(tmp->left) print(tmp->left,h+1,M<<1);
   for(i=h-2;i<h;--i)
     {
      unsigned long long m=(M>>i)&3;
      if((m==0)||(m==3)) printf(" "); else printf("\xB3");
      printf(" ");
     }
   if(h)
     {
      if(M&1) printf("\xC0"); else printf("\xDA");
      printf("\xC4");
     }
   printf("\xDB%d \n", tmp->value);
   if(tmp->right) print(tmp->right,h+1,(M<<1)|1);
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void wprowadzanie(wezel* &r){
    int wstawiany;
    int i = 1;
    int n;

    cout << endl;
    cout << "----Wprowadzanie danych---- " << endl << endl
         << "Ile danych chcesz wprowadzic: ";
    cin >> n;

    for (int j=0; j<n; j++){
        cout << "liczba " << i++ << ": ";
        do{                                             //
            cin >> wstawiany;                           //podawaj dana dopoki nie bedzie unikalna
        }while(BST_search(r,wstawiany) != NULL);        //

        BST_insert(r,wstawiany);
    }
}

void usuwanie(wezel* &r){
    int usuwana;

    cout << endl;
    cout << "------Usuwanie danej------" << endl << endl
         << "Podaj dana do usuniecia: ";
    cin >> usuwana;

    BST_delete(r, usuwana);
}

void drukowanie(wezel*root, int tab[], int &i){
    BT_postorder(root, tab, i);
    rysowanie(tab, i);
    for(int j=0; j<i; j++) tab[j]=NULL;
    i=0;
}

int main(){
    int akcja;
    wezel* root = new wezel;
    root=NULL;
    int m=0;
    int wys=1;
    int wystab[2];
    int tab[100];
    int i=0;

    do{
        cout << endl << endl;
        cout << " -----------MENU----------- " << endl
             << "|     1. dodaj dane        |" << endl
             << "|     2. usun dana         |" << endl
             << "|     3. drukuj drzewo     |" << endl
             << "|     4. zakoncz program   |" << endl
             << " -------------------------- " << endl;
        cout << "Co chcesz zrobic: ";
        do{
            cin >> akcja;
        }while(akcja<1 || akcja>4);
        switch(akcja){
            case 1: wprowadzanie(root)  ; break;     //dodawanie danych
            case 2: usuwanie(root) ; break;          //usuwanie danej
            case 3: {drukowanie(root, tab, i); wysokosc(root, m, wys, wystab); cout << endl << "wysokosc drzewa: " << wystab[0]; m=0; wys=1; }; break;        //{BT_postorder(root, tab, i); rysowanie(tab, i);for(int j=0; j<i; j++) tab[j]=NULL; i=0;}
            case 4: ; break;
            default: ; break;
        };
    }while(akcja!=4);

    wysokosc(root, m, wys, wystab);
    /*print(root, 0, 0);*/

    delete root;
    return 0;
}
