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
    recalcularTodasLasTablas();
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
    recalcularTodasLasTablas();
    cout << "Enrutador '" << nombre << "' agregado correctamente.\n";
}
void Red::agregarEnlace(const string& origen, const string& destino, int costo) {
    if (!existeEnrutador(origen) || !existeEnrutador(destino)) {
        cout << "Uno o ambos enrutadores no existen.\n";
        return;
    }
    enrutadores[origen]->añadirEnlaceDirecto(destino, costo);
    enrutadores[destino]->añadirEnlaceDirecto(origen, costo);
    recalcularTodasLasTablas();
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
    recalcularTodasLasTablas();
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

void Red::dijkstra(const string& origen) {
    Enrutador* enrutOrigen = enrutadores.at(origen);
    enrutOrigen->limpiarTabla();

    // Distancias iniciales: infinito para todos
    const int INF = numeric_limits<int>::max();
    map<string, int> dist;
    for (auto& par : enrutadores)
        dist[par.first] = INF;
    dist[origen] = 0;
    enrutOrigen->setCosto(origen, 0);

    // Min-heap: (costo acumulado, nombre del nodo)
    priority_queue<pair<int,string>,
                   vector<pair<int,string>>,
                   greater<pair<int,string>>> cola;
    cola.push({0, origen});

    while (!cola.empty()) {
        auto [costoActual, nodoActual] = cola.top();
        cola.pop();

        // Si ya procesamos este nodo con menor costo, lo ignoramos
        if (costoActual > dist[nodoActual]) continue;

        // Recorrer vecinos del nodo actual
        const map<string,int>& vecinos = enrutadores.at(nodoActual)->getEnlacesDir();
        for (auto& [vecino, costoEnlace] : vecinos) {
            int nuevoCosto = dist[nodoActual] + costoEnlace;
            if (nuevoCosto < dist[vecino]) {
                dist[vecino] = nuevoCosto;
                enrutOrigen->setCosto(vecino, nuevoCosto);
                enrutOrigen->setPredecesor(vecino, nodoActual);
                cola.push({nuevoCosto, vecino});
            }
        }
    }
}

void Red::recalcularTodasLasTablas() {
    for (auto& par : enrutadores)
        dijkstra(par.first);
}

list<string> Red::caminoMasCorto(const string& origen, const string& destino) const {
    list<string> camino;

    if (!existeEnrutador(origen) || !existeEnrutador(destino)) return camino;
    if (origen == destino) { camino.push_back(origen); return camino; }

    const map<string,string>& pred = enrutadores.at(origen)->getPredecesor();

    // Reconstruir de destino hacia origen
    string actual = destino;
    while (actual != origen) {
        auto it = pred.find(actual);
        if (it == pred.end()) return {};    // sin camino
        camino.push_front(actual);
        actual = it->second;
    }
    camino.push_front(origen);
    return camino;
}

void Red::imprimirCamino(const string& origen, const string& destino) const {
    list<string> camino = caminoMasCorto(origen, destino);

    cout << "\n--- Camino de " << origen << " a " << destino << " ---\n";
    if (camino.empty()) {
        cout << "No existe camino.\n";
        return;
    }

    // Imprimir nodos del camino
    for (auto it = camino.begin(); it != camino.end(); ++it) {
        if (it != camino.begin()) cout << " --> ";
        cout << *it;
    }

    // Imprimir costo total desde la tabla del origen
    const map<string,int>& tabla = enrutadores.at(origen)->getTablaDeCostos();
    auto it = tabla.find(destino);
    int costo = (it != tabla.end()) ? it->second : -1;
    cout << "\nCosto total: " << costo << "\n";
}

void Red::imprimirTablaDeEnrutador(const string& nombre) const {
    if (!existeEnrutador(nombre)) {
        cout << "El enrutador '" << nombre << "' no existe.\n";
        return;
    }
    cout << "\n  Tabla de costos de " << nombre << ":\n";
    cout << "  Destino  | Costo\n";
    cout << "  ---------+-------\n";
    const map<string,int>& tabla = enrutadores.at(nombre)->getTablaDeCostos();
    for (auto& [dest, costo] : tabla)
        cout << "  " << dest << "        | " << costo << "\n";
}

void Red::imprimirTodasLasTablas() const {
    cout << "\n========== Tablas de enrutamiento ==========\n";
    for (auto& par : enrutadores)
        imprimirTablaDeEnrutador(par.first);
    cout << "============================================\n";
}
