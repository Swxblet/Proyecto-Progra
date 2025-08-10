#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;

//Definición de struct
struct loanStructure
{
    double monto;
    int plazo;
    int interes;
    double cuotaMensual;
    double cuotaTotal;
};

//Declaración de funciones
int showMenu();
void callFunction(int selection, loanStructure &loan);
void createLoan(loanStructure &loan);
void addTax(loanStructure &tax);
void addDate(loanStructure &date);
int editLoan();
void switchLoan(int selection, loanStructure &loan, loanStructure &tax, loanStructure &date);
void changeLoan(loanStructure &loan);
void changeTax(loanStructure &tax);
void changeDate(loanStructure &date);
void calculateLoan(loanStructure &mensualPayment, loanStructure &maxPayment, const loanStructure &tax, const loanStructure &loan, const loanStructure &date);
int deleteLoan();
void switchDelete(int selection, loanStructure &loan, loanStructure &tax, loanStructure &date);

//Función principal
int main()
{
    //Se utiliza setlocale para importar la configuración de la computadora, así se utilizan tildes y ñ
    setlocale(LC_ALL, "");
    loanStructure loan{};
    int option;
    do
    {
        option = showMenu();
        callFunction(option, loan);
    }while (option != 5);
    return 0;
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
        cout << "5. Salir" << endl;
        cin >> selection;
        if (selection < 1 || selection > 5)
        {
            cout << "Opción inválida, por favor seleccione una opción de la lista." << endl;
        }
    }while (selection < 1 || selection > 5);
    return selection;
}

//Función para llamar todas las demás funciones
void callFunction(int selection, loanStructure &loan)
{
    switch (selection)
    {
        case 1:
        createLoan(loan);
        addTax(loan);
        addDate(loan);
        break;
        case 2:
        switchLoan(editLoan(), loan, loan, loan);
        break;
        case 3:
        calculateLoan(loan, loan, loan, loan, loan);
        break;
        case 4:
        switchDelete(deleteLoan(), loan, loan, loan);
        break;
        default:
        break;
    }
}

//Función para crear un préstamo
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

//Función para definir los intereses
void addTax(loanStructure &tax)
{
    do
    {
        cout << "Introduzca el porcentaje de impuesto, de un rango de 1 al 100" << endl;
        cin >> tax.interes;
        if (tax.interes < 1 || tax.interes > 100)
        {
            cout << "Introduzca un porcentaje válido, recuerde utilizar solo números" << endl;
            tax.interes = 0;
        }
    }while (tax.interes < 1 || tax.interes > 100);
}

//Función para definir la fecha
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

//Función para editar los distintos valores
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

void switchLoan(int selection, loanStructure &loan, loanStructure &tax, loanStructure &date)
{
    switch (selection)
    {
        case 1:
        changeLoan(loan);
        break;
        case 2:
        changeTax(tax);
        break;
        case 3:
        changeDate(date);
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
        if (tax.interes < 1 || tax.interes > 100)
        {
            cout << "Introduzca un porcentaje adecuado, recuerde solo usar números";
        }
    }while (tax.interes < 1 || tax.interes > 100);
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

int deleteLoan()
{
    int selection;
    do
    {
        cout << "1. Eliminar monto" << endl;
        cout << "2. Eliminar intereses" << endl;
        cout << "3. Eliminar plazo" << endl;
        cout << "4. Eliminar todo" << endl;
        cout << "5. Salir" << endl;
        cin >> selection;
        if (selection < 1 || selection > 5)
        {
            cout << "Seleccione una opción válida";
        }
    }while (selection < 1 || selection > 5);
    return selection;
}

void switchDelete(int selection, loanStructure &loan, loanStructure &tax, loanStructure &date)
{
    switch (selection)
    {
        case 1:
        loan.monto = 0;
        break;
        case 2:
        tax.interes = 0;
        break;
        case 3:
        date.plazo = 0;
        break;
        case 4:
        loan.monto = 0;
        tax.interes = 0;
        date.plazo = 0;
        break;
        default:
        break;
    }
}