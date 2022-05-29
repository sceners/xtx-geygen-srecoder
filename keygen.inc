include windows.inc
include kernel32.inc
include user32.inc
include ole32.inc
include gdi32.inc
include macros.inc
include masm32.inc
include comctl32.inc
include oleaut32.inc
include MyMacros.asm
include winmm.inc
include advapi32.inc
include comdlg32.inc
includelib kernel32.lib
includelib user32.lib
includelib user32.lib
includelib ole32.lib
includelib gdi32.lib
includelib comctl32.lib
includelib oleaut32.lib
includelib masm32.lib
includelib winmm.lib
includelib advapi32.lib
include Libs\BmpFrom.inc
include Libs\image.inc
includelib Libs\image.lib
includelib comdlg32.lib
include Libs\ufmod.inc
includelib Libs\ufmod.lib

include	Libs\pnglib.inc
includelib	Libs\pnglib.lib

MainProc		   proto:DWORD,:DWORD,:DWORD,:DWORD
LoadPng			   proto:DWORD,:DWORD
SetClipboard	   proto:DWORD
FadeIn			   proto
FadeOut			   proto
PlayMidiFile	PROTO:DWORD,:DWORD
.const
MainDlg	=	100
EditSerial	=	101
IDC_NAME	=	1002
GenBtn		=	102
AboutBtn           =        103
ExitBtn                =        104

AboutDlg	=	700
IDC_TIMER	=	10
SIZEOFTITLEBAR	EQU 20
HEIGHTSYSBUTTON	EQU 14
WIDTHSYSBUTTON	EQU 14
TITLEFONT		EQU "Lucida Console"
BTNFONT			EQU "MS Sans Serif"
ABOUTFONT		EQU "Tahoma"
COLORDLG		EQU Black
COLORPEN		EQU Green
COLORTEXT	    EQU Yellow
VITESSEDEFIL	EQU 20
;================================ scroll  horizontal==========================
ScreenWidth    equ 320
	ScreenHeight   equ 20
;================================ scroll  horizontal==========================
.data

	rcDraw		RECT	<0>

; |**** SCROLLER DATA **************|

      text_message    db "                                      "
				db "  KEYGEN SRECODER "
				db "    "
				db "CODE AND GFX BY SP0KE "
				db " SFX BY SLICE "
				db "XTX TEAM 2010 "
				db "THX TO "
				db " COOLMEN      KIRJO     STEPHIO     TALOCHE"
				db"   "
				db"  "
				db "XTX TEAM 2010 "
				db" SP0KE      ",0
      message_index   dd 0
      posindex        dd 0

      include g_goldyfont.inc
; |*********************************|


;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++





Transparency		dd 0
TransColor			COLORREF	0FFFFFFFh
sizeFrame			dd	?,?
MoveDlg				BOOL		?
OldPos				POINT		<>
NewPos				POINT		<>
Rect				RECT		<>
handle				dd				?
ofn OPENFILENAME <>
szCaption			db	"Keygen_SRECODER",0
PressGen			db	"press Generate  !",0
Buffer          db  256 dup(?)
szMIDISeqr  	db "Sequencer",0
TxtFont		LOGFONT <-14,0,0,0,FW_NORMAL,TRUE,FALSE,FALSE,0,3,2,1,20,"Arial Black">
;========================== scroller ===================================================
 AppHWnd         dd 0
 phkResult       dd 0
 lpdwDisposition dd 0
AboutTitle              db "About Keygen",0
ResultTitle             db "  ",0
AboutFlag               dd  ?


szbtnClassName			db "button"     
szNULL					db 0

hCurrentCtl				HWND  NULL
ScrollOffset			DWORD	1
;Transparency		    dd 0
;TransColor			    COLORREF	00000FFh
AboutTxt                    	db "Keygen SRECODER:",10,13,10,13
				db "Code AND GFX by sp0ke ",10,13,10,13
				db "SFX BY SLICE",10,13,10,13
				db "xtx TeaM 2010 ",10,13,10,13
				db "----[Greetings]----",10,13,10,13
				db " Thanks to all Teams,", 10, 13,10,13
				db " Coolmen", 10, 13,10,13
				db"Kirjo",10,13,10,13
				db" ..................",10,13,10,13				
				db " ---------------------",10,13
				db "xtx TeaM 2010 ",10,13,10,13
				db"  ",10,13,10,13
				db" @++",10,13,10,13,0
				
				
szPatchSuccess        db "é",10,13,10,13
;				db "sur le fait d'entrer 6 caractères",10,13,10,13
;				db "en minuscule et certains Noms,",10,13,10,13
;				db " Ce bug donnait un serial,", 10,13,10,13
;				db"éroné ou faisait planter le",10,13,10,13
;				db "Keygen / BruteForce",10,13,10,13
;				db "La cause est le resultat d'un xor ",10,13,10,13
;				db "sur les caractères du Nom en boucle ",10,13,10,13
;				db "Donc pour remédier à ce bug ",10,13,10,13
;				db" Je vous invites à mettre",10,13,10,13			
;				db" une Majuscule à votre Nom.",10,13,10,13	
				db"   ",10,13,10,13,0
			
.data?

;============================================ scrolling horizontal===========================
canvasDC	  dd	?
canvasBmp	  dd	?
hDC           dd  ?
canvas_buffer dd	?
clip1         dd  ?
clip2         dd  ?

ps		  PAINTSTRUCT	<>
canvas	  BITMAPINFO	<>

;========================================================================================



;hInstance	dd	?
hIcon		dd	?
hGen		dd	?
hWND		dd	?
hIMG		dd	?
hBrush		dd	?
hFont		dd	?

;============================================ scrolling ===========================

hBgColor     	HBRUSH				?
;handle          HWND                ?
hpen         	HPEN				?
hFontTitle   	HFONT				?
hFontBtn     	HFONT				?
hFontBtnBold	HFONT				?
dlgRect      	RECT				<?>
txtBoxRect   	RECT				<?>
hInstance    	HINSTANCE			?
hBtnExit       	HWND				?
hBtnMin      	HWND				?
hBtnAbout    	HWND				?
hBtnPatch		HWND				?
hBtnUnPatch		HWND				?
hFontAbout		HFONT				?
AboutRect    	RECT				<?>
rScroll			RECT				<?>
rClientAbout	RECT				<?>
PosRect         RECT                <?>
hbmp			HANDLE				?
chdc			HDC					?

TimerID			DWORD				?
hFile			dd					?
hFileSize		dd					?
hMapFile		dd					?
hViewFile		dd					?
szAboutMsg      db                500 dup(?)
WinBuff			db					200 dup(?)
ResDat			dd					?
ResInf			dd					?
ResSize			dd					?
MidDeviceID 	dd					?











