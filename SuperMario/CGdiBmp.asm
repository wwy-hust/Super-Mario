﻿; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.30319.01 

	TITLE	C:\Users\Administrator\Documents\Visual Studio 2010\Projects\SuperMario__\SuperMario_\SuperMario\CGdiBmp.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB OLDNAMES

PUBLIC	??_R4CGdiBmp@@6B@				; CGdiBmp::`RTTI Complete Object Locator'
PUBLIC	??_GCGdiBmp@@UAEPAXI@Z				; CGdiBmp::`scalar deleting destructor'
PUBLIC	??_C@_02DKCKIIND@?$CFs?$AA@			; `string'
PUBLIC	??_7CGdiBmp@@6B@				; CGdiBmp::`vftable'
EXTRN	??_ECGdiBmp@@UAEPAXI@Z:PROC			; CGdiBmp::`vector deleting destructor'
EXTRN	__imp__CreateCompatibleBitmap@12:PROC
EXTRN	__imp__FillRect@12:PROC
EXTRN	__imp__GetModuleHandleA@4:PROC
EXTRN	__imp__GetObjectA@12:PROC
EXTRN	__imp__LoadImageA@24:PROC
EXTRN	__imp__CreateCompatibleDC@4:PROC
EXTRN	__imp__DeleteDC@4:PROC
EXTRN	__imp__StretchBlt@44:PROC
EXTRN	__imp__TransparentBlt@44:PROC
EXTRN	__imp__CreateFontA@56:PROC
EXTRN	__imp__DeleteObject@4:PROC
EXTRN	__imp__SelectObject@8:PROC
EXTRN	__imp__SetBkMode@8:PROC
EXTRN	__imp__SetTextColor@8:PROC
EXTRN	__imp__wsprintfA:PROC
EXTRN	__imp__DrawTextA@20:PROC
;	COMDAT ??_7CGdiBmp@@6B@
CONST	SEGMENT
??_7CGdiBmp@@6B@ DD FLAT:??_R4CGdiBmp@@6B@		; CGdiBmp::`vftable'
	DD	FLAT:??_ECGdiBmp@@UAEPAXI@Z
CONST	ENDS
;	COMDAT ??_R4CGdiBmp@@6B@
rdata$r	SEGMENT
??_R4CGdiBmp@@6B@ DD 00H				; CGdiBmp::`RTTI Complete Object Locator'
	DD	00H
	DD	00H
	DD	FLAT:??_R0?AVCGdiBmp@@@8
	DD	FLAT:??_R3CGdiBmp@@8
rdata$r	ENDS
;	COMDAT ??_C@_02DKCKIIND@?$CFs?$AA@
CONST	SEGMENT
??_C@_02DKCKIIND@?$CFs?$AA@ DB '%s', 00H		; `string'
PUBLIC	_FontRect$GSCopy$
PUBLIC	__$ArrayPad$
PUBLIC	?DrawWords@CGdiBmp@@SAXPAUHDC__@@PADKHPBDUtagRECT@@H@Z ; CGdiBmp::DrawWords
; Function compile flags: /Ogtp
;	COMDAT ?DrawWords@CGdiBmp@@SAXPAUHDC__@@PADKHPBDUtagRECT@@H@Z
_TEXT	SEGMENT
_FontRect$GSCopy$ = -532				; size = 16
_szText$ = -516						; size = 512
__$ArrayPad$ = -4					; size = 4
_FontSize$ = 8						; size = 4
_FontRect$ = 12						; size = 16
?DrawWords@CGdiBmp@@SAXPAUHDC__@@PADKHPBDUtagRECT@@H@Z PROC ; CGdiBmp::DrawWords, COMDAT
; _hDC$ = esi
; _text$ = ebx
; _FontName$ = ecx
; File c:\users\administrator\documents\visual studio 2010\projects\supermario__\supermario_\supermario\cgdibmp.cpp
; Line 296
	push	ebp
	mov	ebp, esp
	sub	esp, 532				; 00000214H
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	mov	edx, DWORD PTR _FontRect$[ebp]
	push	edi
; Line 301
	push	ecx
	push	0
	mov	eax, DWORD PTR _FontSize$[ebp]
	push	2
	push	0
	push	6
	push	1
	push	0
	push	0
	push	0
	push	700					; 000002bcH
	mov	DWORD PTR _FontRect$GSCopy$[ebp], edx
	mov	edx, DWORD PTR _FontRect$[ebp+4]
	push	0
	mov	DWORD PTR _FontRect$GSCopy$[ebp+4], edx
	mov	edx, DWORD PTR _FontRect$[ebp+8]
	push	0
	mov	DWORD PTR _FontRect$GSCopy$[ebp+8], edx
	mov	edx, DWORD PTR _FontRect$[ebp+12]
	push	0
	push	eax
	mov	DWORD PTR _FontRect$GSCopy$[ebp+12], edx
	call	DWORD PTR __imp__CreateFontA@56
	mov	edi, eax
; Line 302
	push	edi
	push	esi
	call	DWORD PTR __imp__SelectObject@8
; Line 304
	push	ebx
	lea	eax, DWORD PTR _szText$[ebp]
	push	OFFSET ??_C@_02DKCKIIND@?$CFs?$AA@
	push	eax
	call	DWORD PTR __imp__wsprintfA
	add	esp, 12					; 0000000cH
; Line 305
	push	1
	push	esi
	call	DWORD PTR __imp__SetBkMode@8
; Line 306
	push	16777215				; 00ffffffH
	push	esi
	call	DWORD PTR __imp__SetTextColor@8
; Line 308
	push	37					; 00000025H
	lea	ecx, DWORD PTR _FontRect$GSCopy$[ebp]
	push	ecx
	push	-1
	lea	edx, DWORD PTR _szText$[ebp]
	push	edx
	push	esi
	call	DWORD PTR __imp__DrawTextA@20
; Line 309
	push	edi
	call	DWORD PTR __imp__DeleteObject@4
; Line 311
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	pop	edi
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	0
?DrawWords@CGdiBmp@@SAXPAUHDC__@@PADKHPBDUtagRECT@@H@Z ENDP ; CGdiBmp::DrawWords
_TEXT	ENDS
PUBLIC	?DrawMirror@CGdiBmp@@QAEXPAUHDC__@@HHH@Z	; CGdiBmp::DrawMirror
; Function compile flags: /Ogtp
;	COMDAT ?DrawMirror@CGdiBmp@@QAEXPAUHDC__@@HHH@Z
_TEXT	SEGMENT
_hDC$ = 8						; size = 4
?DrawMirror@CGdiBmp@@QAEXPAUHDC__@@HHH@Z PROC		; CGdiBmp::DrawMirror, COMDAT
; Line 135
	push	ebp
	mov	ebp, esp
; Line 137
	mov	eax, DWORD PTR _hDC$[ebp]
	push	ebx
	push	esi
	push	edi
	mov	edi, DWORD PTR ?about@@3PAVCGdiBmp@@A	; about
	push	eax
	call	DWORD PTR __imp__CreateCompatibleDC@4
; Line 140
	mov	ecx, DWORD PTR [edi+4]
	mov	esi, eax
	push	ecx
	push	esi
	call	DWORD PTR __imp__SelectObject@8
; Line 147
	mov	edx, DWORD PTR _hDC$[ebp]
	push	13369376				; 00cc0020H
	mov	ebx, eax
	mov	eax, DWORD PTR [edi+12]
	mov	edi, DWORD PTR [edi+8]
	push	eax
	push	edi
	push	0
	push	0
	push	esi
	push	eax
	push	edi
	push	0
	push	0
	push	edx
	call	DWORD PTR __imp__StretchBlt@44
; Line 167
	push	ebx
	push	esi
	call	DWORD PTR __imp__SelectObject@8
; Line 169
	push	esi
	call	DWORD PTR __imp__DeleteDC@4
; Line 171
	push	ebx
	call	DWORD PTR __imp__DeleteObject@4
	pop	edi
	pop	esi
	pop	ebx
; Line 173
	pop	ebp
	ret	4
?DrawMirror@CGdiBmp@@QAEXPAUHDC__@@HHH@Z ENDP		; CGdiBmp::DrawMirror
_TEXT	ENDS
PUBLIC	__$ArrayPad$
PUBLIC	?LoadBmp@CGdiBmp@@QAEHPAD@Z			; CGdiBmp::LoadBmp
; Function compile flags: /Ogtp
;	COMDAT ?LoadBmp@CGdiBmp@@QAEHPAD@Z
_TEXT	SEGMENT
_dib$ = -88						; size = 84
__$ArrayPad$ = -4					; size = 4
_path$ = 8						; size = 4
?LoadBmp@CGdiBmp@@QAEHPAD@Z PROC			; CGdiBmp::LoadBmp, COMDAT
; _this$ = esi
; Line 112
	push	ebp
	mov	ebp, esp
	sub	esp, 88					; 00000058H
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	mov	eax, DWORD PTR _path$[ebp]
; Line 116
	push	8208					; 00002010H
	push	0
	push	0
	push	0
	push	eax
	push	0
	call	DWORD PTR __imp__GetModuleHandleA@4
	push	eax
	call	DWORD PTR __imp__LoadImageA@24
	mov	DWORD PTR [esi+4], eax
; Line 117
	test	eax, eax
	je	SHORT $LN5@LoadBmp
; Line 119
	lea	ecx, DWORD PTR _dib$[ebp]
	push	ecx
	push	84					; 00000054H
	push	eax
	call	DWORD PTR __imp__GetObjectA@12
	cmp	eax, 84					; 00000054H
	je	SHORT $LN1@LoadBmp
; Line 120
	mov	edx, DWORD PTR [esi+4]
	push	edx
	call	DWORD PTR __imp__DeleteObject@4
; Line 121
	mov	DWORD PTR [esi+4], 0
$LN5@LoadBmp:
; Line 122
	xor	eax, eax
; Line 127
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	4
$LN1@LoadBmp:
; Line 125
	mov	ecx, DWORD PTR _dib$[ebp+32]
	mov	eax, DWORD PTR _dib$[ebp+28]
	mov	DWORD PTR [esi+12], ecx
; Line 127
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	mov	DWORD PTR [esi+8], eax
	xor	ecx, ebp
	mov	eax, 1
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	4
?LoadBmp@CGdiBmp@@QAEHPAD@Z ENDP			; CGdiBmp::LoadBmp
_TEXT	ENDS
PUBLIC	_ibHeight$GSCopy$
PUBLIC	_ibWidth$GSCopy$
PUBLIC	__$ArrayPad$
PUBLIC	?CreateBlankBMP@CGdiBmp@@QAEPAUHBITMAP__@@PAUHDC__@@HHK@Z ; CGdiBmp::CreateBlankBMP
; Function compile flags: /Ogtp
;	COMDAT ?CreateBlankBMP@CGdiBmp@@QAEPAUHBITMAP__@@PAUHDC__@@HHK@Z
_TEXT	SEGMENT
_ibWidth$GSCopy$ = -32					; size = 4
_hOldBitmap$ = -28					; size = 4
_ibHeight$GSCopy$ = -24					; size = 4
_rcBitmap$ = -20					; size = 16
__$ArrayPad$ = -4					; size = 4
_ibWidth$ = 8						; size = 4
_crColor$ = 12						; size = 4
?CreateBlankBMP@CGdiBmp@@QAEPAUHBITMAP__@@PAUHDC__@@HHK@Z PROC ; CGdiBmp::CreateBlankBMP, COMDAT
; _hDC$ = edx
; _ibHeight$ = ecx
; Line 76
	push	ebp
	mov	ebp, esp
	sub	esp, 36					; 00000024H
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	mov	eax, DWORD PTR _ibWidth$[ebp]
	push	ebx
	mov	ebx, DWORD PTR _crColor$[ebp]
	push	esi
	push	edi
; Line 78
	push	ecx
	mov	esi, edx
	push	eax
	push	esi
; Line 82
	mov	DWORD PTR _ibWidth$GSCopy$[ebp], eax
	mov	DWORD PTR _ibHeight$GSCopy$[ebp], ecx
	call	DWORD PTR __imp__CreateCompatibleBitmap@12
	mov	edi, eax
	test	edi, edi
	jne	SHORT $LN1@CreateBlan
; Line 101
	pop	edi
	pop	esi
	pop	ebx
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	8
$LN1@CreateBlan:
; Line 82
	push	esi
	call	DWORD PTR __imp__CreateCompatibleDC@4
; Line 85
	push	ebx
	mov	esi, eax
	call	DWORD PTR __imp__CreateSolidBrush@4
; Line 88
	push	edi
	push	esi
	mov	ebx, eax
	call	DWORD PTR __imp__SelectObject@8
; Line 91
	mov	ecx, DWORD PTR _ibHeight$GSCopy$[ebp]
	mov	DWORD PTR _hOldBitmap$[ebp], eax
	xor	eax, eax
; Line 92
	push	ebx
	lea	edx, DWORD PTR _rcBitmap$[ebp]
	mov	DWORD PTR _rcBitmap$[ebp], eax
	mov	DWORD PTR _rcBitmap$[ebp+4], eax
	mov	eax, DWORD PTR _ibWidth$GSCopy$[ebp]
	push	edx
	push	esi
	mov	DWORD PTR _rcBitmap$[ebp+8], eax
	mov	DWORD PTR _rcBitmap$[ebp+12], ecx
	call	DWORD PTR __imp__FillRect@12
; Line 95
	mov	eax, DWORD PTR _hOldBitmap$[ebp]
	push	eax
	push	esi
	call	DWORD PTR __imp__SelectObject@8
; Line 97
	push	esi
	call	DWORD PTR __imp__DeleteDC@4
; Line 99
	push	ebx
	call	DWORD PTR __imp__DeleteObject@4
; Line 101
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	mov	eax, edi
	pop	edi
	pop	esi
	xor	ecx, ebp
	pop	ebx
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	8
?CreateBlankBMP@CGdiBmp@@QAEPAUHBITMAP__@@PAUHDC__@@HHK@Z ENDP ; CGdiBmp::CreateBlankBMP
_TEXT	ENDS
PUBLIC	?Destroy@CGdiBmp@@QAEXXZ			; CGdiBmp::Destroy
; Function compile flags: /Ogtp
;	COMDAT ?Destroy@CGdiBmp@@QAEXXZ
_TEXT	SEGMENT
?Destroy@CGdiBmp@@QAEXXZ PROC				; CGdiBmp::Destroy, COMDAT
; _this$ = esi
; Line 63
	mov	eax, DWORD PTR [esi+4]
	test	eax, eax
	je	SHORT $LN1@Destroy
; Line 65
	push	eax
	call	DWORD PTR __imp__DeleteObject@4
; Line 66
	mov	DWORD PTR [esi+4], 0
$LN1@Destroy:
; Line 68
	ret	0
?Destroy@CGdiBmp@@QAEXXZ ENDP				; CGdiBmp::Destroy
_TEXT	ENDS
PUBLIC	??1CGdiBmp@@UAE@XZ				; CGdiBmp::~CGdiBmp
; Function compile flags: /Ogtp
;	COMDAT ??1CGdiBmp@@UAE@XZ
_TEXT	SEGMENT
??1CGdiBmp@@UAE@XZ PROC					; CGdiBmp::~CGdiBmp, COMDAT
; _this$ = ecx
; Line 52
	push	esi
	mov	esi, ecx
; Line 53
	mov	eax, DWORD PTR [esi+4]
	mov	DWORD PTR [esi], OFFSET ??_7CGdiBmp@@6B@
	test	eax, eax
	je	SHORT $LN3@CGdiBmp
	push	eax
	call	DWORD PTR __imp__DeleteObject@4
	mov	DWORD PTR [esi+4], 0
$LN3@CGdiBmp:
	pop	esi
; Line 54
	ret	0
??1CGdiBmp@@UAE@XZ ENDP					; CGdiBmp::~CGdiBmp
_TEXT	ENDS
PUBLIC	__$ArrayPad$
PUBLIC	??0CGdiBmp@@QAE@PAD@Z				; CGdiBmp::CGdiBmp
; Function compile flags: /Ogtp
;	COMDAT ??0CGdiBmp@@QAE@PAD@Z
_TEXT	SEGMENT
_dib$135349 = -88					; size = 84
__$ArrayPad$ = -4					; size = 4
_fileName$ = 8						; size = 4
??0CGdiBmp@@QAE@PAD@Z PROC				; CGdiBmp::CGdiBmp, COMDAT
; _this$ = esi
; Line 30
	push	ebp
	mov	ebp, esp
	sub	esp, 88					; 00000058H
	mov	eax, DWORD PTR ___security_cookie
	xor	eax, ebp
	mov	DWORD PTR __$ArrayPad$[ebp], eax
	mov	eax, DWORD PTR _fileName$[ebp]
; Line 32
	push	8208					; 00002010H
	push	0
	push	0
	push	0
	push	eax
	push	0
	mov	DWORD PTR [esi], OFFSET ??_7CGdiBmp@@6B@
	mov	DWORD PTR [esi+4], 0
	call	DWORD PTR __imp__GetModuleHandleA@4
	push	eax
	call	DWORD PTR __imp__LoadImageA@24
	mov	DWORD PTR [esi+4], eax
	test	eax, eax
	je	SHORT $LN7@CGdiBmp@2
	lea	ecx, DWORD PTR _dib$135349[ebp]
	push	ecx
	push	84					; 00000054H
	push	eax
	call	DWORD PTR __imp__GetObjectA@12
	cmp	eax, 84					; 00000054H
	je	SHORT $LN3@CGdiBmp@2
	mov	edx, DWORD PTR [esi+4]
	push	edx
	call	DWORD PTR __imp__DeleteObject@4
	mov	DWORD PTR [esi+4], 0
; Line 33
	mov	eax, esi
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	4
; Line 32
$LN3@CGdiBmp@2:
	mov	eax, DWORD PTR _dib$135349[ebp+28]
	mov	ecx, DWORD PTR _dib$135349[ebp+32]
	mov	DWORD PTR [esi+8], eax
	mov	DWORD PTR [esi+12], ecx
$LN7@CGdiBmp@2:
; Line 33
	mov	ecx, DWORD PTR __$ArrayPad$[ebp]
	xor	ecx, ebp
	mov	eax, esi
	call	@__security_check_cookie@4
	mov	esp, ebp
	pop	ebp
	ret	4
??0CGdiBmp@@QAE@PAD@Z ENDP				; CGdiBmp::CGdiBmp
; Function compile flags: /Ogtp
_TEXT	ENDS
;	COMDAT ??_GCGdiBmp@@UAEPAXI@Z
_TEXT	SEGMENT
___flags$ = 8						; size = 4
??_GCGdiBmp@@UAEPAXI@Z PROC				; CGdiBmp::`scalar deleting destructor', COMDAT
; _this$ = ecx
	push	ebp
	mov	ebp, esp
	push	esi
	mov	esi, ecx
	mov	eax, DWORD PTR [esi+4]
	mov	DWORD PTR [esi], OFFSET ??_7CGdiBmp@@6B@
	test	eax, eax
	je	SHORT $LN6@scalar@3
	push	eax
	call	DWORD PTR __imp__DeleteObject@4
	mov	DWORD PTR [esi+4], 0
$LN6@scalar@3:
	test	BYTE PTR ___flags$[ebp], 1
	je	SHORT $LN9@scalar@3
	push	esi
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$LN9@scalar@3:
	mov	eax, esi
	pop	esi
	pop	ebp
	ret	4
??_GCGdiBmp@@UAEPAXI@Z ENDP				; CGdiBmp::`scalar deleting destructor'
_TEXT	ENDS
PUBLIC	??0CGdiBmp@@QAE@XZ				; CGdiBmp::CGdiBmp
; Function compile flags: /Ogtp
;	COMDAT ??0CGdiBmp@@QAE@XZ
_TEXT	SEGMENT
??0CGdiBmp@@QAE@XZ PROC					; CGdiBmp::CGdiBmp, COMDAT
; _this$ = eax
; Line 19
	mov	DWORD PTR [eax], OFFSET ??_7CGdiBmp@@6B@
	mov	DWORD PTR [eax+4], 0
; Line 20
	ret	0
??0CGdiBmp@@QAE@XZ ENDP					; CGdiBmp::CGdiBmp
PUBLIC	?DrawSingleFrame@CGdiBmp@@QAEXPAUHDC__@@HHHHHHNHK@Z ; CGdiBmp::DrawSingleFrame
; Function compile flags: /Ogtp
;	COMDAT ?DrawSingleFrame@CGdiBmp@@QAEXPAUHDC__@@HHHHHHNHK@Z
_TEXT	SEGMENT
_OldFrameBmp$ = -16					; size = 4
_BlankFrameBmp$ = -12					; size = 4
_hOldBitmap$ = -8					; size = 4
_memDC$ = -4						; size = 4
_FrameDC$ = 8						; size = 4
_this$ = 8						; size = 4
_x$ = 12						; size = 4
_y$ = 16						; size = 4
_Old$66759 = 20						; size = 4
_Blank$66757 = 20					; size = 4
_xFrame$ = 20						; size = 4
_dc$66758 = 24						; size = 4
_yFrame$ = 24						; size = 4
_wFrame$ = 28						; size = 4
_hFrame$ = 32						; size = 4
_mirror$ = 36						; size = 4
_crTransColor$ = 40					; size = 4
_ratio$ = 44						; size = 8
?DrawSingleFrame@CGdiBmp@@QAEXPAUHDC__@@HHHHHHNHK@Z PROC ; CGdiBmp::DrawSingleFrame, COMDAT
; _hDC$ = eax
; Line 185
	push	ebp
	mov	ebp, esp
	sub	esp, 16					; 00000010H
	push	ebx
	push	esi
	mov	esi, DWORD PTR _hFrame$[ebp]
	push	edi
	mov	edi, DWORD PTR _wFrame$[ebp]
	mov	ebx, eax
; Line 188
	push	ebx
	call	DWORD PTR __imp__CreateCompatibleDC@4
; Line 190
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR [ecx+4]
	push	edx
	push	eax
	mov	DWORD PTR _memDC$[ebp], eax
	call	DWORD PTR __imp__SelectObject@8
	mov	DWORD PTR _hOldBitmap$[ebp], eax
; Line 193
	mov	eax, DWORD PTR _crTransColor$[ebp]
	push	eax
	push	edi
	mov	ecx, esi
	mov	edx, ebx
	call	?CreateBlankBMP@CGdiBmp@@QAEPAUHBITMAP__@@PAUHDC__@@HHK@Z ; CGdiBmp::CreateBlankBMP
; Line 195
	push	ebx
	mov	DWORD PTR _BlankFrameBmp$[ebp], eax
	call	DWORD PTR __imp__CreateCompatibleDC@4
; Line 197
	mov	ecx, DWORD PTR _BlankFrameBmp$[ebp]
	push	ecx
	push	eax
	mov	DWORD PTR _FrameDC$[ebp], eax
	call	DWORD PTR __imp__SelectObject@8
; Line 202
	mov	edx, DWORD PTR _yFrame$[ebp]
	mov	ecx, DWORD PTR _memDC$[ebp]
	push	13369376				; 00cc0020H
	push	esi
	push	edi
	push	edx
	mov	edx, DWORD PTR _FrameDC$[ebp]
	mov	DWORD PTR _OldFrameBmp$[ebp], eax
	mov	eax, DWORD PTR _xFrame$[ebp]
	push	eax
	push	ecx
	push	esi
	push	edi
	push	0
	push	0
	push	edx
	call	DWORD PTR __imp__StretchBlt@44
; Line 205
	mov	eax, DWORD PTR _hOldBitmap$[ebp]
	mov	ecx, DWORD PTR _memDC$[ebp]
	push	eax
	push	ecx
	call	DWORD PTR __imp__SelectObject@8
; Line 207
	mov	edx, DWORD PTR _memDC$[ebp]
	push	edx
	call	DWORD PTR __imp__DeleteDC@4
; Line 209
	mov	eax, DWORD PTR _BlankFrameBmp$[ebp]
	push	eax
	call	DWORD PTR __imp__DeleteObject@4
; Line 212
	mov	ecx, DWORD PTR _hOldBitmap$[ebp]
	push	ecx
	call	DWORD PTR __imp__DeleteObject@4
; Line 216
	push	ebx
	call	DWORD PTR __imp__CreateCompatibleDC@4
; Line 217
	mov	edx, DWORD PTR _crTransColor$[ebp]
	push	edx
	push	edi
	mov	ecx, esi
	mov	edx, ebx
	mov	DWORD PTR _memDC$[ebp], eax
	call	?CreateBlankBMP@CGdiBmp@@QAEPAUHBITMAP__@@PAUHDC__@@HHK@Z ; CGdiBmp::CreateBlankBMP
; Line 219
	push	eax
	mov	DWORD PTR _BlankFrameBmp$[ebp], eax
	mov	eax, DWORD PTR _memDC$[ebp]
	push	eax
	call	DWORD PTR __imp__SelectObject@8
	mov	DWORD PTR _hOldBitmap$[ebp], eax
; Line 221
	mov	eax, DWORD PTR _mirror$[ebp]
	test	eax, eax
	jne	SHORT $LN4@DrawSingle
; Line 223
	push	13369376				; 00cc0020H
	push	esi
	push	edi
	push	eax
$LN7@DrawSingle:
	mov	ecx, DWORD PTR _FrameDC$[ebp]
	mov	edx, DWORD PTR _memDC$[ebp]
	push	0
	push	ecx
	push	esi
	push	edi
	push	0
	push	0
	push	edx
	call	DWORD PTR __imp__StretchBlt@44
; Line 226
	jmp	$LN1@DrawSingle
$LN4@DrawSingle:
	cmp	eax, 1
	jne	SHORT $LN3@DrawSingle
; Line 229
	mov	ecx, DWORD PTR _FrameDC$[ebp]
	mov	edx, DWORD PTR _memDC$[ebp]
	push	13369376				; 00cc0020H
	push	esi
	mov	eax, edi
	neg	eax
	push	eax
	push	0
	push	edi
	push	ecx
	push	esi
	push	edi
	push	0
	push	0
	push	edx
	call	DWORD PTR __imp__StretchBlt@44
; Line 232
	jmp	$LN1@DrawSingle
$LN3@DrawSingle:
	cmp	eax, 2
	jne	SHORT $LN2@DrawSingle
; Line 235
	push	13369376				; 00cc0020H
	mov	eax, esi
	neg	eax
	push	eax
	push	edi
	push	esi
; Line 238
	jmp	SHORT $LN7@DrawSingle
$LN2@DrawSingle:
	cmp	eax, 3
	jne	$LN1@DrawSingle
; Line 241
	mov	eax, DWORD PTR _crTransColor$[ebp]
	push	eax
	push	edi
	mov	ecx, esi
	mov	edx, ebx
	call	?CreateBlankBMP@CGdiBmp@@QAEPAUHBITMAP__@@PAUHDC__@@HHK@Z ; CGdiBmp::CreateBlankBMP
; Line 243
	push	ebx
	mov	DWORD PTR _Blank$66757[ebp], eax
	call	DWORD PTR __imp__CreateCompatibleDC@4
; Line 245
	mov	ecx, DWORD PTR _Blank$66757[ebp]
	push	ecx
	push	eax
	mov	DWORD PTR _dc$66758[ebp], eax
	call	DWORD PTR __imp__SelectObject@8
; Line 247
	mov	ecx, DWORD PTR _dc$66758[ebp]
	push	13369376				; 00cc0020H
	push	esi
	mov	edx, edi
	neg	edx
	push	edx
	push	0
	push	edi
	mov	DWORD PTR _Old$66759[ebp], eax
	mov	eax, DWORD PTR _FrameDC$[ebp]
	push	eax
	push	esi
	push	edi
	push	0
	push	0
	push	ecx
	call	DWORD PTR __imp__StretchBlt@44
; Line 249
	mov	eax, DWORD PTR _dc$66758[ebp]
	mov	ecx, DWORD PTR _memDC$[ebp]
	push	13369376				; 00cc0020H
	mov	edx, esi
	neg	edx
	push	edx
	push	edi
	push	esi
	push	0
	push	eax
	push	esi
	push	edi
	push	0
	push	0
	push	ecx
	call	DWORD PTR __imp__StretchBlt@44
; Line 251
	mov	edx, DWORD PTR _Old$66759[ebp]
	mov	eax, DWORD PTR _dc$66758[ebp]
	push	edx
	push	eax
	call	DWORD PTR __imp__SelectObject@8
; Line 252
	mov	ecx, DWORD PTR _dc$66758[ebp]
	push	ecx
	call	DWORD PTR __imp__DeleteDC@4
$LN1@DrawSingle:
; Line 257
	mov	edx, DWORD PTR _crTransColor$[ebp]
	fild	DWORD PTR _hFrame$[ebp]
	fld	QWORD PTR _ratio$[ebp]
	push	edx
	push	esi
	mov	esi, DWORD PTR _memDC$[ebp]
	fmul	ST(1), ST(0)
	fld	QWORD PTR __real@3fe0000000000000
	push	edi
	push	0
	fadd	ST(2), ST(0)
	push	0
	push	esi
	fxch	ST(2)
	call	__ftol2_sse
	fimul	DWORD PTR _wFrame$[ebp]
	push	eax
	faddp	ST(1), ST(0)
	call	__ftol2_sse
	mov	ecx, DWORD PTR _x$[ebp]
	push	eax
	mov	eax, DWORD PTR _y$[ebp]
	push	eax
	push	ecx
	push	ebx
	call	DWORD PTR __imp__TransparentBlt@44
; Line 260
	mov	edx, DWORD PTR _hOldBitmap$[ebp]
	mov	edi, DWORD PTR __imp__SelectObject@8
	push	edx
	push	esi
	call	edi
; Line 261
	mov	eax, DWORD PTR _OldFrameBmp$[ebp]
	mov	ebx, DWORD PTR _FrameDC$[ebp]
	push	eax
	push	ebx
	call	edi
; Line 263
	push	esi
	mov	esi, DWORD PTR __imp__DeleteDC@4
	call	esi
; Line 264
	push	ebx
	call	esi
; Line 266
	mov	ecx, DWORD PTR _hOldBitmap$[ebp]
	mov	esi, DWORD PTR __imp__DeleteObject@4
	push	ecx
	call	esi
; Line 269
	mov	edx, DWORD PTR _OldFrameBmp$[ebp]
	push	edx
	call	esi
; Line 272
	mov	eax, DWORD PTR _BlankFrameBmp$[ebp]
	push	eax
	call	esi
; Line 274
	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	44					; 0000002cH
?DrawSingleFrame@CGdiBmp@@QAEXPAUHDC__@@HHHHHHNHK@Z ENDP ; CGdiBmp::DrawSingleFrame
PUBLIC	?DrawAnimatedFrames@CGdiBmp@@QAEXPAUHDC__@@HHHHHHNHK@Z ; CGdiBmp::DrawAnimatedFrames
; Function compile flags: /Ogtp
;	COMDAT ?DrawAnimatedFrames@CGdiBmp@@QAEXPAUHDC__@@HHHHHHNHK@Z
_TEXT	SEGMENT
_this$ = 8						; size = 4
_hDC$ = 12						; size = 4
_x$ = 16						; size = 4
_y$ = 20						; size = 4
_FrameCount$ = 24					; size = 4
_mirror$ = 28						; size = 4
_crTransColor$ = 32					; size = 4
_ratio$ = 36						; size = 8
?DrawAnimatedFrames@CGdiBmp@@QAEXPAUHDC__@@HHHHHHNHK@Z PROC ; CGdiBmp::DrawAnimatedFrames, COMDAT
; _RowFrames$ = ebx
; _wFrame$ = edi
; _hFrame$ = esi
; Line 279
	push	ebp
	mov	ebp, esp
	push	ecx
; Line 280
	mov	eax, DWORD PTR _FrameCount$[ebp]
; Line 283
	fld	QWORD PTR _ratio$[ebp]
	cdq
	idiv	ebx
	mov	eax, DWORD PTR _crTransColor$[ebp]
	sub	esp, 8
	fstp	QWORD PTR [esp]
	push	eax
	mov	eax, DWORD PTR _FrameCount$[ebp]
	mov	ecx, edx
	mov	edx, DWORD PTR _mirror$[ebp]
	push	edx
	sub	eax, ecx
	imul	ecx, edi
	cdq
	idiv	ebx
	mov	edx, DWORD PTR _this$[ebp]
	push	esi
	push	edi
	imul	eax, esi
	push	eax
	mov	eax, DWORD PTR _y$[ebp]
	push	ecx
	mov	ecx, DWORD PTR _x$[ebp]
	push	eax
	mov	eax, DWORD PTR _hDC$[ebp]
	push	ecx
	push	edx
	call	?DrawSingleFrame@CGdiBmp@@QAEXPAUHDC__@@HHHHHHNHK@Z ; CGdiBmp::DrawSingleFrame
	pop	ecx
; Line 284
	pop	ebp
	ret	36					; 00000024H
?DrawAnimatedFrames@CGdiBmp@@QAEXPAUHDC__@@HHHHHHNHK@Z ENDP ; CGdiBmp::DrawAnimatedFrames
END
