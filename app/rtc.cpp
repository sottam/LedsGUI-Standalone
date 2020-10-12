#include "rtc.hpp"

String setTime(String unix_time_str) {
    uint32_t unix_time = atoll(unix_time_str.c_str());
	
    if(errno == ERANGE || (unix_time == 0 && unix_time_str != "0"))
        return String("INVALID UNIX TIME.");

	timeval tv; //Cria a estrutura temporaria para funcao abaixo.
  	tv.tv_sec = unix_time; //Atribui minha data atual. Voce pode usar o NTP para isso ou o site citado no artigo!
  	settimeofday(&tv, NULL); //Configura o RTC para manter a data atribuida atualizada.
    
    return getFTime(getTime());
}

tm getTime() {
	time_t tt = time(NULL);//Obtem o tempo atual em segundos. Utilize isso sempre que precisar obter o tempo atual
	tm data = *gmtime(&tt);//Converte o tempo atual e atribui na estrutura
	return data;
}

time_t getTimeinSeconds() {
	return time(NULL);
}

String getFTime(tm data) {
	char data_formatada[64];
	strftime(data_formatada, 64, "%d/%m/%Y %H:%M:%S", &data);//Cria uma String formatada da estrutura "data"
	
	return String(data_formatada);
}

void setup_RTC() {
    //SET DEFAULT DATE
	setTime("0"); // 1970-01-01T00:00:00+00:00
}

void loop_RTC() {
	
}