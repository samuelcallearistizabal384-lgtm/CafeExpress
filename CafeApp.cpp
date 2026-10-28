#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

// ==========================================
// 3. PATRÓN DE COMPORTAMIENTO: OBSERVER
// ==========================================
class IObserver {
public:
    virtual void actualizar(const string& mensaje) = 0;
    virtual ~IObserver() = default;
};

class Cliente : public IObserver {
private:
    string nombre;
public:
    Cliente(string n) : nombre(n) {}
    void actualizar(const string& mensaje) override {
        cout << "[Notificacion a " << nombre << "]: " << mensaje << endl;
    }
};

class PedidoSujeto {
private:
    vector<shared_ptr<IObserver>> observadores;
    string estado;
public:
    void agregarObservador(shared_ptr<IObserver> obs) {
        observadores.push_back(obs);
    }
    void notificar(const string& mensaje) {
        for (auto& obs : observadores) {
            obs->actualizar(mensaje);
        }
    }
    void cambiarEstado(const string& nuevoEstado) {
        estado = nuevoEstado;
        notificar("Su pedido ahora esta: " + estado);
    }
};

// ==========================================
// COMPONENTE BASE (Abstracción compartida)
// ==========================================
class IBebida {
public:
    virtual string getDescripcion() const = 0;
    virtual double costo() const = 0;
    virtual ~IBebida() = default;
};

// ==========================================
// 1. PATRÓN CREACIONAL: FACTORY METHOD
// ==========================================
class Cafe : public IBebida {
public:
    string getDescripcion() const override { return "Cafe Espresso"; }
    double costo() const override { return 5.00; }
};

class Te : public IBebida {
public:
    string getDescripcion() const override { return "Te Verde"; }
    double costo() const override { return 4.00; }
};

class CreadorBebida {
public:
    virtual unique_ptr<IBebida> crearBebida() = 0;
    virtual ~CreadorBebida() = default;
};

class CreadorCafe : public CreadorBebida {
public:
    unique_ptr<IBebida> crearBebida() override { return make_unique<Cafe>(); }
};

class CreadorTe : public CreadorBebida {
public:
    unique_ptr<IBebida> crearBebida() override { return make_unique<Te>(); }
};

// ==========================================
// 2. PATRÓN ESTRUCTURAL: DECORATOR
// ==========================================
class BebidaDecorator : public IBebida {
protected:
    unique_ptr<IBebida> bebida;
public:
    BebidaDecorator(unique_ptr<IBebida> b) : bebida(move(b)) {}
    string getDescripcion() const override { return bebida->getDescripcion(); }
    double costo() const override { return bebida->costo(); }
};

class AdicionCrema : public BebidaDecorator {
public:
    AdicionCrema(unique_ptr<IBebida> b) : BebidaDecorator(move(b)) {}
    string getDescripcion() const override { return bebida->getDescripcion() + " + Crema"; }
    double costo() const override { return bebida->costo() + 1.50; }
};

// ==========================================
// FLUJO PRINCIPAL DE LA APLICACIÓN
// ==========================================
int main() {
    cout << "=== SISTEMA CAFEEXPRESS ===" << endl;

    // 1. Uso del patrón Creacional (Factory Method)
    unique_ptr<CreadorBebida> creador = make_unique<CreadorCafe>();
    unique_ptr<IBebida> miBebida = creador->crearBebida();

    // 2. Uso del patrón Estructural (Decorator)
    miBebida = make_unique<AdicionCrema>(move(miBebida));

    cout << "Producto: " << miBebida->getDescripcion() << endl;
    cout << "Costo Total: $" << miBebida->costo() << endl;

    // 3. Uso del patrón de Comportamiento (Observer)
    PedidoSujeto pedido;
    shared_ptr<Cliente> cliente = make_shared<Cliente>("Samuel");
    pedido.agregarObservador(cliente);

    pedido.cambiarEstado("En preparacion");
    pedido.cambiarEstado("Listo para retirar");

    return 0;
}
