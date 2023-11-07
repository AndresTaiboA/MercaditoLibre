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

//Funciones cliente

struct NodoCliente * buscarCliente(struct NodoCliente * clientes, char * rut)
{
  struct NodoCliente * rec = clientes;
  if(clientes != NULL)
  {
    do
    {
      if(strcmp(rec->datosCliente->rut,rut) == 0)
      {
        return rec;
      }
      rec = rec->sig;
    }while(rec != clientes);
  }
  return NULL;
}
void escribirDatosCliente(struct NodoCliente * cliente)
{
  printf("Rut: %s\n",cliente->datosCliente->rut);
  printf("Nombre: %s\n",cliente->datosCliente->nombre);
  printf("Email: %s\n\n",cliente->datosCliente->email);
}
void listarClientes(struct NodoCliente * clientes)
{
  printf("\nMostrar clientes:\n\n");
  int cont = 0;
  struct NodoCliente * rec = clientes;
  if(clientes != NULL)
  {
    do
    {
      cont++;
      printf("Cliente %d\n", cont);
      escribirDatosCliente(rec);
      rec = rec->sig;
    }while(rec != clientes);
  }
}

void poblarCliente(struct Cliente **cliente)
{
    int c;
    char *rut = (char*) malloc(sizeof(char) * 15);
    char *nombre = (char*) malloc(sizeof(char) * 50);
    char *email = (char*) malloc(sizeof(char) * 30);

    printf("Ingrese Rut:\n");
    if(rut != NULL){
        scanf("%14s", rut);
        while ((c = getchar()) != '\n'){
        }
    }
    printf("Ingrese Nombre:\n");
    if(nombre != NULL){
        scanf("%49s", nombre);
        while ((c = getchar()) != '\n'){
        }
    }
    printf("Ingrese Email:\n");
    if(email != NULL){
        scanf("%29s", email);
        while ((c = getchar()) != '\n'){
        }
    }
    (*cliente)->rut = rut;
    (*cliente)->nombre = nombre;
    (*cliente)->email = email;
    (*cliente)->compras = NULL;
}

struct NodoCliente * crearNodoCliente(void)
{
    struct NodoCliente *nodo = NULL;
    struct Cliente *cliente = NULL;
    nodo = (struct NodoCliente*) malloc(sizeof(struct NodoCliente));

    if(nodo != NULL)
    {
        cliente = (struct Cliente*) malloc(sizeof(struct Cliente));
        if(cliente != NULL)
        {
          poblarCliente(&cliente);
          nodo->datosCliente = cliente;
          nodo->ant = nodo;
          nodo->sig = nodo;
        }
    }
    return nodo;
}

void agregarCliente(struct NodoCliente **head, struct SistemaMercaditoLibre * sistemaMercadito)
{
    struct NodoCliente *cliente = NULL;
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
            ultimo = (*head)->ant;
            cliente->sig = (*head);
            cliente->ant = ultimo;

            ultimo->sig = cliente;
            (*head)->ant = cliente;
        }

    }

}

struct Cliente * quitarCliente(struct NodoCliente * clientes, char * rut)
{
  struct NodoCliente * rec = clientes;
  struct Cliente * clienteQuitado = NULL;
  if (clientes != NULL)
  {
    do
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
      rec = rec->sig;
    }while(rec != clientes);
  }
  return clienteQuitado;
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
            printf("\nSeleccione el area que desea modificar en el perfil del cliente\n");
            printf("[1] Nombre\n");
            printf("[2] Email\n");
            printf("[0] Salir\n\n");

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
            };

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

//Funciones proveedor

struct NodoProveedor * buscarProveedor(struct NodoProveedor * proveedores, char * rut)
{
  struct NodoProveedor * rec = proveedores->sig;
  if(proveedores != NULL)
  {
    while(rec != NULL)
    {
      if(strcmp(rec->datosProveedor->rut,rut) == 0)
      {
        return rec;
      }
      rec = rec->sig;
    };
  }
  return NULL;
}
void escribirDatosProveedor(struct NodoProveedor * proveedor)
{
  printf("Rut: %s\n",proveedor->datosProveedor->rut);
  printf("Nombre: %s\n",proveedor->datosProveedor->nombre);
  printf("Direccion: %s\n\n",proveedor->datosProveedor->direccion);
}
void listarProveedores(struct NodoProveedor * proveedor)
{
  printf("\nMostrar proveedores:\n\n");
  int cont = 0;
  struct NodoProveedor * rec = proveedor->sig;
  if(proveedor != NULL)
  {
    while(rec != NULL)
    {
      cont++;
      printf("Proveedor %i\n",cont);
      escribirDatosProveedor(rec);
      rec = rec->sig;
    }
  }
}

void poblarProveedor(struct Proveedor **proveedor)
{
    int c;
    char *rut = (char*) malloc(sizeof(char) * 15);
    char *nombre = (char*) malloc(sizeof(char) * 50);
    char *direccion = (char*) malloc(sizeof(char) * 30);

    printf("Ingrese Rut:\n");
    if(rut != NULL){
        scanf("%14s", rut);
        while ((c = getchar()) != '\n'){
        }
    }
    printf("Ingrese Nombre:\n");
    if(nombre != NULL){
        scanf("%49s", nombre);
        while ((c = getchar()) != '\n'){
        }
    }
    printf("Ingrese Direccion:\n");
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
        while(rec->sig != NULL)
            rec = rec->sig;
        rec->sig = proveedor;
        rec->sig->ant = rec;
        rec->sig->sig = NULL;

    }
}

struct Proveedor * quitarProveedor(struct NodoProveedor * proveedores, char * rut)
{
  struct NodoProveedor * rec = proveedores->sig;
  struct Proveedor * proveedorQuitado = NULL;
  if(proveedores->sig != NULL)
  {
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
            printf("\nSeleccione el area que desea modificar en el perfil del proveedor\n");
            printf("[1] Nombre\n");
            printf("[2] Direccion\n");
            printf("[0] Salir\n\n");

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
            };

        }while(opcion != 0);

        return  1;
    }

    return 0;
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
void mostrarProducto(struct NodoProducto * producto)
{
  if(producto != NULL)
  {
    mostrarProducto(producto->izq);
    
    if(producto->datosProducto != NULL)
    {
      printf("Id: %i\n", producto->datosProducto->id);
      printf("Nombre: %s\n", producto->datosProducto->nombre);
      printf("Precio: %i\n", producto->datosProducto->precio);
      printf("Stock: %i\n", producto->datosProducto->stock);
      printf("\n");
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
            printf("\nSeleccione el area que desea modificar del producto\n");
            printf("[1] Nombre\n");
            printf("[2] Precio\n");
            printf("[0] Salir\n\n");

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
                        printf("Realize el cambio: ");
                        scanf("%d", &(producto->datosProducto->precio) );
                    break;

                case 0:
                    break;

                default:
                    printf("Opcion no valida vuelve a intentarlo\n");
                    break;
            };

        }while(opcion != 0);

        return  1;
    }

    return 0;
}

void avisarBajoStock(struct NodoProducto *ABB, int minimo)
{
    if(ABB != NULL)
    {
        if(ABB->datosProducto != NULL)
        {
            if(ABB->datosProducto->stock < minimo)
            {
                printf("\nAtencion Hay bajo stock en %s, hay exactamente: %d\n", ABB->datosProducto->nombre, ABB->datosProducto->stock);
            }
        }
        avisarBajoStock(ABB->izq, minimo);
        avisarBajoStock(ABB->der, minimo);
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
//Funciones extra


int main(void) {
  printf("================================================\n");
  printf("           Bienvenido\n");
  printf("================================================\n");
  struct SistemaMercaditoLibre *sistemaMercadito;
  int opcion;
  int c;
  int checkOpcion = 1;
  int i;
  int minimoStock = 25;
  int idProducto;
  char *opcionTmp;
  char *rutCliente;
  char *rutProveedor;
  opcionTmp = (char *) malloc(sizeof(char) * 3);
  rutCliente = (char*) malloc(sizeof(char) * 15);
  rutProveedor = (char*) malloc(sizeof(char) * 15);

  sistemaMercadito = (struct SistemaMercaditoLibre *) malloc(sizeof(struct SistemaMercaditoLibre));

  struct NodoProveedor * listaProveedor = NULL;
  struct NodoCliente * listaCliente = NULL;
  sistemaMercadito->clientes = listaCliente;
  sistemaMercadito->proveedores = listaProveedor;
  sistemaMercadito->productos = NULL;

  struct NodoCliente * mejorC = NULL;
  struct Cliente * clienteQuitado = NULL;
  struct Proveedor * proveedorQuitado = NULL;
  
  do
  {
    printf("\nSeleccione un modulo\n");
    printf("[1] Agregar Producto\n");
    printf("[2] Agregar Cliente\n");
    printf("[3] Agregar Proveedor\n");
    printf("[4] Agregar Compra de cliente\n");
    printf("[5] Mostrar Productos\n");
    printf("[6] Mostrar Clientes\n");
    printf("[7] Mostrar Proveedores\n");
    printf("[8] Mostrar Compras hechas por clientes\n");
    printf("[9] Mostrar Compras hechas a proveedores\n");
    printf("[10] Modificar campos de un Cliente\n");
    printf("[11] Modificar campos de un Proveedor\n");
    printf("[12] Modificar campos de un Producto\n");
    printf("[13] Quitar a un cliente\n");
    printf("[14] Quitar a un proveedor\n");
    printf("[20] Saber que cliente es el que mas a comprado\n");
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
        listarProductos(sistemaMercadito);
        break;
      
      case 6:
        listarClientes(sistemaMercadito->clientes);
        break;
      
      case 7:
        listarProveedores(sistemaMercadito->proveedores);
        break;
      
      case 8:
        listarCompras(sistemaMercadito);
        break;
      
      case 9:
        listarVentas(sistemaMercadito);
        break;
      
      case 10:
        if(rutCliente != NULL){
            printf("\nEscriba el Rut del cliente a modificar: ");
            scanf("%14s", rutCliente);
            while ((c = getchar()) != '\n'){
            }
            modificarCliente(&(sistemaMercadito->clientes), rutCliente);
        }
        break;
      
      case 11:
        if(rutProveedor != NULL){
            printf("\nEscriba el Rut del Proveedor a modificar: ");
            scanf("%14s", rutProveedor);
            while ((c = getchar()) != '\n'){
            }
            modificarProveedor(&(sistemaMercadito->proveedores), rutProveedor);
        }
        break;
      
      case 12:
        printf("\nEscriba el Id del producto que desea modificar: ");
        scanf("%d", &idProducto);
        modificarProducto(&(sistemaMercadito->productos), idProducto);
        break;
      
      case 13:
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
      
      case 14:
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
      
      case 20:
        mejorC = mejorCliente(sistemaMercadito->clientes);
        if(mejorC != NULL)
        {
          printf("\nEl cliente que ha comprado mas productos se llama: %s\n", mejorC->datosCliente->nombre);
          printf("Su rut es: %s\n", mejorC->datosCliente->rut);
          printf("Su email es: %s\n\n",mejorC->datosCliente->email);
        }
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