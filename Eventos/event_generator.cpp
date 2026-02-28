#include "event_generator.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "types.h"

/**
 * @file event_generator.cpp
 * @brief Implementación de la clase CEventGenerator.
 * 
 * Este archivo contiene la implementación de los métodos de la clase CEventGenerator,
 * que se encarga de generar eventos, partículas y hits en un detector simulado.
 */

/**
 * @brief Constructor de la clase CEventGenerator.
 * 
 * Inicializa el generador de eventos con la geometría del detector, rangos de ángulos,
 * vértice primario y una semilla para el generador de números aleatorios.
 * 
 * @param geometry Geometría del detector.
 * @param phi_min Mínimo valor del ángulo azimutal (phi).
 * @param phi_max Máximo valor del ángulo azimutal (phi).
 * @param theta_min Mínimo valor del ángulo polar (theta).
 * @param theta_max Máximo valor del ángulo polar (theta).
 * @param vx Coordenada x del vértice primario.
 * @param vy Coordenada y del vértice primario.
 * @param vz Coordenada z del vértice primario.
 * @param seed Semilla para el generador de números aleatorios.
 */

/**
 * @brief Destructor de la clase CEventGenerator.
 * 
 * Libera los recursos asociados al generador de eventos.
 */

/**
 * @brief Genera los hits para una pista en el detector.
 * 
 * @param track_id Identificador de la pista.
 * @param vx Componente x de la dirección de la pista.
 * @param vy Componente y de la dirección de la pista.
 * @param vz Componente z de la dirección de la pista.
 * @param next_hit_id Referencia al siguiente identificador de hit.
 * @return Vector de punteros a los hits generados.
 */

/**
 * @brief Genera un evento con un número dado de partículas.
 * 
 * @param n_particles Número de partículas a generar.
 * @return Vector de punteros a las partículas generadas.
 */

/**
 * @brief Imprime información sobre las partículas y hits generados en un evento.
 * 
 * @param particles Vector de punteros a las partículas generadas.
 */

CEventGenerator::CEventGenerator(const SimpleDetectorGeometry& geometry,
                                 angle phi_min, angle phi_max,
                                 angle theta_min, angle theta_max,
                                 longitud vx, longitud vy, longitud vz,
                                 Seed seed)
    : m_detector_geometry(geometry),
      m_phi_min(phi_min),
      m_phi_max(phi_max),
      m_theta_min(theta_min),
      m_theta_max(theta_max),
      m_primary_vertex(make_tuple(vx, vy, vz)),
      m_rng(seed),
      m_phi_dist(phi_min, phi_max),
      m_cos_theta_dist(cos(theta_max), cos(theta_min)),
      m_pt_dist(0.5, 50.0),           // Pt entre 0.5 y 50 GeV
      m_mass_dist(0.0005, 0.00052) {   // Masa del electrón ~0.000511 GeV
    cout << "Evento con" << geometry.size() << " modulos" << endl;
    cout << "Rango phi: [" << phi_min << ", " << phi_max << "]" << endl;
    cout << "Rango theta: [" << theta_min << ", " << theta_max << "]" << endl;
}

CEventGenerator::~CEventGenerator() {
    cout << "~CEventGenerator" << endl;
}

vector<Hit*> CEventGenerator::GenerateHitsForTrack(ID track_id, velocity vx, velocity vy, velocity vz,
                                                   ID& next_hit_id) {
    vector<Hit*> hits;
    
    longitud pvx = get<0>(m_primary_vertex);
    longitud pvy = get<1>(m_primary_vertex);
    longitud pvz = get<2>(m_primary_vertex);
    
    for (Num i = 0; i < m_detector_geometry.size(); ++i) {
        ID module_id = m_detector_geometry.module_id[i];
        longitud z_module = m_detector_geometry.z[i];
        longitud lx_module = m_detector_geometry.lx[i];
        longitud ly_module = m_detector_geometry.ly[i];
        
        // tiempo de vuelo de la particula hasta el módulo
        time t = (z_module - pvz) / vz;
        
        // calcular posición del hit
        longitud x_hit = pvx + vx * t;
        longitud y_hit = pvy + vy * t;
        
        // verificar si el hit está dentro del módulo
        if (abs(x_hit) < lx_module/2 && abs(y_hit) < ly_module/2) {
            // Crear nuevo hit
            Hit* hit = new Hit(next_hit_id++, x_hit, y_hit, z_module, module_id);
            hits.push_back(hit);
            
            cout << "  Hit generado: ID=" << hit->GetHitID() 
                 << " en modulo " << module_id 
                 << " posicion (" << x_hit << ", " << y_hit << ", " << z_module << ")" << endl;
        }
    }
    
    return hits;
}

vector<CElectron*> CEventGenerator::GenerateEvent(Number n_particles) {
    cout << "\nEvento con" << n_particles << " partículas" << endl;
    
    vector<CElectron*> particles;
    ID next_hit_id = 0;
    
    longitud pvx = get<0>(m_primary_vertex);
    longitud pvy = get<1>(m_primary_vertex);
    longitud pvz = get<2>(m_primary_vertex);
    
    for (ID track_id = 0; track_id < n_particles; ++track_id) {
        cout << "\n particula" << track_id << " ---" << endl;
        
        // Generar direccion
        angle phi = m_phi_dist(m_rng);
        angle cos_theta = m_cos_theta_dist(m_rng);
        angle theta = acos(cos_theta);
        angle sin_theta = sin(theta);
        
        // Generar momento transverso y masa
        longitud pt = m_pt_dist(m_rng);
        Mass mass = m_mass_dist(m_rng);
        
        // Calcular vector dirección
        velocity vx = sin_theta * cos(phi);
        velocity vy = sin_theta * sin(phi);
        velocity vz = cos_theta;
        
        cout << "  direccion: theta=" << theta << ", phi=" << phi << endl;
        cout << "  Pt=" << pt << " GeV, mass=" << mass << " GeV" << endl;
        
        // Generar hits para esta partícula
        vector<Hit*> track_hits = GenerateHitsForTrack(track_id, vx, vy, vz, next_hit_id);
        
        // Crear electrón con los hits generados
        string name = "e" + to_string(track_id);
        CElectron* electron = new CElectron(name, mass, phi, pt, theta, true, pt * 0.95); 
        
        // Añadir todos los hits al electrón
        for (auto hit : track_hits) {
            electron->AddHit(hit);
        }
        
        particles.push_back(electron);
        
        cout << "  particula " << track_id << " generada con " << track_hits.size() << " hits" << endl;
    }
    
    cout << "\n Evento generado: " << particles.size() << " partículas, " 
         << next_hit_id << " hits totales ===" << endl;
    
    return particles;
}

void CEventGenerator::PrintEventInfo(const vector<CElectron*>& particles) const {
    cout << "\nInformación del Evento" << endl;
    cout << "Número de partículas: " << particles.size() << endl;
    
    Number total_hits = 0;
    for (size_t i = 0; i < particles.size(); ++i) {
        cout << "\nPartícula " << i << ":" << endl;
        cout << *particles[i] << endl;
        total_hits += particles[i]->GetNHits();
    }
    
    cout << "\nTotal de hits en el evento: " << total_hits << endl;
}