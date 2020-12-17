//Panasonicのエアコン停止
void off_Panasonic()
{
  IRSenderPWM irSender(3);
  PanasonicDKEHeatpumpIR *heatpumpIR;
  heatpumpIR = new PanasonicDKEHeatpumpIR();
  heatpumpIR->send(irSender, POWER_OFF, MODE_HEAT, FAN_AUTO, 24, VDIR_AUTO, HDIR_AUTO);
}