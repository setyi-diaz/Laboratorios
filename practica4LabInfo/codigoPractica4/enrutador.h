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

public:
    Enrutador();
    void añadirEnlaceDirecto(string& , unsigned short );
    bool buscarEnlaceDirecto(string& ) const;
    void eliminarEnlace(string&);
    string getNombre() const;
    void setNombre(const string &newNombre);
};

#endif // ENRUTADOR_H
