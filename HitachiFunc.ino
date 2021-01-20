#include <HitachiHeatpumpIR.h>

// 日立のエアコン起動
void controlHitachiAirConditionar(int mode, int fan, int temp, int vdir, int hdir)
{
  IRSenderPWM irSender(3);
  HitachiHeatpumpIR *heatpumpIR;
  heatpumpIR = new HitachiHeatpumpIR();
  heatpumpIR->send(irSender, 1, mode, fan, temp, vdir, hdir);
}

// 日立のエアコン停止
void stopHitachiAirConditionar()
{
  IRSenderPWM irSender(3);
  HitachiHeatpumpIR *heatpumpIR;
  heatpumpIR = new HitachiHeatpumpIR();
  heatpumpIR->send(irSender, POWER_OFF, MODE_HEAT, FAN_AUTO, 24, VDIR_AUTO, HDIR_AUTO);
}
