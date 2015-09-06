#include "config.h"
#ifdef RADIO_USE_WIFI_ARDUINO
#include "radio_wifi1.h"
#include "djtimer.h"
#include "uart.h"
#include "debug.h"
//#include "../../common/routing/routing.h"
#include <string.h>
#include <stdio.h>

//#define output_high(port, pin) port |= (1<<pin)
//#define output_low(port, pin) port &= ~(1<<pin)

char self_ip[16] = {0};
char self_net_mask[16] = {0};
char wifi_ssid[] = "intel_wukong";
char wifi_security_key[] = "wukong2012";
//char wifi_ssid[] = "dlink";
//char wifi_security_key[] = "my22346292";
//char wifi_ssid[] = "ICS";
//char wifi_security_key[] = "intel2012";

static uint8_t wifi_wait_and_read(uint16_t wait_ms){
	if(uart_available(WIFI_UART, wait_ms)){
		return uart_read_byte(WIFI_UART);
	}
	return 0;
}

static void clear_buffer(){
	if( uart_available(WIFI_UART, 1000) ){
		uart_read_byte(WIFI_UART);
		while(uart_available(WIFI_UART, 100)) uart_read_byte(WIFI_UART);
	}
}

static void show_result(){
	if( uart_available(WIFI_UART, 1000) ){
		DEBUG_LOG(DBG_WIFI_ARDUINO, "%c", uart_read_byte(WIFI_UART));
		while(uart_available(WIFI_UART, 100))
			DEBUG_LOG(DBG_WIFI_ARDUINO, "%c", uart_read_byte(WIFI_UART));
	}
	DEBUG_LOG(DBG_WIFI_ARDUINO, "\n");
}

static void enter_cmd_mode(){
	uint8_t i;
	char temp[]="$$$";
	dj_timer_delay(250);
	for(i = 0; i < strlen(temp); i++) uart_write_byte(WIFI_UART, temp[i]);
	dj_timer_delay(250);

	if(SHOW_RESULT){
		show_result();
	}else{
		clear_buffer();
	}
}

static void exit_cmd_mode(){
	uint8_t i;
	char temp[]="exit";
	for(i = 0; i < strlen(temp); i++) uart_write_byte(WIFI_UART, temp[i]);
	uart_write_byte(WIFI_UART, '\r');

	if(SHOW_RESULT){
		show_result();
	}else{
		clear_buffer();
	}
}

static void radio_wifi_send_cmd(uint8_t cmd, char* parameter){
	uint8_t i;
	switch (cmd) {
		case CMD_SET_WLAN_SSID:
		{
			char cmd_buf[35]={0};
			strcat(cmd_buf, "set wlan ssid ");
			strcat(cmd_buf, wifi_ssid);
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');

			if(SHOW_RESULT){
				show_result();
			}else{
				clear_buffer();
			}
			break;
		}
		case CMD_SET_WLAN_PASSWORD:
		{
			char cmd_buf[35]={0};
			strcat(cmd_buf, "set wlan phrase ");
			strcat(cmd_buf, wifi_security_key);
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');

			if(SHOW_RESULT){
				show_result();
			}else{
				clear_buffer();
			}
			break;
		}
		case CMD_JOIN_NETWORK:
		{

			char cmd_buf[35]={0};
			strcat(cmd_buf, "join ");
			strcat(cmd_buf, wifi_ssid);
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');
			dj_timer_delay(100);

		      	if(SHOW_RESULT){
				show_result();
			}else{
				clear_buffer();
			}
			break;

		}
		case CMD_OPEN:
		{

			char cmd_buf[35]={0};
			strcat(cmd_buf, "open ");
			strcat(cmd_buf, parameter);
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');
			dj_timer_delay(100);

			if(SHOW_RESULT){
				show_result();
			}else{
				clear_buffer();
			}
			break;

		}
		case CMD_SHOW_CONNECTION:
		{

			char cmd_buf[]="show connection";
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');
			//clear_buffer();
			//show_result();
			break;

		}
		case CMD_CLOSE:
		{

			char cmd_buf[]="close";
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');

			if(SHOW_RESULT){
				show_result();
			}else{
				clear_buffer();
			}
			break;

		}
		case CMD_SAVE:
		{
			char cmd_buf[]="save";
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');

			if(SHOW_RESULT){
				show_result();
			}else{
				clear_buffer();
			}
			break;
		}
		case CMD_GET_NET_MASK_AND_IP:
		{
			char cmd_buf[]="get ip";
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');
			//clear_buffer();
			//show_result();
			break;
		}
		case CMD_SET_IP_PROTO_THREE:
		{
			char cmd_buf[]="set ip proto 3";
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');

			if(SHOW_RESULT){
				show_result();
			}else{
				clear_buffer();
			}
		}
		case CMD_SET_IP_HOST:
		{
			char cmd_buf[35]={0};
			strcat(cmd_buf, "set ip host ");
			strcat(cmd_buf, parameter);
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');

			if(SHOW_RESULT){
				show_result();
			}else{
				clear_buffer();
			}
		}
		case CMD_SET_WLAN_JOIN_ONE:
		{
			char cmd_buf[]="set wlan join 1";
			for(i = 0; i < strlen(cmd_buf); i++) uart_write_byte(WIFI_UART, cmd_buf[i]);
			uart_write_byte(WIFI_UART, '\r');

			if(SHOW_RESULT){
				show_result();
			}else{
				clear_buffer();
			}
		}
	}
}

void radio_wifi_init(){
	//turn on wifi module on wudevice 3.0
	DDRL |= (1<<5);
	PORTL &= ~(1<<5);
	PORTL |= (1<<5);

	uart_inituart(WIFI_UART, 9600);  
	enter_cmd_mode();
	radio_wifi_send_cmd(CMD_SET_WLAN_SSID, NULL);
	radio_wifi_send_cmd(CMD_SET_WLAN_PASSWORD, NULL);
	radio_wifi_send_cmd(CMD_SET_IP_PROTO_THREE, NULL);
	radio_wifi_send_cmd(CMD_SET_WLAN_JOIN_ONE, NULL);
	radio_wifi_send_cmd(CMD_SAVE, NULL);
	//radio_wifi_send_cmd(CMD_JOIN_NETWORK, NULL);
	exit_cmd_mode();
	radio_wifi_get_net_mask_and_ip(self_ip, self_net_mask);
	DEBUG_LOG(DBG_WIFI_ARDUINO, "self_ip = %s, self_net_mask = %s\n", self_ip, self_net_mask);
}

static void clear_line(){	
	while(uart_available(WIFI_UART, 100)){
		if(uart_read_byte(WIFI_UART) == '\n') break;
	}
}

void radio_wifi_get_net_mask_and_ip(char* self_ip, char* self_net_mask){
	char temp[7] = {0};
	uint8_t i = 0;
	enter_cmd_mode();
	radio_wifi_send_cmd(CMD_GET_NET_MASK_AND_IP, NULL);
	while(uart_available(WIFI_UART, 0) == false);
	temp[i] = uart_read_byte(WIFI_UART);
	while(uart_available(WIFI_UART, 100) && temp[i] != '\n'){
		temp[++i] = uart_read_byte(WIFI_UART);
	}

	if(strncmp(temp, "get ip", strlen("get ip")) == 0){
		for(i = 1; i <= 2; i++) clear_line();
		//get ip
		memset(self_ip, 0, 16);
		for(i = 1; i <= 3; i++){
			if(uart_available(WIFI_UART, 100)) uart_read_byte(WIFI_UART);
		}
		i = 0;
		while(uart_available(WIFI_UART, 100)){
			unsigned char temp2 = uart_read_byte(WIFI_UART);
			if(temp2 == ':') {
				self_ip[i]='\0';
				clear_line();
				break;
			}else{
				self_ip[i++] = temp2;
			}
		}
		//get net mask
		memset(self_net_mask, 0, 16);
		for(i = 1; i <= 3; i++){
			if(uart_available(WIFI_UART, 100)) uart_read_byte(WIFI_UART);
		}
		i = 0;
		while(uart_available(WIFI_UART, 100)){
			unsigned char temp2 = uart_read_byte(WIFI_UART);
			if(temp2 == '\n') {
				self_net_mask[--i]='\0';
				clear_buffer();
				break;
			}else{
				self_net_mask[i++] = temp2;
			}
		}
	}else{
		clear_buffer();
	}
	exit_cmd_mode();
}

static void send_wukong_pattern(){
	uart_write_byte(WIFI_UART, 'w');
	uart_write_byte(WIFI_UART, 'u');
	uart_write_byte(WIFI_UART, 'k');
	uart_write_byte(WIFI_UART, 'o');
	uart_write_byte(WIFI_UART, 'n');
	uart_write_byte(WIFI_UART, 'g');
}

void radio_wifi_send(char* ip, unsigned char* data, uint8_t length){
	enter_cmd_mode();
	radio_wifi_send_cmd(CMD_SET_IP_HOST, ip);
	exit_cmd_mode();
	//send pattern
	send_wukong_pattern();
	//transmit data
  	uart_write_byte(WIFI_UART, length);
	uint8_t i;
	for(i = 0; i < length; i++) uart_write_byte(WIFI_UART, data[i]);
	//send ip
	for(i = 0; i < strlen(self_ip); i++) uart_write_byte(WIFI_UART, self_ip[i]);
	uart_write_byte(WIFI_UART, '\0');
}

void radio_wifi_send_without_ip(unsigned char* data, uint8_t length){
	//send pattern
	send_wukong_pattern();
	//transmit data
  	uart_write_byte(WIFI_UART, length);
	uint8_t i;
	for(i = 0; i < length; i++) uart_write_byte(WIFI_UART, data[i]);
	//send ip
	for(i = 0; i < strlen(self_ip); i++) uart_write_byte(WIFI_UART, self_ip[i]);
	uart_write_byte(WIFI_UART, '\0');
}

static void radio_wifi_rece_data(){
	if(uart_available(WIFI_UART, 0)){
		if(wifi_wait_and_read(100) == 'w' && wifi_wait_and_read(100) == 'u' && wifi_wait_and_read(100) == 'k' && 
		wifi_wait_and_read(100) == 'o' && wifi_wait_and_read(100) == 'n' && wifi_wait_and_read(100) == 'g'){
			unsigned char data[50]={0};
			char ip[16]={0};
			uint8_t data_len = wifi_wait_and_read(100);
			if(data_len > 50){
				DEBUG_LOG(DBG_WIFI_ARDUINO, "WIFI_DEBUG: data too big, abandoned.\n");
				clear_buffer();
			}else{
				uint8_t i;
				for(i = 0; i < data_len; i++) data[i] = wifi_wait_and_read(100);
				DEBUG_LOG(DBG_WIFI_ARDUINO, "WIFI_DEBUG: data %s\n", data);
				i = 0;
				ip[i] = wifi_wait_and_read(100);
				while(ip[i] != '\0' && i <= 16){
					ip[++i] = wifi_wait_and_read(100);
				}
				DEBUG_LOG(DBG_WIFI_ARDUINO, "WIFI_DEBUG ip: %s\n", ip);
				routing_handle_wifi_message(ip , data, data_len);
			}
		}else{
			DEBUG_LOG(DBG_WIFI_ARDUINO, "Unkonw data\n");
			clear_buffer();
			//while(uart_available(WIFI_UART, 100))
			//	uart_read_byte(WIFI_UART);
		}
	}
}

void radio_wifi_poll() {
	radio_wifi_rece_data();
}
#endif