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

xcopy /Y %REPERTOIRE_SRC%\bin\libatk-1.0-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libbrotlicommon.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libbrotlidec.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libbz2-1.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libcairo-2.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libcairo-gobject-2.dll	%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libcrypto-1_1-x64.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libcurl-4.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libdatrie-1.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libepoxy-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libexpat-1.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libffi-7.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libfontconfig-1.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libfreetype-6.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libfribidi-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libgcc_s_seh-1.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libgdk-3-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libgdk_pixbuf-2.0-0.dll	%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libgio-2.0-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libglib-2.0-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libgmodule-2.0-0.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libgobject-2.0-0.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libgraphite2.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libgtk-3-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libharfbuzz-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libiconv-2.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libidn2-0.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libintl-8.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libnghttp2-14.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libpango-1.0-0.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libpangocairo-1.0-0.dll	%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libpangoft2-1.0-0.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libpangowin32-1.0-0.dll	%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libpcre-1.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libpixman-1-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libpng16-16.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libpsl-5.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libsqlite3-0.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libssh2-1.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libssl-1_1-x64.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libssp-0.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libstdc++-6.dll			%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libthai-0.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libunistring-2.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libwinpthread-1.dll		%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\libzstd.dll				%REPERTOIRE_DEST%\
xcopy /Y %REPERTOIRE_SRC%\bin\zlib1.dll					%REPERTOIRE_DEST%\

@echo off
color 0F
@echo off

echo Terminee !!
pause