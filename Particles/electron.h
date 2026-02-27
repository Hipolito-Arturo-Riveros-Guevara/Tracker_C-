#ifndef __ELECTRON_H__
#define __ELECTRON_H__

#include "particle.h"

class CElectron : public CParticle {
private:
    bool m_isolated;
    double m_ecalEnergy;

public:
    CElectron(string name, Mass mass, Phi phi, Pt pt, Eta eta, 
              bool isolated = true, double ecalEnergy = 0.0);
    virtual ~CElectron();

    virtual void SetIsolated(bool isolated) { m_isolated = isolated; };
    virtual bool GetIsolated() const { return m_isolated; };
    
    virtual void SetEcalEnergy(double energy) { m_ecalEnergy = energy; };
    virtual double GetEcalEnergy() const { return m_ecalEnergy; };

    string GetParticleType() const override { return string("Lepton"); };
    string GetClassName() const override { return string("Electron"); };
    ostream& Test(ostream &os) const override;
};

#endif // __ELECTRON_H__