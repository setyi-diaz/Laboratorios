#include "enrutador.h"

Enrutador::Enrutador() {
}

string Enrutador::getNombre() const
{
    return nombre;
}

void Enrutador::setNombre(const string &newNombre)
{
    nombre = newNombre;
}

void Enrutador::getEnlace(string* enlacesDirectos) const{
    short ind = 0;
    for(const auto& par : enlaces){
        enlacesDirectos[ind] = par.fir;
        ind++;
    }
}
