#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <iostream>
#include <string>
#include <vector>
#include "hit.h"

// Definición de tipos para las propiedades de partículas
using Mass = double;
using Charge = int;      // Carga en unidades de e
using Phi = double;      // Ángulo azimutal en radianes
using Pt = double;       // Momento transverso en GeV
using Eta = double;      // Pseudorapidez

using namespace std;

class CParticle {
private:
    string m_name;
    Mass m_mass;
    Charge m_charge;
    Phi m_phi;
    Pt m_pt;
    Eta m_eta;
    vector<Hit*> m_hits;  // Lista de punteros a objetos Hit

public:
    CParticle(string name, Mass mass, Charge charge, Phi phi, Pt pt, Eta eta);
    virtual ~CParticle();

    // Getters y setters
    virtual void SetName(string name) { m_name = name; };
    virtual string GetName() const { return m_name; };
    
    virtual void SetMass(Mass mass) { m_mass = mass; };
    virtual Mass GetMass() const { return m_mass; };
    
    virtual void SetCharge(Charge charge) { m_charge = charge; };
    virtual Charge GetCharge() const { return m_charge; };
    
    virtual void SetPhi(Phi phi) { m_phi = phi; };
    virtual Phi GetPhi() const { return m_phi; };
    
    virtual void SetPt(Pt pt) { m_pt = pt; };
    virtual Pt GetPt() const { return m_pt; };
    
    virtual void SetEta(Eta eta) { m_eta = eta; };
    virtual Eta GetEta() const { return m_eta; };

    // Métodos para manejar los hits
    virtual void AddHit(Hit* hit);
    virtual void RemoveHit(HitID hit_id);
    virtual Hit* GetHit(HitID hit_id) const;
    virtual const vector<Hit*>& GetHits() const { return m_hits; };
    virtual int GetNHits() const { return m_hits.size(); };
    virtual void ClearHits();

    // Métodos virtuales puros
    virtual string GetParticleType() const = 0;
    
    // Métodos virtuales con implementación por defecto
    virtual string GetClassName() const { return string("Particle"); };
    virtual ostream &Test(ostream &os) const;
    
    friend ostream &operator<<(ostream &os, const CParticle &particle) {
        particle.Print(os);
        return os;
    };
    
    virtual void Print(ostream &os) const;
};

#endif // __PARTICLE_H__