#include "particle.h"
#include <algorithm>

using namespace std;

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
    auto it = find_if(m_hits.begin(), m_hits.end(), 
        [hit_id](Hit* hit) { return hit && hit->GetHitID() == hit_id; });
    
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