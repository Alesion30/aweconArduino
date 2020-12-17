//三菱重工のエアコン停止
void off_MitsuHeavy()
{
  IRSenderPWM irSender(3);
  MitsubishiHeavyZJHeatpumpIR *heatpumpIR;
  heatpumpIR = new MitsubishiHeavyZJHeatpumpIR();
  heatpumpIR->send(irSender, POWER_OFF, MODE_HEAT, FAN_AUTO, 24, VDIR_AUTO, HDIR_AUTO, false, false, false);
}