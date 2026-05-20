#include "enrutador.h"

Enrutador::Enrutador() : nombre("") {}

Enrutador::Enrutador(const string& n,const map<string,int>& enlaces) {
    nombre = n;
    enlacesDir = enlaces;
}

string Enrutador::getNombre() const
{
    return nombre;
}

void Enrutador::setNombre(const string &newNombre)
{
    nombre = newNombre;
}
const map<string, int>& Enrutador::getEnlacesDir() const {
    return enlacesDir;
}
bool Enrutador::buscarEnlaceDirecto(const string& enrut) const{
    return enlacesDir.find(enrut) != enlacesDir.end();
}

void Enrutador::eliminarEnlace(const string& enrut){
    enlacesDir.erase(enrut);
}
void Enrutador::añadirEnlaceDirecto(const string& nombreEnrut, int costo){
    enlacesDir[nombreEnrut] = costo;
}
