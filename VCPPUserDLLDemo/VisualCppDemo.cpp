// Demo-Beispiel zur Entwicklung eigener User-DLLs in Visual C++ 2008 
// 
// aus "Einf?hrung in WinFACT"


#include "stdafx.h"
#include <string.h>
#include "WFnum.h"
#include "form1.h"
#include <sstream>

using namespace VCPPUserDLLDemo;

typedef struct UserData{
	// TO DO:
	//
	// F?gen Sie hier die Parameterdefinitionen des User-DLL-Blocks ein
	//
	// Beispiel:
	//
	// a,b: extended;
	// c: integer;
	double a,b;  // Flie?kommavariablen
}UserData_t;



typedef unsigned short WORD;
typedef char* PChar;

#pragma pack(1)
typedef struct{	
	char NuE;								 // Anzahl reeller Zahlenwerte																	
	char NuI;								 // Anzahl ganzer Zahlenwerte																	
	char NuB;								 // Anzahl Schalter																						
	WFNum E[32];						 // reelle Zahlenwerte																					
	int I[32];							 // ganze Zahlenwerte																					
	char B[32];							 // Schalter																										
	char D[256];						 // event. Dateiname f?r weitere Daten.												
	WFNum EMin[32];					 // untere Eingabegrenze f?r jeden reellen Zahlenwert					
	WFNum EMax[32];					 // obere Eingabegrenze f?r jeden rellen Zahlenwert						
	int IMin[32];						 // untere Eingabegrenze f?r jeden ganzzahligen Zahlenwert			
	int IMax[32];						 // obere Eingabegrenze f?r jeden ganzzahligen Zahlenwert			
	char NaE[32][41];				 // Namen der reellen Zahlenwerten															
	char NaI[32][41];				 // Namen der ganzen Zahlenwerten															
	char NaB[32][41];				 // Namen der Schalter																		 
	UserData_t *userdata;		 // Zeiger auf Benutzerdaten																		
	void	 *parent;					 // Zeiger auf User-DLL-Block																	
	HANDLE hwnd;						 // Handle des User-DLL-Blocks
	char	 *parentName;			 // Name des User-DLL-Blocks																		
	HANDLE userHwnd;				 // Benutzerdef. Fensterhandle, z. B. f?r Ausgabefenster				
} TParameterStruct, *PParameterStruct;


typedef struct {
	long AllowE;        // Soll die Eingabe eines Wertes   
	long AllowI;				// un-/zul?ssig sein so ist das Bit
	long AllowB;				// des Allow?-Feldes 0 bzw. 1    
	char AllowD;
} TDialogEnableStruct, *PDialogEnableStruct;

typedef struct {
	char Inputs;         // Anzahl Eing?nge 
	char Outputs;				 // Anzahl Ausg?nge
	char NameI[50][41];
	char NameO[50][41];
} TNumberOfInputsOutputs, *PNumberOfInputsOutputs;


typedef WFNum TInputArray[50];  
typedef WFNum TOutputArray[50];

#pragma pack()


//  Exportieren der notwendigen Funktionen und Prozeduren 
#ifdef __cplusplus
extern "C"
{
#endif
	PChar __declspec(dllexport) __stdcall GetDLLName(void);
	void  __declspec(dllexport) __stdcall InitUserDLL(PParameterStruct);
	void  __declspec(dllexport) __stdcall DisposeUserDLL(PParameterStruct); 
	void  __declspec(dllexport) __stdcall WriteToFile(WORD aFileHandle,  PParameterStruct D); 
	void  __declspec(dllexport) __stdcall ReadFromFile(WORD aFileHandle, PParameterStruct D); 
	void  __declspec(dllexport) __stdcall GetParameterStruct(PParameterStruct);
	void  __declspec(dllexport) __stdcall GetDialogEnableStruct(PDialogEnableStruct,PParameterStruct);
	void  __declspec(dllexport) __stdcall GetNumberOfInputsOutputs(PNumberOfInputsOutputs D);
	int   __declspec(dllexport) __stdcall CanSimulateDLL(PParameterStruct D);
	int   __declspec(dllexport) __stdcall CallParameterDialogDLL(PParameterStruct D, PNumberOfInputsOutputs Nio);
	void  __declspec(dllexport) __stdcall InitSimulationDLL(PParameterStruct D,TInputArray Inputs,TOutputArray Outputs);
	void  __declspec(dllexport) __stdcall SimulateDLL(WFNum T,PParameterStruct D,TInputArray Inputs,TOutputArray Outputs);
	void  __declspec(dllexport) __stdcall EndSimulationDLL(void);
	void  __declspec(dllexport) __stdcall IsUserDLL32(void);
#ifdef __cplusplus
}
#endif


void __stdcall InitUserDLL(PParameterStruct D)
{
	D->userdata=new UserData_t;  // Speicher f?r Benutzerdaten anlegen
	// TO DO:
	//
	// Legen Sie hier z. B. Voreinstellungen f?r die Blockparameter fest
	// oder erzeugen Sie zus?tzliche dynamische Variablen
	//
	// Beispiel:
	//
	D->userdata->a=1.0;					 // Voreinstellung Parameter a                 
	D->userdata->b=2.0;					 // Voreinstellung Parameter b                 
}


void __stdcall DisposeUserDLL(PParameterStruct D)
{
	delete D->userdata;          // Speicher f?r Benutzerdaten wieder freigeben
	// TO DO:
	//
	// Geben Sie hier z. B. die in InitUserDLL zus?tzlich erzeugten
	// Variablen wieder frei
}


void __stdcall WriteToFile(WORD aFileHandle, PParameterStruct D)
{
	char s[1000];
	// TO DO:
	//
	// Speichern Sie hier die Blockparameter in Datei ab
	//
	// Beispiel:
	//
	sprintf_s(s,"%g\r\n",D->userdata->a);  	_lwrite(aFileHandle,s,strlen(s));  // Parameter a speichern
	sprintf_s(s,"%g\r\n",D->userdata->b);  	_lwrite(aFileHandle,s,strlen(s));	 // Parameter b speichern
}


void ReadOneLine(WORD aFileHandle, PChar Aps)
{
	int i;
	i=0;
	_lread(aFileHandle,&Aps[i],1);
	do{
		i++;
		_lread(aFileHandle,&Aps[i],1);
	}while(! (Aps[i-1]==13 && Aps[i]==10));
	Aps[i-1]=0;
}

void __stdcall ReadFromFile(WORD aFileHandle, PParameterStruct D)
{
	char s[1000];
	// TO DO:
	//
	// Lesen Sie hier die Blockparameter aus Datei ein
	//
	// Beispiel:
	//
	ReadOneLine(aFileHandle,s);	D->userdata->a=atof(s);   // Parameter a einlesen
	ReadOneLine(aFileHandle,s);	D->userdata->b=atof(s);		// Parameter b einlesen
}


void __stdcall  GetParameterStruct(PParameterStruct D) 
{
  //Anzahl der Parameter
	D->NuE = 0;
	D->NuI = 0;
	D->NuB = 0;
}


void __stdcall GetDialogEnableStruct(PDialogEnableStruct D,PParameterStruct D2)
{
	// Alle Dialogelemente sollen jederzeit zug?nglich sein!}
	D->AllowE=0xFFFFFFFF;
	D->AllowI=0xFFFFFFFF;
	D->AllowB=0xFFFFFFFF;
	D->AllowD=1;
}


void __stdcall GetNumberOfInputsOutputs(PNumberOfInputsOutputs D)
{
	// TO DO:
	//
	// Legen Sie hier die Anzahl der Blockein- und -ausg?nge fest
	//
	// Beispiel:
	//
	D->Inputs=3;
	D->Outputs=2;
	//------------------------
	// TO DO:
	//
	// Legen Sie hier die Bezeichnungen f?r die Ein- und Ausg?nge des Blocks fest
	//
	// Beispiel:
	strncpy_s(D->NameI[0],"Dateneingang 1",sizeof(D->NameI[0]));   // Bezeichnung des 1. Eingangs
	strncpy_s(D->NameI[1],"Dateneingang 2",sizeof(D->NameI[1]));	 // Bezeichnung des 2. Eingangs
	strncpy_s(D->NameI[2],"Steuereingang",sizeof(D->NameI[2]));		 // Bezeichnung des 3. Eingangs
	strncpy_s(D->NameO[0],"Datenausgang",sizeof(D->NameO[0]));		 // Bezeichnung des 1. Ausgangs
	strncpy_s(D->NameO[1],"Vorzeichenflag",sizeof(D->NameO[1]));	 // Bezeichnung des 2. Ausgangs
}


int __stdcall CanSimulateDLL(PParameterStruct D)
{ 
	// TO DO:
	//
	// Legen Sie hier ggf. fest, unter welchen Bedingungen der Block simulierbar sein soll
	return 1;  // Block immer simulierbar
}


void __stdcall SimulateDLL(WFNum T, PParameterStruct D, TInputArray Inputs, TOutputArray Outputs)
{
	// TO DO:
	// 
	// Stimmen Sie die Gr??e der Arrays auf die Anzahl der Ein-/Ausg?nge des Blockes ab
	// und entfernen Sie die Kommentarzeichen:
	double I[3];
	double O[2];
	int i;
	for(i=0; i<3; ++i)
		I[i] = WFNum2double(Inputs[i]);
	
	// TO DO:
	//
	// Legen Sie hier das Verhalten des User-DLL-Blocks bei jedem Simulationsschritt fest
	if (I[2]>2.5)                // 3. Blockeingang HIGH
		O[0] = D->userdata->a * (I[0]+I[1]);
	else                         // 3. Blockeingang LOW
		O[0] = D->userdata->b * (I[0]-I[1]);
	
	if (! ((I[0]<0) ^ (I[1]<0))) // gleiches Vorzeichen
		O[1] = 5.0;
	else                         // unterschiedliche Vorzeichen
		O[1] = 0.0;

	// TO DO: Entfernen Sie die Kommentarzeichen, sofern Sie Blockausg?nge verwenden:
	for(i=0; i<2; ++i)
		Outputs[i]=double2WFNum(O[i]);
}


void __stdcall InitSimulationDLL(PParameterStruct D,TInputArray Inputs,TOutputArray Outputs)
{
	// TO DO:
	//
	// Legen Sie hier das Verhalten des User-DLL-Blocks beim 0-ten Simulationsschritt fest
	SimulateDLL(double2WFNum(0.0),D,Inputs,Outputs);  // Normalen Simulationsschritt ausf?hren
}


void __stdcall EndSimulationDLL(void)
{
	// TO DO:
	//
	// Legen Sie hier das Verhalten des User-DLL-Blocks bei Beendigung der Simulation fest
}


int __stdcall CallParameterDialogDLL(PParameterStruct D, PNumberOfInputsOutputs Nio)
{
	// Stellt den benutzerdefinierten Parameterdialog dar 
	form1 form;
	// TO DO:
	//
	// Aktuelle Parameter an Dialog ?bergeben
	//
	// Beispiel:
	// 	form.seta(D->userdata->a);
 	form.seta(D->userdata->a);
	form.setb(D->userdata->b);
	if (DialogResult::OK == form.ShowDialog()){
		// TO DO:
		//
		// Ge?nderte Parameterwerte aus Dialog zur?cklesen
		//
		// Beispiel:
		//
 		D->userdata->a = form.geta();
		D->userdata->b = form.getb();
	}
	return 1;
}


PChar __stdcall GetDLLName(void)
{
	// TO DO:
	//
	// Legen Sie hier statisch(!) die Bezeichnung des User-DLL-Blocks fest
	//
	// Beispiel:
	//
	static const char name[]="Demo-DLL aus \"Einf?hrung in WinFACT\"";
	return (PChar) &name[0];
}


void __stdcall IsUserDLL32(void)
{ }




