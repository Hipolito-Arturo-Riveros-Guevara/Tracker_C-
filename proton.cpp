#include "proton.h"
#include "types.h"

CProton::CProton(string name, Mass mass, Phi phi, Pt pt, Eta eta, 
                     bool isolated, Energy ecalEnergy)
    : CParticle(name, mass, 1, phi, pt, eta),
      m_isolated(isolated), m_ecalEnergy(ecalEnergy) {
    cout << "CProton(" << GetName() << ")" << endl;
}

CProton::~CProton() {
    cout << "~CProton(" << GetName() << ")" << endl;
}

ostream& CProton::Test(ostream &os) const {
    CParticle::Test(os);
    os << " | Proton: isolated=" << m_isolated 
       << ", ecalEnergy=" << m_ecalEnergy;
    return os;
}