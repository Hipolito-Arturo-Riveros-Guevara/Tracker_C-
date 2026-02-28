#include <iostream>
#include <memory>
#include <algorithm>
#include "particle.h"
#include "electron.h"
#include "hit.h"
#include "Eventos/event_generator.h"
#include "types.h"

using namespace std;

int main() {
    cout << "Detector" << endl;
    
    // geometria del detector
    vector<ID> module_ids = {0, 1, 2, 3, 4};
    vector<longitud> lx = {100.0, 100.0, 100.0, 100.0, 100.0};  
    vector<longitud> ly = {100.0, 100.0, 100.0, 100.0, 100.0};  
    vector<longitud> z_positions = {10.0, 20.0, 30.0, 40.0, 50.0}; 
    
    SimpleDetectorGeometry geometry(module_ids, lx, ly, z_positions);
    
    // genradpr de eventos
    CEventGenerator generator(geometry, 
                             0.0, 2*M_PI,     
                             0.0, M_PI/10,      
                             0.0, 0.0, 0.0,     
                             12345);           
    
    cout << "\nEvento" << endl;
    vector<CElectron*> event_particles = generator.GenerateEvent(5);  // 5 partículas
    
    cout << "\nInfo del Evento" << endl;
    generator.PrintEventInfo(event_particles);
    
    
    // Recolectar hits
    vector<Hit*> all_hits;
    for (auto electron : event_particles) {
        const auto& hits = electron->GetHits();
        for (auto hit : hits) {
            if (find(all_hits.begin(), all_hits.end(), hit) == all_hits.end()) {
                all_hits.push_back(hit);
            }
        }
    }
    
    // Liberar hits
    for (auto hit : all_hits) {
        delete hit;
    }
    
    // Liberar partículas
    for (auto electron : event_particles) {
        delete electron;
    }
    
    
    return 0;
}