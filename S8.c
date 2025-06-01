#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTOS 5

typedef struct {
    char nombre[30];
    int cantidad;
    float tiempo;
    float recursos;
} Producto;

Producto productos[MAX_PRODUCTOS];
int total_productos = 0;

int validarpositivo(const char *mensaje) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        if (valor < 0) {
            printf("No se puede ingresar numeros negativos\n");
        }
    } while (valor < 0);
    return valor;
}

float validarpositivofloat(const char *mensaje) {
    float valor;
    do {
        printf("%s", mensaje);
        scanf("%f", &valor);
        if (valor < 0) {
            printf("No se puede ingresar numeros negativos\n");
        }
    } while (valor < 0);
    return valor;
}

int buscarProducto(char nombre[]) {
    for (int i = 0; i < total_productos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

void pausar() {
    printf("Presione eenter para continuar\n");
    getchar();
    getchar();
}

void agregarProducto() {
    if (total_productos >= MAX_PRODUCTOS) {
        printf("Ya se alcanzo el maximo, no se puede agregar mas productos\n");
        pausar();
        return;
    }

    printf("\nIngreso de producto %d:\n", total_productos + 1);
    printf("Nombre: ");
    scanf("%s", productos[total_productos].nombre);

    productos[total_productos].cantidad = validarpositivo("Cantidad demandada: ");
    productos[total_productos].tiempo = validarpositivofloat("Tiempo por unidad en horas: ");
    productos[total_productos].recursos = validarpositivofloat("Recursos por unidad: ");

    total_productos++;
    printf("El producto se agrego con exito\n");
    pausar();
}

void editarProducto() {
    char nombre[30];
    printf("Ingrese el nombre del producto que se va a editar: ");
    scanf("%s", nombre);

    int indice = buscarProducto(nombre);
    if (indice == -1) {
        printf("Producto no encontrado\n");
        pausar();
        return;
    }

    printf("Editando producto: %s\n", productos[indice].nombre);

    printf("Nuevo nombre: ");
    scanf("%s", productos[indice].nombre);
    productos[indice].cantidad = validarpositivo("Nueva cantidad demandada: ");
    productos[indice].tiempo = validarpositivofloat("Nuevo tiempo por unidad: ");
    productos[indice].recursos = validarpositivofloat("Nuevos recursos por unidad: ");

    printf("El producto se edito con exito\n");
    pausar();
}

void eliminarProducto() {
    char nombre[30];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombre);

    int indice = buscarProducto(nombre);
    if (indice == -1) {
        printf("Producto no encontrado\n");
        pausar();
        return;
    }

    for (int i = indice; i < total_productos - 1; i++) {
        productos[i] = productos[i + 1];
    }
    total_productos--;
    printf("El producto se elimino con exito\n");
    pausar();
}

void calcularYVerificar() {
    float tiempo_total = 0, recursos_totales = 0;
    for (int i = 0; i < total_productos; i++) {
        tiempo_total += productos[i].cantidad * productos[i].tiempo;
        recursos_totales += productos[i].cantidad * productos[i].recursos;
    }

    printf("\nTiempo total requerido: %.2f horas\n", tiempo_total);
    printf("Recursos totales requeridos: %.2f unidades\n", recursos_totales);

    float tiempo_disponible = validarpositivofloat("Ingrese el tiempo total disponible en horas: ");
    float recursos_disponibles = validarpositivofloat("Ingrese la cantidad total de recursos disponibles: ");

    if (tiempo_total <= tiempo_disponible && recursos_totales <= recursos_disponibles) {
        printf("La fabrica AleMati SI puede cumplir con la demanda\n");
    } else {
        printf("La fabrica AleMati NO puede cumplir con la demanda\n");
        if (tiempo_total > tiempo_disponible)
            printf("Hay tiempo insuficiente\n");
        if (recursos_totales > recursos_disponibles)
            printf("Hay recursos insuficientes\n");
    }
    pausar();
}

void mostrarProductos() {
    if (total_productos == 0) {
        printf("No hay productos ingresados\n");
        pausar();
        return;
    }

    printf("\nLista de productos:\n");
    for (int i = 0; i < total_productos; i++) {
        printf("%s - Cantidad: %d - Tiempo/unidad: %.2f - Recursos/unidad: %.2f\n",
            productos[i].nombre,
            productos[i].cantidad,
            productos[i].tiempo,
            productos[i].recursos);
    }
    pausar();
}

void menu() {
    int opcion;
    do {
        printf("\n-          MENU PRINCIPAL          -\n");
        printf("1. Ingresar nuevo producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar productos\n");
        printf("5. Calcular tiempo, recursos y verificar cumplimiento\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: 
                agregarProducto(); 
            break;
            case 2: 
                editarProducto(); 
            break;
            case 3: 
                eliminarProducto(); 
            break;
            case 4: 
                mostrarProductos(); 
            break;
            case 5: 
                calcularYVerificar(); 
            break;
            case 0: 
                printf("Saliendo del programa\n"); 
            break;
            default: 
                printf("Opcion no valida\n"); 
                pausar(); 
            break;
        }
    } while (opcion != 0);
}

int main() {
    printf("Electronica AleMati\n");
    menu();
    return 0;
}
