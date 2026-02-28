#ifndef __PROTON_H__
#define __PROTON_H__

#include "particle.h"
#include "types.h"

class CProton : public CParticle {
private:
    bool m_isolated;
    Energy m_ecalEnergy;

public:
    CProton(string name, Mass mass, Phi phi, Pt pt, Eta eta, 
              bool isolated = true, Energy ecalEnergy = 0.0);
    virtual ~CProton();

    virtual void SetIsolated(bool isolated) { m_isolated = isolated; };
    virtual bool GetIsolated() const { return m_isolated; };
    
    virtual void SetEcalEnergy(Energy energy) { m_ecalEnergy = energy; };
    virtual Energy GetEcalEnergy() const { return m_ecalEnergy; };

    string GetParticleType() const override { return string("Hadron"); };
    string GetClassName() const override { return string("Proton"); };
    ostream& Test(ostream &os) const override;
};

#endif // __PROTON_H__