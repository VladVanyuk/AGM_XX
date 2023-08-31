
//******************FUNCTIONS TO CTRL SHIFT REGISTER 74HC595BT*********************

void stop_charging()
{
  digitalWrite(rel_max, LOW);
  digitalWrite(rel_mid, LOW);
  digitalWrite(rel_low, LOW);
  stop_flag = true;
  stop_flag_indicator();
}

/////////////////////////////////////////////////////////////////
void first_stage()
{
  digitalWrite(rel_max, HIGH);
  digitalWrite(rel_mid, LOW);
  digitalWrite(rel_low, LOW);
  stage1_indicator();
}
/////////////////////////////////////////////////////////////////

void second_stage()
{
  digitalWrite(rel_max, LOW);
  digitalWrite(rel_mid, HIGH);
  digitalWrite(rel_low, LOW);
  flag_stage_2 = true;
  stage2_indicator();
}
/////////////////////////////////////////////////////////////////

void third_stage()
{
  digitalWrite(rel_max, LOW);
  digitalWrite(rel_mid, LOW);
  digitalWrite(rel_low, HIGH);
  flag_stage_3 = true;
  stage3_indicator();
}
/////////////////////////////////////////////////////////////////

void calc_CCV_voltage()
{
  int b0 = analogRead(analogPin); // CCV voltage variable
  delay(200);
  int b1 = analogRead(analogPin);   // read current battery voltage @ CCV
  float w0 = 8 * b0 * (3.3 / 1023); // convert reading to voltage....x8,
  float w1 = 8 * b1 * (3.3 / 1023);
  CCV_voltage = (w0 + w1) / 2; // read voltage twice and calculate M value
}

void calc_SOC_voltage()
{
  int a0 = analogRead(analogPin); // read current battery voltage @ SOC0
  delay(200);
  int a1 = analogRead(analogPin);   // read current battery voltage @ SOC1
  float v0 = 8 * a0 * (3.3 / 1023); // convert reading to voltage....x8, SOC =source from open circuit
  float v1 = 8 * a1 * (3.3 / 1023); // SOC =source from open circuit
  SOC_voltage = (v0 + v1) / 2;      // read voltage twice and calculate M value
}


void pinsSetup()
{
    analogReference(DEFAULT);
    pinMode(rel_max, OUTPUT);
    pinMode(rel_mid, OUTPUT);
    pinMode(rel_low, OUTPUT);
    pinMode(charge_pumpPIN, OUTPUT); // pwm @50% duty, for charge pump to get 27 volts
    pinMode(ac_in, INPUT);           // pin input to indicate when AC mains are availible
  
}




void stagingLoop()
{
    unsigned long currentTime = millis();
  if (currentTime - previousTime >= eventInterval)
  {
    calc_SOC_voltage();
    display_SOC_voltage();
    bat_value();
    previousTime = currentTime;
  }

  if (digitalRead(ac_in) == HIGH)
    AC = true; // 230vac availiable  run program when AC mains 230VAC are availiable
               // if ( SOC_voltage < 5.00 ) no_bat();

  if (SOC_voltage < 12.60)
    stop_flag = false; // 12.89 = 100% bat

  if (stop_flag == false && AC == true)
  {
    charging();
    analogWrite(charge_pumpPIN, 127); // charge pump
    if (currentTime - previousTime >= eventInterval)
    {
      calc_CCV_voltage();
      previousTime = currentTime;
    }

    if (CCV_voltage <= 12.40)
      first_stage(); // first stage charge @ max Amps

    if (CCV_voltage > 12.40 && CCV_voltage <= 12.70)
      second_stage(); // second stage charge of absorbtion

    if (CCV_voltage > 12.70 && CCV_voltage < 14.30)
      third_stage(); // topping charge up to float

    if (CCV_voltage >= 14.30)
      stop_charging(); // stop charging by writing
  }

  if (SOC_voltage >= 12.60 && AC == true)
  {
    stop_charging();
    charged();
    analogWrite(charge_pumpPIN, 0); // charge pump
  }
}

void bat_operating()
{
  if (digitalRead(ac_in) == LOW) // run this program when there are no AC mains 230VAC running on Bat
  {
    flag_stage_1 = false; // bulk charge at max current 16-17A up to 80%
    flag_stage_2 = false; // absorbtion charge 5-6Afrom 80% to 99%
    flag_stage_3 = false; // topping charge 99%-100% at minimum current
    stop_flag = false;
    AC = false;                     // reset AC flag
    analogWrite(charge_pumpPIN, 0); // charge pump
    charged();
  }
}