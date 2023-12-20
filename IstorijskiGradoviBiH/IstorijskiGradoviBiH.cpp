/* ISTORIJSKI (POVIJESNI) GRADOVI BOSNE I HERCEGOVINE - PROJEKAT */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Grad {
    string ime;
    string povrsina;
    string br_stanovnika;
    string informacije;
};

Grad gradovi[50];
int brojGrada = 0;

void procitajIzFajla() {
    ifstream ulaz;
    ulaz.open("istorijskiGradoviBiH.csv");
    if (!ulaz) {
        cout << "Fajl se ne moze otvoriti." << endl;
        return;
    }
    string linija;
    while (getline(ulaz, linija)) {
        stringstream ss(linija);
        string ime, povrsina, br_stanovnika, informacije;
        getline(ss, ime, ',');
        getline(ss, povrsina, ',');
        getline(ss, br_stanovnika, ',');
        getline(ss, informacije, ',');
        gradovi[brojGrada].ime = ime;
        gradovi[brojGrada].povrsina = povrsina;
        gradovi[brojGrada].br_stanovnika = br_stanovnika;
        gradovi[brojGrada].informacije = informacije;
        brojGrada++;
    }
    ulaz.close();
}

void prikaziGradove() {
    for (int i = 0; i < brojGrada; i++) {
        cout << "Ime grada: " << gradovi[i].ime << endl;
        cout << "Povrsina: " << gradovi[i].povrsina << " km^2" << endl;
        cout << "Broj stanovnika: " << gradovi[i].br_stanovnika << endl;
        cout << "O gradu: " << gradovi[i].informacije << endl;
        cout << endl;
    }
}

void pretraziGrad() {
    string pretraga;
    cout << "Upisite ime grada: ";
    cin.ignore();
    getline(cin, pretraga);
    if (pretraga.length() == 0) {
        cout << "Pogresan unos. Molimo Vas da upisete ime grada." << endl;
        return;
    }
    for (int i = 0; i < brojGrada; i++) {
        if (gradovi[i].ime == pretraga) {
            cout << endl;
            cout << "Ime grada: " << gradovi[i].ime << endl;
            cout << "Povrsina: " << gradovi[i].povrsina << " km^2" << endl;
            cout << "Broj stanovnika grada: " << gradovi[i].br_stanovnika << endl;
            cout << "O gradu: " << gradovi[i].informacije << endl;
            cout << endl;
            return;
        }
    }
    cout << endl;
    cout << "Pogresan unos. Molimo Vas da upisete ime grada." << endl;
}

void dodajGrad() {
    Grad noviGrad;
    cin.ignore();
    cout << "Upisite ime grada: ";
    getline(cin, noviGrad.ime);
    cout << "Upisite povrsinu: ";
    cin >> noviGrad.povrsina;
    cout << "Upisite broj stanovnika grada: ";
    cin >> noviGrad.br_stanovnika;
    cin.ignore();
    cout << "Pisite o gradu: ";
    getline(cin, noviGrad.informacije);
    gradovi[brojGrada] = noviGrad;
    brojGrada++;

    ofstream izlaz;
    izlaz.open("istorijskiGradoviBiH.csv", ios::app);
    izlaz << noviGrad.ime << "," << noviGrad.povrsina << "," << noviGrad.br_stanovnika << "," << noviGrad.informacije << endl;
    izlaz.close();
    cout << endl;
    cout << "Grad je uspjesno dodan!" << endl;
}


void kviz() {
    srand(time(NULL));
    int randomIndex = rand() % brojGrada;
    string odgovor;
    int randomPitanje = rand() % 3; // generise nasumican broj od 0 do 2
    switch (randomPitanje) {
    case 0:
        cout << "Koja je povrsina podrucja grada " << gradovi[randomIndex].ime << "?" << endl;
        cout << "\nVas odgovor: "; cin >> odgovor;
        if (odgovor == gradovi[randomIndex].povrsina) {
            cout << "\nTacno!" << endl;
        }
        else {
            cout << "\nNetacno! Tacan odgovor je " << gradovi[randomIndex].povrsina << " km^2." << endl;
        }
        break;
    case 1:
        cout << "Koliko stanovnika ima " << gradovi[randomIndex].ime << "?" << endl;
        cout << "\nVas odgovor: "; cin >> odgovor;
        if (odgovor == gradovi[randomIndex].br_stanovnika) {
            cout << "\nTacno!" << endl;
        }
        else {
            cout << "\nNetacno! Tacan odgovor je " << gradovi[randomIndex].br_stanovnika << "." << endl;
        }
        break;
    case 2:
        cout << "O kojem gradu je rijec: " << "\n" << "'" << gradovi[randomIndex].informacije << "' ?" << endl;
        cout << "\nVas odgovor: "; cin.ignore();
        getline(cin, odgovor);
        if (odgovor == gradovi[randomIndex].ime) {
            cout << "\nTacno!" << endl;
        }
        else {
            cout << "\nNetacno! Tacan odgovor je " << gradovi[randomIndex].ime << "." << endl;
        }
        break;
    }
}

int main() {
    procitajIzFajla();
    int izbor;
    do {
        system("cls");
        cout << endl;
        cout << "\t\t\t\t*************************************************" << endl;
        cout << "\t\t\t\t***   ISTORIJSKI GRADOVI BOSNE I HERCEGOVINE  ***" << endl;
        cout << "\t\t\t\t*************************************************" << endl;
        cout << "\t\t\t\t***                                           ***" << endl;
        cout << "\t\t\t\t***      1. PRIKAZI GRADOVE                   ***" << endl;
        cout << "\t\t\t\t***      2. PRETRAZI GRAD                     ***" << endl;
        cout << "\t\t\t\t***      3. DODAJ GRAD                        ***" << endl;
        cout << "\t\t\t\t***      4. KVIZ                              ***" << endl;
        cout << "\t\t\t\t***      5. IZLAZ                             ***" << endl;
        cout << "\t\t\t\t***                                           ***" << endl;
        cout << "\t\t\t\t*************************************************" << endl;
        cout << "\n\t\t\t\tVas unos (1-5): ";
        cin >> izbor;
        cout << endl;

        while (izbor < 1 || izbor > 5) {
            cout << "Pogresan unos. Molimo Vas da korigujete unos (1-5): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> izbor;
        }

        switch (izbor) {
        case 1:
            prikaziGradove();
            break;
        case 2:
            pretraziGrad();
            break;
        case 3:
            dodajGrad();
            break;
        case 4:
            kviz();
            break;
        case 5:
            cout << "Izlaz iz programa..." << endl;
            break;
        }
        system("pause");
    } while (izbor != 5);
    return 0;
}