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
struct alumno* nuevoAlumno(struct alumno* alumno,int matricula,char nombre[],char uea[],float calificacion)
{
    if (alumno == NULL)
    {
        return crearAlumno(matricula, nombre, uea, calificacion);
    }

    if (matricula < alumno->matricula)
    {
        alumno->izq = nuevoAlumno(alumno->izq, matricula, nombre, uea, calificacion);
    }

    else if (matricula > alumno->matricula)
    {
        alumno->der = nuevoAlumno(alumno->der, matricula, nombre, uea, calificacion);
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
struct alumno* eliminarNodo(struct alumno* padre, int matricula)
{
    if (padre == NULL)
    {
        return padre;
    }

    if (matricula < padre->matricula)
    {
        padre->izq = eliminarNodo(padre->izq, matricula);
    }

    else if (matricula > padre->matricula)
    {
        padre->der = eliminarNodo(padre->der, matricula);
    }

    else
    {
        if (padre->izq == NULL)
        {
            struct alumno* temp = padre->der;
            free(padre);
        return temp;
        }

        else if (padre->der == NULL)
        {
            struct alumno* temp = padre->izq;
            free(padre);
            return temp;
        }

        struct alumno* temp = nodoValorMin(padre->der);
        padre->matricula = temp->matricula;
        strcpy(padre->nombre, temp->nombre);
        strcpy(padre->uea, temp->uea);
        padre->calificacion = temp->calificacion;
        padre->der = eliminarNodo(padre->der, temp->matricula);
    }
    return padre;
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
        printf("\n* Matricula: %d\n", alumno->matricula);
        printf("* Nombre: %s\n", alumno->nombre);
        printf("* UEA: %s\n", alumno->uea);
        printf("* Calificacion: %f\n", alumno->calificacion);
    }
}

// inOrden1
void inOrden(struct alumno* alumno)
{
    if (alumno != NULL)
    {
        inOrden(alumno->izq);
        mostrar(alumno);
        inOrden(alumno->der);
    }
}

// preOrden
void preOrden(struct alumno* alumno)
{
    if (alumno != NULL)
    {
        mostrar(alumno);
        preOrden(alumno->izq);
        preOrden(alumno->der);
    }
}

// postOrden
void postOrden(struct alumno* alumno)
{
    if (alumno != NULL)
    {
        postOrden(alumno->izq);
        postOrden(alumno->der);
        mostrar(alumno);
    }
}


// Desarrolo del Menu interactivo para el usuario
int main()
{
    struct alumno* padre = NULL;
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
                printf("Ingresa la matricula a registrar: ");
                scanf("%d", &matricula);
                printf("Ingrese el nombre a registrar: ");
                scanf("%s", nombre);
                printf("Ingrese la UEA a registrar:  ");
                scanf("%s", uea);
                printf("Ingrese la calificación obtenida:  ");
                scanf("%f", &calificacion);
                padre = nuevoAlumno(padre, matricula, nombre, uea, calificacion);
            break;

            // Eliminar un alumno
            case 2:
                printf("Ingrese matricula del alumno a borrar: ");
                scanf("%d", &matricula);
                padre = eliminarNodo(padre, matricula);
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
                modificar(padre, matricula, nombre, uea, calificacion);
            break;

            // Buscar por matricula
            case 4:
                printf("Ingrese matricula del alumno a buscar: ");
                scanf("%d", &matricula);
                mostrar(buscar(padre, matricula));
            break;

            // Buscar por nombre
            case 5:
                printf("Ingrese nombre del alumno a buscar: ");
                scanf("%s", nombre);
                mostrar(buscarNombre(padre, nombre));
            break;

            // Desplegar datos de un alumno
            case 6:
                mostrar(padre);
            break;

            // inOrden
            case 7:
                inOrden(padre);
            break;

            // preOrden
            case 8:
                preOrden(padre);
            break;

            // postOrden
            case 9:
                postOrden(padre);
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
