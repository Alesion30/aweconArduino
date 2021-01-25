#include <PanasonicHeatpumpIR.h>

// Panasonicのエアコン起動
void controlPanasonicAirConditionar(int mode, int fan, int temp, int vdir, int hdir)
{
  IRSenderPWM irSender(3);
  PanasonicDKEHeatpumpIR *heatpumpIR;
  heatpumpIR = new PanasonicDKEHeatpumpIR();
  heatpumpIR->send(irSender, 1, mode, fan, temp, vdir, hdir);
};

// Panasonicのエアコン停止
void stopPanasonicAirConditionar()
{
  IRSenderPWM irSender(3);
  PanasonicDKEHeatpumpIR *heatpumpIR;
  heatpumpIR = new PanasonicDKEHeatpumpIR();
  heatpumpIR->send(irSender, POWER_OFF, MODE_HEAT, FAN_AUTO, 24, VDIR_AUTO, HDIR_AUTO);
}
