#include "electron.h"
#include "types.h"

CElectron::CElectron(string name, Mass mass, Phi phi, Pt pt, Eta eta, 
                     bool isolated, Energy ecalEnergy)
    : CParticle(name, mass, -1, phi, pt, eta),
      m_isolated(isolated), m_ecalEnergy(ecalEnergy) {
    cout << "CElectron(" << GetName() << ")" << endl;
}

CElectron::~CElectron() {
    cout << "~CElectron(" << GetName() << ")" << endl;
}

ostream& CElectron::Test(ostream &os) const {
    CParticle::Test(os);
    os << " | Electron: isolated=" << m_isolated 
       << ", ecalEnergy=" << m_ecalEnergy;
    return os;
}