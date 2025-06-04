#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usart.h"
#include "guide_sensor.h"

CommandData_t cmd;



#define BUFFER_SIZE 7
char buffer_B[BUFFER_SIZE] = "?B\r";
char buffer_MGD[BUFFER_SIZE] = "?MGD 1";
char buffer_MGM[BUFFER_SIZE] = "?MGM 1";
char buffer_MZ[BUFFER_SIZE] = "?MZ\r";
char buffer_T[BUFFER_SIZE] = "?T\r";
char buffer_MGT[BUFFER_SIZE] = "?MGT 1\r";
char buffer_VAR[BUFFER_SIZE] = "?VAR\r";
char buffer_MGS[BUFFER_SIZE] = "?MGS\r";
char buffer_MGX[BUFFER_SIZE] = "?MGX\r";

char buffer_SET_B[BUFFER_SIZE]   = "!B 1 1\r\n";
char buffer_SET_R_RUN[BUFFER_SIZE] = "!R\r\n";         // Run/Resume
char buffer_SET_R_STOP[BUFFER_SIZE] = "!R 0\r\n";      // Stop
char buffer_SET_R_RESTART[BUFFER_SIZE] = "!R 2\r\n";   // Restart
char buffer_SET_TV[BUFFER_SIZE]  = "!TV\r\n";
char buffer_SET_VAR[BUFFER_SIZE] = "!VAR 5 12345\r\n";
char buffer_SET_TX[BUFFER_SIZE]  = "!TX\r\n";
char buffer_SET_ZER[BUFFER_SIZE] = "!ZER\r\n";

char buffer_ANAM[BUFFER_SIZE] = "^ANAM 0\r\n";
char buffer_BADJ[BUFFER_SIZE] = "^BADJ 0\r\n";
char buffer_BRUN[BUFFER_SIZE] = "^BRUN 0\r\n";
char buffer_DIM[BUFFER_SIZE]  = "^DIM 0\r\n";
char buffer_FCAL[BUFFER_SIZE] = "^FCAL\r\n";
char buffer_MMOD[BUFFER_SIZE] = "^MMOD 0\r\n";
char buffer_PWMM[BUFFER_SIZE] = "^PWMM 0\r\n";
char buffer_RSBR[BUFFER_SIZE] = "^RSBR 0\r\n";
char buffer_SCRO[BUFFER_SIZE] = "^SCRO 0\r\n";
char buffer_TINV[BUFFER_SIZE] = "^TINV 0\r\n";
char buffer_TMS[BUFFER_SIZE]  = "^TMS 0\r\n";
char buffer_TPOL[BUFFER_SIZE] = "^TPOL 0\r\n";
char buffer_TWDT[BUFFER_SIZE] = "^TWDT 0\r\n";
char buffer_TXOF[BUFFER_SIZE] = "^TXOF 0\r\n";
char buffer_ZADJ[BUFFER_SIZE] = "^ZADJ 0 0\r\n";  // Example: channel 0, value 0
CommandType cmd1;

char* findMatchingSubstring(char *buffer);

// List of known keys you want to search for
const char* knownKeys[] = {
    "B=", "MGD=", "MGM=", "MZ=", "MGT=", "T=", "VAR=", "MGS=", "MGX=",
    "SET_B=", "R=", "TV=", "SET_VAR=", "TX=", "ZER=",
    "ANAM=", "BADJ=", "BRUN=", "DIM=", "FCAL=", "MMOD=", "PWMM=",
    "RSBR=", "SCRO=", "TINV=", "TMS=", "TPOL=", "TWDT=", "TXOF=", "ZADJ="
};

#define NUM_KEYS (sizeof(knownKeys) / sizeof(knownKeys[0]));

void guide_sensor1_send_real_time_init()
{
	cmd1=B_INDEX_VALUE;
}









// Function to handle the state machine and execute commands
void guide_sensor1_send_real_time() {
	switch (cmd1) {
	case B_INDEX_VALUE:
		if (HAL_UART_Transmit(&huart3, buffer_B, sizeof(buffer_B), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		HAL_Delay(100);
		cmd1=MGD;
		break;
	case MGD:
		//if(HAL_UART_GetState(&huart3) == HAL_UART_STATE_READY)
		//{
		if (HAL_UART_Transmit(&huart3, buffer_MGD, sizeof(buffer_MGD), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();  // Define your error handler here
		//}
		}
		HAL_Delay(100);
		cmd1=MGM;
		break;
	case MGM:
		if (HAL_UART_Transmit(&huart3, buffer_MGM, sizeof(buffer_MGM), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();  // Define your error handler here
		}
		HAL_Delay(100);
		cmd1=MZ;
		break;
	case MZ:
		if (HAL_UART_Transmit(&huart3, buffer_MZ, sizeof(buffer_MZ), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();  // Define your error handler here
		}
		HAL_Delay(100);
		cmd1=T;
		break;
	case T:
		if (HAL_UART_Transmit(&huart3, buffer_T, sizeof(buffer_T), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();  // Define your error handler here
		}
		HAL_Delay(100);
		cmd1=MGT;
		break;
	case MGT:
		if (HAL_UART_Transmit(&huart3, buffer_MGT, sizeof(buffer_MGT), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();  // Define your error handler here
		}
		HAL_Delay(100);
		cmd1=VAR_INDEX_VALUE;
		break;
	case VAR_INDEX_VALUE:
		if (HAL_UART_Transmit(&huart3, buffer_VAR, sizeof(buffer_VAR), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();  // Define your error handler here
		}
		HAL_Delay(100);
		cmd1=MGS;
		break;
	case MGS:
		if (HAL_UART_Transmit(&huart3, buffer_MGS, sizeof(buffer_MGS), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();  // Define your error handler here
		}
		HAL_Delay(100);
		cmd1=MGX;
		break;
	case MGX:
		if (HAL_UART_Transmit(&huart3, buffer_MGX, sizeof(buffer_MGX), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();  // Define your error handler here
		}
		HAL_Delay(100);
		cmd1=B_INDEX_VALUE;
		break;
	default:
		break;
	}
}





// Function to execute and send buffer over USART
void guide_sensor1_real_time_commands(SetCommandType cmd) {

	switch (cmd) {
	case SET_B:
		if (HAL_UART_Transmit(&huart3, buffer_SET_B, sizeof(buffer_SET_B), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case SET_R:
		if (HAL_UART_Transmit(&huart3, buffer_SET_R_RUN, sizeof(buffer_SET_R_RUN), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case SET_TV:
		if (HAL_UART_Transmit(&huart3, buffer_SET_TV, sizeof(buffer_SET_TV), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case SET_VAR:
		if (HAL_UART_Transmit(&huart3, buffer_SET_VAR, sizeof(buffer_SET_VAR), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case SET_TX:
		if (HAL_UART_Transmit(&huart3, buffer_SET_TX, sizeof(buffer_SET_TX), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case SET_ZER:
		if (HAL_UART_Transmit(&huart3, buffer_SET_ZER, sizeof(buffer_SET_ZER), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	default:
		break;
	}


}

// Function to execute command and send via UART
void guide_sensor1_configuration_command(ConfigCommandType cmd) {

	switch (cmd) {
	case CMD_ANAM:
		if (HAL_UART_Transmit(&huart3, buffer_ANAM, sizeof(buffer_ANAM), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_BADJ:
		if (HAL_UART_Transmit(&huart3, buffer_BADJ, sizeof(buffer_BADJ), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_BRUN:
		if (HAL_UART_Transmit(&huart3, buffer_BRUN, sizeof(buffer_BRUN), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_DIM:
		if (HAL_UART_Transmit(&huart3, buffer_DIM, sizeof(buffer_DIM), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_FCAL:
		if (HAL_UART_Transmit(&huart3, buffer_FCAL, sizeof(buffer_FCAL), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_MMOD:
		if (HAL_UART_Transmit(&huart3, buffer_MMOD, sizeof(buffer_MMOD), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_PWMM:
		if (HAL_UART_Transmit(&huart3, buffer_PWMM, sizeof(buffer_PWMM), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_RSBR:
		if (HAL_UART_Transmit(&huart3, buffer_RSBR, sizeof(buffer_RSBR), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_SCRO:
		if (HAL_UART_Transmit(&huart3, buffer_SCRO, sizeof(buffer_SCRO), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_TINV:
		if (HAL_UART_Transmit(&huart3, buffer_TINV, sizeof(buffer_TINV), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_TMS:
		if (HAL_UART_Transmit(&huart3, buffer_TMS, sizeof(buffer_TMS), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_TPOL:
		if (HAL_UART_Transmit(&huart3, buffer_TPOL, sizeof(buffer_TPOL), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_TWDT:
		if (HAL_UART_Transmit(&huart3, buffer_TWDT, sizeof(buffer_TWDT), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_TXOF:
		if (HAL_UART_Transmit(&huart3, buffer_TXOF, sizeof(buffer_TXOF), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	case CMD_ZADJ:
		if (HAL_UART_Transmit(&huart3, buffer_ZADJ, sizeof(buffer_ZADJ), HAL_MAX_DELAY) != HAL_OK) {
			Error_Handler();
		}
		break;
	default:
		break;
	}

}



Parse_data getCommandEnum(const char *key)
{
	if (strcmp(key, "B") == 0) return B_INDEX_VALUE_1;
	if (strcmp(key, "MGD") == 0) return MGD_1;
	if (strcmp(key, "MGM") == 0) return MGM_1;
	if (strcmp(key, "MZ") == 0) return MZ_1;
	if (strcmp(key, "T") == 0) return T_1;
	if (strcmp(key, "MGT") == 0) return MGT_1;
	if (strcmp(key, "VAR") == 0) return VAR_INDEX_VALUE_1;
	if (strcmp(key, "MGS") == 0) return MGS_1;
	if (strcmp(key, "MGX") == 0) return MGX_1;
	if (strcmp(key, "B") == 0) return SET_B_1;
	if (strcmp(key, "R") == 0) return SET_R_1;
	if (strcmp(key, "TV") == 0) return SET_TV_1;
	if (strcmp(key, "VAR") == 0) return SET_VAR_1;
	if (strcmp(key, "TX") == 0) return SET_TX_1;
	if (strcmp(key, "ZER") == 0) return SET_ZER_1;
	if (strcmp(key, "ANAM") == 0) return CMD_ANAM_1;
	if (strcmp(key, "BADJ") == 0) return CMD_BADJ_1;
	if (strcmp(key, "BRUN") == 0) return CMD_BRUN_1;
	if (strcmp(key, "DIM") == 0) return CMD_DIM_1;
	if (strcmp(key, "FCAL") == 0) return CMD_FCAL_1;
	if (strcmp(key, "MMOD") == 0) return CMD_MMOD_1;
	if (strcmp(key, "PWMM") == 0) return CMD_PWMM_1;
	if (strcmp(key, "RSBR") == 0) return CMD_RSBR_1;
	if (strcmp(key, "SCRO") == 0) return CMD_SCRO_1;
	if (strcmp(key, "TINV") == 0) return CMD_TINV_1;
	if (strcmp(key, "TMS") == 0) return CMD_TMS_1;
	if (strcmp(key, "TPOL") == 0) return CMD_TPOL_1;
	if (strcmp(key, "TWDT") == 0) return CMD_TWDT_1;
	if (strcmp(key, "TXOF") == 0) return CMD_TXOF_1;
	if (strcmp(key, "ZADJ") == 0) return CMD_ZADJ_1;

	return CMD_UNKNOWN;
}







// Returns a pointer to the matching substring in the buffer, or NULL
char *findMatchingSubstring(char *buffer)
{
	for(int i=0;i<30;i++)
	{
	const char *match = strstr(buffer, knownKeys[i]);
	if(match!=NULL)
	{
		return match;
	}
	}
	return NULL;


}


void handleCommand(char *buffer)
{
	char data_1;
	data_1=buffer[0];
//	char *key = strtok(&buffer[1], "=");
//	char *value_str = strtok(NULL, "=");
	char key[32],value_str[32];
	int result;
	char *buffer_1;
	buffer_1 = findMatchingSubstring(buffer);
	if (buffer_1 != NULL) {
	    result = sscanf(buffer_1, "%[^=]=%s", key, value_str);
	} else {
	    return;  // or handle error
	}


	//if (key && value_str)
	//{

		if (key)
			{
		uint32_t value = atoi(value_str);
		Parse_data cmd_2= getCommandEnum(key);

		switch (cmd_2)
		{
		case B_INDEX_VALUE_1:
			cmd.B_INDEX_VALUE = value;
			break;
		case MGD_1:
			cmd.MGD = value;
			break;
		case MGM_1:
			cmd.MGM = value;
			break;
		case MZ_1:
			cmd.MZ = value;
			break;
		case T_1:
			cmd.T = value;
			break;
		case MGT_1:
			cmd.MGT = value;
			break;
		case VAR_INDEX_VALUE_1:
			cmd.VAR_INDEX_VALUE = value;
			break;
		case MGS_1:
			cmd.MGS = value;
			break;
		case MGX_1:
			cmd.MGX = value;
			break;

		case SET_B_1:
			cmd.SET_B= value;
			break;
		case SET_R_1:
			cmd.SET_R = value;
			break;
		case SET_TV_1:
			cmd.SET_TV = value;
			break;
		case SET_VAR_1:
			cmd.SET_VAR = value;
			break;
		case SET_TX_1:
			cmd.SET_TX = value;
			break;
		case SET_ZER_1:
			cmd.SET_ZER = value;
			break;

		case CMD_ANAM_1:
			cmd.CMD_ANAM = value;
			break;
		case CMD_BADJ_1:
			cmd.CMD_BADJ = value;
			break;
		case CMD_BRUN_1:
			cmd.CMD_BRUN = value;
			break;
		case CMD_DIM_1:
			cmd.CMD_DIM = value;
			break;
		case CMD_FCAL_1:
			cmd.CMD_FCAL = value;
			break;
		case CMD_MMOD_1:
			cmd.CMD_MMOD = value;
			break;
		case CMD_PWMM_1:
			cmd.CMD_PWMM = value;
			break;
		case CMD_RSBR_1:
			cmd.CMD_RSBR = value;
			break;
		case CMD_SCRO_1:
			cmd.CMD_SCRO = value;
			break;
		case CMD_TINV_1:
			cmd.CMD_TINV = value;
			break;
		case CMD_TMS_1:
			cmd.CMD_TMS = value;
			break;
		case CMD_TPOL_1:
			cmd.CMD_TPOL = value;
			break;
		case CMD_TWDT_1:
			cmd.CMD_TWDT = value;
			break;
		case CMD_TXOF_1:
			cmd.CMD_TXOF = value;
			break;
		case CMD_ZADJ_1:
			cmd.CMD_ZADJ = value;
			break;

		default:
			// Optional: handle unknown commands or error logging
			break;
		}
	}
}
