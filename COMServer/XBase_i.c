/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Sep 11 14:29:54 2022
 */
/* Compiler settings for C:\DOCUMENTS AND SETTINGS\NATHANPC\MY DOCUMENTS\DEVELOPMENT\WinBase\COMServer\XBase.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IConnection = {0xFE5E78F1,0x88CE,0x4E02,{0x89,0xED,0xE1,0x39,0x39,0xB7,0xCB,0x42}};


const IID LIBID_XBASELib = {0x8BA6F373,0xFBDD,0x470E,{0xA2,0x25,0x5D,0x66,0x33,0xD4,0x70,0xCB}};


const CLSID CLSID_Connection = {0x5489A3D0,0xA55E,0x4DC3,{0xAE,0x51,0x87,0xF5,0xA1,0x05,0x28,0xE7}};


#ifdef __cplusplus
}
#endif

