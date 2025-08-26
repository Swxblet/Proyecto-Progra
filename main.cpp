#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;

const int MAX_USERS = 5; // cantidad de usuarios

// Declaracion de funciones
int showMenu();
void callFunction(int selection, double monto[], int plazo[], int interes[], double cuotaMensual[], double cuotaTotal[], int cedula[], int &userCount);
void createLoan(double monto[], int plazo[], int interes[], int cedula[], int &userCount);
void addTax(int interes[], int userIndex);
void addDate(int plazo[], int userIndex);
int editLoan();
void switchLoan(int selection, double monto[], int interes[], int plazo[], int userIndex);
void changeLoan(double monto[], int userIndex);
void changeTax(int interes[], int userIndex);
void changeDate(int plazo[], int userIndex);
void calculateLoan(double cuotaMensual[], double cuotaTotal[], const int interes[], const double monto[], const int plazo[], int userIndex);
int deleteLoan();
void switchDelete(int selection, double monto[], int interes[], int plazo[], int cedula[], int userIndex);
int selectUser(const int cedula[], int userCount);

bool cedulaExists(const int cedula[], int userCount, int nuevaCedula);
int findUserIndex(const int cedula[], int userCount, int buscada);

// Funcion principal
int main()
{
    setlocale(LC_ALL, "");

    double monto[MAX_USERS] = {0};
    int plazo[MAX_USERS] = {0};
    int interes[MAX_USERS] = {0};
    double cuotaMensual[MAX_USERS] = {0};
    double cuotaTotal[MAX_USERS] = {0};
    int cedula[MAX_USERS] = {0}; // arreglo de cedulas

    int userCount = 0; // cantidad actual de usuarios registrados

    int option;
    do
    {
        option = showMenu();
        callFunction(option, monto, plazo, interes, cuotaMensual, cuotaTotal, cedula, userCount);
    } while (option != 5);
    return 0;
}

int showMenu()
{
    int selection;
    do
    {
        cout << "1. Registrar prestamo" << endl;
        cout << "2. Editar prestamo" << endl;
        cout << "3. Calcular prestamo" << endl;
        cout << "4. Eliminar prestamo" << endl;
        cout << "5. Salir" << endl;
        while (!(cin >> selection) || selection < 1 || selection > 5)
        {
            cout << "Seleccione una opcion valida" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (selection < 1 || selection > 5);
    return selection;
}

void callFunction(int selection, double monto[], int plazo[], int interes[], double cuotaMensual[], double cuotaTotal[], int cedula[], int &userCount)
{
    switch (selection)
    {
    case 1:
        if (userCount < MAX_USERS)
        {
            createLoan(monto, plazo, interes, cedula, userCount);
            addTax(interes, userCount - 1);
            addDate(plazo, userCount - 1);
        }
        else
        {
            cout << "Se alcanzo el numero maximo de usuarios (" << MAX_USERS << ")" << endl;
        }
        break;
    case 2:
        if (userCount > 0)
        {
            int idx = selectUser(cedula, userCount);
            if (idx != -1)
                switchLoan(editLoan(), monto, interes, plazo, idx);
        }
        else
        {
            cout << "No hay usuarios registrados" << endl;
        }
        break;
    case 3:
        if (userCount > 0)
        {
            int idx = selectUser(cedula, userCount);
            if (idx != -1)
                calculateLoan(cuotaMensual, cuotaTotal, interes, monto, plazo, idx);
        }
        else
        {
            cout << "No hay usuarios registrados" << endl;
        }
        break;
    case 4:
        if (userCount > 0)
        {
            int idx = selectUser(cedula, userCount);
            if (idx != -1)
                switchDelete(deleteLoan(), monto, interes, plazo, cedula, idx);
        }
        else
        {
            cout << "No hay usuarios registrados" << endl;
        }
        break;
    default:
        break;
    }
}

void createLoan(double monto[], int plazo[], int interes[], int cedula[], int &userCount)
{
    int nuevaCedula;
    bool repetida;

    // Pedir cedula y verificar que no exista
    do
    {
        cout << "Introduzca la cedula del usuario" << endl;
        while (!(cin >> nuevaCedula) || nuevaCedula <= 0)
        {
            cout << "Entrada invalida, introduzca una cedula numerica mayor a 0" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        repetida = cedulaExists(cedula, userCount, nuevaCedula);
        if (repetida)
        {
            cout << "Esa cedula ya esta registrada, intente de nuevo" << endl;
        }
    } while (repetida);

    cedula[userCount] = nuevaCedula;

    double nuevoMonto;
    do
    {
        cout << "Introduzca el monto del prestamo" << endl;
        while (!(cin >> nuevoMonto) || nuevoMonto <= 0)
        {
            cout << "Entrada invalida, introduzca un monto adecuado mayor a 0" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (nuevoMonto <= 0);

    monto[userCount] = nuevoMonto;
    plazo[userCount] = 0;
    interes[userCount] = 0;
    userCount++;
}

void addTax(int interes[], int userIndex)
{
    do
    {
        cout << "Introduzca el porcentaje de impuesto, de un rango de 1 al 100" << endl;
        while (!(cin >> interes[userIndex]) || interes[userIndex] < 1 || interes[userIndex] > 100)
        {
            cout << "Entrada invalida, introduzca un valor adecuado" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (interes[userIndex] < 1 || interes[userIndex] > 100);
}

void addDate(int plazo[], int userIndex)
{
    do
    {
        cout << "Introduzca el plazo del prestamo en meses, con maximo de 360 meses" << endl;
        while (!(cin >> plazo[userIndex]) || plazo[userIndex] < 1 || plazo[userIndex] > 360)
        {
            cout << "Introduzca un plazo adecuado, entre 1 y 360" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (plazo[userIndex] < 1 || plazo[userIndex] > 360);
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
        while (!(cin >> selection) || selection < 1 || selection > 4)
        {
            cout << "Seleccione una opcion valida" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (selection < 1 || selection > 4);
    return selection;
}

void switchLoan(int selection, double monto[], int interes[], int plazo[], int userIndex)
{
    switch (selection)
    {
    case 1:
        changeLoan(monto, userIndex);
        break;
    case 2:
        changeTax(interes, userIndex);
        break;
    case 3:
        changeDate(plazo, userIndex);
        break;
    default:
        break;
    }
}

void changeLoan(double monto[], int userIndex)
{
    do
    {
        cout << "Introduzca el nuevo monto" << endl;
        while (!(cin >> monto[userIndex]) || monto[userIndex] <= 0)
        {
            cout << "Entrada invalida, introduzca un monto adecuado mayor a 0" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (monto[userIndex] <= 0);
}

void changeTax(int interes[], int userIndex)
{
    do
    {
        cout << "Introduzca el nuevo porcentaje de impuesto de 1 al 100;" << endl;
        while (!(cin >> interes[userIndex]) || interes[userIndex] < 1 || interes[userIndex] > 100)
        {
            cout << "Entrada invalida, introduzca un valor adecuado" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (interes[userIndex] < 1 || interes[userIndex] > 100);
}

void changeDate(int plazo[], int userIndex)
{
    do
    {
        cout << "Introduzca el nuevo plazo, con maximo de 360" << endl;
        while (!(cin >> plazo[userIndex]) || plazo[userIndex] < 1 || plazo[userIndex] > 360)
        {
            cout << "Introduzca un plazo adecuado, entre 1 y 360" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (plazo[userIndex] < 1 || plazo[userIndex] > 360);
}

void calculateLoan(double cuotaMensual[], double cuotaTotal[], const int interes[], const double monto[], const int plazo[], int userIndex)
{
    double monthRate = (interes[userIndex] / 100.0) / 12;
    cuotaMensual[userIndex] = (monto[userIndex] * monthRate) / (1 - pow(1 + monthRate, -plazo[userIndex]));
    cuotaTotal[userIndex] = cuotaMensual[userIndex] * plazo[userIndex];
    cout << "El monto de la cuota mensual es: " << cuotaMensual[userIndex] << endl;
    cout << "El monto total de la cuota es: " << cuotaTotal[userIndex] << endl;
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
        while (!(cin >> selection) || selection < 1 || selection > 5)
        {
            cout << "Seleccione una opcion valida" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (selection < 1 || selection > 5);
    return selection;
}

void switchDelete(int selection, double monto[], int interes[], int plazo[], int cedula[], int userIndex)
{
    switch (selection)
    {
    case 1:
        monto[userIndex] = 0;
        break;
    case 2:
        interes[userIndex] = 0;
        break;
    case 3:
        plazo[userIndex] = 0;
        break;
    case 4:
        monto[userIndex] = 0;
        interes[userIndex] = 0;
        plazo[userIndex] = 0;
        cedula[userIndex] = 0;
        break;
    default:
        break;
    }
}

int selectUser(const int cedula[], int userCount)
{
    int buscada;
    cout << "Introduzca la cedula del usuario: ";
    while (!(cin >> buscada) || buscada <= 0)
    {
        cout << "Entrada invalida, intente de nuevo: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    int idx = findUserIndex(cedula, userCount, buscada);
    if (idx == -1)
    {
        cout << "No se encontro un usuario con esa cedula" << endl;
    }
    return idx;
}

bool cedulaExists(const int cedula[], int userCount, int nuevaCedula)
{
    for (int i = 0; i < userCount; i++)
    {
        if (cedula[i] == nuevaCedula)
            return true;
    }
    return false;
}

int findUserIndex(const int cedula[], int userCount, int buscada)
{
    for (int i = 0; i < userCount; i++)
    {
        if (cedula[i] == buscada)
            return i;
    }
    return -1;
}