#include "red.h"

Red::Red() {}
Red::~Red(){
    for(auto&it : enrutadores){
        delete it.second;
    }
}
void Red::eliminarEnrutador(const string& nombre){
    auto it = enrutadores.find(nombre);

    if(it == enrutadores.end()){
        cout << "El enrutador '" << nombre << "' no existe.\n";
        return;
    }
    delete it->second;
    enrutadores.erase(it);

    for(auto&par : enrutadores){
       par.second->eliminarEnlace(nombre);;
    }
    cout << "Enrutador '" << nombre << "' eliminado correctamente.\n";
}
bool Red::existeEnrutador(const string& nombre) const {
    return enrutadores.find(nombre) != enrutadores.end();
}

void Red::agregarEnrutador(const string& nombre, const map<string,int>& enlaces){
    if (existeEnrutador(nombre)) {
        cout << "El enrutador '" << nombre << "' ya existe.\n";
        return;
    }

    // Validar que todos los vecinos declarados existan
    for (auto& enlace : enlaces) {
        if (!existeEnrutador(enlace.first)) {
            cout << "Advertencia: el vecino '" << enlace.first
                 << "' no existe en la red. Se ignora ese enlace.\n";
        }
    }
    Enrutador* nuevo = new Enrutador(nombre, enlaces);
    enrutadores[nombre] = nuevo;

    // Actualizar el lado opuesto de cada enlace
    for (auto& enlace : enlaces) {
        if (existeEnrutador(enlace.first)) {
            enrutadores[enlace.first]->añadirEnlaceDirecto(nombre, enlace.second);
        }
    }

    cout << "Enrutador '" << nombre << "' agregado correctamente.\n";
}
void Red::agregarEnlace(const string& origen, const string& destino, int costo) {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        cout << "Uno o ambos enrutadores no existen.\n";
        return;
    }
    enrutadores[origen]->añadirEnlaceDirecto(destino, costo);
    enrutadores[destino]->añadirEnlaceDirecto(origen, costo);
    cout << "Enlace " << origen << " <--> " << destino
         << " (costo " << costo << ") agregado.\n";
}

void Red::eliminarEnlace(const string& origen, const string& destino) {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        cout << "Uno o ambos enrutadores no existen.\n";
        return;
    }
    enrutadores[origen]->eliminarEnlace(destino);
    enrutadores[destino]->eliminarEnlace(origen);
    cout << "Enlace " << origen << " <--> " << destino << " eliminado.\n";
}
void Red::imprimirTopologia() const {
    cout << "\n===== Topologia de la red =====\n";
    for (auto& par : enrutadores) {
        cout << "Enrutador " << par.first << " -> vecinos: ";
        const map<string,int>& enlaces = par.second->getEnlacesDir();
        if (enlaces.empty()) {
            cout << "(sin enlaces)";
        }
        for (auto& enlace : enlaces) {
            cout << enlace.first << "(costo=" << enlace.second << ") ";
        }
        cout << "\n";
    }
    cout << "================================\n\n";
}







