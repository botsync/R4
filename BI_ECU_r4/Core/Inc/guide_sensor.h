
#ifndef INC_GUIDE_SENSOR_H_
#define INC_GUIDE_SENSOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Enum representing different command types
typedef enum {
	B_INDEX_VALUE,
	MGD,
	MGM,
	MZ,
	T,
	MGT,
	VAR_INDEX_VALUE,
	MGS,
	MGX,
	UNKNOWN_COMMAND
} CommandType;

// Command Buffers for each command type (storing the exact data)


// Enum for set commands
typedef enum {
	SET_B,
	SET_R,
	SET_TV,
	SET_VAR,
	SET_TX,
	SET_ZER,
	SET_UNKNOWN
} SetCommandType;







// Enum for config commands
typedef enum {
	CMD_ANAM,
	CMD_BADJ,
	CMD_BRUN,
	CMD_DIM,
	CMD_FCAL,
	CMD_MMOD,
	CMD_PWMM,
	CMD_RSBR,
	CMD_SCRO,
	CMD_TINV,
	CMD_TMS,
	CMD_TPOL,
	CMD_TWDT,
	CMD_TXOF,
	CMD_ZADJ,
	CMD_UNKNOWN
} ConfigCommandType;







typedef enum {
	B_INDEX_VALUE_1,
	MGD_1,
	MGM_1,
	MZ_1,
	T_1,
	MGT_1,
	VAR_INDEX_VALUE_1,
	MGS_1,
	MGX_1,
	SET_B_1,
	SET_R_1,
	SET_TV_1,
	SET_VAR_1,
	SET_TX_1,
	SET_ZER_1,
	CMD_ANAM_1,
	CMD_BADJ_1,
	CMD_BRUN_1,
	CMD_DIM_1,
	CMD_FCAL_1,
	CMD_MMOD_1,
	CMD_PWMM_1,
	CMD_RSBR_1,
	CMD_SCRO_1,
	CMD_TINV_1,
	CMD_TMS_1,
	CMD_TPOL_1,
	CMD_TWDT_1,
	CMD_TXOF_1,
	CMD_ZADJ_1,
	CMD_UNKNOWN_1
} Parse_data;

typedef struct {
	// Read Commands
	uint32_t B_INDEX_VALUE;
	uint32_t MGD;
	uint32_t MGM;
	uint32_t MZ;
	uint32_t T;
	uint32_t MGT;
	uint32_t VAR_INDEX_VALUE;
	uint32_t MGS;
	uint32_t MGX;

	// Set Commands
	uint32_t SET_B;
	uint32_t SET_R;
	uint32_t SET_TV;
	uint32_t SET_VAR;
	uint32_t SET_TX;
	uint32_t SET_ZER;

	// Config Commands
	uint32_t CMD_ANAM;
	uint32_t CMD_BADJ;
	uint32_t CMD_BRUN;
	uint32_t CMD_DIM;
	uint32_t CMD_FCAL;
	uint32_t CMD_MMOD;
	uint32_t CMD_PWMM;
	uint32_t CMD_RSBR;
	uint32_t CMD_SCRO;
	uint32_t CMD_TINV;
	uint32_t CMD_TMS;
	uint32_t CMD_TPOL;
	uint32_t CMD_TWDT;
	uint32_t CMD_TXOF;
	uint32_t CMD_ZADJ;
} CommandData_t;


// Function to handle the state machine and execute commands
void guide_sensor1_send_real_time();
void guide_sensor1_real_time_commands(SetCommandType cmd);
void guide_sensor1_configuration_command(ConfigCommandType cmd);
Parse_data getCommandEnum(const char *key);
void handleCommand(char *buffer);
void guide_sensor1_send_real_time_init();




#endif /* INC_GUIDE_SENSOR_H_ */
