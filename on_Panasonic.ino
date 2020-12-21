//Panasonicのエアコン起動
void on_Panasonic(int mode, int fan, int temp, int vdir, int hdir)
{
  IRSenderPWM irSender(3);
  PanasonicDKEHeatpumpIR *heatpumpIR;
  heatpumpIR = new PanasonicDKEHeatpumpIR();
  heatpumpIR->send(irSender, 1, mode, fan, temp, vdir, hdir);
};
