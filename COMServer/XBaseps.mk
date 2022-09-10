
XBaseps.dll: dlldata.obj XBase_p.obj XBase_i.obj
	link /dll /out:XBaseps.dll /def:XBaseps.def /entry:DllMain dlldata.obj XBase_p.obj XBase_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del XBaseps.dll
	@del XBaseps.lib
	@del XBaseps.exp
	@del dlldata.obj
	@del XBase_p.obj
	@del XBase_i.obj
