temp: # 現在の室温を取得
	curl http://localhost:3001/temp

led: # LEDを点灯
	curl http://localhost:3001/control/led

off: # LEDを消灯
	curl http://localhost:3001/control/off
