/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 27 09:58:35 1999
 */
/* Compiler settings for C:\wxz\BHMINet\BHMINet.idl:
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

const IID IID_IBHMSMTP = {0xF3FE9222,0xECD2,0x11D2,{0xA7,0xFE,0x00,0x80,0xC8,0x76,0x3F,0xA4}};


const IID LIBID_BHMINETLib = {0xF3FE9216,0xECD2,0x11D2,{0xA7,0xFE,0x00,0x80,0xC8,0x76,0x3F,0xA4}};


const CLSID CLSID_BHMSMTP = {0xF3FE9223,0xECD2,0x11D2,{0xA7,0xFE,0x00,0x80,0xC8,0x76,0x3F,0xA4}};


#ifdef __cplusplus
}
#endif

