//******************OLED DISPLAY FUNCTIONS***************************************

void bat_value()
{
  if (SOC_voltage < 11.63)
    CHARGE = 0;
  if ((SOC_voltage >= 11.63) && (SOC_voltage < 11.70))
    CHARGE = 10;
  if ((SOC_voltage >= 11.70) && (SOC_voltage < 11.81))
    CHARGE = 20;
  if ((SOC_voltage >= 11.81) && (SOC_voltage < 11.96))
    CHARGE = 30;
  if ((SOC_voltage >= 11.96) && (SOC_voltage < 12.11))
    CHARGE = 40;
  if ((SOC_voltage >= 12.23) && (SOC_voltage < 12.41))
    CHARGE = 50;
  if ((SOC_voltage >= 12.41) && (SOC_voltage < 12.51))
    CHARGE = 60;
  if ((SOC_voltage >= 12.51) && (SOC_voltage < 12.65))
    CHARGE = 70;
  if ((SOC_voltage >= 12.65) && (SOC_voltage < 12.78))
    CHARGE = 80;
  if ((SOC_voltage >= 12.78) && (SOC_voltage < 12.89))
    CHARGE = 90;
  if (SOC_voltage >= 12.89)
    CHARGE = 100;

  display.fillRect(0, 15, 100, 40, BLACK);
  display.setTextSize(3);
  display.setCursor(70, 20);
  display.println("%");
  display.setCursor(10, 20);
  display.println(CHARGE);
}



void display_SOC_voltage()
{
  display.fillRect(64, 0, 40, 10, BLACK);
  display.setTextSize(1);
  display.setCursor(64, 0);
  display.println(SOC_voltage);
  display.setCursor(94, 0);
  display.println("v");
  display.display();
}

void display_CCV_voltage()
{
  display.fillRect(64, 0, 40, 10, BLACK);
  display.setTextSize(1);
  display.setCursor(64, 0);
  display.println(CCV_voltage);
  display.setCursor(94, 0);
  display.println("v");
  display.display();
}

void stage1_indicator()
{
  display.fillRect(100, 32, 28, 32, BLACK);
  display.setTextSize(1);
  display.setCursor(100, 32);
  display.println("st_1");
  display.display();
}

void stage2_indicator()
{
  display.fillRect(100, 32, 28, 32, BLACK);
  display.setTextSize(1);
  display.setCursor(100, 32);
  display.println("st_2");
  display.display();
}

void stage3_indicator()
{
  display.fillRect(100, 32, 28, 32, BLACK);
  display.setTextSize(1);
  display.setCursor(100, 32);
  display.println("st_3");
  display.display();
}

void stop_flag_indicator()
{
  display.fillRect(100, 32, 28, 32, BLACK);
  display.setTextSize(1);
  display.setCursor(100, 32);
  display.println("st_F");
  display.display();
}

void charging()
{
  display.drawRoundRect(0, 0, 48, 10, 2, WHITE);
  display.display();
  display.fillRect(2, 2, 5, 6, WHITE);
  display.display();
  delay(100);
  display.fillRect(9, 2, 5, 6, WHITE);
  display.display();
  delay(100);
  display.fillRect(16, 2, 5, 6, WHITE);
  display.display();
  delay(100);
  display.fillRect(23, 2, 5, 6, WHITE);
  display.display();
  delay(100);
  display.fillRect(30, 2, 5, 6, WHITE);
  display.display();
  delay(100);
  display.fillRect(37, 2, 5, 6, WHITE);
  display.display();
  delay(100);
  display.fillRect(44, 2, 5, 6, WHITE);
  display.display();
  delay(100);
  display.fillRect(2, 2, 44, 6, BLACK);
  display.display();
}

void charged()
{
  display.drawRoundRect(0, 0, 48, 10, 2, WHITE);
  display.fillRect(2, 2, 5, 6, WHITE);
  display.fillRect(9, 2, 5, 6, WHITE);
  display.fillRect(16, 2, 5, 6, WHITE);
  display.fillRect(23, 2, 5, 6, WHITE);
  display.fillRect(30, 2, 5, 6, WHITE);
  display.fillRect(37, 2, 5, 6, WHITE);
  display.fillRect(44, 2, 5, 6, WHITE);
  display.display();
}

void no_bat()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("NO BATTERY");
  display.display();
}

void displaySetup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE);
    display.display();
    display.clearDisplay();
}