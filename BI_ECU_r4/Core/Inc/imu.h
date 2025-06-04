/**
 * @file imu.h
 * @brief IMU communications module for STM32 microcontrollers
 *
 * This module handles communication with an IMU sensor via USART1 interface
 */

#ifndef IMU_H
#define IMU_H

#include <stdint.h>
#include <stdbool.h>

void imu_test_data1();
void imu_test_data2();
void imu_test_data3();
void imu_test_runselftest();
void imu_test_reqgnssplatform();
void imu_test_reqerrormode();
void imu_test_data();
void imu_test_reqtransmitdelay();
void imu_test_reqoptionflag();
void imu_test_reqlocationid();
void imu_test_reqconfiguration();
void imu_test_reqperiod();
void imu_test_reqoutputconfiguration();
void imu_test_reqalignmentrotation();
void imu_test_requtctime();
void imu_test_reqfilterprofile();
void imu_test_reqgnss();
void imu_test_reqlatlon();
void imu_test_data();
void parse_imu_data(xsens_interface_t *interface);

#endif /* IMU_H */
