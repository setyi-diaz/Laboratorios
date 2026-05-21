#include <iostream>
#include "red.h"
#include "cargarArchivo.h"
using namespace std;

int main()
{
    Red red;
    string ruta = "redEnrutadores.txt";
    cargarDesdeArchivo(ruta,red);
    red.imprimirTopologia();

    string origen;
    string destino;
    unsigned short costo;

    int opcion;
    bool ban = true;
    do{
        cout << ">>> Ingrese 1: Agregar enrutador \n";
        cout << ">>> Ingrese 2: Eliminar enlace \n";
        cout << ">>> Ingrese 3: Eliminar enrutador \n";
        cout << ">>> Ingrese 4: si desea encontrar el camino entre dos enrutadores \n";
        cout << ">>> Ingrese 5: si desea visualizar tabla conjunta de enrutadores - enlaces \n";
        cout << ">>> Ingrese 0: Para salir \n";
        cin >> opcion;
        switch (opcion) {
        case 1:
            cout<<"ingrese el nombre del enrutador a crear: \n";
            cin>>origen;
            red.agregarEnrutador(origen, {});
            if(!(red.existeEnrutador(origen))){
                cout << ">>> Para agregar un enlace del enrutador creado\n";
                while(ban){
                    cout << ">>> Ingrese el nombre del enrutador destino \n";
                    cin >> destino;
                    cout << "\n>>> Ingrese el costo del enlace \n";
                    cin >> costo;
                    red.agregarEnlace(origen, destino, costo);
                    cout << ">>> Si desea agregar otro enlace ingrese: 1\n";
                    cout << ">>> De lo contrario ingrese: 0\n";
                    cin >> opcion;
                    if(opcion == 0){
                        ban = false;
                        opcion = -1;
                    }
                }
            }
            red.imprimirTopologia();
            break;
        case 2:
            cout<<"ingrese el nombre del enrutador origen: \n";
            cin>>origen;
            cout<<"ingrese el nombre del enrutador que desea desenlazar: \n";
            cin>>destino;
            red.eliminarEnlace(origen, destino);
            red.imprimirTopologia();
            break;
        case 3:
            cout<<"ingrese el nombre del enrutador a eliminar: \n";
            cin>>origen;
            red.eliminarEnrutador(origen);
            red.imprimirTopologia();
            break;
        case 4:
            cout<<"ingrese el nombre del enrutador origen: \n";
            cin>>origen;
            cout<<"ingrese el nombre del enrutador destino: \n";
            cin>>destino;
            red.imprimirCamino(origen,destino);
            red.imprimirTopologia();
            break;
        case 5:
            red.imprimirTodasLasTablas();
        default:
            break;
        }
    }while(opcion != 0);
}
