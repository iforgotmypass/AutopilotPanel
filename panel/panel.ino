#include <ShiftLCD.h>
ShiftLCD lcd(2, 4, 3);
ShiftLCD lcd2(5, 7, 6);


#define CLK_HDG 22
#define DT_HDG 23
#define SW_HDG 24
#define CLK_ALT 25
#define DT_ALT 27
#define SW_ALT 26
#define CLK_IAS 28
#define DT_IAS 29
#define SW_IAS 30
#define CLK_VSP 31
#define DT_VSP 32
#define SW_VSP 33
#define CLK_CRS 34
#define DT_CRS 35
#define SW_CRS 36
#define AP_SW 37
#define AP_LED 38

int counterHDG = 0;
int counterHDG_tmp, counterALT_tmp, counterIAS_tmp, counterVSP_tmp, counterCRS_tmp;
int currentStateHDG;
int lastStateHDG;
int counterALT = 0;
int currentStateALT;
int lastStateALT;
int counterIAS = 0;
int currentStateIAS;
int lastStateIAS;
int counterVSP = 0;
int currentStateVSP;
int lastStateVSP;
int counterCRS = 0;
int currentStateCRS;
int lastStateCRS;
int APButtonState = 0;
bool APState = false;

unsigned long lastButtonPressHDG = 0;
unsigned long lastButtonPressALT = 0;
unsigned long lastButtonPressIAS = 0;
unsigned long lastButtonPressVSP = 0;
unsigned long lastButtonPressCRS = 0;
unsigned long lastButtonPressAP = 0;

void setup() {
    pinMode(CLK_HDG,INPUT);
    pinMode(DT_HDG,INPUT);
    pinMode(SW_HDG, INPUT_PULLUP);
    pinMode(CLK_ALT,INPUT);
    pinMode(DT_ALT,INPUT);
    pinMode(SW_ALT, INPUT_PULLUP);
    pinMode(CLK_IAS,INPUT);
    pinMode(DT_IAS,INPUT);
    pinMode(SW_IAS, INPUT_PULLUP);
    pinMode(CLK_VSP,INPUT);
    pinMode(DT_VSP,INPUT);
    pinMode(SW_VSP, INPUT_PULLUP);
    pinMode(CLK_CRS,INPUT);
    pinMode(DT_CRS,INPUT);
    pinMode(SW_CRS, INPUT_PULLUP);
    pinMode(AP_SW, INPUT);

    lcd.begin(16, 2);
    lcd2.begin(16, 2);
    Serial.begin(9600);

    lastStateHDG = digitalRead(CLK_HDG);
    lastStateALT = digitalRead(CLK_ALT);
    lastStateIAS = digitalRead(CLK_IAS);
    lastStateVSP = digitalRead(CLK_VSP);
    lastStateCRS = digitalRead(CLK_CRS);
}

void loop() {
    if (counterHDG_tmp != counterHDG){
        lcd.setCursor(0,0);
        lcd.clear();
        lcd.print("HDG:");
        lcd.setCursor(4,0);
        lcd.print(counterHDG);
        lcd.setCursor(8,0);
        lcd.print("IAS:");
        lcd.setCursor(12,0);
        lcd.print(counterIAS);
        lcd.setCursor(0,1);
        lcd.print("ALT:");
        lcd.setCursor(4,1);
        lcd.print(counterALT*100);
    }

    if (counterALT_tmp != counterALT){
        lcd.setCursor(0,0);
        lcd.clear();
        lcd.print("HDG:");
        lcd.setCursor(4,0);
        lcd.print(counterHDG);
        lcd.setCursor(8,0);
        lcd.print("IAS:");
        lcd.setCursor(12,0);
        lcd.print(counterIAS);
        lcd.setCursor(0,1);
        lcd.print("ALT:");
        lcd.setCursor(4,1);
        lcd.print(counterALT*100);
    }    

    if (counterIAS_tmp != counterIAS){
        lcd.setCursor(0,0);
        lcd.clear();
        lcd.print("HDG:");
        lcd.setCursor(4,0);
        lcd.print(counterHDG);
        lcd.setCursor(8,0);
        lcd.print("IAS:");
        lcd.setCursor(12,0);
        lcd.print(counterIAS);
        lcd.setCursor(0,1);
        lcd.print("ALT:");
        lcd.setCursor(4,1);
        lcd.print(counterALT*100);
    }  

    if (counterVSP_tmp != counterVSP){
        lcd2.clear();
        lcd2.setCursor(0,0);
        lcd2.print("VS:");
        lcd2.setCursor(3,0);
        lcd2.print(counterVSP*100);
        lcd2.setCursor(0,1);
        lcd2.print("CRS:");
        lcd2.setCursor(4,1);
        lcd2.print(counterCRS);
    }    

    if (counterCRS_tmp != counterCRS){
        lcd2.clear();
        lcd2.setCursor(0,0);
        lcd2.print("VS:");
        lcd2.setCursor(3,0);
        lcd2.print(counterVSP*100);
        lcd2.setCursor(0,1);
        lcd2.print("CRS:");
        lcd2.setCursor(4,1);
        lcd2.print(counterCRS);
    }
    counterHDG_tmp = counterHDG;
    counterALT_tmp = counterALT;
    counterIAS_tmp = counterIAS;
    counterVSP_tmp = counterVSP;
    counterCRS_tmp = counterCRS;
    currentStateHDG = digitalRead(CLK_HDG);
    currentStateALT = digitalRead(CLK_ALT);
    currentStateIAS = digitalRead(CLK_IAS);
    currentStateVSP = digitalRead(CLK_VSP);
    currentStateCRS = digitalRead(CLK_CRS);

    // ################### HDG COUNTING ###################

    if (currentStateHDG != lastStateHDG  && currentStateHDG == 1){
        if (digitalRead(DT_HDG) != currentStateHDG) {
        counterHDG++;
        } else {
        counterHDG--;
        }
        if (counterHDG < 0){
            counterHDG = 359;
        }
        
        counterHDG = counterHDG % 360;

        Serial.print("HDG: ");
        Serial.println(counterHDG);
    }

    lastStateHDG = currentStateHDG;

    int btnStateHDG = digitalRead(SW_HDG);

    if (btnStateHDG == LOW) {
        if (millis() - lastButtonPressHDG > 50) {
        Serial.println("HDG: CUR");
        }
        lastButtonPressHDG = millis();
    }

    // ################### ALT COUNTING ###################
 
    if (currentStateALT != lastStateALT  && currentStateALT == 1){
        if (digitalRead(DT_ALT) != currentStateALT) {
        counterALT++;
        } 
        if ((digitalRead(DT_ALT) == currentStateALT) && (counterALT > 0)) {
        counterALT--;
        }
        Serial.print("ALT: ");
        Serial.println(counterALT);
    }

    lastStateALT = currentStateALT;

    int btnStateALT = digitalRead(SW_ALT);

    if (btnStateALT == LOW) {
        if (millis() - lastButtonPressALT > 50) {
        Serial.println("ALT: CUR");
        }
        lastButtonPressALT = millis();
    }

    // ################### IAS COUNTING ###################
 
    if (currentStateIAS != lastStateIAS  && currentStateIAS == 1){

        if (digitalRead(DT_IAS) != currentStateIAS) {
        counterIAS++;
        } 
        if ((digitalRead(DT_IAS) == currentStateIAS) && (counterIAS > 0)) {
        counterIAS--;
        }

        Serial.print("IAS: ");
        Serial.println(counterIAS);
    }

    lastStateIAS = currentStateIAS;

    int btnStateIAS = digitalRead(SW_IAS);

    if (btnStateIAS == LOW) {
        if (millis() - lastButtonPressIAS > 50) {
        Serial.println("IAS: CUR");
        }
        lastButtonPressIAS = millis();
    }

    // ################### VSP COUNTING ###################
 
    if (currentStateVSP != lastStateVSP  && currentStateVSP == 1){
 
        if (digitalRead(DT_VSP) != currentStateVSP) {
        counterVSP++;
        } 
        if ((digitalRead(DT_VSP) == currentStateVSP)) {
        counterVSP--;
        }

        Serial.print("VSP: ");
        Serial.println(counterVSP);
    }

    lastStateVSP = currentStateVSP;

    int btnStateVSP = digitalRead(SW_VSP);

    if (btnStateVSP == LOW) {
        if (millis() - lastButtonPressVSP > 50) {
        Serial.println("VSP: CUR");
        }
        lastButtonPressVSP = millis();
    }

        // ################### CRS COUNTING ###################
 
    if (currentStateCRS != lastStateCRS  && currentStateCRS == 1){

        if (digitalRead(DT_CRS) != currentStateCRS) {
        counterCRS++;
        } 
        if ((digitalRead(DT_CRS) == currentStateCRS)) {
        counterCRS--;
        }
        if (counterCRS < 0){
            counterCRS = 359;
        }
        counterCRS = counterCRS % 360;
        Serial.print("CRS: ");
        Serial.println(counterCRS);
    }

    lastStateCRS = currentStateCRS;

    int btnStateCRS = digitalRead(SW_CRS);

    if (btnStateCRS == LOW) {
        if (millis() - lastButtonPressCRS > 50) {
        Serial.println("CRS: CUR");
        }
        lastButtonPressCRS = millis();
    }
    // ################### BUTTON HANDLING ###################
    // ################### AUTOPILOT MASTER ###################


    if (APState == true){
        digitalWrite(AP_LED, HIGH);
    }
    else {
        digitalWrite(AP_LED, LOW);
    }

    APButtonState = digitalRead(AP_SW);
    if (APButtonState == LOW) {
        if (millis() - lastButtonPressAP > 50) {
            if (APState){
                APState = false;
                Serial.println("AP: 0");
            }
            else {
                APState = true;
                Serial.println("AP: 1");
            }
        }
        lastButtonPressAP = millis();
    }
    delay(1);
}
