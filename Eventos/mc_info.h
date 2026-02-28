#ifndef __MC_INFO_H__
#define __MC_INFO_H__

#include <tuple>
#include "types.h"

using namespace std;

/**
 * @file mc_info.h
 * @brief Declaración de la estructura MCInfo.
 * 
 * Este archivo contiene la definición de la estructura MCInfo, que almacena información
 * sobre el vértice primario y los ángulos de una partícula generada en un evento simulado.
 */

/**
 * @struct MCInfo
 * @brief Almacena información de Monte Carlo para una partícula.
 * 
 * La estructura MCInfo contiene información sobre el vértice primario y los ángulos
 * de una partícula generada en un evento simulado.
 */

struct MCInfo {
    tuple<longitud, longitud, longitud> primary_vertex;  // (x, y, z)
    angle theta;
    angle phi;
    
    MCInfo() = default;
    
    MCInfo(velocity vx, velocity vy, velocity vz, angle t, angle p)
        : primary_vertex(make_tuple(vx, vy, vz)), theta(t), phi(p) {}
        
    MCInfo(const tuple<longitud, longitud, longitud>& vertex, angle t, angle p)
        : primary_vertex(vertex), theta(t), phi(p) {}
};

#endif // __MC_INFO_H__