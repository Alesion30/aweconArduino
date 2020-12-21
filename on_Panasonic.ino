//Panasonicのエアコン起動
void on_Panasonic(int power, int mode, int fan, int temp, int vdir, int hdir)
{
  IRSenderPWM irSender(3);
  PanasonicDKEHeatpumpIR *heatpumpIR;
  heatpumpIR = new PanasonicDKEHeatpumpIR();
  heatpumpIR->send(irSender, power, mode, fan, temp, vdir, hdir);
};
