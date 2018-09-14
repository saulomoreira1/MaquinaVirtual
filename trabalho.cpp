/*
	Tamanho das instruções = 16bits
	
	ADD		0001 1
	SUB		0010 2
	STORE	0110 6
	LOAD	1001 9

	Tipo 1:
	
	- Soma/Subtração
	
	(End Reg1)	(End Reg2)	(End Dest) (Tipo de Instrução)
	
	4 bits		4 bits		4 bits		4 bits
	0001		0010		0011		0001 	= 0b0001001000110001
	
	Tipo 2:
	
	- Load/Store
	
	(End Memoria)	(End Reg)	(Tipo de Instrução)
	
		8 bits			4 bits			4 bits
	   00100101			0001			0110	= 0b0010010100010110		


*/

#include<iostream>

using namespace std;

void decodificar();
void executar();

unsigned int MemoriaPrograma[] = {	0b0000000100011001, //load
									0b0000001000101001, //load
									0b0001001000110001, //add
									0b0000001100110110}; //store
						
unsigned int MemoriaDados[] = {5, 6, 0, 0, 0, 0, 0, 0, 0 ,0	};

unsigned int PC;
unsigned int Registrador[10];
unsigned int Instrucao;
unsigned int TipoInstr;
unsigned int RegistradorA;
unsigned int RegistradorB;
unsigned int RegDestino;
unsigned int RegMemoria;
unsigned int Reg[10];

int main()
{
	
	for(int i = 0; i < 10; i++) 
		Registrador[i] = 0;
		
	PC = 0;
	
	while(PC < 4)
	{
		Instrucao = MemoriaPrograma[PC];
		PC++;
		decodificar();
		executar();	
	}
	
	return 0;
}

void decodificar()
{
		TipoInstr = Instrucao & 0b0000000000001111;
		
		if(TipoInstr == 1 || TipoInstr == 2) //add ou sub
		{
			RegistradorA = Instrucao >> 12; //ok
			RegistradorB = Instrucao >> 8;
			RegistradorB = RegistradorB & 0b0000000000001111;
			RegDestino = Instrucao >> 4;
			RegDestino = RegDestino & 0b0000000000001111;
		}
		else if(TipoInstr == 6) //store
		{
			RegistradorA = Instrucao >> 8;
			RegMemoria = RegistradorA & 0b0000000011111111;
		}
		else if(TipoInstr == 9) //load
		{
			RegDestino = Instrucao >> 4;
			RegDestino = RegDestino & 0b0000000000001111;
			RegMemoria = RegDestino;
		}
}

void executar()
{
	if(TipoInstr == 1) //soma
	{
		Reg[RegDestino] = Reg[RegistradorA] + Reg[RegistradorB];
	}
	else if(TipoInstr == 2)//subtracao
	{
		Reg[RegDestino] = Reg[RegistradorA] - Reg[RegistradorB];
	}
	else if(TipoInstr == 6) //store
	{
		MemoriaDados[RegMemoria] = Reg[RegistradorA];
	}
	else if(TipoInstr == 9) //load
	{
		Reg[RegDestino] = MemoriaDados[RegMemoria];
	}
}
