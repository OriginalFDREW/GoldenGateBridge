#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

int gasire_mai_mic(int *v, int n, int pilon) //functie ce gaseste un pilon mai mic decat un setpoint
{
    int counter = 0;

    while(counter <= pilon) {

        for(int i = 0; i < n; i++) {

            if(v[i] == pilon - counter && v[i] != -1) {
                int aux = v[i];
                v[i] = -1;
                return aux;
            }

        }

        counter++;

    }

    return -1;

}

void ordonare(int *v, int n, int directie)
{
    if(directie == 1) {
        for(int i = 0; i < n - 1; i++)
            for(int j = i; j < n; j++)
        if(v[i] > v[j]) {
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    } else {
        for(int i = 0; i < n - 1; i++)
            for(int j = i; j < n; j++)
        if(v[i] < v[j]) {
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }
}

void caz_special(int *v, int n, vector<int> maxime)//caz special: mai putin de 4 piloni ramasi in vector dupa extragerea stalpilor
{
    ordonare(v, n, 1);

    vector<int>::iterator j = maxime.begin();
    int i = 0;
    while(v[i] == -1)
        i++;

    cout << "Solutia: ";

    if(n - maxime.size() == 3) {
        cout << v[i] << " ";
        i++;
        while(j < maxime.end() - 1) {
            cout << *j << " ";
            j++;
        }

        cout << v[i] << " " << *j << " ";
        i++;
        cout << v[i];
    } else if(n - maxime.size() == 2) {
        cout << v[i] << " ";
        i++;
        while(j < maxime.end()) {
            cout << *j << " ";
            j++;
        }

        cout << v[i];
    } else {
        cout << "Nu este posibil, prea putini piloni/stalpi.";
    }

    exit(EXIT_SUCCESS);
}

void afisare(int *v, int n)
{
    for(int i = 0; i < n; i++)
        cout << v[i] << " ";
}

bool caz(int *v, int n)//caz special: piloni de dimensiuni egale ramasi in vector
{
    bool cazul = true;

    int i = 0;
    while(v[i] == -1)
        i++;

    for(int j = i; j < n; j++) {
        if(v[j] != v[i])
            cazul = false;
    }

    return cazul;
}

int main()
{
    cout << "Care este numarul de piloni? ";
    int n;
    cin >> n;

    int *v = new int[n];
    cout << "Pilonii:" << endl;
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<int> maxime; //vector in care se vor pune valorile maxime ale pilonilor(stalpii de rezistenta)
    int mx = 0;

    for(int i = 0; i < n; i++) {
        if(v[i] > mx) {
            mx = v[i];
        }
    }

    for(int i = 0; i < n; i++) {
        if(v[i] == mx) {
            maxime.push_back(v[i]);
            v[i] = -1;
        }
    }

    vector<int>::iterator j = maxime.begin();

    if(maxime.size() == 1)
        maxime.push_back( gasire_mai_mic(v, n, *j) );

    int n1, n2, n3, n4;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    int aux = n - maxime.size();

    if(aux <= 3)
        caz_special(v, n, maxime);

    switch( aux % 4 ) {
case 0:
    n1 = n2 = n3 = n4 = aux / 4;
    break;

case 1:
    n1 = n3 = n4 = aux / 4;
    n2 = n1 + 1;
    break;

case 2:
    n2 = n3 = aux / 4;
    n1 = n4 = n2 + 1;
    break;

case 3:
    n3 = aux / 4;
    n1 = n2 = n4 = n3 + 1;
    break;
    }//depinzand de numarul de piloni ramasi in vector dupa extragerea stalpilor de rezistenta, vom avea dimensiuni diferite pentru
    //cei 4 vectori

    int *v1 = new int[n1],
    *v2 = new int[n2],
    *v3 = new int[n3],
    *v4 = new int[n4]; //4 vectori, ce vor contine pilonii dintre stalpii de rezistenta, cu dimensiuni bazate pe numarul de piloni ramasi dupa eliminarea stalpilor

    ordonare(v, n, 1);
    int i = 0;
    while(v[i] == -1)
        i++;

    for( ; i < n; ) {

        if(i >= n) break;

        if(i < n && i1 < n1) {
            v1[i1] = v[i];
            i++;
            i1++;
        }

        if(i < n && i2 < n2) {
            v2[i2] = v[i];
            i++;
            i2++;
        }

        if(i < n && i3 < n3) {
            v3[i3] = v[i];
            i++;
            i3++;
        }

        if(i < n && i4 < n4) {
            v4[i4] = v[i];
            i++;
            i4++;
        }
    }//punerea pilonilor in cei 4 vectori succesiv, urmarind pozitia in vectorul original si dimensiunile
    //deja setate ale vectorilor pentru piloni

    if( caz(v, n) && (maxime[1] == v1[0]) ) { // daca avem un caz special: un singur maxim

        cout << "Solutia: ";
        afisare(v1, n1);
        afisare(v2, n2);
        cout << maxime[0] << " ";
        afisare(v3, n3);
        cout << maxime[1] << " ";
        afisare(v4, n4);
        goto label;

    }

    ordonare(v1, n1, 1);
    ordonare(v2, n2, 0);
    ordonare(v3, n3, 1);
    ordonare(v4, n4, 0);//sirul de piloni 1 si 3 vor fi ascendente, iar 2 si 4 descendente

    cout << "Solutia: ";
    j = maxime.begin();
    afisare(v1, n1);
    while( j < maxime.end() - 1 ) {
        cout << *j << " ";
        j++;
    }
    afisare(v2, n2);
    afisare(v3, n3);
    cout << *j << " ";
    afisare(v4, n4);

    label:

    return 0;
}
