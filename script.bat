:: Script DLL pour GTK+
:: Bubi Gaudrioles
title DLL EXPORT
@echo off
color 6F

set REPERTOIRE_SRC=C:\msys64\mingw64
set REPERTOIRE_DEST=D:\CodeBlocksProjets\novetat\bin\Release
@echo off

mkdir %REPERTOIRE_DEST%\lib
mkdir %REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0
mkdir %REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0
mkdir %REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders

xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders.cache						%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-ani.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-bmp.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-gif.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-icns.dll	%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-ico.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-jasper.dll	%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-jpeg.dll	%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-png.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-pnm.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-qtif.dll	%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-svg.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-tga.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-tiff.dll	%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-xbm.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders
xcopy /Y %REPERTOIRE_SRC%\lib\gdk-pixbuf-2.0\2.10.0\loaders\libpixbufloader-xpm.dll		%REPERTOIRE_DEST%\lib\gdk-pixbuf-2.0\2.10.0\loaders

@echo off
color AF
@echo off

mkdir %REPERTOIRE_DEST%\share
mkdir %REPERTOIRE_DEST%\share\icons
mkdir %REPERTOIRE_DEST%\share\icons\Adwaita
xcopy /Y /S %REPERTOIRE_SRC%\share\icons\Adwaita %REPERTOIRE_DEST%\share\icons\Adwaita

@echo off
color 5F
@echo off

xcopy /Y %REPERTOIRE_SRC%\bin\LIBATK-1.0-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBBZ2-1.DLL				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBCAIRO-2.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBCAIRO-GOBJECT-2.DLL	%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBCRYPTO-1_1-X64.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBDATRIE-1.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBEPOXY-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBEXPAT-1.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBFFI-7.DLL				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBFONTCONFIG-1.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBFREETYPE-6.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBFRIBIDI-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBGCC_S_SEH-1.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBGDK_PIXBUF-2.0-0.DLL	%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBGDK-3-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBGIO-2.0-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBGLIB-2.0-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBGMODULE-2.0-0.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBGOBJECT-2.0-0.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBGRAPHITE2.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBGTK-3-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBHARFBUZZ-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBICONV-2.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBINTL-8.DLL				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBPANGO-1.0-0.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBPANGOCAIRO-1.0-0.DLL	%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBPANGOFT2-1.0-0.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBPANGOWIN32-1.0-0.DLL	%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBPCRE-1.DLL				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBPIXMAN-1-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBPNG16-16.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBSQLITE3-0.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBSTDC++-6.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBTHAI-0.DLL				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBWINPTHREAD-1.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\ZLIB1.DLL					%REPERTOIRE_DEST%\

xcopy /Y %REPERTOIRE_SRC%\bin\LIBCURL-4.DLL				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBBROTLIDEC.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBIDN2-0.DLL				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBNGHTTP2-14.DLL			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBPSL-5.DLL				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBSSH2-1.DLL				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBSSL-1_1-X64.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBBROTLICOMMON.DLL		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\LIBUNISTRING-2.DLL		%REPERTOIRE_DEST%\


@echo off
color 0F
@echo off

echo Terminee !!
pause