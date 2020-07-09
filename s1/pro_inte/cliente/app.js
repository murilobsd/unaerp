/* host do servidor websocket */
const host = "ws://172.20.10.2:1234/";
const ws = new WebSocket(host);
var entrou = 0;

/*
 * Função altera a cor da div
 */
var altera_vaga = (id_vaga) => {
  /* obtenho o elemento vaga pelo id*/
  const class_preenchida = "preenchida";
  const el_vaga = document.getElementById(id_vaga);
  if (el_vaga != undefined && el_vaga != null) {
    el_vaga.classList.toggle(class_preenchida);
  } else {
    console.log("Não encontrado o elemento de id: ", id_vaga);
  }
  if (entrou === 0) {
    document.getElementById("info-vagas").innerHTML = "Vagas Livres: 2 / 6";
    entrou = 1;
  } else {
    document.getElementById("info-vagas").innerHTML = "Vagas Livres: 1 / 6";
    entrou = 0;
  }
};

ws.onmessage = function (event) {
  const data = event.data;
  console.log("Recebido: ", data);
  const _id = data.split("|");
  altera_vaga(data[0]);
};
