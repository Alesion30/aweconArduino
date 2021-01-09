#include <DaikinHeatpumpIR.h>

// ダイキンのエアコン起動
void controlDaikinAirConditionar(int mode, int fan, int temp, int vdir, int hdir)
{
  IRSenderPWM irSender(3);
  DaikinHeatpumpIR *heatpumpIR;
  heatpumpIR = new DaikinHeatpumpIR();
  heatpumpIR->send(irSender, 1, mode, fan, temp, vdir, hdir);
}

// ダイキンのエアコン停止
void stopDaikinAirConditionar()
{
  IRSenderPWM irSender(3);
  DaikinHeatpumpIR *heatpumpIR;
  heatpumpIR = new DaikinHeatpumpIR();
  heatpumpIR->send(irSender, POWER_OFF, MODE_HEAT, FAN_AUTO, 24, VDIR_AUTO, HDIR_AUTO);
}
