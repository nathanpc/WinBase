/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Sep 11 16:56:36 2022
 */
/* Compiler settings for XBase.idl:
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

const IID IID_IConnection = {0xD7CA4B59,0x6D55,0x4AFC,{0x94,0x38,0xC9,0xB0,0x60,0xC4,0x32,0xD0}};


const IID LIBID_XBASELib = {0xF0A91656,0x0B38,0x42B4,{0x92,0xC5,0x42,0x87,0x2C,0x95,0xB7,0x6C}};


const CLSID CLSID_Connection = {0x5489A3D0,0xA55E,0x4DC3,{0xAE,0x51,0x87,0xF5,0xA1,0x05,0x28,0xE7}};


#ifdef __cplusplus
}
#endif

