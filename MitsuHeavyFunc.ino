#include <MitsubishiHeavyHeatpumpIR.h>

// 三菱重工のエアコン起動
void controlMitsuHeavyAirConditionar(int mode, int fan, int temp, int vdir, int hdir)
{
  IRSenderPWM irSender(3);
  MitsubishiHeavyZJHeatpumpIR *heatpumpIR;
  heatpumpIR = new MitsubishiHeavyZJHeatpumpIR();
  heatpumpIR->send(irSender, 1, mode, fan, temp, vdir, hdir, false, false, false);
}

// 三菱重工のエアコン停止
void stopMitsuHeavyAirConditionar()
{
  IRSenderPWM irSender(3);
  MitsubishiHeavyZJHeatpumpIR *heatpumpIR;
  heatpumpIR = new MitsubishiHeavyZJHeatpumpIR();
  heatpumpIR->send(irSender, POWER_OFF, MODE_HEAT, FAN_AUTO, 24, VDIR_AUTO, HDIR_AUTO, false, false, false);
}
