@echo off
:: ===========================================================================
:: Batch script for linting with PC-Lint-Plus
:: Copyright (C) 2005 Quantum Leaps, LLC. All rights reserved.
::
:: SPDX-License-Identifier: GPL-3.0-or-later
::
:: Contact information:
:: <www.state-machine.com>
:: <info@state-machine.com>
:: ===========================================================================
@setlocal

:: usage of lin.bat
@echo Usage: lin [options...]

:: NOTE: adjust to for your installation directory of PC-Lint-Plus
@set PCLP=C:\tools\lint-plus\windows\pclp64.exe

if NOT exist "%PCLP%" (
    @echo The PC-Lint-Plus toolset not found. Please adjust lin.bat
    @goto end
)

:: linting -------------------------------------------------------------------
%PCLP% -os(lint-16bit.log) std.lnt -i16bit options.lnt %1 %2 %3  ..\main.c
%PCLP% -os(lint-32bit.log) std.lnt -i32bit options.lnt %1 %2 %3  ..\main.c

:end
@endlocal
