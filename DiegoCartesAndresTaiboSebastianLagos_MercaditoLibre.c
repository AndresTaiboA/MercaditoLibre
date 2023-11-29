#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100000

struct NodoCliente
{
  struct Cliente * datosCliente;
  struct NodoCliente * ant;
  struct NodoCliente * sig;
};
struct Cliente
{
  char * rut;
  char * nombre;
  char * email;
  struct NodoCompra * compras;
};
struct Proveedor
{
  char * rut;
  char * nombre;
  char * direccion;
  struct NodoVenta * ventas;
};
struct NodoProveedor
{
  struct Proveedor * datosProveedor;
  struct NodoProveedor * ant;
  struct NodoProveedor * sig;
};
struct Producto
{
  int id;
  char * nombre;
  int precio;
  int stock;
};
struct NodoProducto
{
  struct Producto * datosProducto;
  struct NodoProducto *izq;
  struct NodoProducto *der;
};
struct ProductoAdquirido
{
  int cantidad;
  struct Producto * venta;
};
struct ProductoComprado
{
  int cantidad;
  struct Producto * compra;
};
//Compra que hacen los clientes
struct NodoCompra
{
  struct Compra * datosCompra;
  struct NodoCompra * ant;
  struct NodoCompra * sig;
};
struct Compra
{
  int id;
  struct ProductoComprado ** compras;
};
//Compra que hace la empresa a sus proveedores
struct NodoVenta
{
  struct Venta * datosVenta;
  struct NodoVenta * ant;
  struct NodoVenta * sig;
};
struct Venta
{
  int id;
  struct ProductoAdquirido ** venta;
};
struct SistemaMercaditoLibre
{
  struct NodoProducto * productos;
  struct NodoProveedor * proveedores;
  struct NodoCliente * clientes;
};

struct Rotacion
{
  struct Producto *producto;
  double *rotacion;
};

//Funciones cliente

/*
Funcion que busca en la lista cliente a un cliente determinado usando su rut el cual es unico por persona, para devolver al cliente, en caso de no encontrarlo devuelve NULL.
*/
struct NodoCliente * buscarCliente(struct NodoCliente * clientes, char * rut)
{
  struct NodoCliente * rec = clientes;
  
  if(clientes != NULL)
  {
    do
    {
      if(rec->datosCliente != NULL)
      {
        if(strcmp(rec->datosCliente->rut,rut) == 0)
        {
          return rec;
        }
      }
      
      rec = rec->sig;
    
    }while(rec != clientes);
  }
  
  return NULL;
}

void escribirDatosCliente(struct NodoCliente * cliente, int cont)
{
  printf("Cliente %d\n", cont);
  printf("Rut: %s\n",cliente->datosCliente->rut);
  printf("Nombre: %s\n",cliente->datosCliente->nombre);
  printf("Email: %s\n\n",cliente->datosCliente->email);
}

void listarClientes(struct NodoCliente * clientes)
{
  int cont = 0;
  struct NodoCliente * rec = clientes;
  
  if(clientes != NULL)
  {
    do
    {
      if(rec->datosCliente != NULL)
      {
        cont++;
        escribirDatosCliente(rec, cont);
      }
      
      rec = rec->sig;
    
    }while(rec != clientes);
  }
}

void printfIngreseRut()
{
  printf("Ingrese Rut:\n");
}

void printfIngreseNombre()
{
  printf("Ingrese Nombre:\n");
}

void printfIngreseEmail()
{
  printf("Ingrese Email:\n");
}

void poblarCliente(struct Cliente **cliente)
{
    int c;
    char *rut;
    char *nombre;
    char *email;
  
    rut = (char*) malloc(sizeof(char) * 15);
    nombre = (char*) malloc(sizeof(char) * 50);
    email = (char*) malloc(sizeof(char) * 30);

    printfIngreseRut();
    if(rut != NULL){
        scanf("%14s", rut);
        while ((c = getchar()) != '\n'){
        }
    }
  
    printfIngreseNombre();
    if(nombre != NULL){
        scanf("%49s", nombre);
        while ((c = getchar()) != '\n'){
        }
    }
  
    printfIngreseEmail();
    if(email != NULL){
        scanf("%29s", email);
        while ((c = getchar()) != '\n'){
        }
    }

    //Se asignan las variables estaticas a las del cliente
    (*cliente)->rut = rut;
    (*cliente)->nombre = nombre;
    (*cliente)->email = email;
    (*cliente)->compras = NULL;
}

//Funcion que crea un cliente junto a sus datos
struct NodoCliente * crearNodoCliente(void)
{
    //Se declaran las variables
    struct NodoCliente *nodo = NULL;
    struct Cliente *cliente = NULL;
  
    //se reserva memoria en el nodo
    nodo = (struct NodoCliente*) malloc(sizeof(struct NodoCliente));

    //Condicion en caso de error al reservar memoria
    if(nodo != NULL)
    {
        //reserva de memoria del struct que contiene los datos del cliente
        cliente = (struct Cliente*) malloc(sizeof(struct Cliente));
      
        //Condicion en caso de error al reservar memoria en los datos del cliente
        if(cliente != NULL)
        {
          //llamado a funcion que completa sus datos
          poblarCliente(&cliente);

          //se asignan los datos del cliente al nodo y se realizan enlazes iniciales para evitar errores
          nodo->datosCliente = cliente;
          nodo->ant = nodo;
          nodo->sig = nodo;
        }
    }
  
    //retorna el cliente o NULL en caso de error
    return nodo;
}

void agregarCliente(struct NodoCliente **head, struct SistemaMercaditoLibre * sistemaMercadito)
{
    struct NodoCliente *cliente = NULL;
  
    //nodo con la mision de ser puente al enlazar
    struct NodoCliente *ultimo;
  
    cliente = crearNodoCliente();

    if(cliente != NULL)
    {
        if( (*head) == NULL)
        {
            (*head) = cliente;
            (*head)->sig = (*head);
            (*head)->ant = (*head);
            sistemaMercadito->clientes = (*head);
        }
        else
        {
            //si encuentra al cliente es porque ya existe en la lista
            if( buscarCliente((*head), (cliente->datosCliente->rut)) != NULL )
              return;
          
            ultimo = (*head)->ant;
            cliente->sig = (*head);
            cliente->ant = ultimo;

            ultimo->sig = cliente;
            (*head)->ant = cliente;
        }

    }

}

//Funcion que quita determinado cliente segun Rut ingresado.
struct Cliente * quitarCliente(struct NodoCliente * clientes, char * rut)
{
  struct NodoCliente * rec = clientes;
  struct Cliente * clienteQuitado = NULL;
  if (clientes != NULL)
  {
    do
    {
      if(rec->datosCliente != NULL)
      {
        if(strcmp(rec->datosCliente->rut,rut) == 0)
        {
          if(rec == clientes)
          {
            clientes = clientes->sig;
          }
          clienteQuitado = rec->datosCliente;
          rec->ant->sig = rec->sig;
          rec->sig->ant = rec->ant;
          return clienteQuitado;
        }
      }

      rec = rec->sig;
    }while(rec != clientes);
  }
  return clienteQuitado;
}

void printfSeleccionModCliente()
{
  printf("\nSeleccione el area que desea modificar en el perfil del cliente\n");
  printf("[1] Nombre\n");
  printf("[2] Email\n");
  printf("[0] Salir\n\n");
}

int modificarCliente(struct NodoCliente ** clientes, char * rut)
{
    struct NodoCliente * cliente = buscarCliente( ( * clientes), rut);
    int checkOpcion = 1,
        i,
        c,
        opcion;
    char *opcionTmp;
    opcionTmp = (char *) malloc(sizeof(char) * 3);

    if(cliente != NULL)
    {
        do
        {
            printfSeleccionModCliente();
            do
            {
                scanf("%2s",opcionTmp);
                for(i = 0; opcionTmp[i] != '\0'; i++)
                {
                    if(isdigit(opcionTmp[i]))
                        checkOpcion = 0;
                    else
                        checkOpcion = 1;
                        break;
                }

                while ((c = getchar()) != '\n') {
                }

            }while(checkOpcion);

            checkOpcion = 1;
            opcion = atoi(opcionTmp);

            printf("seleccionaste %i ", opcion);

            switch (opcion)
            {
                case 1:
                    if(cliente->datosCliente != NULL)
                    {
                        if(cliente->datosCliente->nombre != NULL)
                        {
                            printf("Realize el cambio: ");
                            scanf("%49s", cliente->datosCliente->nombre);
                            while ((c = getchar()) != '\n') {
                            }
                        }
                    }
                    break;

                case 2:
                    if(cliente->datosCliente != NULL)
                    {
                        if(cliente->datosCliente->email != NULL)
                        {
                            printf("Realize el cambio: ");
                            scanf("%29s", cliente->datosCliente->email);
                            while ((c = getchar()) != '\n') {
                            }
                        }
                    }
                    break;

                case 0:
                    break;

                default:
                    printf("Opcion no valida vuelve a intentarlo\n");
                    break;
            }

        }while(opcion != 0);

        return  1;
    }

    return 0;
}

int sumarProductosComprados(struct ProductoComprado **compras)
{
    int cont = 0,
        i;
    if(compras != NULL)
    {
        for(i = 0; i < MAX; i++)
        {
            if(compras[i] != NULL)
            {
                cont += compras[i]->cantidad;
            }
        }
    }
    return cont;
}

int SumarNodoCompra(struct NodoCompra * head)
{
    int cont = 0;
    struct NodoCompra * rec = head->sig;

    if(head != NULL)
    {
        while(rec != NULL)
        {
            if(head->datosCompra != NULL)
            {
                cont += sumarProductosComprados(head->datosCompra->compras);
            }
            rec = rec->sig;
        }

    }

    return cont;
}

//Consideramos mejor cliente al que adquirio una mayor cantidad de productos
struct NodoCliente * mejorCliente(struct NodoCliente * head)
{
    struct NodoCliente * mejor = NULL,
                       * rec = head;
    int totalMayor,
        total,
        flag = 1;

    if(head == NULL)
        return NULL;
    do
    {
        if(rec->datosCliente != NULL)
        {
            total = SumarNodoCompra(rec->datosCliente->compras);
            if(flag)
            {
                flag = 0;
                totalMayor = total;
                mejor = rec;
            }
            else
            {
                if(total > totalMayor)
                {
                    totalMayor = total;
                    mejor = rec;
                }
            }
        }
       rec = rec->sig;
    }while(rec != head);

    return mejor;
}

struct NodoCliente *peorCliente(struct NodoCliente *head)
{
    struct NodoCliente *peor = NULL,
                       *rec = head;
    int totalMenor,
        total,
        flag = 1;

    if (head == NULL)
        return NULL;
    do
    {
        if (rec->datosCliente != NULL)
        {
            total = SumarNodoCompra(rec->datosCliente->compras);
            if (flag)
            {
                flag = 0;
                totalMenor = total;
                peor = rec;
            }
            else
            {
                if (total < totalMenor)
                {
                    totalMenor = total;
                    peor = rec;
                }
            }
        }
        rec = rec->sig;
    } while (rec != head);

    return peor;
}

void ordenarClientesPorRut(struct SistemaMercaditoLibre * mercadito)
{
  if(mercadito->clientes != NULL)
  {
    struct NodoCliente *rec = mercadito->clientes->sig;
    do
    {
      while(strcmp(rec->datosCliente->rut, rec->ant->datosCliente->rut)>0)
      {
        rec->ant->ant->sig = rec;
        rec->ant->sig = rec->sig;
        rec->sig = rec->ant;
        rec->ant = rec->ant->ant;
        rec->sig->ant = rec;
        rec->sig->sig->ant = rec->sig;
        if(rec->sig == mercadito->clientes)
        {
          mercadito->clientes = rec;
          rec = rec->sig;
        }
      }
      rec = rec->sig;
    }while(rec != mercadito->clientes);
  }
}

//Funciones proveedor

struct NodoProveedor * buscarProveedor(struct NodoProveedor * proveedores, char * rut)
{
  struct NodoProveedor * rec = proveedores;
  if(proveedores != NULL)
  {
    rec = proveedores->sig;
      
    while(rec != NULL)
    {
      if(rec->datosProveedor != NULL)
      {
        if(strcmp(rec->datosProveedor->rut,rut) == 0)
        {
          return rec;
        }
      }
      rec = rec->sig;
    }
  }
  return NULL;
}

void escribirDatosProveedor(struct NodoProveedor * proveedor, int cont)
{
  printf("Proveedor %i\n",cont);
  printf("Rut: %s\n",proveedor->datosProveedor->rut);
  printf("Nombre: %s\n",proveedor->datosProveedor->nombre);
  printf("Direccion: %s\n\n",proveedor->datosProveedor->direccion);
}

void listarProveedores(struct NodoProveedor * proveedor)
{
  int cont = 0;
  struct NodoProveedor * rec = proveedor->sig;
  
  if(proveedor != NULL)
  {
    while(rec != NULL)
    {
      if(rec->datosProveedor != NULL)
      {
        cont++;
        escribirDatosProveedor(rec, cont);
      }

      rec = rec->sig;
    }
  }
}

void printfIngreseDireccion()
{
  printf("Ingrese Direccion:\n");
}

void poblarProveedor(struct Proveedor **proveedor)
{
    int c;
    char *rut;
    char *nombre;
    char *direccion;

    rut = (char*) malloc(sizeof(char) * 15);
    nombre = (char*) malloc(sizeof(char) * 50);
    direccion = (char*) malloc(sizeof(char) * 30);

    printfIngreseRut();
    if(rut != NULL){
        scanf("%14s", rut);
        while ((c = getchar()) != '\n'){
        }
    }
  
    printfIngreseNombre();
    if(nombre != NULL){
        scanf("%49s", nombre);
        while ((c = getchar()) != '\n'){
        }
    }
  
    printfIngreseDireccion();
    if(direccion != NULL){
        scanf("%29s", direccion);
        while ((c = getchar()) != '\n'){
        }
    }
    (*proveedor)->rut = rut;
    (*proveedor)->nombre = nombre;
    (*proveedor)->direccion = direccion;
    (*proveedor)->ventas = NULL;    
}

struct NodoProveedor * crearNodoProveedor(void)
{
    struct NodoProveedor * nodo = NULL;
    struct Proveedor * proveedor = NULL;
    nodo = (struct NodoProveedor *) malloc(sizeof(struct NodoProveedor));

    if(nodo != NULL)
    {
        proveedor = (struct Proveedor *) malloc(sizeof(struct Proveedor));
        if(proveedor != NULL)
        {
            poblarProveedor(&proveedor);
            nodo->datosProveedor = proveedor;
            nodo->sig = NULL;
            nodo->ant = NULL;
        }
    }
    return nodo;
}

void agregarProveedor(struct NodoProveedor **head, struct SistemaMercaditoLibre * mercaditoLibre)
{
    struct NodoProveedor *proveedor = NULL;
    struct NodoProveedor *rec = (*head);

    proveedor = crearNodoProveedor();

    if(proveedor != NULL)
    {
        if( (*head) == NULL)
        {
            (*head) = (struct NodoProveedor *) malloc(sizeof(struct NodoProveedor));
            (*head)->datosProveedor = NULL;
            (*head)->sig = NULL;
            (*head)->ant = NULL;

            rec = (*head);
            mercaditoLibre->proveedores = (*head);
        }

        //si encuentra al proveedor es porque ya existe
        if(buscarProveedor((*head), proveedor->datosProveedor->rut) != NULL)
          return;
      
        while(rec->sig != NULL)
            rec = rec->sig;
        rec->sig = proveedor;
        rec->sig->ant = rec;
        rec->sig->sig = NULL;

    }
}

struct Proveedor * quitarProveedor(struct NodoProveedor * proveedores, char * rut)
{
  struct NodoProveedor * rec = proveedores;
  struct Proveedor * proveedorQuitado = NULL;
  
  if(proveedores != NULL)
  {
    rec = proveedores->sig;
    
    while(rec != NULL)
    {
      if(strcmp(rec->datosProveedor->rut,rut) == 0)
      {
        proveedorQuitado = rec->datosProveedor;
        rec->ant->sig = rec->sig;
        rec->sig->ant = rec->ant;
        return proveedorQuitado;
      }
    rec = rec->sig;
    }
  }
  return proveedorQuitado;
}

void printfIngreseModProveedor()
{
  printf("\nSeleccione el area que desea modificar en el perfil del proveedor\n");
  printf("[1] Nombre\n");
  printf("[2] Direccion\n");
  printf("[0] Salir\n\n");
}

int modificarProveedor(struct NodoProveedor ** proveedores, char * rut)
{
    struct NodoProveedor * proveedor = buscarProveedor( ( * proveedores), rut);
    int checkOpcion = 1,
            i,
            c,
            opcion;
    char *opcionTmp;
    opcionTmp = (char *) malloc(sizeof(char) * 3);

    if(proveedor != NULL)
    {
        do
        {
            printfIngreseModProveedor();
            do
            {
                scanf("%2s",opcionTmp);
                for(i = 0; opcionTmp[i] != '\0'; i++)
                {
                    if(isdigit(opcionTmp[i]))
                        checkOpcion = 0;
                    else
                        checkOpcion = 1;
                    break;
                }

                while ((c = getchar()) != '\n') {
                }

            }while(checkOpcion);

            checkOpcion = 1;
            opcion = atoi(opcionTmp);

            printf("seleccionaste %i ", opcion);

            switch (opcion)
            {
                case 1:
                    if(proveedor->datosProveedor != NULL)
                    {
                        if(proveedor->datosProveedor->nombre != NULL)
                        {
                            printf("Realize el cambio: ");
                            scanf("%49s", proveedor->datosProveedor->nombre);
                            while ((c = getchar()) != '\n') {
                            }
                        }
                    }
                    break;

                case 2:
                    if(proveedor->datosProveedor != NULL)
                    {
                        if(proveedor->datosProveedor->direccion != NULL)
                        {
                            printf("Realize el cambio: "); 
                            scanf("%29s", proveedor->datosProveedor->direccion);
                            while ((c = getchar()) != '\n') {
                            }
                        }
                    }
                    break;

                case 0:
                    break;

                default:
                    printf("Opcion no valida vuelve a intentarlo\n");
                    break;
            }

        }while(opcion != 0);

        return  1;
    }

    return 0;
}

void intercambiarDatosProveedor(struct  Proveedor **a, struct Proveedor **b)
{
    struct Proveedor *temp = *a;
    *a = *b;
    *b = temp;
}

//ordena por rut de mayor al menor (decreciente)
void ordenarProveedoresPorRut(struct SistemaMercaditoLibre * mercadito)
{
    if(mercadito == NULL || mercadito->proveedores == NULL || mercadito->proveedores->sig == NULL)
        return;

    struct NodoProveedor * pivote = mercadito->proveedores->sig;
    struct NodoProveedor * last = NULL;

    while(pivote != NULL)
    {
        if(pivote->datosProveedor != NULL && pivote->sig != NULL && pivote->sig->datosProveedor != NULL)
        {
            last = pivote;
            while(last != NULL)
            {
                if(strcmp(pivote->datosProveedor->rut, last->datosProveedor->rut) < 0)
                {
                    intercambiarDatosProveedor(&(pivote->datosProveedor), &(last->datosProveedor));
                }
                last = last->sig;
            }
        }
        pivote = pivote->sig;
    }
}

//Funciones producto

struct NodoProducto * buscarProducto(struct NodoProducto * productos, int idProducto)
{
    if (productos == NULL)
    {
        return NULL;
    }

    if (productos->datosProducto != NULL) 
    {
        if (productos->datosProducto->id == idProducto)
        {
            return productos;
        }

        if (idProducto < productos->datosProducto->id) 
        {
            return buscarProducto(productos->izq, idProducto);
        } 
        else 
        {
            return buscarProducto(productos->der, idProducto);
        }
    }
    return NULL;
}

struct NodoProducto * crearNodoProducto(void)
{
    struct NodoProducto * nodo = NULL;
    nodo = (struct  NodoProducto *) malloc(sizeof(struct  NodoProducto));
    nodo->datosProducto = (struct Producto *) malloc(sizeof (struct Producto));

    nodo->datosProducto->nombre = (char *) malloc (50 * sizeof(char));
    nodo->izq = nodo->der = NULL;

    return nodo;
}

void llenarNodoProducto(struct NodoProducto ** producto)
{
    int id, precio, stock, c;
    char * nombre = (char*) malloc(sizeof(char) * 50);

    printf("Ingrese el id del producto:\n");
    scanf("%d", &id);
    printf("Ingrese el nombre del producto:\n");
    if(nombre != NULL)
    {
        scanf("%49s", nombre);
        while ((c = getchar()) != '\n'){
        }
    }
    printf("Ingrese el precio del producto:\n");
    scanf("%d", &precio);
    printf("Ingrese el stock del producto:\n");
    scanf("%d", &stock);

    (* producto)->datosProducto->id = id;
    (* producto)->datosProducto->nombre = nombre;
    (* producto)->datosProducto->precio = precio;
    (* producto)->datosProducto->stock = stock;
    (* producto)->der=NULL;
    (* producto)->izq=NULL;

}

struct NodoProducto * buscarNodoVacio(struct NodoProducto * rec, struct NodoProducto * ant, int idProducto)
{
  if (rec == NULL)
  {
    return ant;
  }
  if(rec->datosProducto->id<idProducto)
  {
    ant = rec;
    buscarNodoVacio(rec->der, ant, idProducto);
  }
  else if(rec->datosProducto->id>idProducto)
  {
    ant = rec;
    buscarNodoVacio(rec->izq, ant, idProducto);
  }
  else if(rec->datosProducto->id == idProducto)
  {
    return NULL;
  }
  return ant;
}

void enlazarNodo(struct SistemaMercaditoLibre * sistemaMercadito, struct NodoProducto * producto)
{
  if(sistemaMercadito->productos == NULL)
  {
    sistemaMercadito->productos = producto;
    return;
  }
  struct NodoProducto * ant = sistemaMercadito->productos;
  struct NodoProducto * rec = sistemaMercadito->productos;
  ant = buscarNodoVacio(rec, ant, producto->datosProducto->id);
  if(ant)
  {
    if(ant->datosProducto->id<producto->datosProducto->id)
    {
      ant->der = producto;
      return;
    }
    ant->izq = producto;
  }
}
void agregarProducto(struct SistemaMercaditoLibre * sistemaMercadito)
{
  struct NodoProducto * producto = NULL;
  producto = crearNodoProducto();
  llenarNodoProducto(&producto);
  enlazarNodo(sistemaMercadito, producto);
}

void escribirProductos(struct NodoProducto *producto)
{
  printf("Id: %i\n", producto->datosProducto->id);
  printf("Nombre: %s\n", producto->datosProducto->nombre);
  printf("Precio: %i\n", producto->datosProducto->precio);
  printf("Stock: %i\n", producto->datosProducto->stock);
  printf("\n");
}

void mostrarProducto(struct NodoProducto * producto)
{
  if(producto != NULL)
  {
    mostrarProducto(producto->izq);
    
    if(producto->datosProducto != NULL)
    {
      escribirProductos(producto);
    }
    
    mostrarProducto(producto->der);
  }
}
void listarProductos(struct SistemaMercaditoLibre * sistemaMercadito)
{
  if(sistemaMercadito->productos != NULL)
  {
    struct NodoProducto * rec = sistemaMercadito->productos;
    mostrarProducto(rec);
  }
}

void printfIngreseModProducto()
{
  printf("\nSeleccione el area que desea modificar del producto\n");
  printf("[1] Nombre\n");
  printf("[2] Precio\n");
  printf("[0] Salir\n\n");
}

int modificarProducto(struct NodoProducto ** productos, int id)
{
    struct NodoProducto * producto = buscarProducto( ( * productos), id);
    int checkOpcion = 1,
            i,
            c,
            opcion;
    char *opcionTmp;
    opcionTmp = (char *) malloc(sizeof(char) * 3);

    if(producto != NULL)
    {
        do
        {
            printfIngreseModProducto();
            do
            {
                scanf("%2s",opcionTmp);
                for(i = 0; opcionTmp[i] != '\0'; i++)
                {
                    if(isdigit(opcionTmp[i]))
                        checkOpcion = 0;
                    else
                        checkOpcion = 1;
                    break;
                }

                while ((c = getchar()) != '\n') {
                }

            }while(checkOpcion);

            checkOpcion = 1;
            opcion = atoi(opcionTmp);

            printf("seleccionaste %i ", opcion);

            switch (opcion)
            {
                case 1:
                    if(producto->datosProducto != NULL)
                    {
                        if(producto->datosProducto->nombre != NULL)
                        {
                            printf("Realize el cambio: ");
                            scanf("%49s", producto->datosProducto->nombre);
                            while ((c = getchar()) != '\n') {
                            }
                        }
                    }
                    break;

                case 2:
                    if(producto->datosProducto != NULL)
                    {
                      printf("Realize el cambio: ");
                      scanf("%d", &(producto->datosProducto->precio) );
                    }
                    break;

                case 0:
                    break;

                default:
                    printf("Opcion no valida vuelve a intentarlo\n");
                    break;
            }

        }while(opcion != 0);

        return  1;
    }

    return 0;
}

void escribirBajoStock(struct NodoProducto *ABB)
{
  printf("\nAtencion Hay bajo stock en %s, hay exactamente: %d\n", ABB->datosProducto->nombre, ABB->datosProducto->stock);
}

void avisarBajoStock(struct NodoProducto *ABB, int minimo)
{
    if(ABB != NULL)
    {
        if(ABB->datosProducto != NULL)
        {
            if(ABB->datosProducto->stock < minimo)
            {
                escribirBajoStock(ABB);
            }
        }
        avisarBajoStock(ABB->izq, minimo);
        avisarBajoStock(ABB->der, minimo);
    }
}

void reemplazar(struct NodoProducto ** productos, struct NodoProducto ** aux)
{
  if(!((*productos)->der))
  {
    (*aux)->datosProducto = (*productos)->datosProducto;
    *aux = *productos;
    *productos = (*productos)->izq;
  }
  else
  {
    reemplazar(&(*productos)->der, &(*aux));
  }
}

void borrarProducto (struct NodoProducto ** productos, int id)
{
  struct NodoProducto * aux = NULL;
  
  if(!(productos))
  {
    return;
  }
  if((*productos)->datosProducto->id<id)
  {
    borrarProducto(&(*productos)->der, id);
  }
  else
  {
    if((*productos)->datosProducto->id>id)
    {
      borrarProducto(&(*productos)->izq, id);
    }
    else
    {
      if((*productos)->datosProducto->id==id)
      {
        aux = *productos;
        if(!((*productos)->izq))
        {
          *productos = (*productos)->der;
        }
        else
        {
          if(!((*productos)->der))
          {
           *productos = (*productos)->izq;
          }
          else
          {
            reemplazar(&(*productos)->izq, &aux);
          }
        }
      }
    }
  }
  
}

//Funciones venta

void listarProductosDeVenta(struct NodoVenta * venta)
{
  int i;
  for(i=0;i<MAX;i++)
  {
    if(venta->datosVenta->venta[i] != NULL)
    {
      printf("Cantidad: %i\n", venta->datosVenta->venta[i]->cantidad);
      printf("Id: %i\n", venta->datosVenta->venta[i]->venta->id);
      printf("Nombre: %s\n", venta->datosVenta->venta[i]->venta->nombre);
      printf("\n");
    }
  }
}
void listarVentasDeProveedor(struct Proveedor * proveedor)
{
  struct NodoVenta * rec = proveedor->ventas->sig;
  int cont=1;
  while(rec != NULL)
  {
    printf("Venta Numero %i\n", cont);
    listarProductosDeVenta(rec);
    rec = rec->sig;
    cont++;
  }
}
void listarVentas(struct SistemaMercaditoLibre * sistemaMercadito)
{
  if(sistemaMercadito->proveedores != NULL)
  {
    struct NodoProveedor * rec = sistemaMercadito->proveedores;
    while(rec != NULL)
    {
      printf("Ventas de proveedor %s\n", rec->datosProveedor->rut);
      listarVentasDeProveedor(rec->datosProveedor);
      rec = rec->sig;
    }
  }
}

struct Venta * buscarVentaEnProveedor(struct Proveedor * proveedor, int id)
{
  struct NodoVenta * rec = proveedor->ventas->sig;
  if(rec != NULL)
  {
    while(rec != NULL)
    {
      if(rec->datosVenta->id == id)
      {
        return rec->datosVenta;
      }
      rec = rec->sig;
    }
  }
  return NULL;
}

struct Venta * buscarVenta(struct NodoProveedor * proveedores, int id)
{
  struct NodoProveedor * rec = proveedores->sig;
  struct Venta * ventaBuscada = NULL;
  if(rec != NULL)
  {
    while(rec != NULL)
    {
      ventaBuscada = buscarVentaEnProveedor(rec->datosProveedor, id);
      if(ventaBuscada != NULL)
        return ventaBuscada;
      rec = rec->sig;
    }
  }
return NULL;
}

void intercambiarDatosVenta(struct Venta **a, struct Venta **b)
{
    struct Venta *temp = *a;
    *a = *b;
    *b = temp;
}

void ordenarVentasCadaProveedor(struct NodoVenta *ventas)
{
    if(ventas == NULL || ventas->datosVenta == NULL || ventas->sig == NULL)
        return;

    struct NodoVenta * pivote = ventas->sig;
    struct NodoVenta * last = NULL;

    while(pivote != NULL)
    {
        if(pivote->datosVenta != NULL && pivote->sig != NULL && pivote->sig->datosVenta != NULL)
        {
            last = pivote;
            while(last != NULL)
            {
                if(pivote->datosVenta->id < last->datosVenta->id)
                {
                    intercambiarDatosVenta(&(pivote->datosVenta), &(last->datosVenta));
                }
                last = last->sig;
            }
        }
        pivote = pivote->sig;
    }
}

void ordenarVentasPorId(struct SistemaMercaditoLibre * mercadito)
{
    if(mercadito == NULL || mercadito->proveedores == NULL || mercadito->proveedores->sig == NULL)
        return;
    struct NodoProveedor * rec = mercadito->proveedores;

    while(rec != NULL)
    {
        if(rec->datosProveedor != NULL)
        {
            if(rec->datosProveedor->ventas != NULL)
            {
                ordenarVentasCadaProveedor(rec->datosProveedor->ventas);
            }
        }
        rec = rec->sig;
    }
}

void crearArregloVentas(struct NodoProducto * productos, struct ProductoAdquirido ** listaDeVentas)
{
  int idProducto, cantidad, cont = 0;
  struct NodoProducto * candidato = NULL;
  while(1)
  {
    printf("Ingrese el id del producto o 0 para salir \n");
    scanf("%i", &idProducto);
    if(idProducto==0)
      break;
    candidato = buscarProducto(productos, idProducto);
    if(candidato)
    {
      printf("Ingrese la cantidad \n");
      printf("Stock disponible: %i\n", candidato->datosProducto->stock);
      scanf("%i", &cantidad);
      listaDeVentas[cont]->venta = candidato->datosProducto;
      listaDeVentas[cont]->cantidad = cantidad;
      cont++;
    }
    else
    {
      printf("No existe el producto \n");
    }
  }
}
struct NodoVenta * crearNodoVenta()
{
  struct NodoVenta * nuevo = (struct NodoVenta *) malloc(sizeof(struct NodoVenta));
  struct Venta * venta = (struct Venta *) malloc(sizeof(struct Venta));
  if(nuevo != NULL && venta != NULL)
  {
    nuevo->datosVenta = venta;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
  }
  return nuevo;
}
void enlazarNodoVenta(struct NodoVenta * nuevo, struct NodoVenta * ventas)
{
  struct NodoVenta * rec = ventas;
  while(rec->sig != NULL)
  {
    rec = rec->sig;
  }
  rec->sig = nuevo;
  nuevo->ant = rec;
}
void crearVenta(struct NodoProveedor * proveedor, struct ProductoAdquirido ** listaDeventas)
{
  struct NodoVenta * nuevo;
  int id;
  nuevo = crearNodoVenta();
  //falta verificar
  printf("Ingrese el id de la adquisicion \n");
  scanf("%i", &id);
  nuevo->datosVenta->id = id;
  enlazarNodoVenta(nuevo, proveedor->datosProveedor->ventas);
}

int agregarVenta(struct SistemaMercaditoLibre * sistemaMercadito)
{
  char * rutProveedor;
  int respuesta;
  struct NodoProveedor * proveedor = NULL;
  struct ProductoAdquirido ** listaDeVentas;

  rutProveedor = (char*) malloc(sizeof(char) * 15);

  printf("Ingrese el rut del proveedor: \n");
  scanf("%s", rutProveedor);
  proveedor = buscarProveedor(sistemaMercadito->proveedores, rutProveedor);
  if(proveedor)
  {
    listaDeVentas = (struct ProductoAdquirido**) malloc(MAX*sizeof(struct ProductoAdquirido*));
    crearArregloVentas(sistemaMercadito->productos, listaDeVentas);
    if(listaDeVentas[0] != NULL)
    {
      //falta verificar
      printf("¿Confirmar adquisicion? 1.Si 0.No\n");
      scanf("%i", &respuesta);
      if(respuesta)
      {
        crearVenta(proveedor, listaDeVentas);
        return 1;
      }
    }
  }
  return 0;
}

//Funciones compra

struct Compra * buscarCompraEnCliente(struct Cliente * cliente, int id)
{
  struct NodoCompra * rec = cliente->compras->sig;
  if(rec != NULL)
  {
    while(rec != NULL)
    {
      if(rec->datosCompra->id == id)
      {
        return rec->datosCompra;
      }
      rec = rec->sig;
    }
  }
  return NULL;
}

struct Compra * buscarCompra(struct NodoCliente * clientes, int id)
{
  struct NodoCliente * rec = clientes->sig;
  struct Compra * compraBuscada = NULL;
  if(rec != NULL)
  {
    while(rec != NULL)
    {
      compraBuscada = buscarCompraEnCliente(rec->datosCliente, id);
      if(compraBuscada != NULL)
        return compraBuscada;
      rec = rec->sig;
    }
  }
return NULL;
}
struct ProductoComprado * quitarProductoDeUnaCompra(struct NodoCompra * compra, int idProducto)
{
  struct ProductoComprado * compraQuitada = NULL;
  int i;
  for(i = 0; i<MAX; i++)
  {
    if(compra->datosCompra->compras[i] != NULL)
    {
      if(compra->datosCompra->compras[i]->compra->id == idProducto)
      {
        compraQuitada = compra->datosCompra->compras[i];
        compra->datosCompra->compras[i]->cantidad--;
        if(compra->datosCompra->compras[i]->cantidad == 0)
        {
          compra->datosCompra->compras[i] = NULL;
        }
        return compraQuitada;
      }
    }
  }
  return compraQuitada;
}
struct ProductoComprado * quitarCompra(struct NodoCliente * cliente, int idCompra, int idProducto)
{
  struct NodoCompra * rec = cliente->datosCliente->compras->sig;
  struct ProductoComprado * compraQuitada = NULL;
  while(rec != NULL)
  {
    if(rec->datosCompra->id==idCompra)
    {
      return (compraQuitada = quitarProductoDeUnaCompra(rec, idProducto));

    }
   rec = rec->sig;
  }
  return compraQuitada;
}
struct ProductoComprado * quitarCompraDeProducto(struct NodoCliente * clientes, char * rut, int idCompra, int idProducto)
{
  struct NodoCliente * rec = clientes;
  struct ProductoComprado * compraQuitada = NULL;
  if(clientes != NULL)
  {
    do
    {
      if(strcmp(rec->datosCliente->rut,rut)==0)
      {
        compraQuitada = quitarCompra(rec, idCompra, idProducto);
      }
      rec = rec->sig;
    }while(rec != clientes);
  }
  return compraQuitada;
}
void listarProductosDeCompra(struct NodoCompra * compra)
{
  int i;
  for(i=0;i<MAX;i++)
  {
    if(compra->datosCompra->compras[i] != NULL)
    {
      printf("Cantidad: %i\n", compra->datosCompra->compras[i]->cantidad);
      printf("Id: %i\n", compra->datosCompra->compras[i]->compra->id);
      printf("Nombre: %s\n", compra->datosCompra->compras[i]->compra->nombre);
      printf("\n");
    }
  }
}
void listarComprasDeCliente(struct Cliente * cliente)
{
  struct NodoCompra * rec = cliente->compras->sig;
  int cont=1;
  while(rec != NULL)
  {
    printf("Compra Numero %i\n", cont);
    listarProductosDeCompra(rec);
    rec = rec->sig;
    cont++;
  }
}
void listarCompras(struct SistemaMercaditoLibre * sistemaMercadito)
{
  if(sistemaMercadito->clientes != NULL)
  {
    struct NodoCliente * rec = sistemaMercadito->clientes;
    do
    {
      printf("Compras de cliente %s\n", rec->datosCliente->rut);
      listarComprasDeCliente(rec->datosCliente);
      rec = rec->sig;
    }while(rec != sistemaMercadito->clientes);
  }
}
void crearArregloCompras(struct NodoProducto * productos, struct ProductoComprado ** listaDeCompras)
{
  int idProducto, cantidad, cont = 0;
  struct NodoProducto * candidato = NULL;
  while(1)
  {
    printf("Ingrese el id del producto o 0 para salir \n");
    scanf("%i", &idProducto);
    if(idProducto==0)
      break;
    candidato = buscarProducto(productos, idProducto);
    if(candidato)
    {
      printf("Ingrese la cantidad \n");
      printf("Stock disponible: %i\n", candidato->datosProducto->stock);
      scanf("%i", &cantidad);
      if(candidato->datosProducto->stock <= cantidad)
      {
        listaDeCompras[cont]->compra = candidato->datosProducto;
        listaDeCompras[cont]->cantidad = cantidad;
        cont++;
      }
      else
      {
        printf("No hay suficiente stock \n");
      }
    }
    else
    {
      printf("No existe el producto \n");
    }
  }
}
struct NodoCompra * crearNodoCompra()
{
  struct NodoCompra * nuevo = (struct NodoCompra *) malloc(sizeof(struct NodoCompra));
  struct Compra * compra = (struct Compra *) malloc(sizeof(struct Compra));
  if(nuevo != NULL && compra != NULL)
  {
    nuevo->datosCompra = compra;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
  }
  return nuevo;
}
void enlazarNodoCompra(struct NodoCompra * nuevo, struct NodoCompra * compras)
{
  struct NodoCompra * rec = compras;
  while(rec->sig != NULL)
  {
    rec = rec->sig;
  }
  rec->sig = nuevo;
  nuevo->ant = rec;
}
void crearCompra(struct NodoCliente * cliente, struct ProductoComprado ** listaDeCompras)
{
  struct NodoCompra * nuevo;
  int id;
  nuevo = crearNodoCompra();
  //falta verificar
  printf("Ingrese el id de la compra \n");
  scanf("%i", &id);
  nuevo->datosCompra->id = id;
  enlazarNodoCompra(nuevo, cliente->datosCliente->compras);
}

int agregarCompra(struct SistemaMercaditoLibre * sistemaMercadito)
{
  char * rutCliente;
  int respuesta;
  struct NodoCliente * cliente = NULL;
  struct ProductoComprado ** listaDeCompras;
  
  rutCliente = (char*) malloc(sizeof(char) * 15);
  
  printf("Ingrese el rut del cliente: \n");
  scanf("%s", rutCliente);
  cliente = buscarCliente(sistemaMercadito->clientes, rutCliente);
  if(cliente)
  {
    listaDeCompras = (struct ProductoComprado**) malloc(MAX*sizeof(struct ProductoComprado*));
    crearArregloCompras(sistemaMercadito->productos, listaDeCompras);
    if(listaDeCompras[0] != NULL)
    {
      //falta verificar
      printf("¿Confirmar compra? 1.Si 0.No\n");
      scanf("%i", &respuesta);
      if(respuesta)
      {
        crearCompra(cliente, listaDeCompras);
        return 1;
      }
    }
  }
  return 0;
}

void escribirCompra(struct ProductoComprado **compras)
{
  int i;
  if(compras != NULL)
  {
    for (i = 0 ; i < MAX ; i++)
      {
        if (compras[i]->compra != NULL)
        {
          printf("Id: %i \n", compras[i]->compra->id);
          printf("Nombre: %s \n", compras[i]->compra->nombre);
          printf("Precio: %d \n", compras[i]->compra->precio);
          printf("Cantidad: %i \n", compras[i]->cantidad);
        }
      }
  }
}

void escribirVenta(struct ProductoAdquirido **ventas)
{
  int i;
  if(ventas != NULL)
  {
    for (i = 0 ; i < MAX ; i++)
      {
        if (ventas[i]->venta != NULL)
        {
          printf("Id: %i \n", ventas[i]->venta->id);
          printf("Nombre: %s \n", ventas[i]->venta->nombre);
          printf("Precio: %d \n", ventas[i]->venta->precio);
          printf("Cantidad: %i \n", ventas[i]->cantidad);
        }
      }
  }
}

void intercambiarDatosCompra(struct Compra **a, struct Compra **b)
{
    struct Compra *temp = *a;
    *a = *b;
    *b = temp;
}

void ordenarComprasCadaCliente(struct NodoCompra *compras)
{
    if(compras == NULL || compras->datosCompra == NULL || compras->datosCompra->compras == NULL)
        return;

    struct NodoCompra * pivote = compras->sig;
    struct NodoCompra * last = NULL;

    while(pivote != NULL)
    {
        if(pivote->datosCompra != NULL && pivote->sig != NULL && pivote->sig->datosCompra != NULL)
        {
            last = pivote;
            while(last != NULL)
            {
                if(pivote->datosCompra->id < last->datosCompra->id)
                {
                    intercambiarDatosCompra(&(pivote->datosCompra), &(last->datosCompra));
                }
                last = last->sig;
            }
        }
        pivote = pivote->sig;
    }
}

void ordenarComprasPorId(struct SistemaMercaditoLibre * mercadito)
{
    if(mercadito == NULL || mercadito->clientes == NULL)
        return;
    struct NodoCliente * rec = mercadito->clientes;

    do
    {
        if(rec->datosCliente != NULL)
        {
            if(rec->datosCliente->compras != NULL)
            {
                ordenarComprasCadaCliente(rec->datosCliente->compras);
            }
        }
        rec = rec->sig;
    }while(rec != mercadito->clientes);
}

//Funcion que cuenta el total de unidades de cada producto y cuenta el total de productos.
void recorrerArbolProductoParaPromedio(struct NodoProducto *raiz, int *totalUnidades, int *totalProductos)
{
    //caso arbol vacio
    if (raiz != NULL)
    {
        // agregar las unidades del producto y sumar el producto
        (*totalUnidades) += raiz->datosProducto->stock;
        (*totalProductos) += 1;

        recorrerArbolProductoParaPromedio(raiz->izq, &(*totalUnidades), &(*totalProductos));
        recorrerArbolProductoParaPromedio(raiz->der, &(*totalUnidades), &(*totalProductos));
    }
}



double calcularPromedioInventarioProducto(struct NodoProducto *productos)
{
  //bloque de declaraciones
  int totalUnidades = 0;
  int totalProductos = 0;
  double promedio;

  //caso de arbol vacio
  if (productos == NULL)
  {
    printf("no hay productos\n");
    return 0.0;
  }

  recorrerArbolProductoParaPromedio(productos, &totalUnidades, &totalProductos);

  //calcular el promedio
  if (totalProductos > 0)
  {
    promedio = (double)totalUnidades / (double)totalProductos;
    return promedio;
  }
  //caso poco probable en el que todos los productos tienen 0 de stock
  else
  {
    printf("no hay productos.\n");
    return 0.0;
  }
}

// falta recorrer el árbol
double calcularIngresosProducto(struct NodoProducto *productos, int cantidadVendida)
{
  double ingresos;
  // se verficia que el nodo y/o el producto no están vacíos
  if (productos == NULL || productos->datosProducto == NULL)
  {
    printf("producto no válido.\n");
    return 0.0;
  }

  if (cantidadVendida > (productos->datosProducto->stock))
  {
    printf("no hay suficiente stock.\n");
    return 0.0;
  }

  // calcular ingresos y actualizar stock del producto
  ingresos = cantidadVendida * productos->datosProducto->precio;
  productos->datosProducto->stock -= cantidadVendida;

  return ingresos;
}

//calcular rotacion total de los productos
double calcularRotacionInventario(struct NodoProducto *productos, int cantidadVendida)
{
  double ingresos = calcularIngresosProducto(productos, cantidadVendida);
  double promedioInventario = calcularPromedioInventarioProducto(productos);
  double rotacion = 0.0;

  if (productos != NULL)
  {
    if (promedioInventario > 0.0)
    {
      rotacion = ingresos / promedioInventario;
    }
  }

  return rotacion;
}


// individual

double calcularIngresosProductoIndividual(struct Producto *producto, struct NodoVenta *ventas)
{
  double ingresos = 0.0;
  struct NodoVenta *rec = ventas;
  struct ProductoAdquirido **venta;
  int i;

  while (rec != NULL)
  {
    // obtener el arreglo de productos adquiridos en la venta
    venta = rec->datosVenta->venta;

    // recorrer el arreglo de productos adquiridos en la venta
    for (i = 0; venta[i] != NULL; ++i)
    {
      if(venta[i] != NULL)
      {
        if(venta[i]->venta != NULL)
        {
          //verificar si el producto actual coincide con el producto dado
          if (venta[i]->venta == producto)
          {
            // aumentar los ingresos por la cantidad adquirida del producto
            ingresos += (venta[i]->cantidad * producto->precio);
          }
        }
      }
    }
    rec = rec->sig;
  }
  return ingresos;
}

double calcularPromedioInventarioProductoIndividual(struct Producto *producto, struct NodoVenta *ventas)
{
  int totalInventario = 0;
  double promedioInventario = 0.0;
  int totalVentas = 0;
  struct NodoVenta *rec = ventas;
  struct ProductoAdquirido **venta;
  int i;

  while (rec != NULL)
  {
    // arreglo de productos adquiridos en la venta
    venta = rec->datosVenta->venta;

    // recorrer arreglo de productos adquiridos en la venta
    for (i = 0; venta[i] != NULL; ++i)
    {
      if (venta[i] != NULL)
      {
        if (venta[i]->venta != NULL)
        {
          // verificar si el producto actual coincide con el producto dado
          if (venta[i]->venta == producto)
          {
            // incrementar el total de inventario y el contador de ventas
            totalInventario += venta[i]->venta->stock;
            totalVentas++;
          }
        }
      }
    }
    rec = rec->sig;
  }

  if (totalVentas > 0)
  {
    promedioInventario = (double) totalInventario / (double)totalVentas;
  }
  return promedioInventario;
}

double calcularRotacionProductoIndividual(struct Producto *producto, struct NodoProveedor *proveedores)
{
    if(producto == NULL || proveedores == NULL || proveedores->sig == NULL)
        return 0.0;

    double ingresos = 0.0;
    double promedioInventario = 0.0;
    double rotacion = 0.0;
    struct NodoProveedor * rec = proveedores->sig;

    while(rec != NULL)
    {
        if(rec->datosProveedor != NULL)
        {
            if(rec->datosProveedor->ventas != NULL)
            {
                ingresos += calcularIngresosProductoIndividual(producto, rec->datosProveedor->ventas);
                promedioInventario += calcularPromedioInventarioProductoIndividual(producto, rec->datosProveedor->ventas);
            }
        }
        rec = rec->sig;
    }

    if (promedioInventario > 0.0)
    {
        rotacion = ingresos / promedioInventario;
    }
    return rotacion;
}

void recorrerArbolYHacerTopRotacion(struct NodoProducto *nodo, struct NodoProveedor * proveedores)
{
    int numProductos = 0;
    struct Rotacion **productos = (struct Rotacion**)malloc(MAX*sizeof(struct Rotacion*));
    int indice;

    if (nodo != NULL)
    {

        *(productos[numProductos]->rotacion) = calcularRotacionProductoIndividual(nodo->datosProducto, proveedores);
        productos[numProductos]->producto = nodo->datosProducto;
        numProductos++;

        recorrerArbolYHacerTopRotacion(nodo->izq, proveedores);
        recorrerArbolYHacerTopRotacion(nodo->der, proveedores);
    }

    // imprimir top
    printf("top de productos con más rotación\n");
    for (indice = 0; indice < numProductos ; indice++)
    {
        printf("%s - rotacion: %f\n", productos[indice]->producto->nombre, productos[indice]->rotacion);
    }

    return;
}




int main(void) {
  struct SistemaMercaditoLibre *sistemaMercadito;
  int opcion;
  int c;
  int checkOpcion = 1;
  int i;
  int minimoStock = 25;
  int idProducto;
  int idCompra; 
  int idVenta;
  char *opcionTmp;
  char *rutCliente;
  char *rutProveedor;
  
  struct NodoProveedor * listaProveedor = NULL;
  struct NodoCliente * listaCliente = NULL;

  struct NodoCliente * mejorC = NULL;
  struct NodoCliente * peorC = NULL;
  struct Cliente * clienteQuitado = NULL;
  struct Proveedor * proveedorQuitado = NULL;
  struct Compra * compra = NULL;
  struct Venta * venta = NULL;
  
  opcionTmp = (char *) malloc(sizeof(char) * 3);
  rutCliente = (char*) malloc(sizeof(char) * 15);
  rutProveedor = (char*) malloc(sizeof(char) * 15);

  sistemaMercadito = (struct SistemaMercaditoLibre *) malloc(sizeof(struct SistemaMercaditoLibre));

  sistemaMercadito->clientes = listaCliente;
  sistemaMercadito->proveedores = listaProveedor;
  sistemaMercadito->productos = NULL;

  printf("================================================\n");
  printf("           Bienvenido\n");
  printf("================================================\n");
  do
  {
    printf("\nSeleccione un modulo\n");
    printf("[1] Agregar Producto\n");
    printf("[2] Agregar Cliente\n");
    printf("[3] Agregar Proveedor\n");
    printf("[4] Agregar Compra de cliente\n");
    printf("[5] Agregar Compra a proveedor\n");
    printf("[6] Mostrar Productos\n");
    printf("[7] Mostrar Clientes\n");
    printf("[8] Mostrar Proveedores\n");
    printf("[9] Mostrar Compras hechas por clientes\n");
    printf("[10] Mostrar Compras hechas a proveedores\n");
    printf("[11] Modificar campos de un Cliente\n");
    printf("[12] Modificar campos de un Proveedor\n");
    printf("[13] Modificar campos de un Producto\n");
    printf("[14] Quitar a un cliente\n");
    printf("[15] Quitar a un proveedor\n");
    printf("[16] borrar producto\n"); 
    printf("[20] Saber que cliente es el que mas a comprado\n");
    printf("[21] Saber que cliente es el que menos ha comprado\n");
    printf("[30] Ordenar clientes por rut\n");
    printf("[31] Ordenar proovedor por rut\n");
    printf("[32] Ordenar Ventas por id\n");
    printf("[33] Ordenar Compras por id\n");
    printf("[34] buscar y mostrar una compra especifica por id\n");//
    printf("[35] buscar y mostrar una venta especifica por id\n");//
    printf("[36] Mostrar los productos con mayor rotación\n");
    printf("[0] Salir\n\n");

    do
    {
        scanf("%2s",opcionTmp);
        for(i = 0; opcionTmp[i] != '\0'; i++)
        {
            if(isdigit(opcionTmp[i]))
            {
              checkOpcion = 0;
            }

            else
            {
              checkOpcion = 1;
              break;
            }
          
        }
      
        while ((c = getchar()) != '\n') {
        }

    }while(checkOpcion);

    checkOpcion = 1;
    opcion = atoi(opcionTmp);
    
    printf("seleccionaste %i\n", opcion);
    
    switch(opcion)
    {
      case 1:
        agregarProducto(sistemaMercadito);
        break;
      
      case 2:
        agregarCliente(&listaCliente, sistemaMercadito);
        break;
      
      case 3:
        agregarProveedor(&listaProveedor, sistemaMercadito);
        break;

      case 4:
        agregarCompra(sistemaMercadito);
        break;
      
      case 5:
        agregarVenta(sistemaMercadito);
        break;
      
      case 6:
        listarProductos(sistemaMercadito);
        break;
      
      case 7:
        printf("\nMostrar clientes:\n\n");
        listarClientes(sistemaMercadito->clientes);
        break;
      
      case 8:
        printf("\nMostrar proveedores:\n\n");
        listarProveedores(sistemaMercadito->proveedores);
        break;
      
      case 9:
        listarCompras(sistemaMercadito);
        break;
      
      case 10:
        listarVentas(sistemaMercadito);
        break;
      
      case 11:
        if(rutCliente != NULL){
            printf("\nEscriba el Rut del cliente a modificar: ");
            scanf("%14s", rutCliente);
            while ((c = getchar()) != '\n'){
            }
            modificarCliente(&(sistemaMercadito->clientes), rutCliente);
        }
        break;
      
      case 12:
        if(rutProveedor != NULL){
            printf("\nEscriba el Rut del Proveedor a modificar: ");
            scanf("%14s", rutProveedor);
            while ((c = getchar()) != '\n'){
            }
            modificarProveedor(&(sistemaMercadito->proveedores), rutProveedor);
        }
        break;
      
      case 13:
        printf("\nEscriba el Id del producto que desea modificar: ");
        scanf("%d", &idProducto);
        modificarProducto(&(sistemaMercadito->productos), idProducto);
        break;
      
      case 14:
        if(rutCliente != NULL)
        {
          printf("\nEscriba el Rut del cliente a quitar: ");
          scanf("%14s", rutCliente);
          while ((c = getchar()) != '\n'){
          }
          clienteQuitado = quitarCliente(sistemaMercadito->clientes, rutCliente);
          if(clienteQuitado != NULL)
          {
            printf("El cliente quitado se llama: %s\n", clienteQuitado->nombre);
            printf("Su Rut es: %s\n", clienteQuitado->rut);
            printf("Su email es: %s\n\n", clienteQuitado->email);
          }
          
        }
        break;
      
      case 15:
        if(rutProveedor != NULL)
        {
            printf("\nEscriba el Rut del Proveedor a quitar: ");
            scanf("%14s", rutProveedor);
            while ((c = getchar()) != '\n'){
            }
            proveedorQuitado = quitarProveedor(sistemaMercadito->proveedores, rutProveedor);
            if(proveedorQuitado != NULL)
            {
              printf("El proveedor quitado se llama: %s\n", proveedorQuitado->nombre);
              printf("Su Rut es: %s\n", proveedorQuitado->rut);
              printf("Su Direccion es: %s\n\n", proveedorQuitado->direccion);
            }
            
          }
        break;

      case 16:
        printf("\nEscriba el Id del producto que desea Borrar: ");
        scanf("%d", &idProducto);
        if(buscarProducto(sistemaMercadito->productos, idProducto) != NULL)
        {
          borrarProducto(&(sistemaMercadito->productos), idProducto);
        }
        break;
      
      case 20:
        mejorC = mejorCliente(sistemaMercadito->clientes);
        if(mejorC != NULL)
        {
          printf("\nEl cliente que ha comprado mas productos se llama: %s\n", mejorC->datosCliente->nombre);
          printf("Su rut es: %s\n", mejorC->datosCliente->rut);
          printf("Su email es: %s\n\n",mejorC->datosCliente->email);
        }
        break;
      case 21:
      peorC = peorCliente(sistemaMercadito->clientes);
      if (peorC != NULL)
      {
        printf("\nEl cliente que ha comprado menos productos se llama :%s\n", peorC->datosCliente->nombre);
        printf("Su rut es: %s\n", peorC->datosCliente->rut);
        printf("Su email es: %s\n\n", peorC->datosCliente->email);
      }
      break;

      case 30:
        ordenarClientesPorRut(sistemaMercadito);
        break;

      case 31:
        ordenarProveedoresPorRut(sistemaMercadito);
        break;

      case 32:
        ordenarVentasPorId(sistemaMercadito);
        break;

      case 33:
        ordenarComprasPorId(sistemaMercadito);
        break;
      
      case 34:
        printf("\nEscriba el Id de la compra: ");
        scanf("%d", &idCompra);
        compra = buscarCompra(sistemaMercadito->clientes, idCompra);
        if( compra != NULL)
        {
          escribirCompra(compra->compras);
        }
        break;
      
      case 35:
        printf("\nEscriba el Id de la Venta: ");
        scanf("%d", &idVenta);
        venta = buscarVenta(sistemaMercadito->proveedores, idVenta);
        if( venta != NULL)
        {
          escribirVenta(venta->venta);
        }
        break;

      case 36:
        recorrerArbolYHacerTopRotacion(sistemaMercadito->productos, sistemaMercadito->proveedores);
        break;
      
      case 0: 
        break;
      
      default:
        printf("Opcion no valida vuelve a intentarlo\n");
        break;
    }
    
    avisarBajoStock(sistemaMercadito->productos, minimoStock);
    
  }while(opcion != 0);
  
  printf("================================================\n");
  printf("           Adios\n");
  printf("================================================\n");
  return 0;
}