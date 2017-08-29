#include "logger.h"
#include <fstream>
#include <sys/time.h>

static struct timeval tv;
static ofstream fout("../output_data/log.csv", ios::out);
static ofstream fout2("../output_data/tofc.csv", ios::out);

void InitLogging()
{
  timerclear(&tv);
}

void ToFCLogging()
{
  gettimeofday(&tv, NULL);
  uint32_t timestamp = (tv.tv_sec % 1000) * 1000000 + tv.tv_usec;

#ifndef FC_DEBUG_MODE
  fout << LogIDToFC <<"," << timestamp << ",";
  fout << unsigned(from_fc.nav_mode_request) << "," << unsigned(from_fc.flightctrl_state) << ",";
  fout << from_fc.accelerometer[0] << "," << from_fc.accelerometer[1] << "," << from_fc.accelerometer[2] << ",";
  fout << from_fc.gyro[0] << "," << from_fc.gyro[1] << "," << from_fc.gyro[2] <<",";
  fout << from_fc.quaternion[0] << "," << from_fc.quaternion[1] << "," << from_fc.quaternion[2] << "," <<from_fc.quaternion[3] << ",";
  fout << from_fc.pressure_alt << endl;
#else
  fout << LogIDFCDebug << "," << timestamp << ",";
  fout << for_debug.motor_setpoint[0] << "," << for_debug.motor_setpoint[1] << ",";
  fout << for_debug.motor_setpoint[2] << "," << for_debug.motor_setpoint[3] << ",";
  fout << for_debug.accelerometer[0] << "," << for_debug.accelerometer[1] << "," << for_debug.accelerometer[2] << ",";
  fout << for_debug.gyro[0] << "," << for_debug.gyro[1] << "," << for_debug.gyro[2] << endl;
#endif
}

void FromFCLogging()
{
  gettimeofday(&tv, NULL);
  uint32_t timestamp = (tv.tv_sec % 1000) * 1000000 + tv.tv_usec;
  fout << LogIDFromFC << "," << timestamp << ",";
  fout << unsigned(from_fc.timestamp) << "," << unsigned(from_fc.nav_mode_request) << "," << unsigned(from_fc.flightctrl_state) << ",";
  fout << from_fc.accelerometer[0] << "," << from_fc.accelerometer[1] << "," << from_fc.accelerometer[2] << ",";
  fout << from_fc.gyro[0] << "," << from_fc.gyro[1] << "," << from_fc.gyro[2] <<",";
  fout << from_fc.quaternion[0] << "," << from_fc.quaternion[1] << "," << from_fc.quaternion[2] << "," << from_fc.quaternion[3] <<",";
  fout << from_fc.pressure_alt << endl;
}

void VisionLogging()
{
  gettimeofday(&tv, NULL);
  uint32_t timestamp = (tv.tv_sec % 1000) * 1000000 + tv.tv_usec;
  fout << LogIDVision << "," << timestamp << ",";
  fout << from_marker.position[0] << "," << from_marker.position[1] << ","<< from_marker.position[2] <<",";
  fout << from_marker.quaternion[0] << ","<< from_marker.quaternion[1] << "," << from_marker.quaternion[2] <<",";
  fout << from_marker.r_var[0] <<","<< from_marker.r_var[1] << "," << from_marker.r_var[2] << ",";
  fout << unsigned(from_marker.status) << endl;
}

void GPSLogging()
{
  gettimeofday(&tv, NULL);
  uint32_t timestamp = (tv.tv_sec % 1000) * 1000000 + tv.tv_usec;
  fout << LogIDGPS << "," << timestamp << ",";
  fout << from_gps.longitude << "," << from_gps.latitude << "," << from_gps.z << ",";
  fout << from_gps.velocity[0] << "," << from_gps.velocity[1] << "," << from_gps.velocity[2] << ",";
  fout << unsigned(from_gps.gps_status) << endl;
}

void LSMLogging()
{
  gettimeofday(&tv, NULL);
  uint32_t timestamp = (tv.tv_sec % 1000) * 1000000 + tv.tv_usec;
  fout << LogIDLSM << "," << timestamp << ",";
  fout << from_lsm.mag[0] << "," << from_lsm.mag[1] << "," << from_lsm.mag[2] << ",";
  fout << unsigned(from_lsm.status) << endl;
}

void FromDPSetDronePortModeLogging(){
  gettimeofday(&tv, NULL);
  uint32_t timestamp = (tv.tv_sec % 1000) * 1000000 + tv.tv_usec;
  fout << LogIDFromDPSetDronePortMode << "," << timestamp << ",";
  fout << from_dp_set_dp_mode.read_write << "," << from_dp_set_dp_mode.drone_port_mode_request << endl;
}

void ToDPSetDronePortModeLogging(){
  gettimeofday(&tv, NULL);
  uint32_t timestamp = (tv.tv_sec % 1000) * 1000000 + tv.tv_usec;
  fout << LogIDToDPSetDronePortMode << "," << timestamp << ",";
  fout << to_dp_set_dp_mode.drone_port_mode << "," << to_dp_set_dp_mode.drone_port_status << endl;
}

void ToFCLogging2()
{
  gettimeofday(&tv, NULL);
  uint32_t timestamp = (tv.tv_sec % 1000) * 1000000 + tv.tv_usec;
  fout2 << timestamp << ",";
  fout2 << unsigned(to_fc.version) << "," << unsigned(to_fc.nav_mode) << "," << unsigned(to_fc.navigation_status) << ",";
  fout2 << to_fc.position[0] << "," << to_fc.position[1] << "," << to_fc.position[2] << ",";
  fout2 << to_fc.velocity[0] << "," << to_fc.velocity[1] << "," << to_fc.velocity[2] <<",";
  fout2 << to_fc.quat0 << "," << to_fc.quatz << "," ;
  fout2 << to_fc.target_position[0] << "," << to_fc.target_position[1] << "," << to_fc.target_position[2] << ",";
  fout2 << to_fc.transit_vel << ",";
  fout2 << to_fc.target_heading << ",";
  fout2 << to_fc.heading_rate << endl;
}
