
BHMINetps.dll: dlldata.obj BHMINet_p.obj BHMINet_i.obj
	link /dll /out:BHMINetps.dll /def:BHMINetps.def /entry:DllMain dlldata.obj BHMINet_p.obj BHMINet_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del BHMINetps.dll
	@del BHMINetps.lib
	@del BHMINetps.exp
	@del dlldata.obj
	@del BHMINet_p.obj
	@del BHMINet_i.obj
