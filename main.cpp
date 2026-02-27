#include <iostream>
#include "electron.h"

using namespace std;

int main() {
    cout << "=== Creando hits ===" << endl;
    Hit hit1(1, 1.0, 2.0, 3.0, 100);
    Hit hit2(2, 1.1, 2.1, 3.1, 100);
    Hit hit3(3, 1.2, 2.2, 3.2, 101);
    
    cout << "\n=== Creando electrón ===" << endl;
    CElectron* electron = new CElectron("e1", 0.000511, 0.5, 25.0, 1.2, true, 24.8);
    
    cout << "\n=== Añadiendo hits al electrón ===" << endl;
    electron->AddHit(&hit1);
    electron->AddHit(&hit2);
    electron->AddHit(&hit3);
    
    cout << "\n=== Mostrando información del electrón con sus hits ===" << endl;
    cout << *electron << endl;
    
    cout << "\n=== Buscando un hit específico ===" << endl;
    Hit* foundHit = electron->GetHit(2);
    if (foundHit) {
        cout << "Hit encontrado: " << *foundHit << endl;
    }
    
    cout << "\n=== Eliminando un hit ===" << endl;
    electron->RemoveHit(2);
    cout << "Después de eliminar: " << *electron << endl;
    
    cout << "\n=== Liberando memoria ===" << endl;
    delete electron;
    
    return 0;
}