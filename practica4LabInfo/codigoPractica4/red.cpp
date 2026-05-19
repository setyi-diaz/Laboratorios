#include "red.h"

Red::Red() {}

void Red::eliminarEnrut(string removeEnrut){
    for(auto& enrutador : enrutadores){
        if(enrutador->getNombre() == removeEnrut){

            enrutadores.remove(enrutador);
        }
    }
}
