#ifndef RED_H
#define RED_H
#include "enrutador.h"
#include <list>
using namespace std;

class Red
{
private:
    list<Enrutador*> enrutadores;
public:
    Red();
    void eliminarEnrut();
};

#endif // RED_H
