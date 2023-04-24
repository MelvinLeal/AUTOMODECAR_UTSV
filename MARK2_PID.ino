#define echoPin 3 // Se define el pin que se utilizará para el Echo del sensor ultrasónico
#define trigPin 2// Se define el pin que se utilizará para el Trigger del sensor ultrasónic

int puntodeseado = 15; // Se da la distancia que debe mantener el carrito de un objeto (en este caso en centímetros)

float duracion, pid, salida, h, distancia, tk, tk_1 = 0, error = 0, error_anterior = 0, derivative = 0, integral = 0, kp = 8, kd = 11, ki = .000001;
//MOTOR IZQUIERDO
const int pwma = 10;
const int a = 8;
const int b = 9;
//MOTOR DERECHO
const int pwmb = 11;
const int c = 12;
const int d = 13;

void setup() {



  TCCR2B = TCCR2B & 0b11111000 | 0x07; // Este comando se utiliza para cambiar la frecuencia de salida del motor para que no suene (este paso es opcional)
  Serial.begin (9600);

  pinMode(2, OUTPUT);//pines del sensor de ultrasonido
  pinMode(3, INPUT);

  //DEFINIR PUERTOS
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);


  //ACTIVADOR CONTROLADOR

  //digitalWrite(stby, HIGH);



}

void loop() {




  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);// datos del sensor de ultrasonido
  distancia = duracion / 58.4; //se calcula la distancia en cm con respecto a la velocidad del sonido con el sensor de ultrasonido
  distancia = round(distancia); //Se redondea el valor obtenido (esto es opcional)
  tk = millis(); //guardamos en tk el tiempo que a transcurido desde que el arduino comenzó a trabajar
  h = tk - tk_1; //guardamos en h el perdiodo de ciclo
  error = puntodeseado - distancia;//calculamos el error
  integral = integral + (error * h); //se calcula el integral del error
  derivative = (error - error_anterior) / h; //se calcula la derivada del error
  pid = (error * kp) + (integral * ki) + (derivative * kd); // ecuaciones del pid
  error_anterior = error;//se manda el error actual al error anterior
  tk_1 = tk; //se manda el tiempo actual al tiempo anterior

  if (pid > 85)     {
    pid  = 85; // Se pone un límite en el valor máximo que puede alcanzar el valor de pid (esto es opcional, en mi caso ayudo a tener una mejor respuesta)
  }
  else if (pid < -100) {
    pid = -100; //Se pone un límite en el valor mínimo que puede alcanzar el valor de pid (esto es opcional, en mi caso ayudo a tener una mejor respuesta)
  }


  if (pid < 0)
  {
    analogWrite(10, 110);
    analogWrite(11, 110);



    digitalWrite(8, HIGH); digitalWrite(9, HIGH); //IZQUIERO ENFRENTE
   // digitalWrite(8, LOW); digitalWrite(9, HIGH); //IZQUIERO ATRAS
   //digitalWrite(12, HIGH); digitalWrite(13, LOW);//DERECHO ENFRENTE
    digitalWrite(12, LOW); digitalWrite(13, HIGH);//DERECHO ATRAS
    delay(500);

  }

  else
  {
   // analogWrite(10, 250);
    //analogWrite(11, 250);
    digitalWrite(9, LOW); digitalWrite(8, LOW);
    digitalWrite(12, LOW); digitalWrite(13, LOW);


  }
  // Estos comandos son para vizualizar los datos obtenidos en el monitor serie (esta en la pestaña de herramientas )

  //Serial.begin(pid);//iniciación de comunicación serial a 9600 baudios
  Serial.print("distancia:");
  Serial.print(distancia);
  //Serial.print(",");
  //Serial.print("Salida:");
  //Serial.print(",");
  //Serial.print("PID:");
  //Serial.print(pid);
  //Serial.print(",");
  //Serial.println(puntodeseado);


}
