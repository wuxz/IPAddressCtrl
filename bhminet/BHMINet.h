/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 27 09:58:35 1999
 */
/* Compiler settings for C:\wxz\BHMINet\BHMINet.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __BHMINet_h__
#define __BHMINet_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IBHMSMTP_FWD_DEFINED__
#define __IBHMSMTP_FWD_DEFINED__
typedef interface IBHMSMTP IBHMSMTP;
#endif 	/* __IBHMSMTP_FWD_DEFINED__ */


#ifndef __BHMSMTP_FWD_DEFINED__
#define __BHMSMTP_FWD_DEFINED__

#ifdef __cplusplus
typedef class BHMSMTP BHMSMTP;
#else
typedef struct BHMSMTP BHMSMTP;
#endif /* __cplusplus */

#endif 	/* __BHMSMTP_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IBHMSMTP_INTERFACE_DEFINED__
#define __IBHMSMTP_INTERFACE_DEFINED__

/* interface IBHMSMTP */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBHMSMTP;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F3FE9222-ECD2-11D2-A7FE-0080C8763FA4")
    IBHMSMTP : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnStartPage( 
            /* [in] */ IUnknown __RPC_FAR *piUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnEndPage( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rcpt( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Rcpt( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_From( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_From( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FromName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FromName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Subject( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Subject( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Message( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Message( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContentType( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ContentType( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Server( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Server( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][hidden][propget] */ HRESULT STDMETHODCALLTYPE get_Attach( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][hidden][propput] */ HRESULT STDMETHODCALLTYPE put_Attach( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBHMSMTPVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBHMSMTP __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBHMSMTP __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBHMSMTP __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnStartPage )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *piUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnEndPage )( 
            IBHMSMTP __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Send )( 
            IBHMSMTP __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rcpt )( 
            IBHMSMTP __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rcpt )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_From )( 
            IBHMSMTP __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_From )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FromName )( 
            IBHMSMTP __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FromName )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Subject )( 
            IBHMSMTP __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Subject )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Message )( 
            IBHMSMTP __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Message )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContentType )( 
            IBHMSMTP __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContentType )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Server )( 
            IBHMSMTP __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Server )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][hidden][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attach )( 
            IBHMSMTP __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Attach )( 
            IBHMSMTP __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IBHMSMTPVtbl;

    interface IBHMSMTP
    {
        CONST_VTBL struct IBHMSMTPVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBHMSMTP_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBHMSMTP_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBHMSMTP_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBHMSMTP_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBHMSMTP_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBHMSMTP_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBHMSMTP_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBHMSMTP_OnStartPage(This,piUnk)	\
    (This)->lpVtbl -> OnStartPage(This,piUnk)

#define IBHMSMTP_OnEndPage(This)	\
    (This)->lpVtbl -> OnEndPage(This)

#define IBHMSMTP_Send(This)	\
    (This)->lpVtbl -> Send(This)

#define IBHMSMTP_get_Rcpt(This,pVal)	\
    (This)->lpVtbl -> get_Rcpt(This,pVal)

#define IBHMSMTP_put_Rcpt(This,newVal)	\
    (This)->lpVtbl -> put_Rcpt(This,newVal)

#define IBHMSMTP_get_From(This,pVal)	\
    (This)->lpVtbl -> get_From(This,pVal)

#define IBHMSMTP_put_From(This,newVal)	\
    (This)->lpVtbl -> put_From(This,newVal)

#define IBHMSMTP_get_FromName(This,pVal)	\
    (This)->lpVtbl -> get_FromName(This,pVal)

#define IBHMSMTP_put_FromName(This,newVal)	\
    (This)->lpVtbl -> put_FromName(This,newVal)

#define IBHMSMTP_get_Subject(This,pVal)	\
    (This)->lpVtbl -> get_Subject(This,pVal)

#define IBHMSMTP_put_Subject(This,newVal)	\
    (This)->lpVtbl -> put_Subject(This,newVal)

#define IBHMSMTP_get_Message(This,pVal)	\
    (This)->lpVtbl -> get_Message(This,pVal)

#define IBHMSMTP_put_Message(This,newVal)	\
    (This)->lpVtbl -> put_Message(This,newVal)

#define IBHMSMTP_get_ContentType(This,pVal)	\
    (This)->lpVtbl -> get_ContentType(This,pVal)

#define IBHMSMTP_put_ContentType(This,newVal)	\
    (This)->lpVtbl -> put_ContentType(This,newVal)

#define IBHMSMTP_get_Server(This,pVal)	\
    (This)->lpVtbl -> get_Server(This,pVal)

#define IBHMSMTP_put_Server(This,newVal)	\
    (This)->lpVtbl -> put_Server(This,newVal)

#define IBHMSMTP_get_Attach(This,pVal)	\
    (This)->lpVtbl -> get_Attach(This,pVal)

#define IBHMSMTP_put_Attach(This,newVal)	\
    (This)->lpVtbl -> put_Attach(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBHMSMTP_OnStartPage_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *piUnk);


void __RPC_STUB IBHMSMTP_OnStartPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBHMSMTP_OnEndPage_Proxy( 
    IBHMSMTP __RPC_FAR * This);


void __RPC_STUB IBHMSMTP_OnEndPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_Send_Proxy( 
    IBHMSMTP __RPC_FAR * This);


void __RPC_STUB IBHMSMTP_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_get_Rcpt_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBHMSMTP_get_Rcpt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_put_Rcpt_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBHMSMTP_put_Rcpt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_get_From_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBHMSMTP_get_From_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_put_From_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBHMSMTP_put_From_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_get_FromName_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBHMSMTP_get_FromName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_put_FromName_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBHMSMTP_put_FromName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_get_Subject_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBHMSMTP_get_Subject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_put_Subject_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBHMSMTP_put_Subject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_get_Message_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBHMSMTP_get_Message_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_put_Message_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBHMSMTP_put_Message_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_get_ContentType_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBHMSMTP_get_ContentType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_put_ContentType_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBHMSMTP_put_ContentType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_get_Server_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBHMSMTP_get_Server_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_put_Server_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBHMSMTP_put_Server_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][hidden][propget] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_get_Attach_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IBHMSMTP_get_Attach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][hidden][propput] */ HRESULT STDMETHODCALLTYPE IBHMSMTP_put_Attach_Proxy( 
    IBHMSMTP __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBHMSMTP_put_Attach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBHMSMTP_INTERFACE_DEFINED__ */



#ifndef __BHMINETLib_LIBRARY_DEFINED__
#define __BHMINETLib_LIBRARY_DEFINED__

/* library BHMINETLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BHMINETLib;

EXTERN_C const CLSID CLSID_BHMSMTP;

#ifdef __cplusplus

class DECLSPEC_UUID("F3FE9223-ECD2-11D2-A7FE-0080C8763FA4")
BHMSMTP;
#endif
#endif /* __BHMINETLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
