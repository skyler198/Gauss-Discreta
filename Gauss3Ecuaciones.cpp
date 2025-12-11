#include <iostream>
#include <iomanip>
using namespace std;

void imprimirMatriz(double A[3][4]) {
    cout << fixed << setprecision(2);
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 4; j++) {
            cout << setw(8) << A[i][j] << " ";
        }
        cout << "|\n";
    }
    cout << "\n";
}

int main() {
    double A[3][4];

    cout << "Ingrese los coeficientes del sistema Ax + By + Cz = D\n";
    for (int i = 0; i < 3; i++) {
        cout << "Ecuacion " << i + 1 << " (A B C D): ";
        cin >> A[i][0] >> A[i][1] >> A[i][2] >> A[i][3];
    }

    cout << "\nMatriz inicial:\n";
    imprimirMatriz(A);

    // --- Paso 1: Hacer A[0][0] = 1
    if (A[0][0] != 0) {
        double p = A[0][0];
        cout << "R1 = R1 / " << p << "\n";
        for (int j = 0; j < 4; j++) A[0][j] /= p;
        imprimirMatriz(A);
    }

    // --- Paso 2: Eliminar debajo de la columna 0
    for (int i = 1; i < 3; i++) {
        if (A[i][0] != 0) {
            double p = A[i][0];
            cout << "R" << i+1 << " = R" << i+1 << " - (" << p << ") * R1\n";
            for (int j = 0; j < 4; j++)
                A[i][j] -= p * A[0][j];
            imprimirMatriz(A);
        }
    }

    // --- Paso 3: Hacer A[1][1] = 1
    if (A[1][1] != 0) {
        double p = A[1][1];
        cout << "R2 = R2 / " << p << "\n";
        for (int j = 0; j < 4; j++) A[1][j] /= p;
        imprimirMatriz(A);
    }

    // --- Paso 4: Eliminar arriba y abajo de la columna 1
    for (int i = 0; i < 3; i++) {
        if (i != 1 && A[i][1] != 0) {
            double p = A[i][1];
            cout << "R" << i+1 << " = R" << i+1 << " - (" << p << ") * R2\n";
            for (int j = 0; j < 4; j++)
                A[i][j] -= p * A[1][j];
            imprimirMatriz(A);
        }
    }

    // --- Paso 5: Hacer A[2][2] = 1
    if (A[2][2] != 0) {
        double p = A[2][2];
        cout << "R3 = R3 / " << p << "\n";
        for (int j = 0; j < 4; j++) A[2][j] /= p;
        imprimirMatriz(A);
    }

    // --- Paso 6: Eliminar arriba en columna 2
    for (int i = 0; i < 2; i++) {
        if (A[i][2] != 0) {
            double p = A[i][2];
            cout << "R" << i+1 << " = R" << i+1 << " - (" << p << ") * R3\n";
            for (int j = 0; j < 4; j++)
                A[i][j] -= p * A[2][j];
            imprimirMatriz(A);
        }
    }

    // --- Analizar resultados ---
    bool sinSol = false, infinitas = false;

    for (int i = 0; i < 3; i++) {
        // 0 0 0 | D  → sin solución si D != 0
        if (A[i][0] == 0 && A[i][1] == 0 && A[i][2] == 0 && A[i][3] != 0)
            sinSol = true;

        // 0 0 0 | 0  → fila redundante → posiblemente infinitas soluciones
        if (A[i][0] == 0 && A[i][1] == 0 && A[i][2] == 0 && A[i][3] == 0)
            infinitas = true;
    }

    if (sinSol) {
        cout << "El sistema NO TIENE SOLUCION.\n";
        return 0;
    }

    if (infinitas) {
        cout << "El sistema tiene INFINITAS SOLUCIONES.\n";
        return 0;
    }

    // --- Solución única ---
    cout << "Solucion unica:\n";
    cout << "x = " << A[0][3] << "\n";
    cout << "y = " << A[1][3] << "\n";
    cout << "z = " << A[2][3] << "\n";

    return 0;
}
