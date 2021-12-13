ORIGIN		= Symantec C++
ORIGIN_VER	= Version 7.20
VERSION		= RELEASE

!IFDEF SUB_DEBUG
DEBUG		= $(SUB_DEBUG)
NDEBUG		= !$(SUB_DEBUG)
!ELSE
DEBUG		= 0
NDEBUG		= 1
!ENDIF

PROJ		= frshell
APPTYPE		= WIN32 EXE
PROJTYPE	= EXE

CC		= SC
CPP		= SPP
MAKE		= SMAKE
RC		= RCC
HC		= HC31
ASM		= SC
DISASM		= OBJ2ASM
LNK		= LINK
DLLS		= 

HEADERS		= C:\SC\INCLUDE\win32\winver.h C:\SC\INCLUDE\win32\ver.h C:\SC\INCLUDE\win32\scdefs.h  \
		C:\SC\INCLUDE\ver.h C:\SC\MFC\INCLUDE\mfc30\winres.h C:\SC\MFC\INCLUDE\mfc30\afxres.h C:\SC\MFC\INCLUDE\afxres.h  \
		C:\SC\INCLUDE\win32\poppack.h C:\SC\INCLUDE\win32\pshpack1.h stdafx.h C:\SC\MFC\INCLUDE\afxwin.h  \
		C:\SC\MFC\INCLUDE\mfc30\afxwin.h C:\SC\MFC\INCLUDE\afx.h C:\SC\MFC\INCLUDE\mfc30\afx.h C:\SC\MFC\INCLUDE\afxver_.h  \
		C:\SC\MFC\INCLUDE\mfc30\afxver_.h C:\SC\MFC\INCLUDE\afxv_w32.h C:\SC\MFC\INCLUDE\mfc30\afxv_w32.h C:\SC\INCLUDE\windows.h  \
		C:\SC\INCLUDE\win32\windows.h C:\SC\INCLUDE\excpt.h C:\SC\INCLUDE\stdarg.h C:\SC\INCLUDE\windef.h  \
		C:\SC\INCLUDE\win32\windef.h C:\SC\INCLUDE\winnt.h C:\SC\INCLUDE\win32\winnt.h C:\SC\INCLUDE\ctype.h  \
		C:\SC\INCLUDE\pshpack4.h C:\SC\INCLUDE\win32\pshpack4.h C:\SC\INCLUDE\poppack.h C:\SC\INCLUDE\string.h  \
		C:\SC\INCLUDE\winbase.h C:\SC\INCLUDE\win32\winbase.h C:\SC\INCLUDE\winerror.h C:\SC\INCLUDE\win32\winerror.h  \
		C:\SC\INCLUDE\wingdi.h C:\SC\INCLUDE\win32\wingdi.h C:\SC\INCLUDE\pshpack1.h C:\SC\INCLUDE\pshpack2.h  \
		C:\SC\INCLUDE\win32\pshpack2.h C:\SC\INCLUDE\winuser.h C:\SC\INCLUDE\win32\winuser.h C:\SC\INCLUDE\winnls.h  \
		C:\SC\INCLUDE\win32\winnls.h C:\SC\INCLUDE\wincon.h C:\SC\INCLUDE\win32\wincon.h C:\SC\INCLUDE\winver.h  \
		C:\SC\INCLUDE\winreg.h C:\SC\INCLUDE\win32\winreg.h C:\SC\INCLUDE\winnetwk.h C:\SC\INCLUDE\win32\winnetwk.h  \
		C:\SC\INCLUDE\winsvc.h C:\SC\INCLUDE\win32\winsvc.h C:\SC\INCLUDE\mcx.h C:\SC\INCLUDE\win32\mcx.h  \
		C:\SC\INCLUDE\imm.h C:\SC\INCLUDE\win32\imm.h C:\SC\INCLUDE\commctrl.h C:\SC\INCLUDE\win32\commctrl.h  \
		C:\SC\INCLUDE\prsht.h C:\SC\INCLUDE\win32\prsht.h C:\SC\INCLUDE\tchar.h C:\SC\INCLUDE\mbstring.h  \
		C:\SC\INCLUDE\mbctype.h C:\SC\INCLUDE\stdio.h C:\SC\INCLUDE\stdlib.h C:\SC\INCLUDE\time.h  \
		C:\SC\MFC\INCLUDE\afxcoll.h C:\SC\MFC\INCLUDE\mfc30\afxcoll.h C:\SC\MFC\INCLUDE\afxstat_.h C:\SC\MFC\INCLUDE\mfc30\afxstat_.h  \
		C:\SC\INCLUDE\shellapi.h C:\SC\INCLUDE\win32\shellapi.h C:\SC\MFC\INCLUDE\afxmsg_.h C:\SC\MFC\INCLUDE\mfc30\afxmsg_.h  \
		C:\SC\MFC\INCLUDE\afxdd_.h C:\SC\MFC\INCLUDE\mfc30\afxdd_.h C:\SC\INCLUDE\limits.h C:\SC\MFC\INCLUDE\afxext.h  \
		C:\SC\MFC\INCLUDE\mfc30\afxext.h C:\SC\MFC\INCLUDE\afxdlgs.h C:\SC\MFC\INCLUDE\mfc30\afxdlgs.h C:\SC\INCLUDE\commdlg.h  \
		C:\SC\INCLUDE\win32\commdlg.h FRSHELL.h resource.h cfrmodin.h  \
		cpathdia.h C:\SC\INCLUDE\fcntl.h C:\SC\INCLUDE\conio.h C:\SC\INCLUDE\io.h  \
		C:\SC\INCLUDE\sys\stat.h C:\SC\INCLUDE\math.h C:\SC\INCLUDE\alloc.h C:\SC\INCLUDE\direct.h  \
		fr3ddoc.h fr3dvw.h mainfrm.h 

DEFFILE		= frshell.DEF

!IF $(DEBUG)
OUTPUTDIR	= .
CREATEOUTPUTDIR	=
TARGETDIR	= .
CREATETARGETDIR	=

LIBS		= KERNEL32.LIB GDI32.LIB USER32.LIB NAFXCWD.LIB COMDLG32.LIB SHELL32.LIB ADVAPI32.LIB MFCANS32.LIB MFCUIA32.LIB WINSPOOL.LIB ADVAPI32.LIB 

CFLAGS		=  -cpp -Ae -mn -C -o+time -WA -ff -S -3 -a8 -c -H -HO- -g -gd 
CFLAGS_1	=  -cpp -Ae -mn -C -o+time -WA -ff -S -4 -a8 -c -H -HO- -l -g -gd
DEFINES_1	= -D_DEBUG=1 -D_X86_=1 -D_MT=1 -D_MBCS=1
LFLAGS		=  /CO /NOI /DE /XN /NT /ENTRY:WinMainCRTStartup /VERS:1.0 /BAS:4194304 /A:512 /RC   :FRSHELL.RES
DEFINES		= -D_DEBUG=1 -D_X86_=1 -D_MT=1 -D_MBCS=1
!ELSE
OUTPUTDIR	= .
CREATEOUTPUTDIR	=
TARGETDIR	= .
CREATETARGETDIR	=

LIBS		= KERNEL32.LIB GDI32.LIB USER32.LIB NAFXCW.LIB COMDLG32.LIB SHELL32.LIB ADVAPI32.LIB MFCANS32.LIB MFCUIA32.LIB WINSPOOL.LIB ADVAPI32.LIB 

CFLAGS		=  -cpp -Ae -mn -o+time -WA -ff -GT65535 -3 -a8 -c -H -HO- -g -gd -gf -gh -gg 
CFLAGS_1	=  -cpp -Ae -mn -o+time -WA -3 -a8 -c -H -HO-
DEFINES_1	= -D_X86_=1 -D_MT=1 -D_MBCS=1
LFLAGS		=  /NOI /DE /PACKF /XN /NT /ENTRY:WinMainCRTStartup /VERS:1.0 /BAS:4194304 /A:512 /RC   :FRSHELL.RES
DEFINES		= -D_X86_=1 -D_MT=1 -D_MBCS=1
!ENDIF

HFLAGS		= $(CFLAGS) 
MFLAGS		= MASTERPROJ=$(PROJ) 
LIBFLAGS	=  /C 
RESFLAGS	=  -32 
DEBUGGERFLAGS	=  
AFLAGS		= $(CFLAGS) 
HELPFLAGS	= 

MODEL		= N

PAR		= PROJS BATS OBJS

RCDEFINES	= -D_MFC_VER=0x300

INCLUDES	= 

INCLUDEDOBJS	= 

OBJS		= mainfrm.OBJ fr3ddoc.OBJ FRSHELL.OBJ  \
		fr3dvw.OBJ cfrmodin.OBJ cpathdia.OBJ 

RCFILES		=  FRSHELL.RES 

RESFILES	= 

SYMS		=  .\stdafx.SYM 

HELPFILES	= 

BATS		= 

.SUFFIXES: .C .CP .CPP .CXX .CC .H .HPP .HXX .COM .EXE .DLL .LIB .RTF .DLG .ASM .RES .RC .OBJ 

.C.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.c

.CPP.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cpp

.CXX.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cxx

.CC.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cc

.CP.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cp

.H.SYM:
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF -o.\$(*B).sym $*.h

.HPP.SYM:
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF -o.\$(*B).sym $*.hpp

.HXX.SYM:
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF -o.\$(*B).sym $*.hxx

.C.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES)   $*.c   -o$*.lst

.CPP.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES) $*.cpp -o$*.lst

.CXX.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES) $*.cxx -o$*.lst

.CP.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES)  $*.cp  -o$*.lst

.CC.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES)  $*.cc  -o$*.lst

.ASM.EXP:
	$(CPP) $(CFLAGS) $(DEFINES) $(INCLUDES) $*.asm -o$*.lst

.OBJ.COD:
	$(DISASM) $*.OBJ -c

.OBJ.EXE:
	$(LNK) $(LFLAGS) @$(PROJ).LNK

.RTF.HLP:
	$(HC) $(HELPFLAGS) $*.HPJ

.ASM.OBJ:
	$(ASM) $(AFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.asm

.RC.RES: 
	$(RC) $(RCDEFINES) $(RESFLAGS) $(INCLUDES) $*.rc -o$*.res

.DLG.RES:
	echo ^#include "windows.h" >$$$*.rc
	echo ^IF EXIST "$*.h" >>$$$*.rc
	echo ^#include "$*.h" >>$$$*.rc
	echo ^#include "$*.dlg" >>$$$*.rc
	$(RC) $(RCDEFINES) $(RESFLAGS) $(INCLUDES) $$$*.rc
	-del $*.res
	-ren $$$*.res $*.res



all:	createdir $(PRECOMPILE) $(SYMS) $(OBJS) $(INCLUDEDOBJS) $(POSTCOMPILE) $(TARGETDIR)\$(PROJ).$(PROJTYPE) $(POSTLINK) _done

createdir:
	$(CREATEOUTPUTDIR)
	$(CREATETARGETDIR)

$(TARGETDIR)\$(PROJ).$(PROJTYPE): $(SYMS) $(OBJS) $(INCLUDEDOBJS) $(RCFILES) $(RESFILES) $(HELPFILES) $(DEFFILE)
			-del $(TARGETDIR)\$(PROJ).$(PROJTYPE)
			$(LNK) $(LFLAGS) @$(PROJ).LNK;
			-ren $(TARGETDIR)\$$SCW$$.$(PROJTYPE) $(PROJ).$(PROJTYPE)
			-echo $(TARGETDIR)\$(PROJ).$(PROJTYPE) built

_done:
		-echo $(PROJ).$(PROJTYPE) done

buildall:	clean	all


clean:
		-del $(TARGETDIR)\$$SCW$$.$(PROJTYPE)
		-del $(TARGETDIR)\$(PROJ).CLE
		-del $(OUTPUTDIR)\SCPH.SYM
		-del frshell.dpd
		-del $(OBJS)
		-del .\stdafx.SYM
		-del FRSHELL.RES

cleanres:
		-del FRSHELL.RES

res:		cleanres $(RCFILES) all


link:
		$(LNK) $(LFLAGS) @$(PROJ).LNK;
		-del $(TARGETDIR)\$(PROJ).$(PROJTYPE)
		-ren $(TARGETDIR)\$$SCW$$.$(PROJTYPE) $(PROJ).$(PROJTYPE)




!IF EXIST (frshell.dpd)
!INCLUDE frshell.dpd
!ENDIF

FRSHELL.OBJ:	FRSHELL.cpp
		$(CC) $(CFLAGS_1) $(DEFINES_1) $(INCLUDES) -oFRSHELL.obj FRSHELL.cpp


.\stdafx.SYM: stdafx.h
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF.\stdafx.SYM -o.\stdafx.OBJ stdafx.h



