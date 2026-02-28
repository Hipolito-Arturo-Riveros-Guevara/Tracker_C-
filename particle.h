#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <iostream>
#include <string>
#include <vector>
#include "hit.h"
#include "types.h"

/**
 * @file particle.h
 * @brief Declaración de la clase base CParticle para representar partículas en el sistema.
 * 
 * Este archivo contiene la definición de la clase CParticle, que actúa como una clase base
 * para representar partículas con propiedades como nombre, masa, carga, momento, etc.
 * También incluye métodos para gestionar hits asociados a la partícula.
 */

/**
 * @class CParticle
 * @brief Clase base para representar partículas.
 * 
 * La clase CParticle proporciona una interfaz para manejar partículas con propiedades
 * físicas como masa, carga, momento, etc. También permite asociar y gestionar hits.
 */

using namespace std;

class CParticle {
private:

    string m_name;
    Mass m_mass;
    Charge m_charge;
    Phi m_phi;
    Pt m_pt;
    Eta m_eta;
    vector<Hit*> m_hits;

public:
    /**
     * @brief Constructor de la clase CParticle.
     * 
     * @param name Nombre de la partícula.
     * @param mass Masa de la partícula.
     * @param charge Carga de la partícula.
     * @param phi Ángulo azimutal de la partícula.
     * @param pt Momento transversal de la partícula.
     * @param eta Pseudorapidez de la partícula.
     */
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

    
    virtual void AddHit(Hit* hit);
    virtual void RemoveHit(HitID hit_id);
    virtual Hit* GetHit(HitID hit_id) const;
    virtual const vector<Hit*>& GetHits() const { return m_hits; };
    virtual Number GetNHits() const { return m_hits.size(); };
    virtual void ClearHits();

   
    virtual string GetParticleType() const = 0;
    
 
    friend bool operator==(const CParticle& lhs, const CParticle& rhs) {
    return lhs.m_name == rhs.m_name && lhs.m_mass == rhs.m_mass;
   }
   
 
    friend bool operator!=(const CParticle& lhs, const CParticle& rhs) {
        return !(lhs == rhs);
    }

    // Métodos ostream y print
    virtual string GetClassName() const { return string("Particle"); };
    virtual ostream &Test(ostream &os) const;
    
    friend ostream &operator<<(ostream &os, const CParticle &particle) {
        particle.Print(os);
        return os;
    };
    
    virtual void Print(ostream &os) const;
};

#endif // __PARTICLE_H__