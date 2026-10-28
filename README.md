# CaféExpress: Sistema Integrado de Pedidos en C++

## 1. Integrantes del Grupo
* Samuel Calle Aristizabal

## 2. Nombre de la Aplicación y Problema que Resuelve
* **Nombre:** CaféExpress (Simulador de pedidos de una cafetería).
* **Problema:** Sin patrones de diseño, añadir nuevas bebidas o complementos requeriría modificar el código central con múltiples estructuras condicionales (`if-else`), haciendo el sistema rígido y difícil de escalar. Esta aplicación usa patrones para desacoplar la creación de objetos, la personalización y las notificaciones a los clientes.

## 3. Patrones de Diseño Elegidos
La aplicación integra tres patrones obligatorios del catálogo de Refactoring.Guru:
1. **Creacional (Factory Method):** Se encarga de instanciar las familias de bebidas base (`Café`, `Té`) desacoplando su creación del flujo principal.
2. **Estructural (Decorator):** Envuelve dinámicamente la bebida base para añadir extras (como crema) modificando costos y descripciones en tiempo de ejecución compartiendo la misma interfaz.
3. **De Comportamiento (Observer):** Mantiene sincronizado al cliente notificándole automáticamente los cambios de estado del pedido.

## 4. Diagrama de Relaciones entre Patrones
```text
[CreadorBebida / Factory Method] ---> crea ---> [IBebida (Interfaz Base)]
                                                      ^
                                                      | es envuelto por
                                              [BebidaDecorator / Decorator]

[PedidoSujeto / Observer] ---> notifica a ---> [Cliente (IObserver)]
```
