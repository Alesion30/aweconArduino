//三菱重工のエアコン起動
void on_MitsuHeavy(int mode, int fan, int temp, int vdir, int hdir)
{
  IRSenderPWM irSender(3);
  MitsubishiHeavyZJHeatpumpIR *heatpumpIR;
  heatpumpIR = new MitsubishiHeavyZJHeatpumpIR();
  heatpumpIR->send(irSender, 1, mode, fan, temp, vdir, hdir, false, false, false);
}