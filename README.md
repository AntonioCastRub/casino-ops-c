# Casino Ops — Gestión de Máquinas (C, structs, control de flujo)
Proyecto académico para **Método Caso 3 – Programación**. Implementa un sistema de gestión de máquinas de casino usando **registros (struct)**, **arreglos de registros**, **funciones**, **paso por referencia (punteros)** y **sentencias de control** (`if-else`, `for`, `while`, `do-while`). Incluye **uso de funciones predefinidas** (`strncpy`, `strcmp`, `strlen`, `toupper`) y un **modo demo determinista** para evidencias.

---

## Estructura

```
.
├── main.c.c                 # Código fuente principal (C99, sin warnings con -Wall -Wextra)
└── README.md              # Este archivo
```

---

## Compilación y ejecución

### Requisitos
- Compilador C (GCC/Clang) con soporte C99.

### Modo DEMO (genera la misma salida que el pantallazo)
```bash
gcc -std=c99 -Wall -Wextra -O2 -DDEMO_RUN main.c -o casino_ops
./casino_ops
```

### Modo interactivo (menú)
```bash
gcc -std=c99 -Wall -Wextra -O2 main.c -o casino_ops
./casino_ops
```
**Menú**
1. Registrar uso de una máquina (jugadas, ingresos, pérdidas, horas)  
2. Listar máquinas  
3. KPIs (ganancia neta total, mejor máquina y ganancia media/jugada)  
0. Salir

---

## Modelo de datos (registro `Machine`)

```c
typedef struct {
    int   id;
    char  name[40];
    int   plays;
    float earnings;
    float losses;
    float hoursUsed;
    int   usageFrequency;
    int   active;           // 1=activa, 0=inactiva
} Machine;
```

- **Arreglo de registros**: `Machine machines[MAX_MACHINES];`
- **Inicialización**: `initMachine(&machines[i], id, "Nombre");`
- **Acceso a miembros**: `machines[i].plays` (punto) y `m->plays` (puntero con flecha).

---

## Puntos clave del diseño

- **Paso por referencia** con punteros para actualizar directamente elementos del arreglo (`registerUsage`).
- **Validaciones** y mensajes en `if-else` (alertas de uso/beneficio).
- **Recorridos** con `for` (listado), `while` (agregados/KPIs) y `do-while` (bucle del menú).
- **Funciones estándar**: normalización y comparación de cadenas (`toupper`, `strlen`, `strcmp`), copia segura (`strncpy`).

---

## Salida esperada (DEMO_RUN)

```
Listado de máquinas
----------------------------------------------------------------------------------
ID  | Nombre       | Juegos | Ingresos   | Pérdidas  | Horas   | Freq
----------------------------------------------------------------------------------
1   | Tragamonedas1| 2000   |    6800.75 |  4100.50  |   140.00 | 2
2   | Ruleta       | 200    |    7500.40 |  4520.25  |    50.00 | 1
3   | Tragamonedas2| 800    |    6200.50 |  3200.75  |   130.00 | 1

KPIs
----------------------------------------------------------------------------------
Ganancia neta total: 9680.15
Mejor máquina (neto): Ruleta (2980.15)
Ganancia media por jugada de Ruleta: 14.9008
```

---

## Criterios de evaluación — Cómo se cubren

- **Claridad y profundidad**: código comentado, funciones separadas, KPIs.
- **Justificación técnica**: structs para cohesión/contigüidad; punteros para eficiencia.
- **Teoría aplicada**: métodos mixtos (ver informe), control de flujo, librería estándar.
- **Presentación**: README + evidencia + flags de compilación sin warnings.
- **Creatividad**: KPIs listos; fácil extender a reportes/CSV/ordenamientos por neto.

---

## Referencias (APA7)

- cppreference. (2024). *Struct declaration (C).* https://en.cppreference.com/w/c/language/struct  
- cppreference. (2023). *Member access operators (C).* https://en.cppreference.com/w/c/language/operator_member_access  
- cppreference. (2024). *Pointers (C): indirection & pass-by-reference semantics.* https://en.cppreference.com/w/c/language/pointer  
- Linode Docs. (2022). *Understanding Data Structures: Definition, Uses & Benefits.* https://www.linode.com/docs/guides/data-structure/  
- Creswell, J. W. (2009). *Research Design: Qualitative, Quantitative, and Mixed Methods Approaches* (3rd ed.). SAGE.  
- Creswell, J. W., & Plano Clark, V. L. (2018). *Designing and Conducting Mixed Methods Research* (3rd ed.). SAGE.
