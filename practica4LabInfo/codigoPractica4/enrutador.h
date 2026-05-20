#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <map>
#include <string>
using namespace std;

class Enrutador
{
private:
    string nombre;
    map<string,int> enlacesDir;
    map<string, int> tablaDeCostos;
    map<string, string> predecesor;

public:
    Enrutador();
    Enrutador(const string& ,const map<string,int>&);

    string getNombre() const;
    const map<string, int>& getEnlacesDir() const;
    const map<string, int>& getTablaDeCostos() const;
    const map<string, string>& getPredecesor() const;

    void setNombre(const string &newNombre);

    void añadirEnlaceDirecto(const string& , int );
    bool buscarEnlaceDirecto(const string& ) const;
    void eliminarEnlace(const string&);

    void setCosto(const string& destino, int costo);
    void setPredecesor(const string& destino, const string& anterior);
    void limpiarTabla();

};

#endif // ENRUTADOR_H
