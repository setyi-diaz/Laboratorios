#include <iostream>
#include "red.h"
using namespace std;

int main()
{
    Red red;

    // ── Prueba 1: agregar enrutadores de la Figura 1 del enunciado ──
    cout << ">>> Prueba 1: Agregar enrutadores A, B, C, D\n";
    red.agregarEnrutador("A", {});          // sin enlaces iniciales
    red.agregarEnrutador("B", {});
    red.agregarEnrutador("C", {});
    red.agregarEnrutador("D", {});

    // ── Prueba 2: agregar los enlaces con sus costos ──
    cout << "\n>>> Prueba 2: Agregar enlaces\n";
    red.agregarEnlace("A", "B", 4);
    red.agregarEnlace("A", "C", 10);
    red.agregarEnlace("A", "D", 5);
    red.agregarEnlace("B", "C", 3);
    red.agregarEnlace("B", "D", 1);
    red.agregarEnlace("C", "D", 2);

    red.imprimirTopologia();

    // ── Prueba 3: intentar agregar un enrutador duplicado ──
    cout << ">>> Prueba 3: Agregar enrutador duplicado\n";
    red.agregarEnrutador("A", {});

    // ── Prueba 4: eliminar un enlace ──
    cout << "\n>>> Prueba 4: Eliminar enlace A <--> C\n";
    red.eliminarEnlace("A", "C");
    red.imprimirTopologia();

    // ── Prueba 5: agregar un nuevo enrutador con enlace a uno existente ──
    cout << ">>> Prueba 5: Agregar enrutador E con enlace a B (costo 6)\n";
    red.agregarEnrutador("E", {{"B", 6}});
    red.imprimirTopologia();

    // ── Prueba 6: eliminar un enrutador y verificar que se limpian sus referencias ──
    cout << ">>> Prueba 6: Eliminar enrutador D\n";
    red.eliminarEnrutador("D");
    red.imprimirTopologia();

    // ── Prueba 7: eliminar enrutador inexistente ──
    cout << ">>> Prueba 7: Eliminar enrutador que no existe\n";
    red.eliminarEnrutador("Z");
}
