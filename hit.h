#ifndef __HIT_H__
#define __HIT_H__

#include <iostream>
#include "types.h"
 

using namespace std;

class Hit {
private:
    HitID m_hit_id;
    X m_x;
    Y m_y;
    Z m_z;
    module_id m_module_id;

public:
    Hit(HitID hit_id, X x, Y y, Z z, module_id module_id);
    ~Hit();
    
    // Getters
    HitID GetHitID() const { return m_hit_id; };
    X GetX() const { return m_x; };
    Y GetY() const { return m_y; };
    Z GetZ() const { return m_z; };
    module_id GetModuleID() const { return m_module_id; };
    
    // Setters
    void SetHitID(HitID hit_id) { m_hit_id = hit_id; };
    void SetX(X x) { m_x = x; };
    void SetY(Y y) { m_y = y; };
    void SetZ(Z z) { m_z = z; };
    void SetModuleID(module_id module_id) { m_module_id = module_id; };
    
    // prints
    friend ostream& operator<<(ostream& os, const Hit& hit) {
        os << "Hit[ID=" << hit.m_hit_id 
           << ", pos=(" << hit.m_x << ", " << hit.m_y << ", " << hit.m_z << ")"
           << ", module=" << hit.m_module_id << "]";
        return os;
    };
};

#endif // __HIT_H__