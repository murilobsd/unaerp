/* $Id$	*/

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

/*
 * Projeto da Atividade Parcial de Lógica e Criatividade
 * PiPi Pet v0.0.1
 */

#define HI  HIGH
#define LO  LOW
#define IN  INPUT
#define OUT OUTPUT

/* pinos leds */
const int	L_RED = 7;
const int	L_GREEN = 8;

/* pinto alarme */
const int 	S_ALARM = 10;

/* pinos sensor ultrasônico  */
const int  	S_ULTRAS_TRIG = 4;
const int  	S_ULTRAS_ECHO = 5;

/* pino botao liga e desliga */
const int  	B_ONOFF = 12;

/* limite de distância para ativar o alarme em cm */
const int 	DIST_MAX = 20;

long   		tempo = 0;  /* tempo em ms */
float   	dist = 0;   /* distância em cm */
int   		is_on = 0;  /* sistema esta ligado */


void
setup(void)
{
  /* leds */
  pinMode(L_RED, OUT);
  pinMode(L_GREEN, OUT);

  /* botao liga/desliga */
  pinMode(B_ONOFF, IN);

  /* sensor ultrasonico */
  pinMode(S_ULTRAS_TRIG, OUT);
  pinMode(S_ULTRAS_ECHO, IN);

  /* tone */
  pinMode(S_ALARM, OUT);

  /* baudrate 9600 da saída serial */
  Serial.begin(9600);
}

void
loop(void)
{
  /* leio o valor do botão liga e desliga */
  is_on = digitalRead(B_ONOFF);

  /* esta ligado */
  if (is_on == HI) {
    /* ligamos o led verde */
    digitalWrite(L_GREEN, HI);
    Serial.println("ligado");

    /* checamos a distância */
    digitalWrite(S_ULTRAS_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(S_ULTRAS_TRIG, HIGH);

    delayMicroseconds(10);

    digitalWrite(S_ULTRAS_TRIG, LOW);

    tempo = pulseIn(S_ULTRAS_ECHO, HI);

    /* ditância em cm */
    dist = tempo * 0.034 / 2;

    Serial.print(dist);
    Serial.println(" cm");

    /*
     * o pet esta bem proximo do sensor sinal que pode
     * estar realizando suas necessidades
     */
    if (dist <= DIST_MAX) {
	     digitalWrite(L_RED, HI);
	     tone(S_ALARM, 200);
    } else {
	    noTone(S_ALARM);
	    digitalWrite(L_RED, LO);
    }
  } else {
	  Serial.println("desligado");
	  digitalWrite(L_GREEN, LO);
	  digitalWrite(L_RED, LO);
	  noTone(S_ALARM);
  }
  delay(100);
}
