#include "string.h"

#include "xsens_mdata2.h"
#include "xsens_mti.h"
#include "xsens_mti_private.h"
#include "xsens_utility.h"
#include "usart.h"



void imu_test_data()
{
	xsens_interface_t test_imu={0};
	//xsens_mti_request(&test_imu, 0x00);
	HAL_Delay(100);
		//xsens_mti_request(&test_imu, 0x1C);
		//imu_test_data1();
		HAL_Delay(100);
		imu_test_data2();
		HAL_Delay(100);
		//imu_test_data3();
		HAL_Delay(100);
		//imu_test_runselftest();
		HAL_Delay(100);
		//imu_test_reqgnssplatform();
//		HAL_Delay(100);
//		imu_test_reqerrormode();
//		HAL_Delay(100);
//		imu_test_reqtransmitdelay();
//		HAL_Delay(100);
//		imu_test_reqoptionflag();
//		HAL_Delay(100);
//		imu_test_reqlocationid();
//		HAL_Delay(100);
//		imu_test_reqconfiguration();
//		HAL_Delay(100);
//		imu_test_reqperiod();
//		HAL_Delay(100);
//		imu_test_reqoutputconfiguration();
//		HAL_Delay(100);
//		imu_test_reqalignmentrotation();
//		HAL_Delay(100);
//		imu_test_requtctime();
//		HAL_Delay(100);
//		imu_test_reqfilterprofile();
//		HAL_Delay(100);
//		imu_test_reqgnss();
//		HAL_Delay(100);
//		imu_test_reqlatlon();
}

			void imu_test_data1()
	{
		xsens_interface_t test_imu1={0};
		xsens_mti_request(&test_imu1, 0x1E);
	}
void imu_test_data2()
	{
		xsens_interface_t test_imu2={0};
		xsens_mti_request(&test_imu2, 0x10);
	}
void imu_test_data3()
	{
		xsens_interface_t test_imu3={0};
		xsens_mti_request(&test_imu3, 0x18);
	}
void imu_test_runselftest()
	{
		xsens_interface_t test_imu4={0};
		xsens_mti_request(&test_imu4, 0x24);
	}void imu_test_reqgnssplatform()
	{
		xsens_interface_t test_imu5={0};
		xsens_mti_request(&test_imu5, 0x76);
	}void imu_test_reqerrormode()
	{
		xsens_interface_t test_imu6={0};
		xsens_mti_request(&test_imu6, 0xDA);
	}
	void imu_test_reqtransmitdelay()
	{
		xsens_interface_t test_imu8={0};
		xsens_mti_request(&test_imu8, 0xDC);
	}void imu_test_reqoptionflag()
	{
		xsens_interface_t test_imu9={0};
		xsens_mti_request(&test_imu9, 0x48);
	}void imu_test_reqlocationid()
	{
		xsens_interface_t test_imu10={0};
		xsens_mti_request(&test_imu10, 0x84);
	}
	void imu_test_reqconfiguration()
	{
		xsens_interface_t test_imu12={0};
		xsens_mti_request(&test_imu12, 0x0C);
	}void imu_test_reqperiod()
	{
		xsens_interface_t test_imu13={0};
		xsens_mti_request(&test_imu13, 0x04);
	}void imu_test_reqoutputconfiguration()
	{
		xsens_interface_t test_imu14={0};
		xsens_mti_request(&test_imu14, 0xC0);
	}void imu_test_reqalignmentrotation()
	{
		xsens_interface_t test_imu15={0};
		xsens_mti_request(&test_imu15, 0xEC);
	}void imu_test_requtctime()
	{
		xsens_interface_t test_imu16={0};
		xsens_mti_request(&test_imu16, 0x60);
	}void imu_test_reqfilterprofile()
	{
		xsens_interface_t test_imu17={0};
		xsens_mti_request(&test_imu17, 0x64);
	}void imu_test_reqgnss()
	{
		xsens_interface_t test_imu18={0};
		xsens_mti_request(&test_imu18, 0x68);
	}void imu_test_reqlatlon()
	{
		xsens_interface_t test_imu19={0};
		xsens_mti_request(&test_imu19, 0x6E);
	}









void parse_imu_data(xsens_interface_t *interface)
{
	xsens_packet_buffer_t *packet = &(interface->packet);
	uint8_t data=0;
	switch(packet->message_id)
	{
	case MT_WAKEUP:
		data++;
		break;

	case MT_ACK_GOTOCONFIG:
		data++;
		break;

	case MT_ACK_GOTOMEASUREMENT:
		data++;
		break;

	case MT_ACK_RESET:
		data++;
		break;

    // Informational Messages
	case MT_DEVICEID:
		data++;
		break;

	case MT_PRODUCTCODE:
		data++;
		break;

	case MT_HARDWAREVERSION:
		data++;
		break;

	case MT_FIRMWAREREV:
		data++;
		break;
	case MT_ERROR:
		data++;
		break;

    // Device Specific Messages
	case MT_ACK_BAUDRATE:
		data++;
		break;
	case MT_ACK_SELFTEST:
		data++;
		break;

	case MT_ACK_GNSSPLATFORM:
		data=1;
		break;
	case MT_ACK_ERRORMODE:
		data++;
		break;// DEPRECATED by xsens 2020.A
	case MT_ACK_TRANSMITDELAY:
		data++;
		break;
	case MT_ACK_OPTIONFLAGS:
		data++;
		break;
	case MT_ACK_LOCATIONID:
		data++;
		break;

    // Synchronisation Messages
	case MT_ACK_SYNCSETTINGS:
		data++;
		break;

    // Configuration Messages
	case MT_CONFIGURATION:
		data++;
		break;
	case MT_ACK_PERIOD:
		data++;
		break;
	case MT_ACK_EXTOUTPUTMODE:
		data++;
		break;
	case MT_ACK_OUTPUTCONFIGURATION:
		data++;
		break;
	case MT_ACK_STRINGOUTPUTTYPES:
		data++;
		break;
	case MT_ACK_OUTPUTMODE:
		data++;
		break;// DEPRECATED by xsens rev w
	case MT_ACK_OUTPUTSETTINGS:
		data++;
		break;// DEPRECATED by xsens rev w

    // Data Messages
	case MT_MTDATA:
		data++;
		break;
	case MT_MTDATA2:
		xsens_mdata2_process(packet);
		break;
	case MT_ACK_RESETORIENTATION:
		data++;
		break;
	case MT_UTCTIME:
		data++;
		break;
	case MT_ACK_AVAILABLEFILTERPROFILES:
		data++;
		break;
	case MT_ACK_FILTERPROFILE:
		data++;
		break;
	case MT_ACK_GNSSLEVERARM:
		data++;
		break;
	case MT_ACK_LATLONALT:
		data++;
		break;
	case MT_ACK_NOROTATION:
		data++;
		break;
	case MT_ACK_ICCCOMMAND:
		data++;
		break;

    // Not in xsens manual summary tables
	case MT_WARNING:
		break;
	case MT_ACK_INITIALHEADING:
		break;
	case MT_ACK_FORWARDGNSSDATA:
		break;
	default:
		break;
	}
}
