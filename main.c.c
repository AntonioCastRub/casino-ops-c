
/*
 * Proyecto: Casino Ops - Gestión de máquinas con registros (struct) en C
 * Archivo:  main.c.c
 * Compila:  gcc -std=c99 -Wall -Wextra -O2 main.c -o casino_ops
 * Ejecución (demo determinista para el informe):
 *           gcc -std=c99 -Wall -Wextra -O2 -DDEMO_RUN main.c -o casino_ops && ./casino_ops
 *
 * Características:
 * - Uso de tipos de datos estructurados (registros/struct) y arreglos de registros.
 * - Declaración de variables y constantes.
 * - Sentencias de control: if-else, for, while, do-while.
 * - Funciones con paso de parámetros por referencia (punteros).
 * - Uso de funciones predefinidas de la biblioteca estándar: strlen, strcmp, strncpy, toupper.
 * - Documentado y comentado para evaluación académica.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_MACHINES 10
#define NAME_LEN     40

/* -------------------------------
 * Definición del registro Machine
 * ------------------------------- */
typedef struct {
    int   id;
    char  name[NAME_LEN];
    int   plays;            // Número de jugadas
    float earnings;         // Ingresos
    float losses;           // Pérdidas
    float hoursUsed;        // Tiempo de uso (horas)
    int   usageFrequency;   // Veces que se usó
    int   active;           // 1=activa, 0=inactiva
} Machine;

/* -------------------------------
 * Firmas de funciones
 * ------------------------------- */
void initMachine(Machine *m, int id, const char *name);
int  findMachineIndex(const Machine machines[], int size, const char *name);
void registerUsage(Machine machines[], int size, const char *name,
                   int plays, float earnings, float losses, float hours);
float avgEarningsPerPlay(const Machine *m);
void toUpperInline(char *s);
void displayAll(const Machine machines[], int size);
void displayKPIs(const Machine machines[], int size);

/* -------------------------------
 * Implementaciones
 * ------------------------------- */

void initMachine(Machine *m, int id, const char *name) {
    if (!m) return;
    m->id = id;
    // Uso de strncpy (función predefinida); garantizamos terminación nula
    strncpy(m->name, name, NAME_LEN - 1);
    m->name[NAME_LEN - 1] = '\0';
    m->plays = 0;
    m->earnings = 0.0f;
    m->losses = 0.0f;
    m->hoursUsed = 0.0f;
    m->usageFrequency = 0;
    m->active = 1;
}

int findMachineIndex(const Machine machines[], int size, const char *name) {
    for (int i = 0; i < size; i++) {
        if (machines[i].active && strcmp(machines[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void registerUsage(Machine machines[], int size, const char *name,
                   int plays, float earnings, float losses, float hours) {
    int idx = findMachineIndex(machines, size, name);
    if (idx < 0) {
        printf("Aviso: máquina \"%s\" no encontrada.\n", name);
        return;
    }
    // Paso por referencia: modificamos el registro original vía el arreglo
    Machine *m = &machines[idx];
    m->plays          += plays;
    m->earnings       += earnings;
    m->losses         += losses;
    m->hoursUsed      += hours;
    m->usageFrequency += 1;

    // Ejemplo de if-else (alertas simples de operación)
    if (avgEarningsPerPlay(m) < 0.0f) {
        printf("Alerta: %s con ganancia media negativa.\n", m->name);
    } else if (m->hoursUsed > 200.0f) {
        printf("Info: %s supera 200h de uso acumulado.\n", m->name);
    }
}

float avgEarningsPerPlay(const Machine *m) {
    if (!m || m->plays == 0) return 0.0f;
    return (m->earnings - m->losses) / (float)m->plays;
}

void toUpperInline(char *s) {
    // Uso de toupper (función predefinida) para normalizar cadenas
    for (size_t i = 0; s && i < strlen(s); i++) {
        s[i] = (char)toupper((unsigned char)s[i]);
    }
}

void displayAll(const Machine machines[], int size) {
    printf("\nListado de máquinas\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("%-3s | %-12s | %-6s | %-10s | %-9s | %-8s | %-4s\n",
           "ID", "Nombre", "Juegos", "Ingresos", "Pérdidas", "Horas", "Freq");
    printf("----------------------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        if (!machines[i].active) continue;
        printf("%-3d | %-12s | %-6d | %10.2f | %9.2f | %8.2f | %-4d\n",
               machines[i].id, machines[i].name, machines[i].plays,
               machines[i].earnings, machines[i].losses,
               machines[i].hoursUsed, machines[i].usageFrequency);
    }
}

void displayKPIs(const Machine machines[], int size) {
    int i = 0;
    float totalNet = 0.0f;
    float bestNet = -1e9f;
    int   idxBest = -1;

    // while: acumulados y mejor desempeño neto
    while (i < size) {
        if (machines[i].active) {
            float net = machines[i].earnings - machines[i].losses;
            totalNet += net;
            if (net > bestNet) { bestNet = net; idxBest = i; }
        }
        i++;
    }

    printf("\nKPIs\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Ganancia neta total: %.2f\n", totalNet);
    if (idxBest >= 0) {
        printf("Mejor máquina (neto): %s (%.2f)\n", machines[idxBest].name, bestNet);
        printf("Ganancia media por jugada de %s: %.4f\n",
               machines[idxBest].name, avgEarningsPerPlay(&machines[idxBest]));
    }
}

/* -------------------------------
 * main con menú (interactivo) y DEMO_RUN (determinista)
 * ------------------------------- */
int main(void) {
    Machine machines[MAX_MACHINES];
    int count = 3;

    // Inicialización con arreglo de registros (evidencia de la P2)
    initMachine(&machines[0], 1, "Tragamonedas1");
    initMachine(&machines[1], 2, "Ruleta");
    initMachine(&machines[2], 3, "Tragamonedas2");
    for (int i = 3; i < MAX_MACHINES; ++i) {
        machines[i].active = 0;
    }

#ifdef DEMO_RUN
    // Simulación determinista (para evidencia y pruebas automáticas)
    registerUsage(machines, MAX_MACHINES, "Tragamonedas1", 1500, 5000.75f, 3200.50f, 120.0f);
    registerUsage(machines, MAX_MACHINES, "Ruleta",         200,  7500.40f, 4520.25f,  50.0f);
    registerUsage(machines, MAX_MACHINES, "Tragamonedas2",  800,  6200.50f, 3200.75f, 130.0f);
    registerUsage(machines, MAX_MACHINES, "Tragamonedas1",  500,  1800.00f,  900.00f,  20.0f);

    displayAll(machines, count);
    displayKPIs(machines, count);
    printf("\n(Ejecución demo finalizada)\n");
    return 0;
#else
    int option;
    do {
        printf("\n=== Casino Ops ===\n");
        printf("1) Registrar uso\n");
        printf("2) Listar máquinas\n");
        printf("3) KPIs\n");
        printf("0) Salir\n");
        printf("Opción: ");
        if (scanf("%d", &option) != 1) {
            // Limpieza de entrada
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            option = -1;
        }

        if (option == 1) {
            char name[NAME_LEN];
            int plays;
            float earn, loss, hours;
            printf("Nombre exacto de la máquina (Tragamonedas1/Ruleta/...): ");
            scanf("%39s", name);
            printf("Jugadas, Ingresos, Pérdidas, Horas: ");
            if (scanf("%d %f %f %f", &plays, &earn, &loss, &hours) == 4) {
                registerUsage(machines, MAX_MACHINES, name, plays, earn, loss, hours);
            } else {
                printf("Entrada inválida.\n");
            }
        } else if (option == 2) {
            displayAll(machines, count);
        } else if (option == 3) {
            displayKPIs(machines, count);
        } else if (option == 0) {
            // do-while se encarga de salir
        } else {
            printf("Opción no válida.\n");
        }
    } while (option != 0);
    printf("Hasta pronto.\n");
    return 0;
#endif
}
