#include <iostream>
using namespace std;

//Definicion de variables
int monto, plazo, intereses;

//Funcion principal
int main()
{
    int option;
    do
    {
        cout << "1. Ingresar datos del préstamo" << endl;
        cout << "2. Calcular cuota mensual" << endl;
        cout << "3. Mostrar el total a pagar" << endl;
        cout << "4. Mostrar detalle de pago mensual" << endl;
        cout << "5. Salir" << endl;
        cin >> option;
        if (option < 1 || option > 5)
        {
            cout << "Opcion no valida, seleccione una opción de la lista" << endl;
        }
    }
    while (option < 1 || option > 5);
    switch (option)
    {
        case 1:
        do
        {
            cout << "Ingrese el monto del prestamo" << endl;
            cin >> monto;
            if (monto <= 0)
            {
                cout << "El monto del prestamo no puede ser negativo o igual a 0" << endl;
            }
        }
        while (monto > 0);
        do
        {
            cout << "Ingrese el plazo del prestamo en meses, el maximo es 360 meses" << endl;
            cin >> plazo;
            if (plazo <= 0)
            {
                cout << "El plazo del prestamo no puede ser negativo o igual a 0" << endl;
            }
        }
        while (plazo > 0 && plazo <= 360);
        do
        {
            cout << "Ingrese el interes del prestamo en porcentaje, el maximo es 100" << endl;
            cin >> intereses;
            if (intereses <= 0)
            {
                cout << "El interes del prestamo no puede ser negativo" << endl;
            }
        }
        while (intereses > 0 && intereses <= 100);
    }
}