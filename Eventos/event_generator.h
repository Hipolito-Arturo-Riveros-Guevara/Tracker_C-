#ifndef __EVENT_GENERATOR_H__
#define __EVENT_GENERATOR_H__

#include <vector>
#include <random>
#include <memory>
#include <cmath>
#include "detector_geometry.h"
#include "mc_info.h"
#include "../particle.h"
#include "../electron.h"
#include "../hit.h"
#include "../types.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class CEventGenerator {
private:
    SimpleDetectorGeometry m_detector_geometry;
    angle m_phi_min;
    angle m_phi_max;
    angle m_theta_min;
    angle m_theta_max;
    tuple<longitud, longitud, longitud> m_primary_vertex;
    
    // Generador de números aleatorios
    mt19937 m_rng;
    uniform_real_distribution<angle> m_phi_dist;
    uniform_real_distribution<angle> m_cos_theta_dist;
    uniform_real_distribution<angle> m_pt_dist;      
    uniform_real_distribution<angle> m_mass_dist;   
    
public:
    CEventGenerator(const SimpleDetectorGeometry& geometry,
                   angle phi_min = 0.0,
                   angle phi_max = 2*M_PI,
                   angle theta_min = 0.0,
                   angle theta_max = M_PI/10,
                   longitud vx = 0.0, longitud vy = 0.0, longitud vz = 0.0,
                   Seed seed = 42);
    
    virtual ~CEventGenerator();
    
    //setters
    void SetPhiRange(longitud min, longitud max) { m_phi_min = min; m_phi_max = max; }
    void SetThetaRange(longitud min, longitud max) { m_theta_min = min; m_theta_max = max; }
    void SetPrimaryVertex(longitud x, longitud y, longitud z) { 
        m_primary_vertex = make_tuple(x, y, z); 
    }
    
   // Generar vector de electrones
    vector<CElectron*> GenerateEvent(Number n_particles);
    
    //genera hits para una partícula dada su dirección y el vértice primario
    vector<Hit*> GenerateHitsForTrack(ID track_id, velocity vx, velocity vy, velocity vz, 
                                      ID& next_hit_id);
    
    void PrintEventInfo(const vector<CElectron*>& particles) const;
    
    //referencia a la geometría del detector
    const SimpleDetectorGeometry& GetGeometry() const { return m_detector_geometry; }
};

#endif // __EVENT_GENERATOR_H__