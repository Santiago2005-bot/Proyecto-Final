#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

// Lee un numero y lo repite hasta que este dentro del rango
double leer(string mensaje, double minimo, double maximo) {
    double valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= minimo && valor <= maximo) return valor;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Dato invalido, intente de nuevo." << endl;
    }
}

void linea(string texto) {
    cout << "  - " << texto << endl;
}

void evaluar() {
    string nombre;
    cout << "\nNombre del paciente: ";
    getline(cin, nombre);

    int edad = (int)leer("Edad (1 - 110): ", 1, 110);
    double alturaCm = leer("Altura en cm (50 - 250): ", 50, 250);
    double peso = leer("Peso en kg (2 - 300): ", 2, 300);

    double h = alturaCm / 100;
    double imc = peso / (h * h);
    double pesoMin = 18.5 * h * h;     // limite inferior del peso saludable
    double pesoMax = 24.9 * h * h;     // limite superior del peso saludable

    cout << fixed << setprecision(1);
    cout << "\n========== INFORME DE SALUD ==========" << endl;
    cout << "Paciente: " << nombre << " (" << edad << " anios)" << endl;
    cout << "Altura: " << alturaCm << " cm   Peso: " << peso << " kg" << endl;
    cout << "IMC: " << imc << endl;
    cout << "Peso saludable para su altura: " << pesoMin << " a " << pesoMax << " kg" << endl;

    if (edad < 18) {
        cout << "\nEn menores de 18 anios el IMC se interpreta con curvas de" << endl;
        cout << "crecimiento (percentiles). Consulte a su pediatra." << endl;
        return;
    }

    string categoria;
    bool buenaSalud = false;
    if (imc < 18.5) categoria = "Bajo peso";
    else if (imc < 25) { categoria = "Peso normal"; buenaSalud = true; }
    else if (imc < 30) categoria = "Sobrepeso";
    else categoria = "Obesidad";

    cout << "Clasificacion: " << categoria << endl;
    if (buenaSalud) cout << "ESTADO: se encuentra en buen estado segun su IMC." << endl;
    else cout << "ESTADO: necesita mejorar. Siga las recomendaciones." << endl;

    cout << "\n--- DIETA ---" << endl;
    if (imc < 18.5) {
        linea("Haga 5 comidas al dia y no se salte ninguna.");
        linea("Incluya frutos secos, aguacate, legumbres, huevos, lacteos y cereales integrales.");
        linea("Agregue una fuente de proteina en cada comida.");
    } else if (buenaSalud) {
        linea("Mantenga una dieta equilibrada: verduras, frutas, proteinas y cereales integrales.");
        linea("Tome agua durante el dia y limite los dulces y las frituras.");
    } else {
        linea("Llene la mitad del plato con verduras y frutas.");
        linea("Reduzca bebidas azucaradas, ultraprocesados, frituras y dulces.");
        linea("Cuide las porciones y prefiera proteinas magras (pollo, pescado, legumbres).");
        if (imc >= 30) linea("Busque a un nutricionista y evite las dietas extremas.");
    }

    cout << "\n--- EJERCICIOS ---" << endl;
    if (imc < 18.5) {
        linea("Fuerza 3 dias por semana, 30 a 40 min: sentadillas, flexiones, remo con banda y plancha.");
        linea("Caminata ligera de 20 min, 2 dias por semana.");
    } else if (buenaSalud) {
        linea("150 min por semana de actividad moderada (caminata rapida, bicicleta, natacion).");
        linea("Fuerza 2 dias por semana, 20 a 30 min.");
    } else if (imc < 30) {
        linea("Caminata rapida, bicicleta o natacion: 30 a 45 min, 5 dias por semana.");
        linea("Fuerza 2 dias por semana, 20 a 30 min.");
    } else {
        linea("Consulte a su medico antes de empezar.");
        linea("Comience con caminatas de 20 a 30 min, 5 dias por semana, y suba 5 min cada semana.");
        linea("Alterne con natacion o bicicleta estatica (bajo impacto) y fuerza suave 2 dias por semana.");
    }
    if (edad >= 65) linea("Agregue ejercicios de equilibrio 3 dias por semana (por ejemplo, pararse en un pie con apoyo).");

    cout << "\n--- TIEMPO Y METAS ---" << endl;
    if (imc < 18.5) {
        double dif = pesoMin - peso;
        cout << "  - Le faltan unos " << dif << " kg para el rango saludable." << endl;
        cout << "  - A 0.25 - 0.5 kg por semana: entre " << (int)ceil(dif / 0.5) << " y " << (int)ceil(dif / 0.25) << " semanas." << endl;
    } else if (buenaSalud) {
        linea("Objetivo: mantener su peso y completar 150 min de actividad por semana.");
    } else {
        double dif = peso - pesoMax;
        cout << "  - Primera meta: bajar entre " << peso * 0.05 << " y " << peso * 0.10 << " kg (5% a 10%) en 3 a 6 meses." << endl;
        cout << "  - Para llegar al rango saludable faltan unos " << dif << " kg." << endl;
        cout << "  - A 0.5 - 1 kg por semana: entre " << (int)ceil(dif) << " y " << (int)ceil(dif / 0.5) << " semanas." << endl;
    }

    cout << "\n--- HABITOS ---" << endl;
    linea("Duerma de 7 a 9 horas y tome agua durante el dia.");
    linea("Evite el tabaco y limite el alcohol.");
    linea("Haga una pausa activa cada hora si trabaja sentado.");
    linea("Hagase un chequeo medico una vez al anio.");

    cout << "\nNota: esta evaluacion usa solo el IMC y no reemplaza una consulta medica." << endl;
}

int main() {
    char otra;
    cout << "=== CONSULTA DE SALUD ===" << endl;
    do {
        evaluar();
        cout << "\nEvaluar otro paciente? (s/n): ";
        cin >> otra;
        cin.ignore(1000, '\n');
    } while (otra == 's' || otra == 'S');

    cout << "Hasta luego!" << endl;
    return 0;
}