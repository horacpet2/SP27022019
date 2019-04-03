@echo off

set oldcp=%classpath%
set classpath=postest2.jar
set classpath=%classpath%;jpos-1.13.0.jar
set classpath=%classpath%;xerces.jar
set classpath=%classpath%;%cd%\

set JRE_Version=7

for /d %%i in ("%ProgramFiles%\Java\jre%jre_Version%*") do (set Located=%%i)
rem check if JDK was located
if "%Located%"=="" goto SetJavaFXFromJavaHome


:SetJavaFXFromLocatedFolder
set classpath=%classpath%;"%Located%\lib\jfxrt.jar"
goto endif


:SetJavaFXFromJavaHome
if "%JAVA_HOME%"=="" goto NoExistingJavaHome
set classpath=%classpath%;"%JAVA_HOME%\jre\lib\jfxrt.jar"
goto endif


:NoExistingJavaHome
rem display message to the user that %JAVA_HOME% is not available
echo     No Existing value of JAVA_HOME is available!
goto exit

:endif
rem clear the variables used by this script
set JDK_Version=
set Located=


set lp=%SystemRoot%\system32


REM ***************************************
REM *  Add Device Specific jar's here...  *
REM ***************************************

REM add Classes to classpath
REM set lp=%lp%;c:\path_to_native_methods

java -cp %classpath% -Djava.library.path=%lp% postest2.POSTest2

set classpath=%oldcp%

:exit
