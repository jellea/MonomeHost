#include <Usb.h>  
#include "MonomeController.h"

USBHost usb;
MonomeController monome(usb);

#if (USB_VID==0x2341 && defined(ARDUINO_SAMD_ZERO)) || (USB_VID==0x2a03 && defined(ARDUINO_SAM_ZERO))
#define SerialDebug SERIAL_PORT_MONITOR
#else
#define SerialDebug Serial1
#endif

void GridKeyCallback(byte x, byte y, byte z) { 
  SerialDebug.print("grid key: ");
  SerialDebug.print(x);
  SerialDebug.print(" , ");
  SerialDebug.print(y);
  SerialDebug.print(" , ");
  SerialDebug.print(z);
  SerialDebug.print("\r\n");
  
  monome.led_clear();
  monome.led_set(x, y, 15);
  monome.refresh();
}

void ConnectCallback(const char * name, byte cols, byte rows) {
  SerialDebug.print("\r\nmonome device connected; type: ");
  SerialDebug.print(name);
  SerialDebug.print(" ; columns: ");
  SerialDebug.print(cols);
  SerialDebug.print(" ; rows: ");
  SerialDebug.print(rows);
  SerialDebug.print("\r\n");
}


void setup() { 



  SerialDebug.begin(9600);
  
  SerialDebug.print("\n\nStarting...\n");
  delay(200);


  // set connection callback
  monome.SetConnectCallback(&ConnectCallback);
  // set key event callback
//  monome.SetGridKeyCallback(&GridKeyCallback);
  SerialDebug.print("\n\nConnect set...\n");

  delay(200);

}

void loop() { 
  usb.Task();
  /// alternatively, refresh on every tick:
  //  monome.refresh();
}
