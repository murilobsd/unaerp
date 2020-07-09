/*
 * Copyright (c) 2020 Murilo Ijanc' <mbsd@m0x.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <ESP8266WiFi.h>
#include <Hash.h>
#include <WebSocketsClient.h>

/* wifi ssid e senha */
const char 		*wifi_ssid = "";
const char 		*wifi_password = "";

/* leds */
const int	 	 PIN_VERM = 16;		/* D0 */
const int	 	 PIN_AMAR = 5;		/* D1 */

/* Sensor ultrasônico */
const int	 	 PIN_ECHO = 4; 		/* D2 */
const int	 	 PIN_TRIG = 0; 		/* D3 */

/* BaudRate 1152000 */
const int 	 	 BRD = 115200;

/* configurações do servidor websocket */
const char		*ip_servidor = "172.20.10.2";
const char		*rota = "/";
const int	 	 porta = 1234;

/* instância global websocket */
WebSocketsClient 	 websocket;
int 			 count = 0;
int 			 distance;
int 			 estacionado = 0;
long 			 duration;

static void 	 	 fn_recebe_evento(WStype_t, uint8_t *, size_t);
static void 	 	 send_data_txt(const char *);

/*
 * Função Setup
 */
void
setup(void)
{
	/* inicializo o serial */
	Serial.begin(BRD);

	/* inicializamos os leds */
	pinMode(PIN_VERM, OUTPUT);
	pinMode(PIN_AMAR, OUTPUT);

	/* inicializamos o sensor ultrasônico */
	pinMode(PIN_ECHO, INPUT);
	pinMode(PIN_TRIG, OUTPUT);

	/* inicializar wifi modo estação (cliente) */
	WiFi.mode(WIFI_STA);
	WiFi.begin(wifi_ssid, wifi_password);

	while (WiFi.status() != WL_CONNECTED) {
		digitalWrite(PIN_VERM, HIGH);
		delay(500);
		digitalWrite(PIN_VERM, LOW);
		Serial.println("Não conectado.");
	}

	digitalWrite(PIN_VERM, LOW);
	digitalWrite(PIN_AMAR, HIGH);

	/* imprime o ssid da rede wifi */
	Serial.print("Conectado Wifi: ");
	Serial.println(wifi_ssid);
	Serial.println("");

	/* retorna o ip da placa */
	Serial.print("IP: ");
	Serial.print(WiFi.localIP());

	/* conectar ao servidor websocket */;
	websocket.begin(ip_servidor, porta, rota);
	/* qualquer evento */
	websocket.onEvent(fn_recebe_evento);
	/* intervalo de reconexão */
	websocket.setReconnectInterval(5000);
	/* heart beat */
	websocket.enableHeartbeat(15000, 3000, 2);
}

static void
send_data_txt(const char *msg)
{
	websocket.sendTXT(msg);
}

static void
fn_recebe_evento(WStype_t tipo, uint8_t *dado, size_t tamanho)
{
	switch(tipo) {
		case WStype_DISCONNECTED:
			Serial.println("Desconectado Websocket");
			break;
		case WStype_CONNECTED:
			Serial.println("Conectado no Websocket");
			break;
		case WStype_PING:
			Serial.println("Ping");
			break;
		case WStype_PONG:
			Serial.println("Pong");
			break;
	}
}

/*
 * Loop principal
 */
void
loop(void)
{
	//websocket.loop();
	//char buf[5];

	delay(1000);

	/* aguarde 2 segundos */
	//delay(2000);

	// Clears the PIN_TRIG
	digitalWrite(PIN_TRIG, LOW);
	delayMicroseconds(2);

	// Sets the PIN_TRIG on HIGH state for 10 micro seconds
	digitalWrite(PIN_TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(PIN_TRIG, LOW);

	// Reads the PIN_ECHO, returns the sound wave travel time in microseconds
	duration = pulseIn(PIN_ECHO, HIGH);

	// Calculating the distance
	distance = duration * 0.034/2;

	// Prints the distance on the Serial Monitor
	Serial.print("Distance: ");
	Serial.println(distance);
	//sprintf(buf, "%.2f", distance);

	if (distance <= 40) {
		if (count > 3 && estacionado == 0) {
			send_data_txt("1|p");
			estacionado = 1;
		} else if (estacionado == 1)
			;
		count += 1;
	} else {
		if (count > 3 && estacionado == 1)
			send_data_txt("1|l");
		count = 0;
		estacionado = 0;
	}
	websocket.loop();
}
