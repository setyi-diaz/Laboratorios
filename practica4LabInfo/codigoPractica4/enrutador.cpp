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

bool Enrutador::buscarEnlaceDirecto(string& enrut) const{
    auto it = enlacesDir.find(enrut);
    return (it != enlacesDir.end()) ? true : false;
}

void Enrutador::eliminarEnlace(string& enrut){
    if(buscarEnlaceDirecto(enrut)){
        auto it = enlacesDir.find(enrut);
        enlacesDir.erase(it);
    }
}
void Enrutador::añadirEnlaceDirecto(string& nombreEnrut, unsigned short costo){
    enlacesDir[nombreEnrut] = costo;
}
