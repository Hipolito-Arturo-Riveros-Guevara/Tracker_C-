#include "particle.h"
#include <algorithm>

using namespace std;

/**
 * @file particle.cpp
 * @brief Implementación de la clase base CParticle.
 * 
 * Este archivo contiene la implementación de los métodos de la clase CParticle,
 * que representa partículas con propiedades físicas y permite gestionar hits asociados.
 */

/**
 * @brief Constructor de la clase CParticle.
 * 
 * Inicializa una partícula con sus propiedades físicas y un nombre.
 * 
 * @param name Nombre de la partícula.
 * @param mass Masa de la partícula.
 * @param charge Carga de la partícula.
 * @param phi Ángulo azimutal de la partícula.
 * @param pt Momento transversal de la partícula.
 * @param eta Pseudorapidez de la partícula.
 */

/**
 * @brief Destructor de la clase CParticle.
 * 
 * Libera los recursos asociados a la partícula.
 */

/**
 * @brief Añade un hit a la partícula.
 * 
 * @param hit Puntero al hit que se añadirá.
 */

/**
 * @brief Elimina un hit de la partícula por su ID.
 * 
 * @param hit_id Identificador del hit que se eliminará.
 */

/**
 * @brief Obtiene un hit de la partícula por su ID.
 * 
 * @param hit_id Identificador del hit que se buscará.
 * @return Puntero al hit encontrado, o nullptr si no se encuentra.
 */

/**
 * @brief Elimina todos los hits asociados a la partícula.
 */

/**
 * @brief Imprime información de la partícula en un flujo de salida.
 * 
 * @param os Flujo de salida donde se imprimirá la información.
 */

CParticle::CParticle(string name, Mass mass, Charge charge, Phi phi, Pt pt, Eta eta)
    : m_name(name), m_mass(mass), m_charge(charge), m_phi(phi), m_pt(pt), m_eta(eta) {
    cout << "CParticle(" << m_name << ")" << endl;
}

CParticle::~CParticle() {
    cout << "~CParticle(" << m_name << ")" << endl;
    
}

void CParticle::AddHit(Hit* hit) {
    if (hit) {
        m_hits.push_back(hit);
        cout << "Hit " << hit->GetHitID() << " añadido a partícula " << m_name << endl;
    }
}

void CParticle::RemoveHit(HitID hit_id) {
    auto it = find_if(m_hits.begin(), m_hits.end(), [hit_id](Hit* hit) { return hit && hit->GetHitID() == hit_id; });
    
    if (it != m_hits.end()) {
        cout << "Hit " << hit_id << " eliminado de partícula " << m_name << endl;
        m_hits.erase(it);
    }
}

Hit* CParticle::GetHit(HitID hit_id) const {
    auto it = find_if(m_hits.begin(), m_hits.end(), 
        [hit_id](Hit* hit) { return hit && hit->GetHitID() == hit_id; });
    
    return (it != m_hits.end()) ? *it : nullptr;
}

void CParticle::ClearHits() {
    cout << "Eliminando hits " << m_name << endl;
    m_hits.clear();
}

ostream& CParticle::Test(ostream &os) const {
    os << "Particle: mass=" << m_mass 
       << ", charge=" << m_charge
       << ", phi=" << m_phi
       << ", pt=" << m_pt
       << ", eta=" << m_eta
       << ", nhits=" << m_hits.size();
    return os;
}

void CParticle::Print(ostream &os) const {
    os << "Tipo: " << GetClassName() << " | " << GetParticleType() 
       << " Nombre: " << GetName()
       << " Mass: " << GetMass()
       << " Charge: " << GetCharge()
       << " Phi: " << GetPhi()
       << " Pt: " << GetPt()
       << " Eta: " << GetEta()
       << " Nhits: " << GetNHits()
       << " Test: ";
    Test(os);
    
    // Opcional: imprimir detalles de los hits
    if (!m_hits.empty()) {
        os << "\n  Hits:";
        for (const auto& hit : m_hits) {
            if (hit) {
                os << "\n    " << *hit;
            }
        }
    }
}