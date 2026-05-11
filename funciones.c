#include <stdio.h>
#include <string.h>
#include "funciones.h"

void registrarlimites(float *tiempolim, int *recursoslim){
    printf("Ingrese la cantidad de tiempo disponible (horas): ");
    *tiempolim = validarFloatConRango(0, 1000000000);
    printf("Ingrese la cantidad de recursos disponibles: ");
    *recursoslim = validarenterosconrango(0, 10000000);
}

//Busca el primer espacio con estado 0 para registrar
void registrarproductos(char nombres[5][30], float *tiempo, int *recursos, int *demanda, int *estado){
    int indice = -1;
    for(int i = 0; i < 5; i++){
        /*si el espacio i es == 0 entonces indice de -1 a i, o sea, se ocupa el espacio disponible*/
        if(estado[i] == 0){
            indice = i;
            break;
        }
    }

    if(indice != -1){
        printf("Ingrese el nombre del producto: ");
        leerCadena(nombres[indice], 30);
        printf("Ingrese el tiempo que toma elaborar el producto: ");
        *(tiempo + indice) = validarFloatConRango(0, 150);
        printf("Ingrese la cantidad de recursos que toma elaborar el producto: ");
        *(recursos + indice) = validarenterosconrango(0, 150);
        printf("Ingrese la demanda del producto: ");
        *(demanda + indice) = validarenterosconrango(0, 150);
        estado[indice] = 1;
        printf("Producto registrado con exito en la posicion %d.\n", indice + 1);
    } else {
        printf("No hay espacio disponible para mas productos (Maximo 5).\n");
    }
}

void verdatos(char nombres[5][30], float *tiempo, int *recursos, int *demanda, float *tiempot, int *recursost, float *tiempolim, int *recursoslim, int *estado){

    /*Ver datos*/
    printf("#\t\tNombre\t\tTiempo\t\tRecursos\tDemanda\t\tTiempo(demanda)\t\tRecursos(demanda)\n");
    float tiempototal = 0;
    int recursostotal = 0;

    
    for (int i = 0; i < 5; i++)
    {
        /*Solo procesar si el estado es 1*/
        if (estado[i] == 1) 
        {
            /*Calcular tiempo y recursos segun la demanda*/
            *(tiempot + i) = *(tiempo + i) * *(demanda + i);;
            //tiempot[i] = tiempo[i] * demanda[i];
            *(recursost + i) = *(recursos + i) * *(demanda + i);
            //recursost[i] = recursos[i] * demanda[i];
            
            /*Imprimir la tabla*/
            printf("%d\t\t%s\t\t%.2f\t\t%d\t\t%d\t\t%.2f\t\t\t%d\n", i + 1, nombres[i], *(tiempo + i), *(recursos + i), *(demanda + i), *(tiempot + i), *(recursost + i));
            
            /* Acumular totales SOLO de los productos activos   */
            tiempototal = tiempototal + *(tiempot + i);
            recursostotal = recursostotal + *(recursost + i);
        }
    }
    
    printf("\n");
    printf("Tiempo necesario total de la fabrica: %.2f\n", tiempototal);
    printf("Recursos necesarios total de la fabrica: %d\n", recursostotal);
    printf("-----------------------------------------------------\n");
    printf("Tiempo disponible: %.2f\n", *tiempolim);
    printf("Recursos disponibles: %d\n", *recursoslim);
    printf("-----------------------------------------------------\n");

    /*Verificar si el tiempo y recursos definidos son menores a los disponibles*/
    if(*tiempolim < tiempototal){
        printf("El tiempo requerido es mayor al tiempo disponible\n");
    }
    if (*recursoslim < recursostotal){
        printf("Los recursos requeridos son mayores a los recursos disponibles\n");
    } 
}

void eliminarProducto(char nombres[5][30], int *estado) {
    char nombreBuscado[30];
    int indiceEncontrado = -1; 
    printf("Ingrese el nombre del producto a eliminar: ");
    leerCadena(nombreBuscado, 30);
 
    /*Encontrar nombres*/
    for(int i = 0; i < 5; i++) {
        if(*(estado + i) == 1) { 
            if(strcmp(nombres[i], nombreBuscado) == 0) { /*Si son exactamente iguales strcmp devuelve 0*/
                indiceEncontrado = i; /*se guarda la posicion a elminar*/
                break;
            }
        }
    }
    if(indiceEncontrado != -1) { 
        *(estado + indiceEncontrado) = 0; /*ya no ocupa 1, ahora ocupa 0. Eso significa que no está activo ni se tomará en cuenta*/
        printf("\nEl producto '%s' ha sido eliminado con exito.", nombreBuscado);
    } else {
        printf("\nNo se encuentra el producto: '%s'.", nombreBuscado);
    }
}

void editarProducto(char nombres[5][30], float *tiempo, int *recursos, int *demanda, int *estado){
    char nombreBuscado[30];
    int indiceEncontrado = -1;

    /*Encontrar nombres*/
    printf("Ingrese el nombre del producto que quiere editar: ");
    leerCadena(nombreBuscado, 30);

    for(int i = 0; i < 5; i++){
        if(estado[i] == 1){
            if(strcmp(nombres[i], nombreBuscado) == 0){
                indiceEncontrado = i;
                break;
            }
        }
    }

    /*repetir el registro pero con el nuevo indice*/
    if(indiceEncontrado != -1){
        printf("Ingrese el nuevo nombre: ");
        leerCadena(nombres[indiceEncontrado], 30);
        printf("Ingrese el nuevo tiempo: ");
        tiempo[indiceEncontrado] = validarFloatConRango(0, 150);
        printf("Ingrese la nueva cantidad de recursos: ");
        recursos[indiceEncontrado] = validarenterosconrango(0, 150);
        printf("Ingrese la nueva demanda: ");
        demanda[indiceEncontrado] = validarenterosconrango(0, 150);
        printf("\nProducto editado correctamente.\n");
    } else {
        printf("\nNo se encontro el producto '%s'.", nombreBuscado);
    }
}

/*FUNCIONES GENERALEEEEEEEEEEEEEES*/

void leerCadena(char *cadena, int n){
    int len;
    fgets(cadena, n, stdin);
    len = strlen(cadena) - 1;
    if (cadena[len] == '\n') {
        cadena[len] = '\0';
    }
}

int menu(){
    int opc = 0;
    printf("\nSeleccione una opcion\n");
    printf("1.Definir recursos y tiempo limites\n");
    printf("2.Registrar producto\n");
    printf("3.Ver datos\n");
    printf("4.Editar un producto\n");
    printf("5.Eliminar un producto\n");
    printf(">> ");
    opc = validarenterosconrango(1, 5);
    return opc;
}

int validarenterosconrango(int a, int b){
    int aux;
    int num;
    do {
        aux = scanf("%d", &num);
        while (getchar() != '\n'); // Limpia el buffer para evitar bucles infinitos
        if (aux != 1 || num < a || num > b){
            printf("El valor ingresado es incorrecto. Ingrese nuevamente: ");
        }
    } while (aux != 1 || num < a || num > b);
    return num;
}

float validarFloatConRango(float a, float b){
    int aux;
    float num;
    do {
        aux = scanf("%f", &num);
        while (getchar() != '\n'); // Limpia el buffer
        if (aux != 1 || num < a || num > b){
            printf("El valor ingresado es incorrecto. Ingrese nuevamente: ");
        }
    } while (aux != 1 || num < a || num > b);
    return num;
}
