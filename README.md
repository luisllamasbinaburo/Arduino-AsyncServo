# Librería Arduino AsyncServo
Librería de Arduino que permite mover un servo de forma no bloqueante. De esta forma se tiene un servo que tiene un cierto comportamiento "asíncrono".

Más información https://www.luisllamas.es/libreria-arduino-asyncservo/

## Instrucciones de uso
La clase AsyncServo implementa un servo cuyos movimientos están temporizados, en lugar de ser bloqueantes. El objetivo de la librería es poder mover uno o varios servos en un proyecto, incluso a diferentes velocidades, mientras que no se impide la ejecución otras tareas en el bucle de control principal.

Un objeto Asyncservo se instancia a través de su constructor, similar a la de un servo convencional. La posición puede indicarse mediante tres acciones,

- Write, recibe el ángulo en decigrados.
- WriteDegrees, recibe el ángulo en grados.
- WriteMicroseconds, recibe el ángulo en microsegundos.

La opción por defecto `Write` se usa decigrados, porque proporciona una precisión superior a indicar los ángulos en grados con `WriteDegree`, pero sin añadir la complejidad de uso que supone indicar microsegundos con `WriteMicroseconds`.

El comportamiento "asíncrono” se consigue mediante las funciones `Move` y `MoveDegress`, que reciben la posición deseada para el servo y el tiempo del desplazamiento.

Para actualizar la posicion del servo es necesario llamar a la función `Update`, que debe ser llamada frecuentemente desde el bucle de control principal

Opcionalmente, los métodos `Move` y `MoveDegress` admiten una función de callback final, que resulta útil para formar movimientos encadenados y loops.

Adicionalmente se tienen de otras funciones para mejorar el uso de un servo en un proyecto real. Estas funciones son `SetInput` y `SetOutput`, que establecen el rango de entrada y salida para el servo, y ayudan a calibrar el servo. Esto es muy útil en el caso de robots articulados. Por ejemplo, es posible hacer que mapee los valores de -90º, 0º y 90º a 0.1º, 90.5º y 179.9.

### Uso como objeto
La clase AsyncServo puede instanciarse como un objeto a través de su constructor, y se actualiza con el método `Update()`.
```c++
// Constructor
AsyncServo();

// Vincular el AsyncServo a un pin I/O
uint8_t Attach(int pin);
void Detach();

// Actualiza la posicion del servo
// Es necesario llamar a este metodo frecuentemente desde el bucle principal
void Update();

// Establecer el mapeo de rango de entrada y salida
void SetInput(int low, int mid, int high);
void SetOutput(int low, int mid, int high);

// Mover instantameamente el servo
void write(int dec);
void WriteDegree(int deg);
void WriteMicroseconds(int uS);

// Estado del servo
int Read();
int16_t GetCurrentPosition() const;

// Mover el servo de forma temporizada ("asincrona")
void Move(int dec, int timeMs);
void Move(int dec, int timeMs, ServoAction finish);
void MoveDegrees(int deg, int timeMs);
void MoveDegrees(int deg, int timeMs, ServoAction finish);
void Stop();

// Callback cuando acaba un movimiento temporizado
ServoAction Finish;
```


## Ejemplos
La librería AsyncServo incluye los siguientes ejemplos para ilustrar su uso.

* Sweep: Ejemplo que muestra como hacer un efecto balanceo con AsyncServo
```c++
#include "AsyncServoLib.h"

AsyncServo asyncServo;

void setup()
{
	Serial.begin(115200);
	Serial.println("Restart");
	
	asyncServo.Attach(9);
	asyncServo.SetOutput(500, 1500, 2500);

	step1();
}

void step1()
{
	asyncServo.Move(1350, 4000, step2);
}

void step2()
{
	asyncServo.Move(450, 4000, step1);
}


void loop()
{
	asyncServo.Update();
}
```


* TwoServos: Ejemplo que extiende el ejemplo Sweep a dos servos
```c++
#include "AsyncServoLib.h"

AsyncServo asyncServo09;
AsyncServo asyncServo10;

void setup()
{
	Serial.begin(115200);
	Serial.println("Restart");
	
	asyncServo09.Attach(9);
	asyncServo10.Attach(10);

	asyncServo09.SetOutput(500, 1500, 2500);
	asyncServo10.SetOutput(500, 1500, 2500);
	delay(1000);
	asyncServo10.write(450);
	delay(1000);
	asyncServo10.write(1350);
	delay(1000);
	asyncServo10.write(900);
	delay(1000);

	step1();
	step4();
}

void step1()
{
	asyncServo10.Move(1350, 2000, step2);
}

void step2()
{
	asyncServo10.Move(450, 2000, step1);
}


void step4()
{
	asyncServo09.Move(1350, 4000, step5);
}

void step5()
{
	asyncServo09.Move(450, 4000, step4);
}


void loop()
{
	delay(10);
	asyncServo09.Update();
	asyncServo10.Update();
}
```
