#include "hit.h"

using namespace std;

Hit::Hit(HitID hit_id, X x, Y y, Z z, module_id module_id)
    : m_hit_id(hit_id), m_x(x), m_y(y), m_z(z), m_module_id(module_id) {
    cout << "Hit(" << m_hit_id << ")" << endl;
}

Hit::~Hit() {
    cout << "~Hit(" << m_hit_id << ")" << endl;
}