#include "cargarArchivo.h"

void cargarDesdeArchivo(const string& rutaArchivo,Red& red) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo '" << rutaArchivo << "'.\n";
        return;
    }

    string linea;
    int nLinea = 0;
    while (getline(archivo, linea)) {
        nLinea++;
        // Ignorar comentarios y líneas vacías
        if (linea.empty() || linea[0] == '#') continue;

        istringstream ss(linea);
        string tipo;
        ss >> tipo;

        if (tipo == "ENRUTADOR") {
            string nombre;
            ss >> nombre;
            red.agregarEnrutador(nombre, {});

        } else if (tipo == "ENLACE") {
            string origen, destino;
            int costo;
            ss >> origen >> destino >> costo;
            red.agregarEnlace(origen, destino, costo);

        } else {
            cout << "Advertencia: linea " << nLinea << " no reconocida: " << linea << "\n";
        }
    }
    archivo.close();
    cout << "Archivo cargado correctamente.\n";
}
