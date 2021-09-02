//rev 0.2 20210902

#define reso 144 //MCM de las subdivisiones ritmicas utilizadas
#define multReso 1 // en caso de querer mejorar la resolución del índice

#include <LedControl.h>
#define NumMatrix 1

// pinData, pinClock, pinLoad, NumMatrices
LedControl lc = LedControl(12, 10, 11, NumMatrix);

int tempoMS = 1000; //tempo de la máquina (en ms)

float tikTime;
int indice;
int samples;

byte    divs[]  = {  1,  2,  3,  4,  6,  8,  9, 12, 16};
bool    flag[]  = {  0,  0,  0,  0,  0,  0,  0,  0,  0};
bool    pFlag[] = {  0,  0,  0,  0,  0,  0,  0,  0,  0};
int     index[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1};
byte    out[]   = {  2,  3,  4,  5,  6,  7,  8,  9, 13};

byte   initX[]  = {  0,  1,  3,  6,  2,  0,  4,  0,  0}; // FILA INICIAL MAX7219
byte   initY[]  = {  0,  0,  0,  0,  1,  2,  6,  5,  3}; // COLUMNA INICIAL

byte    posX[]  = {  0,  0,  0,  0,  0,  0,  0,  0,  0}; // FILA INICIAL MAX7219
byte    posY[]  = {  0,  0,  0,  0,  0,  0,  0,  0,  0}; // COLUMNA INICIAL

unsigned long currentMillis, pMillis;
unsigned long ledMillis[9] = {  0,  0,  0,  0,  0,  0,  0,  0,  0};
bool          ledState[9]  = {  0,  0,  0,  0,  0,  0,  0,  0,  0};
bool          outState[9]  = {  0,  0,  0,  0,  0,  0,  0,  0,  0};
int           onTime; // Tiempo de encendido de led
int           outTime; // Tiempo de encendida salida

int     clockIn = 1000;
int     minTime = 650;
int     maxTime = 5000;
int cvIn = 0;

int reset, pReset, flagReset;

int clockPin = A0;
int resetPin = A1;
int cvPin = A2;

void setup() {

// Serial.begin(9600);
  indice = 0;
  onTime = 30;
  outTime = 30;
  reset = 1;
  pReset = 1;
  samples = reso * multReso; // NUMERO DE SAMPLES DEL INDICE
  ledInit();

  for (int i = 0; i <= 8; i++) {
    pinMode(out[i], OUTPUT); //SALIDAS CHANNELS
  }
  pinMode(clockPin, INPUT);
  pinMode(resetPin, INPUT);
  pinMode(cvPin, INPUT);

  
}

void updateCh() {

  for (int i = 0; i <= 8; i++) {
    if (indice % (samples / divs[i]) == 0) { //SUBDIVISIONES POSIBLES
      flag[i] = 1;                          //AVISA ENCENDIDO
      if (flag[i] != pFlag[i]) {            //SOLO POR 1 TIK
        if (flag[i] == 1 && ledState[i] == 0) {
          ledMillis[i] = currentMillis;
          ledState[i] = HIGH;
          outState[i] = HIGH;
          digitalWrite(out[i], HIGH);
          index[i]++;
          if (index[i] >= divs[i])index[i] = 0; // LIMITE EL CANAL DEL INDEX A SU TAMAÑO
        }
      }
      pFlag[i] = flag[i];
    }
    else {
      flag[i] = 0;
      pFlag[i] = flag[i];
    }

    // Chequeo posiciones Leds
    posX[i] = initX[i] + index[i];
    posY[i] = initY[i];
    if (posX[i] > 7) {
      posX[i] = index[i] - (8 - initX[i]);
      posY[i] = initY[i] + 1;
    }

    //Encendido Leds
    if (ledState[i] == HIGH) {
      lc.setLed(0, posX[i], posY[i], HIGH);
    }
    if ((currentMillis - ledMillis[i]) > onTime && ledState[i] == HIGH) {
      lc.setLed(0, posX[i], posY[i], LOW);
      ledState[i] = LOW;
    }

    // Encendido Outputs
    if ((currentMillis - ledMillis[i]) > outTime && outState[i] == HIGH) {
      digitalWrite(out[i], LOW);
      outState[i] = LOW;
    }

  }

}

void loop() {
  currentMillis = millis();

  indexTiming();
  
   updateCh();

  clockIn = analogRead(A0);
  cvIn = analogRead(A2);
//  tempoMS = map(clockIn, 0, 1023, minTime, maxTime);
//Serial.print("tempo ms = ");
//  Serial.print(tempoMS);
//  Serial.print("| clockIn ");
//  Serial.print(clockIn);
//   Serial.print("| cvIn ");
//  Serial.println(cvIn);
//  

    outTime = (tempoMS /144)*4;
    onTime = (tempoMS /144)*4;

}

void ledInit() {
  // Inicializar matriz
  lc.shutdown(0, false); // Activar la matriz
  lc.setIntensity(0, 1); // Poner el brillo a un valor intermedio
  lc.clearDisplay(0);    // Y borrar todo
}

void indexTiming() {
  tikTime = tempoMS / samples;
  currentMillis = millis();

  reset = digitalRead(resetPin);
  if (reset != pReset){
    if (reset == LOW){
      indice = 0;
      for (int i = 0; i<= 8; i++){
        lc.clearDisplay(0);
        index[i] = -1;
        ledState[i] = LOW;
      }
    }
  }
  flagReset = 1;
  pReset = reset;

  if (currentMillis - pMillis >= tikTime) {
   tempoMS = map(clockIn + cvIn, 0, 2047, maxTime, minTime);
    indice++;
    pMillis = currentMillis;
  }
  if (indice >= samples) {
    indice = 0;
  }

}
