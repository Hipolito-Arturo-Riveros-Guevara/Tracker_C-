#ifndef __DETECTOR_GEOMETRY_H__
#define __DETECTOR_GEOMETRY_H__

#include <vector>
#include <iostream>
#include "types.h"
using namespace std;

/**
 * @file detector_geometry.h
 * @brief Declaración de la estructura SimpleDetectorGeometry.
 * 
 * Este archivo contiene la definición de la estructura SimpleDetectorGeometry,
 * que representa la geometría de un detector con información sobre módulos y sus posiciones.
 */

/**
 * @struct SimpleDetectorGeometry
 * @brief Representa la geometría de un detector.
 * 
 * La estructura SimpleDetectorGeometry almacena información sobre los módulos de un detector,
 * incluyendo sus identificadores, dimensiones y posiciones en el espacio.
 */

struct SimpleDetectorGeometry {
    vector<ID> module_id;
    vector<longitud> lx;  
    vector<longitud> ly;  
    vector<longitud> z;   
    
    /**
     * @brief Constructor por defecto de SimpleDetectorGeometry.
     */
    SimpleDetectorGeometry() = default;
    
    /**
     * @brief Constructor parametrizado de SimpleDetectorGeometry.
     * 
     * Inicializa la geometría del detector con los identificadores de los módulos,
     * sus dimensiones y posiciones.
     * 
     * @param ids Identificadores de los módulos.
     * @param lengths_x Longitudes de los módulos en el eje X.
     * @param lengths_y Longitudes de los módulos en el eje Y.
     * @param z_positions Posiciones de los módulos en el eje Z.
     */
    SimpleDetectorGeometry(const vector<ID>& ids, 
                          const vector<longitud>& lengths_x,
                          const vector<longitud>& lengths_y,
                          const vector<longitud>& z_positions)
        : module_id(ids), lx(lengths_x), ly(lengths_y), z(z_positions) {
        if (module_id.size() != lx.size() || 
            module_id.size() != ly.size() || 
            module_id.size() != z.size()) {
            cerr << "Error: Todos los vectores deben tener el mismo tamaño" << endl;
        }
    }
    
    /**
     * @brief Devuelve el número de módulos en la geometría.
     * 
     * @return Número de módulos.
     */
    Num size() const { return module_id.size(); }
};

#endif // __DETECTOR_GEOMETRY_H__