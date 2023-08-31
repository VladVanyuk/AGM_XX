#define analogPin A0 // ANALOG_PIN
// #define REL_MAX D8
// #define REL_MID D7
// #define REL_LOW D6
// #define AC_IN D5
// #define CHARGE_PUMP_IN D4



#define OLED_WIDTH 128
#define OLED_HEIGHT 64


Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

const unsigned long eventInterval = 5000; //better to make #define
unsigned long previousTime = 0;

const unsigned long eventInterval_4 = 6900;
unsigned long previousTime_4 = 0;

const unsigned long eventInterval_5 = 7130;
unsigned long previousTime_5 = 0;

unsigned char CHARGE;
unsigned char CCV_CHARGE;
float SOC_voltage;
float CCV_voltage;

const int rel_max = D8; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const int rel_mid = D7; //should be const or define REL_MID
const int rel_low = D6;
const int ac_in = D5;
const int charge_pumpPIN = D4;

bool flag_stage_1 = false; // bulk charge at max current 16-17A up to 80%
bool flag_stage_2 = false; // absorbtion charge 5-6Afrom 80% to 99%
bool flag_stage_3 = false; // topping charge 99%-100% at minimum current
bool stop_flag = false;    // charging disabled
bool AC = false;           // 230 vac