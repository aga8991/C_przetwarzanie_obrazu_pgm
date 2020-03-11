Attribute VB_Name = "Module1"
'PGM Image Viewer for Visual Basic 6.0
'
'Copyright 2003 by Dmitry Brant, All Rights Reserved.

'Version 1.1, Last modified 04-27-2000
'
'me@dmitrybrant.com
'
'http://www.dmitrybrant.com


'This program fully supports the PGM format.

'Feel free to make improvements or optimizations to the program.
'If you do, please tell me or show me what you have done.

'This program is FREEWARE. Use freely, but give me credit
'where credit is due. (this program is NOT in the
'public domain). If you will use this source code in
'your software, the copyright notice stated above
'must be included in your source code and/or in the
'Help/About box of your program.

'The SOURCE CODE of this program, or portions of it, may not
'be redistributed, either by itself or in a compilation
'package, without express authorization from the author.

'ALL PRODUCT NAMES MENTIONED IN THIS SOFTWARE ARE TRADEMARKS
'OR REGISTERED TRADEMARKS OF THEIR RESPECTIVE OWNERS.

'THIS SOFTWARE IS DISTRIBUTED "AS IS". THE SOFTWARE IS
'DISTRIBUTED WITH NO WARRANTY, EIHER EXPRESSED
'OR IMPLIED, INCLUDING, BY WAY OF EXAMPLE THE IMPLIED
'WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
'PURPOSE. THE AUTHOR WILL NOT BE LIABLE FOR DATA LOSS, DAMAGES,
'LOSS OF PROFITS OR ANY OTHER KIND OF LOSS RESULTING FROM THE
'USE OR MISUSE OF THIS SOFTWARE.

Option Explicit
DefInt A-Z

Declare Function SetPixel Lib "gdi32" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal crColor As Long) As Long

Public Sub DoPGM(FName As String, FObject As Object)
    Dim FWidth As Integer, FHeight As Integer, theHdc As Long
    Dim FColors As Integer, dx As Integer, dy As Integer
    Dim str1 As String, FType As String
    Dim g As Integer
    
    On Error GoTo ErrorTrap0
    
    Open FName For Binary As #1
    
    dx = 0: dy = 0
    theHdc = FObject.hdc
    
    FType = GetNextObj
    If FType <> "P2" And FType <> "P5" Then
        Close #1
        MsgBox "This is not a valid PGM File.", , "Error"
        Exit Sub
    End If
    
    Do
        str1 = GetNextObj
        If Left(str1, 1) <> "#" Then Exit Do
    Loop
    
    FWidth = Val(str1)
    FHeight = Val(GetNextObj)
    FColors = Val(GetNextObj)
    
    If FType = "P2" Then
        For dy = 0 To FHeight - 1
            For dx = 0 To FWidth - 1
                g = Val(GetNextObj)
                SetPixel theHdc, dx, dy, RGB(g, g, g)
            Next dx
            If dy Mod 16 = 0 Then FObject.Refresh: DoEvents
        Next dy
    Else
        ReDim Scanline(0 To FWidth - 1) As Byte
        For dy = 0 To FHeight - 1
            Get #1, , Scanline
            For dx = 0 To FWidth - 1
                g = Scanline(dx)
                SetPixel theHdc, dx, dy, RGB(g, g, g)
            Next dx
            If dy Mod 32 = 0 Then FObject.Refresh: DoEvents
        Next dy
        Erase Scanline
    End If
    Close #1
    Exit Sub

ErrorTrap0:
    Close #1
    MsgBox "There was an error reading the file:" + vbCrLf + Error$, vbCritical, "Error"
End Sub

Private Function GetNextObj() As String
    Dim a As Byte, Res As String
    
    'eliminate whitespace
    Do
        Get #1, , a
    Loop Until a > 32 Or EOF(1)
    
    
    If a = 35 Then     'it's a comment
        Do Until a = 13 Or a = 10
            Res = Res + Chr(a)
            Get #1, , a
        Loop
        GetNextObj = Res
        Exit Function
    End If

    Do Until a <= 32
        Res = Res + Chr(a)
        Get #1, , a
    Loop
    GetNextObj = Res
End Function
