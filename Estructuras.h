#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#define TAM_MEMORIA 4096
#define TAM_KERNEL 1024
#define NUM_ENTRADAS_TABLAPAGINAS 128
#define NUM_REGISTROS 16

// MM
typedef struct MM {
    int *code; // Puntero a la dirección virtual de comienzo del segmento de código.
    int *data; // Puntero a la dirección virtual de comienzo del segmento de datos.
    int *pgb; // Puntero a la dirección física de la correspondiente tabla de páginas.
} MM;

// PCB
typedef struct PCB {
    int pid;
    int estado; // 0: listo, 1: ejecutando, 2: interrumpido(Quantum o expulsado)
    int tiempoEjecucion;
    int prioridad;
    MM mm;
    // campos para salvar el estado de la ejecución
    int PC;
    int registros[NUM_REGISTROS];
} PCB;

// PCBNode
typedef struct PCBNode {
    PCB *pcb;
    struct PCBNode *sig;
} PCBNode;

// Process queue
typedef struct Queue {
    PCBNode *head;
    PCBNode *tail;
    int numProcesos;
    int quantum;
    int prioridad;
} Queue;

// TLB
typedef struct TLB {
    int numeroPagina;
    int marco;
} TLB;

// MMU
typedef struct MMU {
    TLB *TLB;
    int numEntradasTLB;
} MMU;

// Thread
typedef struct Thread{
    PCB *pcb;
    int tid;
    int estado; // 0: ocioso, 1: ejecutando
    int tEjecucion;
    int PC;
    int IR;
    int *PTBR;
    MMU mmu;
    int registros[NUM_REGISTROS];
} Thread;

// Core
typedef struct Core {
    int numThreads;
    Thread *threads;
} Core;

// CPU
typedef struct CPU {
    int numCores;
    Core *cores;
} CPU;

// Machine
typedef struct Machine {
    int numCPUs;
    CPU *cpus;
} Machine;

// Tabla de páginas
typedef struct TablaPaginas {
    int TablaDePaginas[NUM_ENTRADAS_TABLAPAGINAS];
    int numEntradas;
} TablaPaginas;

// Memoria física
// Cada elemento del array simulará una "palabra" de memoria
typedef struct MemoriaFisica {
    int memoria[TAM_MEMORIA];
    int primeraDireccionLibre;
    int primeraDireccionLibreKernel;
} MemoriaFisica;

// Estructura para representar un hueco en la memoria
typedef struct Hueco {
    int direccionInicio; // Dirección de inicio del hueco
    int tamano;          // Tamaño del hueco
} Hueco;

// Nodo de la lista enlazada para los huecos
typedef struct NodoHueco {
    Hueco hueco;
    struct NodoHueco *siguiente;
} NodoHueco;

// Lista enlazada para los huecos
typedef struct ListaHuecos {
    NodoHueco *inicio;
} ListaHuecos;

#endif // ESTRUCTURAS_H

