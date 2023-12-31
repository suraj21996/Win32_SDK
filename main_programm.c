#include <windows.h>
#include<stdio.h>
//#define MAX 1024

FILE *fPtr=NULL;
char eventCount[15]; 

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPSTR pszCmdLine,
				int iCmdShow
				)
{
	MSG msg;
	int iRet;
	HWND hwnd;
	WNDCLASSEX wndClass;
	TCHAR szAppName[] = TEXT("My Window");
	
	fPtr = fopen("Log.txt","w");

	if(NULL == fPtr)
	{
		MessageBox(NULL,TEXT("File Not Found For Log:"),szAppName,MB_OKCANCEL);
		exit(0);
	}

	// step1 : first wndClass cha object bharun ghyaycha(कुटुंबावर संस्कार याचा आदर्श घेऊन बाकीचा window जन्माला येणार ).
	
	fputs("In WinMain Function:\n\n",fPtr);

	wndClass.cbSize				= sizeof(WNDCLASSEX);					// cbObject purn wndClass chi size
	wndClass.style				= CS_HREDRAW | CS_VREDRAW;				// Window horizontally and vertically resize honyasathi
	wndClass.cbClsExtra			= 0;
	wndClass.cbWndExtra			= 0;
	wndClass.hIcon				= LoadIcon(NULL,IDI_APPLICATION);		// Icon load karnyasathi API call 1. Kuthun anaycha(path) 2. kont
	wndClass.hIconSm			= LoadIcon(NULL,IDI_QUESTION);			// Small Icon load karnyasathi API call 1. Kuthun anaycha(path) 2. kont	
	wndClass.hCursor			= LoadCursor(NULL,IDC_ARROW);			// cursor load karnyasathi API call 1. Kuthun anaycha(path) 2. konta anaycha 
	wndClass.hInstance			= hInstance;							// aplyala alela hInstance
	wndClass.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);	// Brush (chuna lavnyasathi yacha use).
	wndClass.lpszClassName		= szAppName;							// wndClass cha nav
	wndClass.lpszMenuName		= NULL;									// ithe menu dile ki to saglya windows la asnar defaul
	wndClass.lpfnWndProc		= WndProc;								// maze event ya function madhe handle honar


	// step2 : tu 12 members tar bharle pan OS la sang mhnjech Register kar , to tula ATOM deil.
	
	fputs("Calling RegisterClassEx API:\n\n",fPtr);
	
	if(!RegisterClassEx(&wndClass))
	{
		MessageBox(NULL,TEXT("Register class Failure:"),szAppName,MB_OKCANCEL);
		fputs("Register class Failure:\n\n",fPtr);
		exit(0);
	}

	// step3 : ata window tayar kar tula je sanskar tuze extra vagare takachet tase,ha tula handle deto return madhe 

	fputs("Calling CreateWindow API:\n\n",fPtr);

	hwnd = CreateWindow(
					szAppName,					// wndClass cha nav
					TEXT("My First Window"),	// Caption for that window.
					WS_OVERLAPPEDWINDOW,		// 
					CW_USEDEFAULT,				// x axis co-ordinate
					CW_USEDEFAULT,				// y axis co-ordinate
					CW_USEDEFAULT,				// width
					CW_USEDEFAULT,				// height
					NULL,						// Parent window cha handle
					NULL,						// menu bar
					hInstance,					// varti milalela
					NULL);						// lpParm	


	// checking handle madhe kahi failure ala ahe ka

	if(NULL == hwnd)
	{
		MessageBox(NULL,TEXT("Create window failure:"),szAppName,MB_OKCANCEL);
		fputs("Create window failure:\n\n",fPtr);
		exit(0);
	}

	// step4 : window tayar zali memory madhe ata ti jagasamor aan Show kar.

	fputs("Calling ShowWindow API:\n\n",fPtr);

	ShowWindow(hwnd,iCmdShow);

	// step5 : window la update kar mhnjech repaint kar

	fputs("Calling UpdateWindow API:\n\n",fPtr);

	UpdateWindow(hwnd);

	// step6 : Message queue tayar kara
	fputs("Calling GetMessage API:\n\n",fPtr);

	while((iRet=GetMessage(&msg,NULL,0,0) != 0))
	{
		if(-1 == iRet)
		{
			MessageBox(NULL,TEXT("GetMessage Failure:"),szAppName,MB_OKCANCEL);
			fputs("GetMessage Failure:\n\n",fPtr);

			exit(0);
		}
		
		//fputs("Calling TranslateMessage API:\n\n",fPtr);
		TranslateMessage(&msg);
	
		//fputs("Calling DispatchMessage API:\n\n",fPtr);
		DispatchMessage(&msg);
		
	}
	
	// Total Number of events happening
	fputs(eventCount,fPtr);

	fputs("Leaving WinMain Function: \n\n",fPtr);

	fclose(fPtr);
	
	return (int)msg.wParam;

}

LRESULT CALLBACK WndProc(
					HWND hwnd,
					UINT uMsg,
					WPARAM wParam,
					LPARAM lParam
					)
{
	int message[50];
	static int iCountOfEvent=0;

	switch(uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	
	}

	iCountOfEvent++;
	sprintf(eventCount,"Total Number of events Are : %d \n\n",iCountOfEvent,uMsg);
	
	sprintf(message,"Message Number  is \t:\t%d \n\n",uMsg);
	fputs(message,fPtr);
	
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
