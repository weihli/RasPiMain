
#include "../../libraries/Handlers/handlers.h"
#include "../../libraries/timer/timer.hpp"

#include <thread>
#include <mutex>
#include <unistd.h>

 // TODO: remove this in the future
#define SERIAL_BAUDRATE_FC (57600)
#define MAIN_FREQ 64 //hz or whatever

#define TCP_PORT_MARKER (8080)

#define ENABLE_DISP_FROM_FC (1)
#define ENABLE_DISP_TO_FC (1)
#define ENABLE_DISP_FROM_MARKER (1)
#define ENABLE_DISP_FROM_GPS (1)

const char SERIAL_PORT_FC[] = "/dev/ttyAMA0";
const char WAYPOINT_FILENAME[] = "../input_data/wp.json";

//==============================================================================
FromFCVector    FCVector;

#define MAIN_LOOP_TIMER 15 // 1divide by 64Hz ->15ms

//==============================================================================

int main(int argc, char const *argv[])
{
    InitLogging();
    ut_serial FC_comm(SERIAL_PORT_FC, SERIAL_BAUDRATE_FC);
    std::thread dp_comm(&RecvFromDP);
    std::thread gps_handler(&GPSHandler);

    ReadWPfromFile(WAYPOINT_FILENAME);
    if (argc == 2) {
        if (!SetRoute(atoi(argv[1]))) {
            return -1;
        }
    }

    Timer Main_timer(MAIN_FREQ);

    for(;;)
    {

        if(Main_timer.check())
        {
            std::clock_t c_start = std::clock(); //debug
            /*
                ORDER DO MATTER PLEASE VERIFY
             */

            if(!FCVector->empty())
            {
                from_fc = FCVector->back();     //get most recent data
                FCVector->clear();              //remove old datas

            }

            if(!GPSVector->empty())
            {
                from_gps = GPSVector->back();   //get most recent data
                GPSVector->clear();             //remove old datas
            }

            //if(!LSMVector->empty())
            //{
            //    from_lsm = LSMVector->back();   //get most recent data
            //    LSMVector->clear();             //remove old datas
            //}
            //ORDER HAS TO BE CHECKED
            //GPS
            UpdateGPSPosFlag();
            UpdateGPSVelFlag();
            PositionMeasurementUpdateWithGPSPos();
            PositionMeasurementUpdateWithGPSVel();
            if(ENABLE_DISP_FROM_GPS) DispFromGPS();
            GPSLogging();

            //FC
            if(ENABLE_DISP_FROM_FC) DispFromFC();
            ToFCLogging();
            ToFCLogging2(); // This will be removed in the future
            FromFCLogging();
            PositionTimeUpdate();
            AttitudeTimeUpdate();
            PositionMeasurementUpdateWithBar();
            UpdateNavigation();
            if(ENABLE_DISP_TO_FC) DispToFC();
            FC_comm.send_data(UT_SERIAL_COMPONENT_ID_RASPI, 1, (uint8_t *)&to_fc, sizeof(to_fc));
            ResetHeadingCorrectionQuat();

            //LSM
            UpdateLSMFlag();
            AttitudeMeasurementUpdateWithLSM();
            LSMLogging();

            }

    }

    // dp_comm.join();
    // gps_handler.join();

    return 0;
}
