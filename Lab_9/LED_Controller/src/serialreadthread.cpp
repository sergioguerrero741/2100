#include <glib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "global.h"

#define READ_THREAD_SLEEP_DURATION_US 100000
#define BETWEEN_CHARACTERS_TIMEOUT_US 1000
#define MAX_VOLTAGE 3.3
#define MAX_ADC_VALUE 1024.0
#define POT_COMMAND 'P'

// define packet parameters
#define PACKET_START_BYTE  0xAA
#define PACKET_OVERHEAD_BYTES  3
#define PACKET_MIN_BYTES  PACKET_OVERHEAD_BYTES + 1
#define PACKET_MAX_BYTES  255

bool validatePacket(unsigned int packetSize, unsigned char *packet) {
    if(packetSize < PACKET_MIN_BYTES || packetSize > PACKET_MAX_BYTES) {
        return false;
    }
    if(packet[0] != PACKET_START_BYTE) {
        return false;
    }
    if(packet[1] != packetSize) {
        return false;
    }
    char checksum = 0x00;
    for(unsigned int i = 0; i < packetSize - 1; i++) {
        checksum = checksum ^ packet[i];
    }
    if(packet[packetSize - 1] != checksum) {
        return false;
    }
    return true;
}

gpointer Serial_Read_Thread() {
  ssize_t r_res;
  char ob[50];
  unsigned int count=0;
  static unsigned char buffer[PACKET_MAX_BYTES];
  unsigned int packetSize = PACKET_MIN_BYTES;
  double voltage_disp;

  while(!kill_all_threads) {
    if(ser_dev!=-1) {
      r_res = read(ser_dev,ob,1);
	  //	  cout<<(int)ob[0]<<endl;
      if(r_res==0) {
        usleep(BETWEEN_CHARACTERS_TIMEOUT_US);
      }
      else if(r_res<0) {
        cerr<<"Read error:"<<(int)errno<<" ("<<strerror(errno)<<")"<<endl;
      }
      else {
        char b = ob[0];
        if(count == 0 && b == PACKET_START_BYTE) {
          buffer[count] = b;
          count++;
          continue;
        }
        else if(count == 0) {
          continue;
        }
        else if(count == 1) {
          buffer[count] = b;
          if(packetSize < PACKET_MIN_BYTES || packetSize > PACKET_MAX_BYTES) {
            count = 0;
          }
          else {
            packetSize = b;
            count++;
          }
          continue;
        }
        else if(count < packetSize) {
          buffer[count] = b;
          count++;
        }
        if(count >= packetSize) {
          if(validatePacket(packetSize, buffer)) {
            g_mutex_lock(mutex_to_protect_voltage_display);
            int vd = buffer[3];
            vd *= 256;
            vd += buffer[4];
            double voltage_disp = vd * MAX_VOLTAGE / MAX_ADC_VALUE;
            sprintf(c_voltage_value, "%1.3f", voltage_disp);
            g_mutex_unlock(mutex_to_protect_voltage_display);
          }
          count = 0;
        }
      }
    }
    else {
      usleep(READ_THREAD_SLEEP_DURATION_US);
    }
  }
  return NULL;
}
