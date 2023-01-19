/*
    Jorge Eduardo Estrada Reza
    2183078946
    Algoritmos y Estructura de Datos
    Examen Global
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Estructura de Alumno
struct alumno
{
    int matricula;
    char nombre[30];
    char uea[15];
    float calificacion;
    struct alumno* izq;
    struct alumno* der;
};

//Estructura para un crear a un nuevo alumno
struct alumno* crearAlumno(int matricula, char nombre[], char uea[], float calificacion)
{
    struct alumno* new = (struct alumno*)malloc(sizeof(struct alumno));
    new->matricula = matricula;
    strcpy(new->nombre, nombre);
    strcpy(new->uea, uea);
    new->calificacion = calificacion;
    new->izq = NULL;
    new->der = NULL;
    return new;
}

// Estructura para agregar un nuevo alumno
struct alumno* agregarNuevo(struct alumno* alumno,int matricula,char nombre[],char uea[],float calificacion)
{
    if (alumno == NULL)
    {
        return crearAlumno(matricula, nombre, uea, calificacion);
    }

    if (matricula < alumno->matricula)
    {
        alumno->izq = agregarNuevo(alumno->izq, matricula, nombre, uea, calificacion);
    }

    else if (matricula > alumno->matricula)
    {
        alumno->der = agregarNuevo(alumno->der, matricula, nombre, uea, calificacion);
    }

    return alumno;
}

// Estructura para buscar a un alumno por matricula
struct alumno* buscar(struct alumno* alumno, int matricula)
{
    if (alumno == NULL || alumno->matricula == matricula)
    {
        return alumno;
    }

    if (alumno->matricula < matricula)
    {
        return buscar(alumno->der, matricula);
    }

    return buscar(alumno->izq, matricula);
}

// Estructura para buscar por nombre
struct alumno* buscarNombre(struct alumno* alumno, char nombre[])
{
    if (alumno == NULL)
    {
        return NULL;
    }

    if (strcmp(alumno->nombre, nombre) == 0)
    {
        return alumno;
    }
    struct alumno* izq = buscarNombre(alumno->izq, nombre);
    if (izq != NULL) {
        return izq;
    }
    return buscarNombre(alumno->der, nombre);
}

// Estructura para valor minimo de un nodo
struct alumno* nodoValorMin(struct alumno* alumno)
{
    struct alumno* current = alumno;
    while (current->izq != NULL)
    {
        current = current->izq;
    }

    return current;
}

// Estructura para aliminar dato
struct alumno* eliminarNodo(struct alumno* raiz, int matricula)
{
    if (raiz == NULL)
    {
        return raiz;
    }

    if (matricula < raiz->matricula)
    {
        raiz->izq = eliminarNodo(raiz->izq, matricula);
    }

    else if (matricula > raiz->matricula)
    {
        raiz->der = eliminarNodo(raiz->der, matricula);
    }

    else
    {
        if (raiz->izq == NULL)
        {
            struct alumno* temp = raiz->der;
            free(raiz);
        return temp;
        }

        else if (raiz->der == NULL)
        {
            struct alumno* temp = raiz->izq;
            free(raiz);
            return temp;
        }

        struct alumno* temp = nodoValorMin(raiz->der);
        raiz->matricula = temp->matricula;
        strcpy(raiz->nombre, temp->nombre);
        strcpy(raiz->uea, temp->uea);
        raiz->calificacion = temp->calificacion;
        raiz->der = eliminarNodo(raiz->der, temp->matricula);
    }
    return raiz;
}

// Modificar nombre del datos de un alumno
void modificar(struct alumno* alumno, int matricula, char nombre[], char uea[], float calificacion)
{
    if (alumno!= NULL)
    {
        if (alumno->matricula == matricula)
        {
            strcpy(alumno->nombre, nombre);
            strcpy(alumno->uea, uea);
            alumno->calificacion = calificacion;
        }

        else
        {
            modificar(alumno->izq, matricula, nombre, uea, calificacion);
            modificar(alumno->der, matricula, nombre, uea, calificacion);
        }
    }
}

// Mostrar datos de un alumno
void mostrar(struct alumno* alumno)
{
    if (alumno!= NULL)
    {
        printf("Matricula: %d\n", alumno->matricula);
        printf("Nombre: %s\n", alumno->nombre);
        printf("UEA: %s\n", alumno->uea);
        printf("Calificacion: %f\n", alumno->calificacion);
    }
}

// INORDER
void inorder(struct alumno* alumno)
{
    if (alumno != NULL)
    {
        inorder(alumno->izq);
        mostrar(alumno);
        inorder(alumno->der);
    }
}

// PREORDER
void preorder(struct alumno* alumno)
{
    if (alumno != NULL)
    {
        mostrar(alumno);
        preorder(alumno->izq);
        preorder(alumno->der);
    }
}

// POSTORDER
void postorder(struct alumno* alumno)
{
    if (alumno != NULL)
    {
        postorder(alumno->izq);
        postorder(alumno->der);
        mostrar(alumno);
    }
}


// Desarrolo del Menu interactivo para el usuario
int main()
{
    struct alumno* raiz = NULL;
    int opcion, matricula;
    char nombre[30], uea[15];
    float calificacion;

    //Creación del menu de opciones
    while(1)
    {
        printf("\n\n\t\t\t|------MENU------|\n");

        printf("\n\t[ 1 ] - Insertar alumno");
        printf("\n\t[ 2 ] - Borrar Alumno");
        printf("\n\t[ 3 ] - Modificar Datos del Alumno");
        printf("\n\t[ 4 ] - Buscar un alumno por matricula");
        printf("\n\t[ 5 ] - Buscar un Alumno por Nombre");
        printf("\n\t[ 6 ] - Desplegar los datos de un alumno");
        printf("\n\t[ 7 ] - Desplegado por in-orden");
        printf("\n\t[ 8 ] - Desplegado por pre-orden");
        printf("\n\t[ 9 ] - Desplegado por post-orden");
        printf("\n\t[ 0 ] - salir");

        printf("\n\n - Ingresar opcion: ");
        scanf("%d", &opcion);
        
        // Creación de las opciones
        switch(opcion)
        {
            // Insertar alumno
            case 1:
                printf("Ingrese matricula: ");
                scanf("%d", &matricula);
                printf("Ingrese nombre: ");
                scanf("%s", nombre);
                printf("Ingrese UEA: ");
                scanf("%s", uea);
                printf("Ingrese calificacion: ");
                scanf("%f", &calificacion);
                raiz = agregarNuevo(raiz, matricula, nombre, uea, calificacion);
            break;
            
            // Eliminar un alumno
            case 2:
                printf("Ingrese matricula del alumno a borrar: ");
                scanf("%d", &matricula);
                raiz = eliminarNodo(raiz, matricula);
            break;

            // Modificación de datos de un alumno
            case 3:
                printf("Ingrese matricula del alumno a modificar: ");
                scanf("%d", &matricula);
                printf("Ingrese nuevo nombre: ");
                scanf("%s", nombre);
                printf("Ingrese nueva UEA: ");
                scanf("%s", uea);
                printf("Ingrese nueva calificacion: ");
                scanf("%f", &calificacion);
                modificar(raiz, matricula, nombre, uea, calificacion);
            break;
            
            // Buscar por matricula
            case 4:
                printf("Ingrese matricula del alumno a buscar: ");
                scanf("%d", &matricula);
                mostrar(buscar(raiz, matricula));
            break;

            // Buscar por nombre
            case 5:
                printf("Ingrese nombre del alumno a buscar: ");
                scanf("%s", nombre);
                mostrar(buscarNombre(raiz, nombre));
            break;

            // Desplegar datos de un alumno
            case 6:
                mostrar(raiz);
            break;

            // Inorder
            case 7:
                inorder(raiz);
            break;

            // Preorder
            case 8:
                preorder(raiz);
            break;

            // Postorder
            case 9:
                postorder(raiz);
            break;

            // Salir de la aplicacion.
            case 0:
                exit(0);
            break;

            //opcion no valida al seleccionar una opción que no se encunetra en el menu.
            default:
                printf("OPCION NO VALIDA.\n\n");
            break;
        }
    }
    return 0;
}
