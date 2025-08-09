#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;

//Declaración de funciones
void callFunction(int selection);
int showMenu();

//Definición de struct
struct loanStructure
{
    double monto;
    int plazo;
    int interes;
    double cuotaMensual;
    double cuotaTotal;
};

//Funcion principal
int main()
{
    //Se utiliza setlocale para importar la configuración de la computadora, así se utilizan tildes y ñ
    setlocale(LC_ALL, "spanish");

}

int showMenu()
{
    int selection;
    do
    {
        cout << "1. Registrar préstamo" << endl;
        cout << "2. Editar préstamo" << endl;
        cout << "3. Calcular préstamo" << endl;
        cout << "4. Eliminar préstamo" << endl;
        cout << "5. Salir";
        cin >> selection;
        if (selection < 1 || selection > 5)
        {
            cout << "Opción inválida, por favor seleccione una opción de la lista." << endl;
        }
    }while (selection < 1 || selection > 5);
    return selection;
}

void callFunction(int selection)
{
    switch (selection)
    {
        case 1:
        cout << "crear prestamo" << endl;
        break;
        case 2:
        cout << "editar prestamo" << endl;
        case 3:
        cout << "mostrar prestamo" << endl;
        case 4:
        cout << "eliminar prestamo" << endl;
        default:
        break;
    }
}

void createLoan(loanStructure &loan)
{
    do
    {
        cout << "Introduzca el monto del préstamo" << endl;
        cin >> loan.monto;
        if (loan.monto <= 0)
        {
            cout << "Introduzca un monto válido, tiene que ser mayor a 0" << endl;
            loan.monto = 0;
        }
    }while (loan.monto <= 0);
}

void addTax(loanStructure &tax)
{
    do
    {
        cout << "Introduzca el porcentaje de impuesto, de un rango de 1 al 100" << endl;
        cin >> tax.interes;
        if (tax.interes < 0 || tax.interes > 100)
        {
            cout << "Introduzca un porcentaje válido, recuerde utilizar solo números" << endl;
            tax.interes = 0;
        }
    }while (tax.interes < 0 || tax.interes > 100);
}

void addDate(loanStructure &date)
{
    do
    {
        cout << "Introduzca el plazo del préstamo en meses, con máximo de 360 meses" << endl;
        cin >> date.plazo;
        if (date.plazo <0 || date.plazo >360)
        {
            cout << "Introduzca un plazo adecuado" << endl;
            date.plazo = 0;
        }
    }while (date.plazo <0 || date.plazo >360);
}

int editLoan()
{
    int selection;
    do
    {
        cout << "1. Editar monto" << endl;
        cout << "2. Editar intereses" << endl;
        cout << "3. Editar plazo" << endl;
        cout << "4. Regresar" << endl;
        cin >> selection;
        if (selection <1 || selection > 4)
        {
            cout << "Seleccione una opción válida";
        }
    }while (selection < 1 || selection > 4);
    return selection;
}

void switchLoan(int selection)
{
    switch (selection)
    {
        case 1:
        cout << "editar monto" << endl;
        break;
        case 2:
        cout << "editar intereses" << endl;
        break;
        case 3:
        cout << "editar plazo" << endl;
        break;
        default:
        break;
    }
}

void changeLoan(loanStructure &loan)
{
    do
    {
        cout << "Introduzca el nuevo monto" << endl;
        cin >> loan.monto;
        if (loan.monto <= 0)
        {
            cout << "Introduzca un monto adecuado, mayor a 0" << endl;
        }
    }while (loan.monto <= 0);
}

void changeTax(loanStructure &tax)
{
    do
    {
        cout << "Introduzca el nuevo porcentaje de impuesto de 1 al 100;" << endl;
        cin >> tax.interes;
        if (tax.interes < 0 || tax.interes > 100)
        {
            cout << "Introduzca un porcentaje adecuado, recuerde solo usar numeros";
        }
    }while (tax.interes < 0 || tax.interes > 100);
}

void changeDate(loanStructure &date)
{
    do
    {
        cout << "Introduzca el nuevo plazo, con máximo de 360" << endl;
        cin >> date.plazo;
        if (date.plazo < 1 || date.plazo > 360)
        {
            cout << "Introduzca un plazo adecuado" << endl;
        }
    }while (date.plazo < 1 || date.plazo > 360);
}

void calculateLoan(loanStructure &mensualPayment, loanStructure &maxPayment, const loanStructure &tax, const loanStructure &loan, const loanStructure &date)
{
    int monthPayment = tax.interes / 12;
    mensualPayment.cuotaMensual = (loan.monto * monthPayment) / (1 - (1 + monthPayment) * pow(1 + monthPayment, -date.plazo));
    maxPayment.cuotaTotal = mensualPayment.cuotaMensual * date.plazo;
    cout << "El monto de la cuota mensual es: " << mensualPayment.cuotaMensual << endl;
    cout << "El monto total de la cuota es: " << maxPayment.cuotaTotal << endl;
}
