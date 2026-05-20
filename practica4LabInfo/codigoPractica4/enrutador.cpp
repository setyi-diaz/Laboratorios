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
const map<string, int>& Enrutador::getTablaDeCostos() const {
    return tablaDeCostos;
}

const map<string, string>& Enrutador::getPredecesor() const {
    return predecesor;
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
void Enrutador::setCosto(const string& destino, int costo) {
    tablaDeCostos[destino] = costo;
}

void Enrutador::setPredecesor(const string& destino, const string& anterior) {
    predecesor[destino] = anterior;
}

// Se llama antes de cada ejecución de Dijkstra para este enrutador
void Enrutador::limpiarTabla() {
    tablaDeCostos.clear();
    predecesor.clear();
}
